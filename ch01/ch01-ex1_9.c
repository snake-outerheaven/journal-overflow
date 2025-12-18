#include <stdio.h>

/*
        Write a program to copy its input to its output, replacing each tab by \t, each backspace by \b, and each backslash by \\.
        This makes tabs and backspaces visible in an unambiguous way.
*/

int main()
{
        int input;

        while ((input = getchar()) != EOF)
        {
                if (input == '\t')
                        printf("\\t");
                else if (input == '\b')
                        printf("\\b");
                else if (input == '\\')
                        putchar('\\');
                else
                        putchar(input);
        }
        return 0;
}