//  13 - A confederação brasileira de natação fará o cadastro de atletas por
//  categoria. Fazer um programa que receba a idade de um nadador e apresente a
//  sua categoria segundo as seguintes faixas: Infantil A 5 – 7 anos -- Infantil
//  B 8 – 10 anos -- Juvenil A 11 – 13 anos -- Juvenil B 14 – 17 anos.

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int idade;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    srand(time(NULL));

    idade = (rand() % 20) + 5;

    printf("Idade gerada: %d.\n", idade);

    if (idade > 4 && idade < 8)
        printf("Infantil A.\n");

    else if (idade > 7 && idade < 11)
        printf("Infantil B.\n");

    else if (idade > 10 && idade < 14)
        printf("Juvenil A.\n");

    else if (idade > 13 && idade < 18)
        printf("Juvenil B.\n");

    else
        printf("Fora das categorias oficiais.\n");

    return 0;
}