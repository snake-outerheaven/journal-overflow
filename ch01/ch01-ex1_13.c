#include <stdio.h>

/*
        Write a program to print a histogram of the lengths of words in its input.
        It is easy to draw the histogram with the bars horizontal;
        a vertical orientation is more challenging.

        this is exercise  1-13.
*/

#define IN 1
#define OUT 0
#define MAX 20

int main()
{
        int c, i, i2, state, len;
        int wcount[MAX];

        state = OUT;

        len = 0;

        for (i = 0; i < MAX; i++)
                wcount[i] = 0;

        while ((c = getchar()) != EOF)
        {
                if (c == ' ' || c == '\t' || c == '\n' || c == '.' || c == '!' || c == '?')
                {
                        if (state == IN)
                        {
                                if (len > MAX)
                                        len = MAX;
                                wcount[len - 1]++;
                                len = 0;
                        }
                        state = OUT;
                }
                else
                {
                        state = IN;
                        len++;
                }
        }

        for (i = 0; i < MAX; i++)
        {
                printf("%d: ", i + 1);
                for (i2 = 0; i2 < wcount[i]; i2++)
                        printf("* ");
                putchar('\n');
        }

        return 0;
}