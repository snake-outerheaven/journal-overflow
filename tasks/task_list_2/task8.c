// 8)Faça um programa que gere aleatoriamente 5 números entre 0 e 
// 10 e seus respectivos pesos (1, 2 ou 3) ao final calcule sua média ponderada.

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXNUM 10
#define MINNUM 0

#define QUANT 5

#define MAXWEI 3
#define MINWEI 1

int main()
{
	size_t i;
	int n[QUANT], p[QUANT];
	float sum1, sum2;
	float avg;

	setlocale(LC_ALL, "pt_BR.UTF-8");

	srand(time(0));

	i = sum1 = sum2 = 0;

	
	while(i < QUANT)
	{
		n[i] = rand() % (MAXNUM - MINNUM + 1) + MINNUM;
		p[i] = rand() % (MAXWEI - MINWEI + 1) + MINWEI;

		printf("Número gerado: %d\nPeso gerado: %d\n",
				n[i], p[i]);

		sum1 += n[i] * p[i];
		sum2 += p[i];
		
		++i;
	}

	avg = sum1 / sum2;

	printf("A média ponderada dos %d números é:"
			" %.2f.\n", QUANT, avg);

	return 0;
}
