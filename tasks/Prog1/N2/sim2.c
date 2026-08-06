#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 145

#define MAXBUF 35

#define MAXTYPE 3
#define MINTYPE 1

#define MAXLIFE 240
#define MINLIFE 12

#define MAXQUANT 50
#define MINQUANT 0

typedef struct equip_t
{
  char cod[MAXBUF];
  int type;
  float life;
  int quant;
} equip_t;

int
main (void)
{
  // inteiros para loops
  int i, x;

  // vetor de structs, inicializado zerado para assegurar proteção de memória
  equip_t equips[N] = { 0 };

  // variável que guarda o contador iniciando em 5001 para formar o código de
  // cada equipamento
  int cont = 5001;

  // variáveis utilizadas para gerar a média geral da vida útil dos
  // equipamentos
  float sumLife = 0, totLife = N, medLife = 0;

  // variáveis utilizadas para gerar a média da vida útil por tipo de
  // equipamento.

  float sumLife1 = 0, sumLife2 = 0, sumLife3 = 0, totLife1 = 0, totLife2 = 0,
        totLife3 = 0, medLife1, medLife2, medLife3;

  // variáveis utilizadas para gerar o percentual de equipamentos de cada tipo
  // em relação ao total
  float totTypes = N, totType1 = 0, totType2 = 0, totType3 = 0, percType1 = 0,
        percType2 = 0, percType3 = 0;

  // variáveis usadas para calcular o percentual de equipamentos de segurança
  // com vida menor q 3 anos

  float totSeg3 = 0, percSeg3 = 0;

  // variáveis utilizadas para ordenar o vetor de structs, pela quantidade de
  // forma decrescente
  equip_t temp = { 0 };

  srand (time (0));

  setlocale (LC_ALL, "pt_BR.UTF-8");

  printf ("Gerando notas\n");
  printf ("%-12s %-6s %-12s %-10s\n", "Código", "Tipo", "Vida Útil",
          "Quantidade");
  printf ("---------------------------------------------\n");

  for (i = 0; i < N; i++)
    {
      equips[i].life
          = ((float)rand () / RAND_MAX) * (MAXLIFE - MINLIFE) + MINLIFE;
      equips[i].quant = rand () % (MAXQUANT - MINQUANT + 1) + MINQUANT;
      equips[i].type = rand () % (MAXTYPE - MINTYPE + 1) + MINTYPE;

      sumLife += equips[i].life;

      switch (equips[i].type)
        {
        case 1:
          sprintf (equips[i].cod, "ES%d", cont);
          sumLife1 += equips[i].life;
          totLife1++;
          totType1++;

          if (equips[i].life < 36.0)
            totSeg3++;

          break;
        case 2:
          sprintf (equips[i].cod, "FE%d", cont);
          sumLife2 += equips[i].life;
          totLife2++;
          totType2++;
          break;
        case 3:
          sprintf (equips[i].cod, "EE%d", cont);
          sumLife3 += equips[i].life;
          totLife3++;
          totType3++;
          break;
        default:
          puts ("?????");
          break;
        }
      printf ("%-12s %-6d %-12.2f %-10d\n", equips[i].cod, equips[i].type,
              equips[i].life, equips[i].quant);
      cont++;
    }

  for (i = 1; i < N; i++)
    for (x = N - 1; x >= i; x--)
      if (equips[x].quant > equips[x - 1].quant)
        {
          temp = equips[x];
          equips[x] = equips[x - 1];
          equips[x - 1] = temp;
        }

  for (i = 0; i < 2; ++i)
    puts ("");

  medLife = sumLife / totLife;

  medLife1 = (totLife1 > 0) ? (sumLife1 / totLife1) : 0;
  medLife2 = (totLife2 > 0) ? (sumLife2 / totLife2) : 0;
  medLife3 = (totLife3 > 0) ? (sumLife3 / totLife3) : 0;

  percType1 = (totType1 / totTypes) * 100.0f;
  percType2 = (totType2 / totTypes) * 100.0f;
  percType3 = (totType3 / totTypes) * 100.0f;

  percSeg3 = (totType1 > 0) ? ((totSeg3 / totType1) * 100.0f) : 0;

  printf ("--- RELATÓRIO DE INVENTÁRIO OFFSHORE ---\n\n");
  printf ("a) Média geral da vida útil dos equipamentos: %.2f meses\n\n",
          medLife);

  printf ("b) Média da vida útil por tipo de equipamento:\n");
  printf ("   - Segurança (Tipo 1): %.2f meses\n", medLife1);
  printf ("   - Ferramentas Elétricas (Tipo 2): %.2f meses\n", medLife2);
  printf ("   - Elevação (Tipo 3): %.2f meses\n\n", medLife3);

  printf ("c) Percentual de equipamentos de cada tipo:\n");
  printf ("   - Segurança (Tipo 1): %.2f%%\n", percType1);
  printf ("   - Ferramentas Elétricas (Tipo 2): %.2f%%\n", percType2);
  printf ("   - Elevação (Tipo 3): %.2f%%\n\n", percType3);

  printf ("d) Percentual de Equipamentos de Segurança com vida útil < 3 anos: "
          "%.2f%%\n\n",
          percSeg3);

  printf (
      "e) Vetor de equipamentos por quantidade disponível (Decrescente):\n");
  printf ("%-12s %-6s %-12s %-10s\n", "Código", "Tipo", "Vida Útil",
          "Quantidade");
  printf ("---------------------------------------------\n");
  for (i = 0; i < N; i++)
    {
      printf ("%-12s %-6d %-12.2f %-10d\n", equips[i].cod, equips[i].type,
              equips[i].life, equips[i].quant);
    }

  return EXIT_SUCCESS;
}
