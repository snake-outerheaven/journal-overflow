// 11 – Faça um programa para calcular o IMC de um indivíduo após a leitura de
// seu peso e altura. Em seguida classifique-o pela tabela : IMC abaixo de 18,5
// Abaixo do peso IMC de 18,5 até 24,9 Peso Normal, IMC de 25 até 29,9 Sobre
// Peso IMC de 30 até 34,9 Obesidade Grau 1, IMC de 35 ate 39,9 Obesidade Grau
// 2, A partir 40 Obesidade Mórbida.

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    double peso, altura, imc;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    srand(time(NULL));

    altura = 1.55 + ((double)rand() / RAND_MAX) * (2.20 - 1.55);
    peso = 55.0 + ((double)rand() / RAND_MAX) * (150.0 - 55.0);

    imc = peso / (altura * altura);

    printf("Peso gerado: %.2lf\tAltura gerada: %.2lf\tIMC calculado: %.2lf\n",
           peso, altura, imc);

    if (imc < 18.5)
        printf("Indivíduo abaixo do peso.\n");

    else if (imc >= 18.5 && imc < 25.0)
        printf("Indivíduo com peso normal.\n");

    else if (imc >= 25 && imc < 30.0)
        printf("Indivíduo com sobrepeso.\n");

    else if (imc >= 30.0 && imc < 35.0)
        printf("Indivíduo com Obesidade grau 1.\n");

    else if (imc >= 35.0 && imc < 40.0)
        printf("Indivíduo com Obesidade grau 2.\n");

    else
        printf("Indivíduoc om Obesidade Mórbida.\n");

    return 0;
}