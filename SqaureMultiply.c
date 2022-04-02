// Sumitram Kumar 201951156, Section 2

//Square and Multiply Algorithm, D.H. Key Exchange
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int SqaureMultiply (unsigned int x, int H, int n) {

    int h = 0;
    unsigned int r = 0;
    int temp [32];
    int i = 0;

    r = x;
    
    // part 1 of question
    // Step 1: Convert input into binary
    while (H > 0) {
        if (H % 2 == 0) {
            temp[i] = 0;
        }

        else {
            temp [i] = 1;
        }

        H = H/2;
        i++;
    }
    i--;

    // Step 2: If we encounter r as 0, sqaure r.
    // If we encounter r, then multiply by r.

    while (i > 0) {
        r = (r * r) % n;

        if (temp[--i] == 1) {
            r = (r * x) % n;
        }
    }

    return r;
} 


int main () {

    srand(time(0)); // associating random number with time

    // part 2 of question
    unsigned int a = rand() , b = rand(); 
    int p = 131 , g = 2;

    // part 3 of question
    // for Alice
    printf ("Alice chooses a as %d and value of his private key (g ^ a %% p) = %d and value of (g ^ (a * b) %% p) = %d\n"
    , a, SqaureMultiply(g, a, p), SqaureMultiply(g, a * b, p));

    // for Bob
    printf ("Bob chooses b as %d and value of his private key (g ^ b %% p) = %d and value of (g ^ (b * a) %% p) = %d\n"
    , b, SqaureMultiply(g, b, p) , SqaureMultiply(g, b * a, p));

    return 0;
}
