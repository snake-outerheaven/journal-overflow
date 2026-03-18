#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 90

void skip()
{
    putchar('\n');
    putchar('\n');
}

void quicksort(int *item, int left, int right)
{
    int walker1, walker2;
    int pivot, temp;

    walker1 = left, walker2 = right;
    pivot = item[(right + left) / 2];

    do
    {
        while (pivot > item[walker1] && walker1 < right)
            walker1++;

        while (pivot < item[walker2] && walker2 > left)
            walker2--;

        if (walker1 <= walker2)
        {
            temp = item[walker1];
            item[walker1] = item[walker2];
            item[walker2] = temp;
            walker1++, walker2--;
        }
    } while (walker1 <= walker2);

    if (left < walker2)
        quicksort(item, left, walker2);
    if (right > walker1)
        quicksort(item, walker1, right);
}

void quick(int *item, int count)
{
    quicksort(item, 0, count - 1);
}

int main()
{
    int i;
    int array[MAX];

    srand(time(NULL));

    for (i = 0; i < MAX; i++)
        array[i] = rand() % MAX;

    for (i = 0; i < MAX; i++)
        printf("|\t%d\t|\n", array[i]);

    quick(array, MAX);

    for (i = 0; i < 2; i++)
        skip();

    for (i = 0; i < MAX; i++)
        printf("|\t%d\t|\n", array[i]);

    return 0;
}
