#include <stdio.h>

/*
        Just another way to make last example more expressive
*/

int main()
{
        int c;

        while ((c = getchar()) != EOF)
                putchar(c);
}