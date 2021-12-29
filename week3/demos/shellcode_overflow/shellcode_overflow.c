#include<stdlib.h>
#include<stdio.h>

int main(){
    int marker = 0;
    char buf[10];

    printf("marker is at %p\n",&marker);
    printf("Input your name:\n");
    fgets(buf,200,stdin);
    printf("hello %s\n",buf);
}
