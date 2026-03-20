// 3) Dado o exercício 2 faça outro algoritmo que calcule o percentual de
// operários de cada linha de produção e o percentual de operários que
// produziram mais de 300 peças.

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OPNUMBER 50

#define MAXPROD 350
#define MINPROD 120

#define MAXLINE 2
#define MINLINE 1

int gen_prod();
int gen_line();
int gen_percs(int[], int[], float[], float *);

int main()
{
    size_t i;
    int line[OPNUMBER] = {0};
    int prod[OPNUMBER] = {0};
    float linepercs[MAXLINE] = {0};
    float perc300 = 0;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    srand(time(0));

    for (i = 0; i < OPNUMBER; ++i)
    {
        line[i] = gen_line();
        prod[i] = gen_prod();
    }

    if (!gen_percs(line, prod, linepercs, &perc300))
        puts("Falha ao gerar percentuais.");

    for (i = 0; i < MAXLINE; i++)
        printf("Percentual de trabalhadores da linha %zu: %.2f\n", i + 1,
               linepercs[i]);

    printf("Percentual de trabalhadores com produção > 300: %.2f.\n", perc300);

    return 0;
}

int gen_prod()
{
    return rand() % (MAXPROD - MINPROD + 1) + MINPROD;
}

int gen_line()
{
    return rand() % (MAXLINE - MINLINE + 1) + MINLINE;
}

int gen_percs(int line[], int prod[], float percs[], float *perc300)
{
    size_t i;
    int sums[MAXLINE] = {0};
    int sum300 = 0;

    if (!line || !prod || !percs || !perc300)
        return 0;

    for (i = 0; i < OPNUMBER; ++i)
    {
        if (prod[i] > 300)
            sum300++;
        switch (line[i])
        {
        case 1:
            sums[0]++;
            break;
        case 2:
            sums[1]++;
            break;
        default:
            printf("Linha %d não existe no domínio do problema!\n", line[i]);
            break;
        }
    }

    for (i = 0; i < MAXLINE; i++)
        percs[i] = ((float)sums[i] * 100.0F) / OPNUMBER;

    *perc300 = ((float)sum300 * 100.0F) / OPNUMBER;

    return 1;
}
