#include <stdio.h>
#include <string.h>
/*
        Write a program to print a histogram of the lengths of words in its input.
        It is easy to draw the histogram with the bars horizontal;
        a vertical orientation is more challenging.

        we are going for the challenging version now.
*/

#define OUT 0
#define IN 1
#define MAX 20

int main()
{
        int c, i, i2, state, len;
        int wcount[MAX];

        state = OUT;

        len = 0;

        memset(wcount, 0, sizeof(wcount)); /* function from string.h that allows memory to be set up.*/
}