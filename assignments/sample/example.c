#include<stdio.h>
#include<stdlib.h>
void get_shell(){
    system("/bin/sh");
}

int main(){
    char vuln_buf[10];
    gets(vuln_buf);
}
