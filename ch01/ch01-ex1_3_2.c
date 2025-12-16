#include <stdio.h> // incluo informações da biblioteca padrão de entrada e saida
/*
        Exemplo do livro.
*/
int main()
{
        float fahr, celsius;    // variáveis de temperatura agora são de ponto flutuante.
        int lower, upper, step; // variaveis de controle do loop seguem inteiras

        /*
                Variáveis seguem iguais do exercício anterior;
        */
        lower = 0;
        upper = 300;
        step = 20;

        fahr = lower;

        while (fahr <= upper)
        {
                celsius = (5.0F / 9.0F) * (fahr - 32.0F); // note que para ter números de ponto flutuante, que buscam representar números reais,
                                                                              // foi essencial colocar o .0, e para especificar que não são de precisão dupla, é usado F 
                                                                              // no final de cada número.
                printf("%.1f\t->\t%.3f\n", fahr, celsius); // na função printf, %.xf  é usado para formatar o número de ponto flutuante
                                                                                  // onde .x de 0 até 6 especifica quantas casas depois da vírgula.
                fahr += step; // == fahr = fahr + step;
        }
        return 0;
}