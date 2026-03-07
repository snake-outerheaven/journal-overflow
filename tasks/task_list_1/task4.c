// 4 – Fazer Um programa que leia três valores verifique se estes podem ser os
// lados de um triângulo, caso afirmativo, classifique o triângulo quanto ao seu
// tipo.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NSIDES 3

// recebe um vetor de inteiros e o tamanho do vetor
// aplica a lógica da Desigualdade Triangular.
// retorna 1 se o triangulo for válido, 0 se não for.
int validate(int[], int);

// verifica lados e determina o tipo do triangulo
// retorna 1 se o triângulo for equilátero, 2 se o triângulo for isósceles, 3 se
// o triângulo for escaleno, 0 se não for válido
int classify(int[], int);

int main()
{
    size_t i;
    int lados[NSIDES];

    srand(time(NULL));

    for (i = 0; i < NSIDES; i++)
    {
        printf("Digite o %zu° lado: ", i + 1);
        scanf("%d", lados + i);
    }

    if (!validate(lados, NSIDES))
    {
        puts("Triângulo inválido!");
        return 1;
    }

    switch (classify(lados, NSIDES))
    {
    case 1:
        puts("Equilátero.");
        break;
    case 2:
        puts("Isósceles.");
        break;
    case 3:
        puts("Escaleno.");
        break;
    default:
        puts("Undefined");
        break;
    }

    return 0;
}

int validate(int l[], int size)
{
    if (!l || !size)
        return 0;

    if (l[0] >= l[1] + l[2])
        return 0;

    if (l[1] >= l[0] + l[2])
        return 0;

    if (l[2] >= l[1] + l[0])
        return 0;

    return 1;
}

int classify(int l[], int size)
{
    if (!l || size < 3)
        return 0;

    if (l[0] == l[1] && l[1] == l[2])
        return 1;

    if (l[0] == l[1] || l[0] == l[2] || l[1] == l[2])
        return 2;

    return 3;
}
