#include <stdio.h>

/*
        Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank.

        this is exercise 1-9
*/

int main()
{
        int input, bflag;
        
        bflag = 0;
        
        while ((input = getchar()) != EOF)
        {
                if (input == ' ')
                {
                        if (!bflag)
                                putchar(input);
                        bflag = 1;
                }
                else
                {
                        putchar(input);
                        bflag = 0;
                }
        
        }
        
        return 0;
}