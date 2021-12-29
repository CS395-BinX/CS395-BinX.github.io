#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void print_assignment() {
    printf("=====================\n");
    printf("=== Assignment 0 ===\n");
    printf("=====================\n\n");
}

int main(){
    char str1[] = "Hello!";
    char str2[25];
    print_assignment();
    printf("Whats your favorite string?\n");
    fgets(str2,100,stdin);
    printf("My favorite word is %s yours is %s\n",str1,str2);
}

void getShell(){
    printf("Good Job!\n");
    system("/bin/sh");
}
