#include <stdio.h>
/*
        Verify that the expression getchar() != EOF is 0 or 1. <- this code does it. as it infinitely prints 1 after typing anything
        Write a program to print the value of EOF. <- done at the start.
*/
int main()
{
        int c;

        c = EOF;

        printf("%d\n", c);

        while ((c = getchar()) != EOF)
                printf("%d\n", c);

        return 0;
}