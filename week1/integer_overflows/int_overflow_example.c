#include <stdio.h>
#include <limits.h>

int main() {
    unsigned int points;
    int input;
    char buf[30];

    points = UINT_MAX;
    while(points != 0) {
        printf("You need %u more points to win.\n", points);
        printf("Enter your value: ");
        fgets(buf, 10, stdin);
        sscanf(buf, "%d", &input);
        if(input > 10) {
            printf("Hey, that's too big!!!\n");
        } else {
            points -= input;
        }
    }

    printf("\nYou win!!\n");
}
