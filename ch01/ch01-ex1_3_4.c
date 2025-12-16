#include <stdio.h>

/*
        Modify the temperature conversion program to print a heading above the table.
*/

int main()
{
        float celsius, fahr;
        int lower, upper, step;

        lower = 0;
        upper = 300;
        step = 20;
        fahr = lower;

        printf("Fahr/Cels temperature convertion table.\n");

        while (fahr <= upper)
        {
                celsius = (5.0 / 9.0) * (fahr - 32.0);
                printf("|%.1f\t->\t%.2f\t|\n", fahr, celsius);
                fahr += step;
        }
        return 0;
}