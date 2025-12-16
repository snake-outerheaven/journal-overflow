#include <stdio.h>

/*
        Another way of doing the last loop
*/

int main()
{
        double c;

        for (c = 0.0; getchar() != EOF; c++)
                ; /*null statement*/

        printf("\n%.1lf\n", c);

        return 0;
}