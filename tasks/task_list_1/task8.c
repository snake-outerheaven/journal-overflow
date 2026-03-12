// 8 - Escreva um programa que receba um número e imprima uma das mensagens: “é
//  múltiplo de 3”ou “não é múltiplo de 3”. Sabendo que na expressão (A= B%3) A
//  receberá o resto da divisão de B por 3

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int num;

    setlocale(LC_ALL, "pt-BR.UTF-8");

    srand((unsigned int)time(NULL));

    num = (rand() % 80) + 1;

    if (!(num % 3))
        printf("%d é múltiplo de 3.\n", num);
    else
        printf("%d não é múltiplo de 3.\n", num);

    return 0;
}