#include<stdio.h>
#include<string.h>

int main(){
	char shellcode[] = "\xb8\x3b\x00\x00\x00\xbb\x00\x00\x00\x00\x53\x48\xbb\x2f\x62\x69\x6e\x2f\x73\x68\x00\x53\x48\x89\xe7\xbe\x00\x00\x00\x00\xba\x00\x00\x00\x00\x0f\x05";
	char input[128];
	char *nop = "\x90";
	int len;

    puts("sliiiiiiiide up the stack!");
	fgets(input,250,stdin);
	len = strlen(input);

	int i = 0;
	for(;i <= len+1; i++){
		input[i] = *nop;
	}

    puts("cha-cha real smooth!");
    ((void (*)())(input))();
}
