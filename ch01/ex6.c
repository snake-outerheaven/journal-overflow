#include <stdio.h>

/*
Verify that the expression getchar() != EOF is 0 or 1.
*/

int main(void)
{
    int c, d;

    while ((d = ((c = getchar()) != EOF)))
        if (c == '\n')
            puts("Newline typed.");
        else
            printf("Char: %c\tInt: %d\tResult: %d\n", c, c, d);

    puts("EOF typed, end of program");

    return 0;
}