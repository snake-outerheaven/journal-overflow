#include <stdio.h>

/*
Modify the temperature conversion program to print the table in reverse order,
that is, from 300 degrees to 0.
*/

int main(void)
{
    int celsius, fahr;
    int upper, lower, step;

    upper = 300;
    lower = 0;
    step = 20;

    fahr = upper;

    printf("\tF\tC\n");

    while (fahr > lower)
    {
        celsius = 5 * (fahr - 32) / 9;
        printf("\t%d\t%d\n", fahr, celsius);
        fahr -= step;
    }

    return 0;
}