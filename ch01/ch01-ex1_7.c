#include <stdio.h>

/*
        every exercise from now on is a number upper than the number on the book, since i solved 1-7 exercise on 1-6.
        Write a program to count blanks, tabs, and newlines.

        this is exercise 1-8
*/

int main()
{
        int input;
        size_t bcount, tcount, nlcount, ccount;

        input = ccount = bcount = tcount = nlcount = 0;

        while ((input = getchar()) != EOF)
        {
                ccount++;
                putchar(input);
                if (input == ' ')
                        bcount++;
                if (input == '\t')
                        tcount++;
                if (input == '\n')
                        nlcount++;
        }

        printf("Characters typed: %zu\nBlanks typed: %zu\nTabs typed: %zu\nNewlines typed: %zu\n", ccount, bcount, tcount, nlcount);
        return 0;
}