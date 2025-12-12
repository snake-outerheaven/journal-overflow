#include <stdio.h> // incluo informações da biblioteca padrão de entrada e saída de C

/*
        print Fahrenheit-Celsius table
        for fahr = 0, 20, ..., 300
*/

int main() // inicio do programa sempre na função main.
{
        int fahr, celsius;
        int lower, upper, step;

        lower = 0; // limite inferior da tabela
        upper = 300; // limite superior da tabela
        step = 20; // tamanho do passo a cada iteração do loop abaixo

        while (fahr <= upper)
        {
                celsius = 5 * (fahr - 32) / 9;
                printf("%d\t->\t%d\n",fahr,celsius);
                fahr = fahr + step; // fahr += step; significa a mesma coisa e fica mais fácil de escrever.
        }
        return 0; // fim, do programa
}