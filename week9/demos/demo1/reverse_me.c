#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc,char *argv[]){
    puts("I will take 4 numbers less than 20 from you and apply my ~secret hashing~ to them");
    puts("Give me the input that will produce: 96 1 18 27");

    if(argc != 5){
        puts("Invalid input, give me 4 numbers from the command line");
        exit(1);
    }

    int first = atoi(argv[1]);
    int second = atoi(argv[2]);
    int third = atoi(argv[3]);
    int fourth = atoi(argv[4]);
    printf("given numbers: %d %d %d %d\n",first,second,third,fourth); 

    int new_first = 3*(first*third);
    int new_second = (second%fourth)-1;
    int new_third = third + 2*(fourth);
    int new_fourth = (fourth*fourth) + (first*first*first);

    if(new_first == 96 && new_second == 1 && new_third == 18 &&
            new_fourth == 89){
        puts("Congratulations! You win!");
    }
    else{
        puts("Wrong! Try again nerd!");
    }
    printf("output numbers: %d %d %d %d\n",new_first,new_second,new_third,new_fourth); 
}
