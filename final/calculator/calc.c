#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compilation: gcc -o calc -fno-stack-protector -z execstack calc.c

char *getname() {
    char *name = malloc(32);
    if(name == NULL) {
        printf("Error: malloc() returned NULL!\n");
        exit(1);
    }

    printf("Enter your name: ");
    fgets(name, 32, stdin);
    name[strlen(name) - 1] = '\0';
    printf("Hello ");
    printf(name);
    printf("!\nWelcome to the calculator application!\n\n");

    free(name);
}

int options() {
    char buf[32];
    int option = 0;

    printf("Options: \n");
    printf("1.) Addition\n");
    printf("2.) Subtraction\n");
    printf("3.) Multiplication\n");
    printf("4.) Quit\n");
    printf("Enter option: ");

    fgets(buf, 32, stdin);
    sscanf(buf, "%d", &option);
    return option;
}

void add() {
    char buf[256];
    int x, y;

    printf("Enter first number: ");
    fgets(buf, 256, stdin);
    sscanf(buf, "%d", &x);

    printf("Enter second number: ");
    fgets(buf, 256, stdin);
    sscanf(buf, "%d", &y);

    printf("Answer: %d\n", x+y);
}

void sub() {
    char buf[128];
    int x, y;

    printf("Enter first number: ");
    fgets(buf, 256, stdin);
    sscanf(buf, "%d", &x);

    printf("Enter second number: ");
    fgets(buf, 256, stdin);
    sscanf(buf, "%d", &y);

    printf("Answer: %d\n", x-y);
}

void mult() {
    char buf[256];
    int x, y;

    printf("Enter first number: ");
    fgets(buf, 256, stdin);
    sscanf(buf, "%d", &x);

    printf("Enter second number: ");
    fgets(buf, 256, stdin);
    sscanf(buf, "%d", &y);

    printf("Answer: %d\n", x*y);
}

void calc() {
    int option = 0;

    while(option != 4) {
        option = options();
        switch(option) {
            case 1:
                add();
                break;
            case 2:
                sub();
                break;
            case 3:
                mult();
                break;
            case 4:
                printf("Closing calculator application.\n");
                break;
            default:
                printf("Invalid option.\n");
                break;
        }
    }
}

int main(int argc, char **argv) {
    getname();
    calc();
    return 0;
}
