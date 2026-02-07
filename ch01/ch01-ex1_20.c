#include <stdio.h>

/*
        Write a program detab that replaces tabs in the input with the proper
        number of blanks to space to the next tab stop.
        Assume a fixed set of tab stops, say every n columns.
        Should n be a variable or a symbolic parameter?

        this is exercise 1-20.
*/

#define TABSIZE 8 /*just like linux source code.*/

int main()
{
    int c;
    int i;
    int spaces;
    int column = 0;

    for (c = 0; (c = getchar()) != EOF;)
    {
        if (c == '\t')
        {
            spaces = TABSIZE - (column % TABSIZE);
            for (i = 0; i < spaces; i++)
                putchar(' '), column++;
        }

        else if (c == '\n')
            putchar(c), column = 0;

        else
            putchar(c), column++;
    }

    return 0;
}
