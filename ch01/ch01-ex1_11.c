#include <stdio.h>
/*
        Write a program that prints its input one word per line.
        this is exercise 1-12
*/
#define OUT 0
#define IN 1

int main()
{
        int c, state;

        state = OUT;

        while ((c = getchar()) != EOF)
        {
                if (c == ' ' || c == '\n' || c == '\t')
                {
                        /*Too bad i forgot this very important part, where i needed to check if the program was actually
                                checking if the FSM of in and out of words  was working correctly.*/
                        if (state == IN)
                                putchar('\n');
                        state = OUT;
                }
                else
                {
                        state = IN;
                        putchar(c);
                }
        }
        return 0;
}
