#include <stdio.h>
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
        int c, x, y, h, hmax, state, len;
        int wcount[MAX];

        /*
                Initialization part
        */
        state = OUT;

        len = 0;

        for (x = 0; x < MAX; x++)
                wcount[x] = 0;

        while ((c = getchar()) != EOF) /* FSM loop!*/
        {
                /* Defining a clear boundary between characters and separators */
                if (c == ' ' || c == '\t' || c == '\n' || c == '.' || c == '!' || c == '?')
                {
                        /*
                                most important part of the loop
                                dealing with IN -> OUT state transition.
                        */
                        if (state == IN)
                        {
                                if (len > MAX)
                                        len = MAX;
                                wcount[len - 1]++;
                                len = 0;
                        }
                        state = OUT;
                }
                /* OUT -> IN state transition. */
                else
                {
                        state = IN;
                        len++;
                }
        }

        /* How tall is the tallest collumn on a vertical histogram? */
        hmax = 0;
        for (x = 0; x < MAX; x++)
        {
                if (wcount[x] > hmax)
                        hmax = wcount[x];
        }

        /* How to render the vertical histogram on ascii characters? */
        for (h = hmax; h > 0; h--)
        {
                for (x = 0; x < MAX; x++)
                {
                        if (wcount[x] >= h)
                                printf(" *\t");
                        else
                                printf(" \t");
                }
                putchar('\n');
        }

        /* How to render axis labels? */
        for (x = 0; x < MAX; x++)
                printf("%2d \t", x + 1);
        putchar('\n');

        return 0;
}