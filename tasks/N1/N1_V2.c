// TODO: Refazer exercício da prova com vetor

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 123     // numero de notas
#define MAXBUF 20 // tamanho de strings

#define MAXDAY 30 // max de dias

#define NUM_MIN 1550 // número mínimo para compor o código da nota
#define NUM_MAX 1800 // número máximo para compor o código da nota

int
main (void)
{
  size_t i; // variável usada pelo loop

  // número ser gerado
  int num;

  // valores individuais de cada nota.
  int ts[N], loc[N], val[N], day[N];
  char code[N][MAXBUF], mes[N][MAXBUF];

  // variáveis para salvar a maior nota
  char codeMaiorV[20], mesMaiorV[20];
  int tsMaiorV, locMaiorV, valMaiorV = 0, dayMaiorV = 0;

  // var para comparação da maior nota, começa com o -1 coringa.
  int valCmp = -1;

  int totLoc1 = 0;     // total de notas loc 1
  float totLoc115 = 0; // total de notas loc 1 com day < 15

  // variáveis para o cálculo da média de dias dependendo do tipo de serviço
  int contTs1 = 0, contTs0 = 0;
  float sumTs1 = 0, sumTs0 = 0, sumTsTot = 0;

  // calcular valor médio em cima do mês
  float val39 = 0, val41 = 0, val43 = 0;
  float avg39, avg41, avg43;

  // variáveis para armazenar o percentual de notas especial + média de dias.
  float perNtLoc115, avgDayTot, avgDayTs1, avgDayTs0;

  setlocale (LC_ALL,
             "pt_BR.UTF-8"); // seta o terminal para português brasileiro UTF-8
  srand (time (NULL));

  num = rand () % (NUM_MAX - NUM_MIN + 1) + NUM_MIN;

  for (i = 0; i < N; ++i)
    {
      ts[i] = rand () % 2;
      loc[i] = rand () % 2;
      day[i] = rand () % MAXDAY + 1;

      if (ts[i])
        {
          val[i] = day[i] * 450 + 750;
          sumTs1 += day[i];
          contTs1++;
        }

      else
        {
          val[i] = day[i] * 300 + 500;
          sumTs0 += day[i];
          contTs0++;
        }

      sumTsTot += day[i];

      if (loc[i])
        {
          totLoc1++;

          if (day[i] < 15)
            totLoc115++;
        }

      if (i < 39)
        {
          sprintf (mes[i], "Setembro");
          val39 += val[i];
        }
      else if (i < 80)
        {
          sprintf (mes[i], "Outubro");
          val41 += val[i];
        }
      else
        {
          sprintf (mes[i], "Novembro");
          val43 += val[i];
        }

      sprintf (code[i], "NT%d%c", num, ts[i] ? 'T' : 'F');

      if (val[i] > valCmp)
        {
          valCmp = val[i];
          strcpy (codeMaiorV, code[i]);
          strcpy (mesMaiorV, mes[i]);
          tsMaiorV = ts[i];
          locMaiorV = loc[i];
          dayMaiorV = day[i];
          valMaiorV = val[i];
        }

      printf ("%-10s %-10s %-12s %-13s %-5d %-8d\n", code[i], mes[i],
              ts[i] ? "Transporte" : "Fretamento",
              loc[i] ? "Interestadual" : "Estadual", day[i], val[i]);

      num++;
    }

  perNtLoc115 = (totLoc1 > 0) ? totLoc115 / totLoc1 * 100
                              : 0; // percentual de nts com day < 15 & loc 1
                                   // de todas as notas loc 1
  avgDayTot = sumTsTot / N; // média de dias de todas as notas, não há operador
                            // ternário porque não há divisão por zero
  avgDayTs0 = (contTs0 > 0) ? sumTs0 / contTs0 : 0;
  avgDayTs1 = (contTs1 > 0) ? sumTs1 / contTs1 : 0;
  avg39 = val39 / 39;
  avg41 = val41 / 41;
  avg43 = val43 / 43;

  puts ("");
  puts ("");
  puts ("");

  printf ("Percentual de nts com duração menor que 15 dias e interestaduais: "
          "%.2f%%\n",
          perNtLoc115);
  printf ("Média de dias de todas as nts: %.2f\n", avgDayTot);
  printf ("Média de dias das nts de tipo 0: %.2f\n", avgDayTs0);
  printf ("Média de dias das nts de tipo 1: %.2f\n", avgDayTs1);
  printf ("Nota com maior valor:\n");
  printf ("%-10s %-10s %-12s %-13s %-5d %-8d\n", codeMaiorV, mesMaiorV,
          tsMaiorV ? "Transporte" : "Fretamento",
          locMaiorV ? "Interestadual" : "Estadual", dayMaiorV, valMaiorV);

  return 0;
}
