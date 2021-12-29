#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ncha.h"

#define BUF_SIZE 128

// Compilation: gcc -Wall -g -fno-stack-protector -z execstack -o ncna ncna.c ncha.c ncha.h

// Stores data about a single note
typedef struct note {
    char note[BUF_SIZE];
    struct note *next;
    struct note *prev;
    unsigned long id;
} note_t;

// Prints out a single note
void print_note(note_t *n) {
    printf("Note #%ld\n", n->id);
    printf(n->note);
}

// Generates an ID that has not been taken
unsigned long generate_id(note_t *head) {
    note_t *tmp = NULL;
    unsigned long id = 0;
    id = rand();

    // Loop through the linked list to make sure the ID isn't used
    for(tmp = head; tmp != NULL; tmp = tmp->next) {
        // If it has been used, recursively generate a new ID
        if(id == tmp->id) {
            id = generate_id(head);
            break;
        }
    }

    return id;
}

// Creates a new note
void new_note(note_t **head) {
    note_t *new = NULL;

    // Allocate memory
    new = ncha_alloc(sizeof(note_t));
    if(new == NULL) {
        printf("ncha_alloc() failed.");
        exit(1);
    }

    // Insert the note into the linked list
    new->next = *head;
    if(*head != NULL) {
        (*head)->prev = new;
    }
    *head = new;
    new->id = generate_id(*head);

    // User inputs the note
    printf("Enter the note (%d max characters): ", BUF_SIZE);
    fgets(new->note, BUF_SIZE, stdin);
    
    // Print out a message
    printf("Note created with ID #%lu.\n", new->id);
}

// Prints out a note with the given ID
void print_id(unsigned long id, note_t *head) {
    note_t *tmp = head;
    while(tmp != NULL && tmp->id != id) {
        tmp = tmp->next;
    }

    if(tmp != NULL) {
        print_note(tmp);
    } else {
        printf("Invalid ID.\n");
    }
}

// Modifies a note with the given ID
void modify_id(unsigned long id, note_t *head) {
    note_t *tmp = head;
    while(tmp != NULL && tmp->id != id) {
        tmp = tmp->next;
    }
    if(tmp != NULL) {
        printf("Enter the modified note (%d max characters): ", BUF_SIZE);
        fgets(tmp->note, 1000, stdin);
    } else {
        printf("Invalid ID.\n");
    }
}

// Deletes a note with the given ID
void del_id(unsigned long id, note_t **head) {
    note_t *tmp = *head;
    while(tmp != NULL) {
        if(tmp->id == id) {
            if(tmp->prev != NULL) {
                tmp->prev->next = tmp->next;
            }
            if(tmp->next != NULL) {
                tmp->next->prev = tmp->prev;
            }
            ncha_free(tmp);
            break;
        }
        tmp = tmp->next;
    }
}

// Deletes EVERYTHING!!!
void del_all(note_t *head) {
    note_t *tmp = NULL;
    while(head != NULL) {
        tmp = head;
        head = head->next;
        ncha_free(tmp);
    }
}

// Prints out the available commands
void print_cmds() {
    printf("Available commands:\n");
    printf("new: Create a new note.\n");
    printf("print <id>: Prints out the note with the given ID.\n");
    printf("del <id>: Deletes the note with the given ID.\n");
    printf("modify <id>: Modifies the note with the given ID.\n");
    printf("heap: Prints out the chunks on the heap.\n");
    printf("quit: Stop the program.\n");
}

// Prints an introduction to the program
void print_intro() {
    printf("Welcome to Nihaal\'s Crappy Note Application (NCNA)!\n\n");
    printf("Nihaal\'s Crappy Note Application is an application\n");
    printf("designed to store your most important notes! It is a\n");
    printf("must have for anybody who needs to save their most\n");
    printf("important thoughts on a reliable program. This program\n");
    printf("was made with security in mind, so no hackers will ever\n");
    printf("be able to hack your notes!\n\n");
    printf("Note: This program uses Nihaal\'s Crappy Heap Allocator\n");
    printf("(NCHA), the world\'s greatest memory allocator, to\n");
    printf("allocate memory for your notes in the background. Please\n");
    printf("be careful when storing data, as you might accidentally\n");
    printf("overwrite the metadata for the next chunk on the heap.\n\n");
    printf("(Your exploit must work with ASLR enabled to obtain full\n");
    printf("credit for your writeup.)\n\n");
}

// Allows the user to type in commands
void command_line() {
    unsigned long id = 0;
    char stop = 0;
    char buf[BUF_SIZE] = {0};
    note_t *head = NULL;

    while(!stop) {
        printf("> ");
        fgets(buf, BUF_SIZE, stdin);
        if(strncmp(buf, "new", 3) == 0) {
            new_note(&head);
        } else if(strncmp(buf, "print ", 6) == 0) {
            sscanf(buf+6, "%lu", &id);
            print_id(id, head);
        } else if(strncmp(buf, "del ", 4) == 0) {
            sscanf(buf+4, "%lu", &id);
            del_id(id, &head);
        } else if(strncmp(buf, "modify ", 7) == 0) {
            sscanf(buf+7, "%lu", &id);
            modify_id(id, head);
        } else if(strncmp(buf, "heap", 4) == 0){
            ncha_print();
        } else if(strncmp(buf, "quit", 4) == 0 || strncmp(buf, "q\n", 2) == 0) {
            stop = 1;
        } else {
            printf("Invalid command.\n");
        }
    }

    printf("Ending program.\n");
    del_all(head);
    head = NULL;
}

// Main function
int main(int argc, char **argv) {
    char name[BUF_SIZE] = {0};
    srand((unsigned) time(0));

    printf("Enter your name: ");
    fgets(name, BUF_SIZE, stdin);
    name[strlen(name)-1] = '\0';
    printf("Hello there %s!\n\n", name);

    print_intro();
    print_cmds();
    command_line();

    return 0;
}
