// 2) Fazer um programa que gere aleatoriamente a produção (120 a 350) e a linha
// de produção (1 ou 2) de 50 operários a calcule a média de produção geral e de
// cada linha.

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXPROD 350
#define MINPROD 120

#define OPNUMBER 50
#define LINENUMBER 2

#define MINLINE 1
#define MAXLINE LINENUMBER

int gen_prod();
int gen_line();
void gen_avg(int[], int[], float[], float *);

int main()
{
    size_t i;
    int prod[OPNUMBER] = {0};
    int line[OPNUMBER] = {0};
    float avg[LINENUMBER] = {0};
    float total_avg = 0;

    setlocale(LC_ALL, "pt_BR.UTF-8");

    srand(time(NULL));

    for (i = 0; i < OPNUMBER; i++)
    {
        prod[i] = gen_prod();
        line[i] = gen_line();
    }

    gen_avg(prod, line, avg, &total_avg);

    for (i = 0; i < LINENUMBER; i++)
        printf("Média da linha %zu: %.2f.\n", i + 1, avg[i]);

    printf("Média de todas as linhas: %.2f.\n", total_avg);

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

void gen_avg(int prod[], int line[], float avg[], float *total_avg)
{
    size_t i;
    int sum[MAXLINE] = {0};
    int accum_sum = 0;
    int total[MAXLINE] = {0};

    if (!prod || !line || !avg)
        return;

    for (i = 0; i < OPNUMBER; i++)
    {
        accum_sum += prod[i];
        switch (line[i])
        {
        case 1:
            sum[0] += prod[i];
            total[0]++;
            break;
        case 2:
            sum[1] += prod[i];
            total[1]++;
            break;
        }
    }

    for (i = 0; i < MAXLINE; i++)
    {
        if (!total[i])
        {
            avg[i] = 0.0F;
            continue;
        }
        avg[i] = (float)sum[i] / total[i];
    }

    *total_avg = (float)accum_sum / OPNUMBER;
}
