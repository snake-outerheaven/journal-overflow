#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 123
#define NUM_MIN 1550
#define NUM_MAX 1800
#define DAY_MIN 1
#define DAY_MAX 30

/*
 * função macro para obter facilmente o tamanho de um array de qualquer tipo
 * o tipo da função macro é determinado em tempo de compilação
 */
#define arr_siz(arr) sizeof (arr) / sizeof (arr[0])

/*
 *  Declaração de tipo incompĺeto, dá pra fazer encapsulamento colocando
 *  isso em um .h, junto com protótipos da função, e colocando a implementação
 *  em um .c separado.
 */
typedef struct nt_t nt_t;

/*
 * Implementação da struct que representa as notas, é colocada aqui
 * para fim de usar a notação de vetor no protótipo da função de ordenação
 * e os campos diretamente na função principal
 */
struct nt_t
{
  char code[20];
  char month[20];
  int ts;
  int loc;
  int day;
  int val;
};

/*
 * Protótipo da função de ordenação do vetor de notas, em C,
 * matrizes passadas como argumento de funções decaem em ponteiros,
 * sendo essencial passar o tamanho do vetor como argumento de forma
 * a trabalhar bem com os dados.
 */

void bubble_nt (nt_t[], size_t);

int
main ()
{
  // vetor de notas
  nt_t nts[N] = { { 0 } };

  size_t i;

  // número ser gerado
  int num;

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

  setlocale (LC_ALL, "pt_BR.UTF-8");

  srand (time (NULL));

  num = rand () % (NUM_MAX - NUM_MIN + 1) + NUM_MIN;

  for (i = 0; i < N; ++i)
    {
      nts[i].ts = rand () % 2;
      nts[i].loc = rand () % 2;
      nts[i].day = rand () % (DAY_MAX - DAY_MIN + 1) + DAY_MIN;

      if (nts[i].ts)
        {
          nts[i].val = nts[i].day * 450 + 750;
          sumTs1 += nts[i].day;
          contTs1++;
        }

      else
        {
          nts[i].val = nts[i].day * 300 + 500;
          sumTs0 += nts[i].day;
          contTs0++;
        }

      sumTsTot += nts[i].day;

      if (nts[i].loc)
        {
          totLoc1++;

          if (nts[i].day < 15)
            totLoc115++;
        }

      if (i < 39)
        {
          sprintf (nts[i].month, "Setembro");
          val39 += nts[i].val;
        }

      else if (i < 80)
        {
          sprintf (nts[i].month, "Outubro");
          val41 += nts[i].val;
        }

      else
        {
          sprintf (nts[i].month, "Novembro");
          val43 += nts[i].val;
        }

      sprintf (nts[i].code, "NT%d%c", num, nts[i].ts ? 'T' : 'F');

      if (nts[i].val > valCmp)
        {
          valCmp = nts[i].val;
          strcpy (codeMaiorV, nts[i].code);
          strcpy (mesMaiorV, nts[i].month);
          tsMaiorV = nts[i].ts;
          locMaiorV = nts[i].loc;
	  dayMaiorV = nts[i].day;
          valMaiorV = nts[i].val;
        }

      printf ("Nota %zu gerada: ", i + 1);
      printf ("%-10s %-10s %-12s %-13s %-5d %-8d\n", nts[i].code, nts[i].month,
              nts[i].ts ? "Transporte" : "Fretamento",
              nts[i].loc ? "Interestadual" : "Estadual", nts[i].day,
              nts[i].val);

      num++;
    }

  /*
   * lógica de ordenação encapsulada para facilitar a leitura do código
   */

  bubble_nt (nts, arr_siz (nts));

  /*
   * TODO: imprimir vetor após ordenação por valores de nota e
   * fazer relatório de acordo com N1_V2.c
   */

  return 0;
}
