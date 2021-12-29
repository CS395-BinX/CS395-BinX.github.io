#include<stdio.h>
#include<stdlib.h>

void getShell(char str[]){
    printf("Running %s...",str);
    system(str);
}

int main(){
    char buf[10];
    char str[] = "/bin/sh";
    printf("Look at this cool string I found: %s\n",str);

    printf("Input your name:\n");
    gets(buf);
    printf("hello %s\n",buf);
}
