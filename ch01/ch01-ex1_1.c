#include <ctype.h>  // biblioteca que se refere a texto
#include <stdio.h>  // biblioteca padrão de entrada e saída
#include <string.h> // biblioteca de manipulação bruta de memória.
#include <stdlib.h> // funções de gerenciamento de memória e comuns de C
#include <time.h>   // biblioteca que cuida de funções temporais

/*
        Protótipos de funções.
*/

int clear(void);
int stripe(char *str);

// int main(void) {}

int clear(void)
{
        return system("cls") ? 0 : 1;
}

int stripe(char *str)
{
        size_t end = strlen(str);
        if (end == 0)
                return 2;
        end--; // \0
        size_t start = 0;
        while (start <= end && isspace((unsigned char)str[start]))
                start++;
        while (end >= start && isspace((unsigned char)str[end]))
                end--;
        memmove(str, str + start, end - start + 1);
        str[end-start+1] = '\0';
        return 0;
}
// [H][e][l][l][o][][][][][][\0]
int main()
{

        int numero_aleatorio_da_silva;
        int chute;
        int tentativas = 0;

        printf("Duvido tu adivinhar meu numero kkkk \n");
        printf("é um número de 1 a 100 \n ");

        do
        {
                printf("faça um chute: ");
                scanf("%d", &tentativas);

                tentativas++; // tentativa = tentativa + 1;

                if (tentativas < numero_aleatorio_da_silva)
                {
                        printf("Tá frio! Tenta um numero maior.\n");
                }
                else if (tentativas > numero_aleatorio_da_silva)
                {
                        printf("Tá quente! Tenta um numero menor.\n");
                }
                else
                {
                        printf("Parabéns, Você adivinhou o número aleatorio da silva\n");
                        printf("O Número era %d\n", numero_aleatorio_da_silva);
                        printf("tu gastou %d tentativas.\n", tentativas);
                }

        } while (tentativas != numero_aleatorio_da_silva);

        return 0;
}
