#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 120

#define CODEMAX 122120
#define CODEMIN 122001

int main()
{
    size_t i;

    int cod, u0, ts, ld, qh;
    int val;

    float totVal1 = 0, totVal2 = 0, totVal3 = 0;
    float totSA = 0;
    float contSv1 = 0, contSv2 = 0, contSv3 = 0;

    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(0));

    for (i = 0; i < N; ++i)
    {
        cod = rand() % (CODEMAX - CODEMIN + 1) + CODEMIN;
        u0 = (rand() % 2 == 0) + 1;
        ts = rand() % 3 + 1;
        ld = (rand() % 2 == 0);
        qh = rand() % 40 + 1;
        val = 1200 + ((ts * 200) * qh);

        puts("");
        puts("");

        printf("Nota %zu gerada:\n", i + 1);
        printf("Código: %d\n", cod);
        printf("Unidade Operacional: %d\n", u0);
        printf("Tipo de serviço: %d\n", ts);
        printf("Local de Destino: %s\n", ld ? "Estadual" : "Interestadual");
        printf("Quantidade de horas: %d\n", qh);
        printf("Valor da Nota: R$ %d\n", val);

        puts("");
        puts("");

        if (ts == 1)
        {
            contSv1++;
            totVal1 += val;
        }

        if (ts == 2)
        {
            contSv2++;
            totVal2 += val;

            if (qh < 10)
                totSA++;
        }

        if (ts == 3)
        {
            contSv3++;
            totVal3 += val;

            if (qh < 10)
                totSA++;
        }
    }

    printf("Impressão de estatísticas para a Segunda Entrega:\n");

    printf("Percentual de notas do tipo de serviço 1: %.2f%%\n",
           (contSv1 / N) * 100);
    printf("Percentual de notas do tipo de serviço 2: %.2f%%\n",
           (contSv2 / N) * 100);
    printf("Percentual de notas do tipo de serviço 3: %.2f%%\n",
           (contSv3 / N) * 100);

    printf("Percentual de serviços de alta complexidade com dur < 10: %.2f%%\n",
           (totSA / (N - contSv1) * 100));

    printf("Média de valores para o tipo de serviço 1: %.2g\n",
           totVal1 / contSv1);

    printf("Média de valores para o tipo de serviço 2: %.2g\n",
           totVal2 / contSv2);

    printf("Média de valores para o tipo de serviço 3: %.2g\n",
           totVal3 / contSv3);

    return 0;
}
