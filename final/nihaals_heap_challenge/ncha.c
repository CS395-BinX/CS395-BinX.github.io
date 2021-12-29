#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "ncha.h"

/*
 * How Nihaal's Crappy Heap Allocator works:
 *
 * The heap is a part of memory that grows upwards,
 * towards the stack. The heap can be increased or
 * decreased depending on the situation. The pointer
 * to the highest memory address on the heap is
 * called the "program break," and it can be changed
 * by calling sbrk(). The static void *heap_end
 * variable that you see below should be equal to 
 * the program break.
 *
 * This program will maintain a linked list of free
 * chunks. Suppose a user calls ncha_alloc(n), where
 * n is any positive integer. If there is a free
 * chunk that can contain at least n bytes, then
 * that free chunk will be marked as not free, 
 * removed from the linked list, and returned to the
 * user. The first fit algorithm is used to search
 * for free chunks. If there are no free chunks
 * available for the user that have at least n bytes,
 * then the program will increase the value of the
 * program break by n and return the beginning of the
 * newly created memory.
 *
 * Whenever a user calls ncha_free(block), where block
 * is a pointer to a chunk of memory that was returned
 * by ncha_alloc(), that chunk of memory will be marked
 * as free. Then, the entire heap will be defragmented,
 * and the linked list will be reconstructed. If two
 * free blocks are sitting next to each other, they will
 * be combined to form one giant free block. If a free
 * block is sitting at the end of the heap, the program
 * break will be reduced, which will delete the block.
 *
 * Every chunk of memory has a header that the user
 * does not directly see (unless they do something crazy
 * like subtract the pointer that was returned). The header
 * is very important, and it contains information such as
 * the size of each chunk and whether the chunk is free or
 * not. If the chunk is part of the linked list of free
 * chunks, then the next and prev pointers will also be
 * set accordingly.
 */

// Start and end of the heap
static void *heap_start = NULL;
static void *heap_end = NULL;

// Head for the linked list of free chunks
static ncha_header_t *head = NULL;

// Mutex lock for modifying heap
static pthread_mutex_t *ncha_lock = NULL;

// Allocates memory on the heap
void *ncha_alloc(size_t size) {
    ncha_err_t err = NCHA_FAIL;
    ncha_header_t *ret = NULL;

    // Make sure some idiot didn't try to allocate zero bytes of memory.
    if(size == 0) {
        err = NCHA_INVALID_SIZE;
        goto end;
    }

    // If the heap has not been initialized, then initialize it
    if(heap_start == NULL && heap_end == NULL) {
        heap_start = sbrk(0);
        heap_end = heap_start;
        pthread_mutex_init(ncha_lock, NULL);
    }

    // Acquire the lock
    pthread_mutex_lock(ncha_lock);

    // Check if a suitable chunk already exists in the linked list.
    ret = first_fit(size);
    if(ret) {
        // If we found a suitable free chunk in the linked list, then remove
        // that chunk from the linked list of free chunks.
        if(ret->data.prev) {
            ret->data.prev->data.next = ret->data.next;
        }
        if(ret->data.next) {
            ret->data.next->data.prev = ret->data.prev;
        }
        if(ret == head) {
            head = ret->data.next;
            if(head) {
                head->data.prev = NULL;
            }
        }
    } else {
        // If there are no free chunks in the linked list with a big enough
        // size for the requested data, then increase the size of the heap.
        ret = sbrk(size + sizeof(ncha_header_t));
        if(ret == (void *) -1) {
            err = NCHA_SBRK_FAIL;
            goto end;
        }
        ret->data.size = size;
        heap_end += size + sizeof(ncha_header_t);
    }

    // Mark the chunk as not free and return
    ret->data.free = 0;
    ret = (void *)ret + sizeof(ncha_header_t);
    err = NCHA_SUCCESS;

end:
    pthread_mutex_unlock(ncha_lock);
    ncha_err(err, "ncha_alloc()");
    return ret;
}

// Loops through the linked list and finds a chunk that has a size big enough to store
// the user's data. Uses the first fit algorithm. May return NULL if there is no free
// chunk in the linked list, in which case the size of the heap must be increased.
// Assumes that the mutex lock has already been acquired.
ncha_header_t *first_fit(size_t size) {
    ncha_header_t *ret = NULL;
    ncha_header_t *curr = head;
    while(curr) {
        // Check if this current chunk meets the size requirements.
        if(curr->data.size >= size) {
            // If the chunk works, return it
            ret = curr;
            break;
        }

        // Go to the next chunk in the linked list
        curr = curr->data.next;
    }

    return ret;
}

