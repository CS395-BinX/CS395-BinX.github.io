#include<stdio.h>
#include<stdlib.h>
int health = 100;

void printmenu(){
    printf("\nYou have these attacks:\n");
    puts("1. Chop");
    puts("2. Kick");
    puts("3. Punch");
    puts("4. Ultimate Power Overflow");
    printf("\n");
}

void printboss(){
    puts("    ()");
    puts("    |");
    puts("   ---");
    puts("    |");
    puts("   / \\");
    printf("Boss health: %d",health);
}

void printdeadboss(){
    puts("   (xx)");
    puts("    |");
    puts("   ---");
    puts("    |");
    puts("   / \\");
    puts("Boss health: 0");
}

void chop(){
    health -= 10;
    puts("It did 10 damage!");
}

void kick(){
    health -= 20;
    puts("It did 20 damage!");
}

void punch(){
    health -= 30;
    puts("It did 30 damage!");
}

void super(){
    char limit[10];
    fgets(limit,100,stdin);
}

int getInput(){
   puts("Input a move:");
   char input[3];
   fgets(input,3,stdin);
   return atoi(input);
}

int main(){
    printf("You are fighting the final boss! You must use your most powerful technique to defeat him!\n");
    while(health > 0){
        printboss();
        printmenu();
        switch(getInput()){
            case 1:
                puts("You used chop!");
                chop();
                break;
            case 2:
                puts("You used kick!");
                kick();
                break;
            case 3:
                puts("You used punch!");
                punch();
                break;
            case 4:
                puts("You begin generating power for your super combo move...");
                super();
                break;
            default:
                puts("Invalid move, enter a number 1-4");
                continue;
        }
        if(health > 0){
            puts("Your attack lands, but the enemy regenerates his health!");
            health = 100;
        }
    }
    puts("Congratulations, you've defeated the enemy!");
    printdeadboss();
    puts("Turn in a write-up for how you got here and you've completed the challenge!");
}

