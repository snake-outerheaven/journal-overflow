#include <stdio.h>  // biblioteca padrão de entrada e saída
#include <stdlib.h> // funções de gerenciamento de memória e comuns de C
#include <time.h>   // biblioteca que cuida de funções temporais

int main(void)
{
        int secret, guess, tries = 0;

        srand((unsigned int)time(NULL));
        secret = rand() % 100 + 1;
        while (1)
        {
                printf("Write your guess: ");
                if (scanf("%3d", &guess) != 1)
                {
                        guess = 0;
                        printf("Wrong input.\n");
                        return EXIT_FAILURE;
                }
                tries++;
                if (secret < guess)
                {
                        printf("Too high!\n");
                        continue;
                }
                else if (secret > guess)
                {
                        printf("Too low!\n");
                        continue;
                }
                else
                {
                        printf("Congrats, you done it in %d tries!\n", tries);
                        return EXIT_SUCCESS;
                }
        }
}

