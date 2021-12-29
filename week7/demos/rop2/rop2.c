#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int x = 0;
int y = 0;

void callme1(){
    x = 1;
}

void callme2(int c){
    if(c == 1337)
        y = 1;
}

void getInput(){
    char buf[50];
    fgets(buf,300,stdin);
}

void getShell(){
    if(x == 0)
        exit(1);
    if(y == 0)
        exit(1);
  
    system("/bin/sh");
}

int main(){
    puts("Only a ROP champion could solve this one!");   
    getInput();
    getShell();
}
