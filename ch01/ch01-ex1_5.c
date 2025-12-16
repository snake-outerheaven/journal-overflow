#include <stdio.h>

/*
        Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0.
*/

int main()
{
        float fahr;

        for (fahr = 300.0F; fahr >= 0.0F; fahr -= 20.0F)
                printf("%.1f\t\t%.2f\n", fahr, (5.0F / 9.0F) * (fahr - 32));
        return 0;
}