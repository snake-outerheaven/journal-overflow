#include <stdio.h>

/*
        Write a program to print the corresponding Celsius to Fahrenheit table.
*/

int main()
{
        float celsius;

        for (celsius = 0.0F; celsius <= 300.0F; celsius += 20.0F)
                printf("%.1f\t\t%.2f\n", celsius, (celsius * 9.0F / 5.0F) - 32.0F);
}