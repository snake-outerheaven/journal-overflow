// 7 - Fazer um programa leia dois números e efetue a sua adição. Caso o valor
// encontrado seja maior que 20, este deverá ser apresentado somando-se a ele
// mais 8; caso o valor somado seja menor ou igual a 20, este deverá ser
// apresentado subtraindo-se 5.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 2
#define MAX 15

int main()
{
    size_t i;
    int nums[SIZE], sum = 0;

    srand(time(NULL));

    for (i = 0; i < SIZE; i++)
        nums[i] = rand() % MAX;

    for (i = 0; i < SIZE; i++)
        sum += nums[i];

    (sum > 20) ? printf("%d\n", sum + 8) : printf("%d\n", sum - 5);

    return 0;
}
