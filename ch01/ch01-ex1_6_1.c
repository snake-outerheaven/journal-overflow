#include <stdio.h>

/*
        count characters in input; 1st version
*/

int main()
{
        long c;

        c = 0;

        while (getchar() != EOF)
                c++;

        printf("%ld\n", c);

        return 0;
}