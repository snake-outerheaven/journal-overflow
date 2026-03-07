// 5 - Fazer Um programa que receba três valores A, B e C, os apresente em ordem
// crescente.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

#define MAX 70

// implementa o algoritmo da ordenação bolha para
// ordenar o vetor em ordem crescente.
int bubble(int[], size_t);

int main()
{
    size_t i;
    int nums[SIZE];

    for (i = 0; i < SIZE; i++)
        nums[i] = rand() % MAX;

    puts("Números desorganizados:");

    for (i = 0; i < SIZE; i++)
        printf("%d\n", nums[i]);

    if (!bubble(nums, SIZE))
        return 1;

    puts("Números organizados:");

    for (i = 0; i < SIZE; i++)
        printf("%d\n", nums[i]);

    return 0;
}

int bubble(int arr[], size_t size)
{
    size_t i, x;
    int temp;

    if (!arr)
        return 0;

    for (i = 0; i < size; i++)
        for (x = size - 1; x > i; x--)
        {
            if (arr[x] < arr[x - 1])
            {
                temp = arr[x];
                arr[x] = arr[x - 1];
                arr[x - 1] = temp;
            }
        }

    return 1;
}
