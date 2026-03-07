// 3 - Fazer um programa que receba o peso e a altura de uma pessoa e calcule o
// seu IMC Índice de Massa Corporal.  IMC=peso/(altura X altura) Verifique se o
// indivíduo está no peso ideal. IMC>=18.5 e IMC<25

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WEIGHT 150.0F
#define MAX_HEIGHT 2.20F

#define MIN_WEIGHT 40.0F
#define MIN_HEIGHT 1.45F

float gen_weight();
float gen_height();
float gen_imc(float, float);

int main()
{
    float w, h;
    float imc;

    srand(time(NULL));

    w = gen_weight();
    h = gen_height();

    printf("Altura gerada: %.2f\tPeso gerado: %.2f\n", h, w);

    imc = gen_imc(w, h);

    if (imc < 18.5)
        printf("Abaixo do peso. IMC = %.2f.\n", imc);

    else if (imc >= 18.5F && imc < 25.0F)
        printf("Peso ideal. IMC = %.2f.\n", imc);

    else if (imc >= 25.0F && imc < 30.0F)
        printf("Sobrepeso. IMC = %.2f.\n", imc);

    else if (imc >= 30.0F && imc < 35.0F)
        printf("Obesidade 1. IMC = %.2f.\n", imc);

    else if (imc >= 35.0F && imc < 40.0)
        printf("Obesidade 2. IMC = %.2f.\n", imc);

    else
        printf("Obesidade mórbida. IMC = %.2f.\n", imc);

    return 0;
}

float gen_weight()
{
    float r = rand() / (float)RAND_MAX;
    return MIN_WEIGHT + r * (MAX_WEIGHT - MIN_WEIGHT); // transformação linear
}

float gen_height()
{
    float r = rand() / (float)RAND_MAX;
    return MIN_HEIGHT + r * (MAX_HEIGHT - MIN_HEIGHT);
}

float gen_imc(float w, float h)
{
    return w / (h * h);
}
