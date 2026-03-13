// 10 - A prefeitura de Contagem abriu uma linha de crédito para seus
// funcionários. O valor máximo da prestação não poderá ultrapassar 30% do
// salário bruto. Fazer um programa que permita entrar salário bruto e o valor
// da prestação, e informar se o empréstimo pode ou não ser concedido.

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    double sal, prest;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    srand(time(NULL));

    sal = (double)(rand() % (15000)) + 500;

    prest = (double)(rand() % (7000)) + 500;

    printf("Salário gerado: %.2lf\tPrestação gerada: %.2lf\n", sal, prest);

    if (((prest / sal) * 100.0) <= 30.0)
        printf("Empréstimo pode ser feito.\n");

    else
        printf("Empréstimo não pode ser feito.\n");

    return 0;
}
