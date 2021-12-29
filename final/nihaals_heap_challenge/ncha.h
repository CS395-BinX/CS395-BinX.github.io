#ifndef NCHA_H
#define NCHA_H

#include <stdio.h>

// Header for each chunk of allocated memory
typedef union ncha_header {
    struct { // Actual header data that we care about
        union ncha_header *next; // Next value in linked list.
        union ncha_header *prev; // Previous value in list.
        size_t size; // Amount of memory allocated for user.
        char free; // Set to 1 if memory isn't being used.
    } data;
    char align[32]; // Only used to align header to 32 bytes
} ncha_header_t;

// Defines error codes
typedef enum {
    NCHA_SUCCESS = 0,
    NCHA_FAIL,
    NCHA_INVALID_SIZE,
    NCHA_INVALID_BLOCK,
    NCHA_SBRK_FAIL
} ncha_err_t;

// Functions
void *ncha_alloc(size_t size); // Allocates memory on the heap
ncha_header_t *first_fit(size_t size); // Finds a free block (if available)
void ncha_free(void *block); // Frees memory on the heap
void ncha_defrag(); // Defrags the heap
void ncha_err(ncha_err_t err, const char *func); // Prints errors
void ncha_print(); // Prints out every chunk on the heap

#endif
