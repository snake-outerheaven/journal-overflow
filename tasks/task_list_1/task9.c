// 9 – Escreva um programa que leia um número e informe se ele é divisível por 3
// e por 7.

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int x;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    srand((unsigned)time(NULL));

    x = rand();

    if (!(x % 3) && !(x % 7))
        printf("%d é divisível por 3 e por 7\n", x);

    else
        printf("%d não é divisível por 3 e por 7", x);

    return 0;
}