// Frees the given block of memory.
void ncha_free(void *block) {
    if(block == NULL) {
        ncha_err(NCHA_INVALID_BLOCK, "ncha_free()");
    } else {
        // Mark the chunk of memory as free
        ncha_header_t *to_free = (ncha_header_t *) (block - sizeof(ncha_header_t));
        to_free->data.free = 1;

        // Defrag the heap (will automatically modify linked list)
        ncha_defrag();
    }
}

// Defragmentation does the following:
// 1.) Combines free blocks sitting next to each other.
// 2.) Reduces the size of the heap if there are free block(s) at the end.
// 3.) Reconstructs the entire linked list of free blocks.
void ncha_defrag() {
    ncha_err_t err = NCHA_FAIL;
    ncha_header_t *chunk = NULL, *last_free_chunk = NULL;
    void *curr = NULL;
    int size = 0;

    // Acquire the lock
    pthread_mutex_lock(ncha_lock);

    // Delete the linked list
    head = NULL;

    // Loop through every chunk
    curr = heap_start;
    while(curr < heap_end) {
        chunk = (ncha_header_t *) curr;
        if(chunk->data.free) { // Check if this is a free chunk
            if(!head) { // If there is no linked list, then make this the head
                head = chunk;
                head->data.next = NULL;
                head->data.prev = NULL;
                last_free_chunk = chunk; // Save the last free chunk
            } else { // Else, add the chunk to the linked list
                // Check if the current chunk is adjacent to the last free
                // chunk that we stored.
                if((void *)last_free_chunk + last_free_chunk->data.size
                        + sizeof(ncha_header_t) == curr) {
                    // Instead of adding this chunk to the linked list, just
                    // increase the size of the last free chunk.
                    last_free_chunk->data.size += sizeof(ncha_header_t) + chunk->data.size;
                } else {
                    // If chunks aren't adjacent, then just add the current
                    // chunk to the linked list.
                    chunk->data.prev = last_free_chunk;
                    if(last_free_chunk) {
                        last_free_chunk->data.next = chunk;
                    }
                    chunk->data.next = NULL;
                    last_free_chunk = chunk; // Save the last free chunk
                }
            }
        }
        curr += chunk->data.size + sizeof(ncha_header_t);
    }

    // Check if the last free chunk is at the end of the heap
    size = sizeof(ncha_header_t) + last_free_chunk->data.size;
    if((void *)last_free_chunk + size == heap_end) {
        // If so, reduce the size of the heap with sbrk() and check for errors
        if(sbrk(-1 * size) == (void *) -1) {
            err = NCHA_SBRK_FAIL;
            goto end;
        }

        // If the head of the linked list was the last freed chunk,
        // then we should set it to the previous chunk.
        if((void *)head + size == heap_end &&
                head != heap_start && head) {

            head = head->data.prev; // Set head to the previous value
            if(head) { // Delete the next value in the linked list
                head->data.next = NULL;
            }
        }

        // Reduce the size of the heap
        heap_end -= size;
    }

    err = NCHA_SUCCESS;

end:
    pthread_mutex_unlock(ncha_lock);
    ncha_err(err, "ncha_defrag()");
}

// Prints out error messages
void ncha_err(ncha_err_t err, const char *func) {
    switch(err) {
        case NCHA_SUCCESS:
            break; // Do nothing
        case NCHA_FAIL:
            printf("%s: failed.\n", func);
            break;
        case NCHA_INVALID_SIZE:
            printf("%s: invalid size.\n", func);
            break;
        case NCHA_INVALID_BLOCK:
            printf("%s: invalid block.\n", func);
            break;
        case NCHA_SBRK_FAIL:
            printf("%s: srbk() failed.\n", func);
            break;
    }
}

// Prints out every single chunk on the heap.
void ncha_print() {
    int i = 0, count = 0;
    void *curr = heap_start;
    ncha_header_t *chunk = heap_start;

    pthread_mutex_lock(ncha_lock);
    printf("=== Printing Heap ===\n");
    printf("Heap Start: %p\n", heap_start);
    printf("Heap End:   %p\n", heap_end);
    while(curr < heap_end) {
        chunk = (ncha_header_t *) curr;
        printf("\nChunk #%d:\n", count);
        printf("Location: %p\n", chunk);
        printf("Size: %lu\n", chunk->data.size);
        if(chunk->data.free) {
            printf("Free chunk.\n");
            printf("Next free chunk: %p\n", chunk->data.next);
            printf("Previous free chunk: %p\n", chunk->data.prev);
        } else {
            printf("Data: ");
            for(i = 0; i < chunk->data.size; i++) {
                printf("%x", *((char *) chunk+sizeof(ncha_header_t)+i));
            }
            printf("\n");
        }
        count++;
        curr += sizeof(ncha_header_t) + chunk->data.size;
    }
    printf("=== End Of Heap ===\n");
    pthread_mutex_unlock(ncha_lock);
}
