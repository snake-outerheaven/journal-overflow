// 6 - Fazer Um programa que receba três valores A, B , C e OP, quando OP=1
// apresente em ordem crescente caso contrário os números devem ser apresentados
// em ordem decrescente.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

#define MAX 80

// implementa ordenação bolha
// para ordenar um vetor de forma
// crescente e decrescente de acordo con OP.
int bubble(int v[], size_t len, int op);

int main()
{
    size_t i;
    int v[SIZE], op;

    srand(time(NULL));

    for (i = 0; i < SIZE; i++)
        v[i] = rand() % MAX;

    puts("Vetor desorganizado: ");

    for (i = 0; i < SIZE; i++)
        printf("%d\n", v[i]);

    op = (rand() % 2 == 0) ? 1 : 0;

    bubble(v, SIZE, op);

    printf("Vetor organizado com OP = %d\n", op);

    for (i = 0; i < SIZE; i++)
        printf("%d\n", v[i]);

    return 0;
}

int bubble(int v[], size_t len, int op)
{
    size_t i, x;
    int temp;

    if (!v)
        return 0;

    for (i = 0; i < len; i++)
        for (x = len - 1; x > i; x--)
            switch (op)
            {
            case 1:
                if (v[x] < v[x - 1])
                {
                    temp = v[x];
                    v[x] = v[x - 1];
                    v[x - 1] = temp;
                }
                break;
            default:
                if (v[x] > v[x - 1])
                {
                    temp = v[x];
                    v[x] = v[x - 1];
                    v[x - 1] = temp;
                }
                break;
            }

    return 1;
}
