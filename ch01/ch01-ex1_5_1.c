#include <stdio.h>

/*
        Book tells how to define stuff so we kill magic numbers
*/

#define LOWER 0
#define UPPER 300
#define STEP 20

int main()
{
        float fahr;

        for (fahr = UPPER; fahr >= LOWER; fahr -= STEP)
                printf("%.1f\t\t%.2f\n", fahr, (5.0F / 9.0F) * (fahr - 32));
        return 0;
}