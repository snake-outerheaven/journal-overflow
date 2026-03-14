// 12 - A CEF concederá um crédito especial com juros de 2% aos seus clientes de
// acordo com o saldo médio no último ano. Fazer um programa que leia o saldo
// médio de um cliente e calcule o valor do crédito de acordo com a tabela a
// seguir.
// Imprimir uma mensagem informando o saldo médio e o valor de crédito.
// De 0 a 500 Nenhum crédito - De 501 a 1000 30% do valor do saldo médio - De
// 1001 a 3000 40% do valor do saldo médio - Acima de 3001 50% do valor do saldo
// médio

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int saldo, valor;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    srand(time(NULL));

    saldo = rand() % 5000;

    printf("Saldo gerado: %d\n", saldo);

    if (saldo >= 0 && saldo <= 500)
        valor = 0;

    else if (saldo >= 501 && saldo <= 1000)
        valor = (saldo * 3) / 10;

    else if (saldo >= 1001 && saldo <= 3000)
        valor = (saldo * 4) / 10;

    else if (saldo >= 3001)
        valor = (saldo * 5) / 10;

    printf("Valor do crédito calculado: %d", valor);

    return 0;
}