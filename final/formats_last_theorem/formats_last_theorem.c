#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// gcc -o formats_last_theorem formats_last_theorem.c

unsigned int read_int(char c) {
    char buf[16] = {0};
    unsigned int ret = 0;
    
    printf("Enter a value for %c: ", c);
    fgets(buf, 16, stdin);
    sscanf(buf, "%u", &ret);

    if(c == 'n' && ret <= 2) {
        printf("This variable needs to be greater than 2.\n");
        ret = read_int('n');
    } else if(ret == 0) {
        printf("This variable needs to be greater than 0.\n");
        ret = read_int(c);
    }

    return ret;
}

unsigned int power(unsigned int x, unsigned int y) {
    unsigned int i = 0, ret = 1;

    for(i = 0; i < y; i++) {
        ret = ret * x;
    }

    if(ret < x) {
        ret = UINT_MAX;
    }

    return ret;
}

void print_crap() {
    printf("Fermat\'s Last Theorem states that no three positive integers\n");
    printf("a, b, and c can satisfy a^n + b^n = c^n, where n is a\n");
    printf("positive integer greater than 2. Unfortunately, Fermat died\n");
    printf("in 1665 before he could write down the proof. Nobody was able\n");
    printf("to figure out the proof for centuries until 1995, when Andrew\n");
    printf("Wiles and Richard Taylor proved that Fermat\'s Last Theorem was\n");
    printf("indeed true.\n\n");

    printf("Source: https://www.britannica.com/science/Fermats-last-theorem\n\n");

    printf("Why don\'t we try to test out this theory ourselves? Give me\n");
    printf("three numbers to work with and let\'s see if they satisfy\n");
    printf("Fermat\'s Last Theorem.\n\n");
}

void name(unsigned int *an, unsigned int *bn, unsigned int *cn) {
    char buf[64];

    printf("\nBefore I tell you my calculations, why don\'t you tell me your name:\n");
    fgets(buf, 64, stdin);
    buf[strlen(buf) - 1] = '\0';
    printf("Hello there ");
    printf(buf);
    printf(", it\'s a pleasure to meet you.\n\n");
}

int main(int argc, char **argv) {
    unsigned int a, b, c, n, an, bn, cn;

    print_crap();

    a = read_int('a');
    b = read_int('b');
    c = read_int('c');
    n = read_int('n');

    an = power(a, n);
    bn = power(b, n);
    cn = power(c, n);

    name(&an, &bn, &cn);
    
    printf("Anyways, here are my calculations:\n");
    printf("a^n = %u\n", an);
    printf("b^n = %u\n", bn);
    printf("c^n = %u\n", cn);

    if(an + bn == cn && n > 2) {
        printf("a^n + b^n == c^n\n");
        printf("Holy crap!\nYou actually broke Fermat\'s Last Theorem!\n");
        system("/bin/sh");
    } else {
        printf("a^n + b^n != c^n\n");
        printf("Looks like Fermat\'s Last Theorem is correct.\n");
    }

    return 0;
}
