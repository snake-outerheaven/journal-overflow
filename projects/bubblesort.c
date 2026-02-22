#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ASIZE 10

#define MAX ASIZE
#define MIN 0

int bubble(int[], size_t);

int main()
{
    int i = 0;
    int random;
    int a[ASIZE];


    while (i < ASIZE)
    {
        srand(time(NULL));
        random = rand() % MAX + MIN;
        a[i] = random;
        i++;
    }

    for (i = 0; i < ASIZE; i++)
        printf("|\t%d\t|\n", a[i]);

    bubble(a, sizeof(a) / sizeof(a[0]));

    printf("\n\n\n");

    for (i = 0; i < ASIZE; i++)
        printf("|\t%d\t|\n", a[i]);

    return EXIT_SUCCESS;
}

int bubble(int a[], size_t size)
{
    int i;
    int x;
    int temp;

    if (!a)
        return EXIT_FAILURE;

    if (size == 0)
        return EXIT_FAILURE;

    for (i = 1; i < size; i++)
        for (x = size - 1; x >= i; x--)
            if (a[x] < a[x - 1])
            {
                temp = a[x];
                a[x] = a[x - 1];
                a[x - 1] = temp;
            }

    return EXIT_SUCCESS;
}
