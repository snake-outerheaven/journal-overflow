#include <stdio.h>

/* 
        count digits, white space, others
        example from part 1.6 from chapter 1.

        Please, on Windows, type CTRL + Z then enter for the EOF character.
 */

int main()
{
        int c, i, nwhite, nother;
        int ndigit[10];

        nwhite = nother = 0;

        for (i = 0; i < 10; i++)
                ndigit[i] = 0;
        while ((c = getchar()) != EOF)
                if (c >= '0' && c <= '9')
                        ndigit[c - '0']++;
                else if (c == ' ' || c == '\n' || c == '\t')
                        nwhite++;
                else
                        nother++;

        printf("Digits = ");

        for (i = 0; i < 10; i++)
                printf("%d ", ndigit[i]);
        printf(", whitespace = %d, other = %d.\n", nwhite, nother);
        return 0;
}