#include <stdio.h>

/*
        This is an example of a bare bones version of the UNIX program wc,
        shown by the book on part 1.5.4
*/

#define IN 1
#define OUT 0

/*
        Count lines, words, and characters in input
*/

int main()
{
        int c, nl, nw, nc, state;

        state = OUT;
        nl = nw = nc = 0;

        while ((c = getchar()) != EOF)
        {
                nc++;
                if (c == '\n')
                        nl++;
                if (c == ' ' || c == '\n' || c == '\t')
                        state = OUT;
                else if (state == OUT)
                {
                        state = IN;
                        nw++;
                }
        }
        printf("%d\t%d\t%d\n", nl, nw, nc);
        return 0;
}