#include<stdio.h>
#include<stdlib.h>
void get_shell(){
    system("/bin/sh");
}

int main(){
    char str1[] = "Hello";
    char str2[10];
    gets(str2);
    printf("%s %s",str1,str2);
}
