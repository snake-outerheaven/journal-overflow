// 6) Uma empresa de manutenção de equipamentos deseja fazer um estudo em
// relação um conjunto de 250 Ordens de Serviço executadas, para isso ofereceu
// um arquivo contendo o Número da OS(1354- 1603) a quantidade de dias previstos
// par a entrega, a quantidade de dias gastos e o tipo do serviço (1 –
// Manutenção ou 2 – Reparo) . Faça um programa que gere aleatoriamente as
// informações e calcule: O percentual de ordens de serviço de cada tipo
// entregue fora do prazo e o número da OS com maior atraso.

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
    int OSmaiorAtraso, atrasoAtual, maiorAtraso = -1;
    float totAtraso1 = 0, totAtraso2 = 0, TotT1 = 0, TotT2 = 0;
    float percAtrasoT1, percAtrasoT2;

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

        if (tipoServ == 1)
            TotT1++;

        if (tipoServ == 2)
            TotT2++;

        if (diasGast > diasPrev)
        {
            atrasoAtual = diasGast - diasPrev;

            if (atrasoAtual > maiorAtraso)
            {
                maiorAtraso = atrasoAtual;
                OSmaiorAtraso = numeroOS;
            }

            if (tipoServ == 1)
                totAtraso1++;

            if (tipoServ == 2)
                totAtraso2++;
        }
    }

    percAtrasoT1 = totAtraso1 / TotT1 * 100;
    percAtrasoT2 = totAtraso2 / TotT2 * 100;

    putchar('\n');
    putchar('\n');
    putchar('\n');

    printf("Exibição de resultados.\n");
    printf("------------------------------\n");
    printf("Percentuais de pedidos atrasados do tipo 1: %.2f\n", percAtrasoT1);
    printf("Percentuais de pedidos atrasados do tipo 2: %.2f\n", percAtrasoT2);
    printf("Número da ordem de serviço com maior atraso: %d\n", OSmaiorAtraso);

    return 0;
}
