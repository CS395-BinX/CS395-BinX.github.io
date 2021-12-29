#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void fail(){
    puts("\n!!! INTRUDER ALERT !!! INTRUDER ALERT !!!");
    exit(1);
}

int main(){
    char str1[10];
    char str2[10];
    char str3[10];
    
    puts("What's the password?");
    fgets(str1,10,stdin);
    if(strncmp(str1,"password",8) == 0){
        puts("\nWell done, but I still don't trust you...");
        puts("What's the second password?");
        fgets(str2,10,stdin);
        if(strncmp(str2,"secret",6) == 0){
            puts("\nFantastic! I almost believe you deserve access!");
            puts("What's the third password?");
            fgets(str3,10,stdin);
            if(strncmp(str3,"cs395",5) == 0){
                puts("\nGreat job! You're an Angr master!");
                exit(0);
            }
        }
    }
    fail();
}
