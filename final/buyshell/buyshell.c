#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

void print_market_menu() {
    printf("Here are the things that you can buy: \n");
    printf("Water: $1\n");
    printf("Soda: $2\n");
    printf("Hamburger: $3\n");
    printf("Pizza: $4\n");
    printf("Shell: $%u\n", UINT_MAX);
    printf("Enter the thing you want to buy (case sensitive): ");
}

void print_sleep() {
    printf("Sleeping...\n");
    sleep(10);
    printf("Sleeping...\n");
    sleep(10);
    printf("Sleeping...\n");
    sleep(10);
}

void print_work() {
    printf("Working...\n");
    sleep(1);
    printf("Working...\n");
    sleep(1);
    printf("Working...\n");
    sleep(1);
    printf("You went to work for an entire day.\n");
}

void market(unsigned int *money) {
    char buf[256];

    print_market_menu();
    fgets(buf, 256, stdin);
    
    if(strncmp("Water\n", buf, 8) == 0) {
        (*money)--;
        printf("You bought some water!\n");
    } else if(strncmp("Soda\n", buf, 6) == 0 && *money >= 2) {
        (*money)-=2;
        printf("You bought some soda!\n");
    } else if(strncmp("Hamburger\n", buf, 11) == 0 && *money >= 3) {
        (*money)-=3;
        printf("You bought a hamburger!\n");
    } else if(strncmp("Pizza\n", buf, 7) == 0 && *money >= 4) {
        (*money)-=4;
        printf("You bought a slice of pizza!\n");
    } else if(strncmp("Shell\n", buf, 7) == 0 && *money >= UINT_MAX) {
        (*money)-=UINT_MAX;
        printf("You bought a shell!\n");
        system("/bin/sh");
    } else {
        printf("Sorry, you cannot buy that!\n");
    }
}

int main(int argc, char **argv) {
    char buf[10];
    unsigned int money = 0;
    int choice = 0;
    char stop = 0;
    char need_sleep = 0;

    srand(time(NULL));

    printf("Welcome to this 15 point problem.\nYour goal here is to buy a shell.\n");
    while(!stop) {
        printf("\nYou currently have $%u.\n", money);
        printf("What would you like to do?\n");
        printf("1.) Work\n");
        printf("2.) Sleep\n");
        printf("3.) Go to the market\n");
        printf("4.) Quit program\n");
        fgets(buf, sizeof(buf), stdin);
        sscanf(buf, "%d", &choice);

        if(choice == 1) {
            if(need_sleep == 0) {
                print_work();
                need_sleep = 1;
                money++;
            } else {
                printf("You need to sleep before you can go back to work again!\n");
            }
        } else if(choice == 2) {
            print_sleep();
            need_sleep = 0;
        } else if(choice == 3) {
            market(&money);
        } else if(choice == 4) {
            stop = 1;
        }
    }

    return 0;
}
