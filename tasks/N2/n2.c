// Nome: Otávio Augusto de Sousa Brito e Silva
// Matéria: Programação de Computadores 1
// Professor: Sérgio Eduardo Côrrea Neto
// Turma: 7594

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 120

#define MINPROD 80.0
#define MAXPROD 250.0

#define MININJ 150.0
#define MAXINJ 400.0

#define MINNUM 0
#define MAXNUM 15

#define SEQ 77001

typedef struct duto_t
{
  char code[35];
  int func;
  float bar;
  int alert;
} duto_t;

int
main (void)
{
  // números para loop
  int i, x;

  int codnum = SEQ;

  duto_t dutos[N] = { 0 }, temp;

  float sumAlertTot = 0, avgAlertTot;

  float totProd = 0, totInj = 0, sumProd = 0, sumInj = 0, avgProd, avgInj;

  float tot200Bar = 0, tot220Bar = 0, perc200, perc220;

  float percZero, totZero = 0;

  setlocale (LC_ALL, "pt_BR.UTF-8");
  srand (time (0));

  printf ("%-35s %-35s %-35s %-35s\n", "Código de linha", "Função do duto",
          "Pressão Interna Operacional", "Número de alertas");

  for (i = 0; i < N; ++i)
    {
      dutos[i].func = rand () % 2 + 1;
      dutos[i].alert = rand () % (MAXNUM - MINNUM + 1) + MINNUM;

      if (dutos[i].func == 1)
        {
          sprintf (dutos[i].code, "P-%d", codnum);
          dutos[i].bar
              = ((float)rand () / RAND_MAX) * (MAXPROD - MINPROD) + MINPROD;
          sumProd += dutos[i].bar;
          totProd++;

          if (dutos[i].bar > 200.0) // se pressao tubo 1 > 200, conto ele
            tot200Bar++;
        }

      else
        {
          sprintf (dutos[i].code, "I-%d", codnum);
          dutos[i].bar
              = ((float)rand () / RAND_MAX) * (MAXINJ - MININJ) + MININJ;
          sumInj += dutos[i].bar;
          totInj++;

          if (dutos[i].bar < 220.0) // se pressao tubo 2 < 220 conto ele.
            tot220Bar++;

          if (dutos[i].alert == 0)
            totZero++;
        }

      codnum++;

      sumAlertTot += dutos[i].alert;

      printf ("%-35s %-35d %-35.1f %-35d\n", dutos[i].code, dutos[i].func,
              dutos[i].bar, dutos[i].alert);
    }

  avgAlertTot = sumAlertTot / N;

  avgProd = (totProd > 0) ? sumProd / totProd : 0;
  avgInj = (totInj > 0) ? sumInj / totInj : 0;

  perc200 = totProd > 0 ? tot200Bar / totProd * 100 : 0;

  perc220 = totInj > 0 ? tot220Bar / totInj * 100 : 0;

  percZero = totZero / N * 100;

  printf ("Relatório de dados pedidos\n");

  printf (
      "Média do número geral de alertas gerados pela malha de dutos: %.2f\n",
      avgAlertTot);

  printf ("Média de pressão nos tubos de linha de produção: %.2f\n", avgProd);
  printf ("Média de pressão nos tubos de linha de injeção: %.2f\n", avgInj);

  printf ("Percentual de Linhas de produção > 200 bar: %.2f%%\n", perc200);
  printf ("Percentual de Linhas de injeção < 220 bar: %.2f%%\n", perc220);

  printf ("Percentual de dutos sem alertas de variação: %.2f%%\n", percZero);

  for (i = 1; i < N; ++i)
    for (x = N - 1; x >= i; x--)
      if (dutos[x].alert > dutos[x - 1].alert)
        {
          temp = dutos[x];
          dutos[x] = dutos[x - 1];
          dutos[x - 1] = temp;
        }

  printf ("Apresentando relatório de tudos ordenados pelo número de alertas "
          "em ordem decrescente\n");

  for (i = 0; i < N; ++i)
    printf ("%-35s %-35d %-35.1f %-35d\n", dutos[i].code, dutos[i].func,
            dutos[i].bar, dutos[i].alert);

  return 0;
}
