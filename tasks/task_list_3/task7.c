// 7) Dado o exercício 6 calcule a média de dias de atraso para as OS’s de cada
// tipo quando houver e o percentual de OS’s independente do tipo entregues
// antes do prazo.

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 250

#define MAX_OS 1603
#define MIN_OS 1354

#define MAX_DAYS 100
#define MIN_DAYS 3

int main()
{
    size_t i;
    int numeroOS, diasPrev, diasGast, tipoServ;
    int atrasoAtual;
    float totT1At = 0, totT2At = 0, sumAt1 = 0, sumAt2 = 0, sumNoPrazo = 0;
    float avgT1At, avgT2At, percNoPrazo;

    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(0));

    for (i = 0; i < N; ++i)
    {
        numeroOS = rand() % (MAX_OS - MIN_OS + 1) + MIN_OS;
        diasPrev = rand() % (MAX_DAYS - MIN_DAYS + 1) + MIN_DAYS;
        diasGast = rand() % (MAX_DAYS - MIN_DAYS + 1) + MIN_DAYS;
        tipoServ = (rand() % 2 == 0) + 1;

        printf("Ordem de serviço gerada\nNúmero da OS: %d\tDias previstos: "
               "%d\tDias gastos: %d\tTipo de serviço: %d\n",
               numeroOS, diasPrev, diasGast, tipoServ);

        atrasoAtual = diasGast - diasPrev;

        if (atrasoAtual > 0)
        {

            if (tipoServ == 1)
            {
                sumAt1 += atrasoAtual;
                totT1At++;
            }
            else
            {
                sumAt2 += atrasoAtual;
                totT2At++;
            }

        }
        else
            sumNoPrazo++;
    }

    avgT1At = (sumAt1 > 0) ? sumAt1 / totT1At : 0;
    avgT2At = (sumAt2 > 0) ? sumAt2 / totT2At : 0;
    percNoPrazo = sumNoPrazo / N * 100;

    puts("Resultados das OSs processadas:");
    printf("Média de dias de atraso das OS tipo 1: %.2f\n", avgT1At);
    printf("Média de dias de atraso das OS tipo 2: %.2f\n", avgT2At);
    printf("Percentual de ordens de serviço no prazo: %.2f%%\n", percNoPrazo);

    return 0;
}
