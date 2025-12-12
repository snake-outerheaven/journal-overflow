#include <stdio.h>  // biblioteca padrão de entrada e saída
#include <stdlib.h> // funções de gerenciamento de memória e comuns de C (srand() e rand())
#include <time.h>   // biblioteca que cuida de funções temporais

int main(void)
{
        int secret, guess, tries = 0; // variáveis que espero que sejam auto explanatórias

        srand((unsigned int)time(NULL)); // seed rand com a quantidade de segundos desde 1 de janeiro de 1970 (esse tempo é chamado de Unix Epoch.)
        secret = rand() % 100 + 1; // gera o número secreto de 1 até 100
        while (1) // verdadeiro por baixo dos panos é simplesmente 1, então é o loop infinto da linguagem
        {
                printf("Write your guess: ");
                if (scanf("%3d", &guess) != 1) // aqui eu rodo uma condicional que avalia se a função scanf lê exatamente o que está dentro dos parâmetros dela, ela retorna 1 se está positivo, 0 se não foi possível.
                {
                        guess = 0;
                        printf("Wrong input.\n");
                        return EXIT_FAILURE; // exit_failure é um macro que expande para 1, serve para deixar o código mais legível.
                }
                tries++;  // tries = tries + 1; (incremento)
                if (secret < guess)
                {
                        printf("Too high!\n");
                        continue; // continue faz o loop infinito seguir para a próxima iteração
                }
                else if (secret > guess)
                {
                        printf("Too low!\n");
                        continue;
                }
                else
                {
                        printf("Congrats, you done it in %d tries!\n", tries); 
                        return EXIT_SUCCESS; // exit_success expande para 0
                }
        }
}

