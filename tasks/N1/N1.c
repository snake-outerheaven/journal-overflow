#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 123
#define NUM_MIN 1550
#define NUM_MAX 1800
#define DAY_MAX 30
#define DAY_MIN 1

int main()
{
  size_t cont = 0;

  // dados principais
  int codenum, ts, loc, val, day;
  char code[20], mes[20];

  char codeMaiorV[20], mesMaiorV[20];
  int tsMaiorV = 0, locMaiorV = 0, valMaiorV = -1, dayMaiorV = 0,
    valMaiorVS = 0; // valMaiorV setado para -1 pois é um valor coringa útil
  // para comparações entre iterações

  // salvando as menores notas
  char codeMenorV[20], mesMenorV[20];
  int tsMenorV = 0, locMenorV = 0, valMenorV = 100000, dayMenorV = 0,
    valMenorVS = 0;

  int sumDiasEstadual = 0, sumDiasInterestadual = 0;

  float totLoc115 = 0, tot15 = 0;
  float contTs1 = 0, contTs0 = 0;
  float sumTs1 = 0, sumTs0 = 0, sumTsTot = 0;

  float val39 = 0, val41 = 0, val43 = 0;
  float avg39, avg41, avg43;

  float percNt15Int, avgDayTot, avgDayTs1, avgDayTs0;

  setlocale(LC_ALL, "pt_BR.UTF-8");
  // configurando locale do executável, pois o Windows coloca a pagina de
  // código sem unicode.
  srand(time(0));
  // inicializando gerador de números aleatórios

  codenum = rand() % (NUM_MAX - NUM_MIN + 1) + NUM_MIN;

  puts("Código\t\tMês\t\tTipo\t\tLocal\t\tDias\t\tValor\t\t");

  while (cont < N)
    {
      ts = rand() % 2;
      loc = rand() % 2;
      day = rand() % (DAY_MAX - DAY_MIN + 1) + DAY_MIN;

      sprintf(code, "NT%d%c", codenum,
	      ts ? 'T' : 'F'); // geração do código de acordo com ts.

      if (ts)
	val = day * 450 + 750;
      else
	val = day * 300 + 500;

      if (cont < 39)
        {
	  sprintf(mes, "Setembro");
	  val39 += val;
        }
      else if (cont < 80)
        {
	  sprintf(mes, "Outubro");
	  val41 += val;
        }
      else
        {
	  sprintf(mes, "Novembro");
	  val43 += val;
        }

      if (val > valMaiorV)
        {
	  valMaiorV = val; // valor que é comparado a cada loop
	  strcpy(codeMaiorV, code);
	  strcpy(mesMaiorV, mes);
	  tsMaiorV = ts;
	  locMaiorV = loc;
	  dayMaiorV = day;
	  valMaiorVS = val; // valor que é salvo em cada iteração para ser
	  // imprimido no final.
        }

      if(val < valMenorV)
	{
	  valMenorV = val; // salva menor valor.
	  strcpy(codeMenorV, code);
	  strcpy(mesMenorV, mes);
	  tsMenorV = ts;
	  locMenorV = loc;
	  dayMenorV = day;
	  valMenorVS = val;
	}

      if (ts)
        {
	  sumTs1 += day; // acumulo total de dias de ts 1
	  contTs1++;     // conto total de nts de tipo 1
        }

      else
        {
	  sumTs0 += day; // acumulo total de dias de ts 0
	  contTs0++;     // conto total  de nts de tipo 0
        }

      sumTsTot += day;

    
      if (day < 15)
        {
	  tot15++;

	  if(loc) // nova contagem, agora certo.
	    totLoc115++;
	}

      if(!loc)
	sumDiasEstadual += day;
      else
	sumDiasInterestadual += day;

      printf("%s\t\t%s\t\t%s\t\t%s\t\t%d\t\t%d\n", code, mes,
	     ts ? "Transporte" : "Fretamento",
	     loc ? "Interestadual" : "Estadual", day, val);

      cont++, codenum++;
    }

  percNt15Int = totLoc115 / tot15 * 100; // percentual de loc 1 com day < 15 entre todas as notas com dias < 15
  avgDayTot = sumTsTot / N;     // média de dias de todas as notas
  avgDayTs0 = sumTs0 / contTs0; // media de dias de ts 0
  avgDayTs1 = sumTs1 / contTs1; // media de dias de ts 1
  avg39 = val39 / 39;           // média dos valores das 39 iniciais
  avg41 = val41 / 41;        // média dos valores das 2 notas com mes outubro.
  avg43 = val43 / 43; // total menos as 41 iniciais

  puts("");
  puts("");
  puts("");

  printf("Percentual de nts com duração menor q 15 dias e interestaduais: "
	 "%.2f%%\n",
	 percNt15Int);
  printf("Total de notas com dias menores que 15: %.2f\n", tot15);
  printf("Média de dias de todas as nts: %.2f\n", avgDayTot);
  printf("Média de dias das nts de tipo 0: %.2f\n", avgDayTs0);
  printf("Média de dias das nts de tipo 1: %.2f\n", avgDayTs1);
  printf("Nota com maior valor:\n");
  puts("Código\t\tMês\t\tTipo\t\tLocal\t\tDias\t\tValor\t\t");
  printf("%s\t\t%s\t\t%s\t\t%s\t\t%d\t\t%d\n", codeMaiorV, mesMaiorV,
	 tsMaiorV ? "Transporte" : "Fretamento",
	 locMaiorV ? "Interestadual" : "Estadual", dayMaiorV, valMaiorVS);

  printf("Nota com menor valor:\n");
  puts("Código\t\tMês\t\tTipo\t\tLocal\t\tDias\t\tValor\t\t");
  printf("%s\t\t%s\t\t%s\t\t%s\t\t%d\t\t%d\n", codeMenorV, mesMenorV,
	 tsMenorV ? "Transporte" : "Fretamento",
	 locMenorV ? "Interestadual" : "Estadual", dayMenorV, valMenorVS);

  printf("Total de dias em serviços estaduais: %d\n", sumDiasEstadual);
  printf("Total de dias em serviços interestaduais: %d\n", sumDiasInterestadual);
  
  printf("Valor médio de nts em Setembro: %.2f\n", avg39);
  printf("Valor médio de nts em Outubro: %.2f\n", avg41);
  printf("Valor médio de nts em novembro: %.2f\n", avg43);

  return 0;
}
