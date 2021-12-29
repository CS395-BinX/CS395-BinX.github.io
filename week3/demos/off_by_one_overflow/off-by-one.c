#include<stdio.h>
#include<stdlib.h>

int getInput(){
    char input[4];
    fgets(input,4,stdin); 
    return atoi(input);
}

int main(){
    int three_hundred = 300;
    char string[15];
    char string2[] = "This is secure!!!";
    int i;

    for(i=0;i<=15;i++){
        string[i] = string2[i];
    }

    if(three_hundred == getInput()){
        printf("You Win!\n");
    }
    else{
        printf("You Lose!\n");
    }
}
