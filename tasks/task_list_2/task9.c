// 9)Escreva um programa que gere 10 números inteiros entre 0 e 100 
// e escreva o menor e o maior valor .


#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define MIN 0
#define QUANT 10

int main()
{
	size_t i;
	int n, min, max;

	setlocale(LC_ALL, "pt_BR.UTF-8");

	srand(time(0));

	i = 0;
	
	n = min = max = rand() % (MAX - MIN + 1) + MIN; // maior e menor são gerados aqui
							// junto com o primeiro

	i++; // aumenta 1 iteração para o loop dar bom.


	while(i < QUANT)
	{
		n = rand() % (MAX - MIN + 1) + MIN;

		printf("Número gerado: %d\n", n);

		if(n < min)
			min = n;

		if(n > max)
			max = n;

		++i;
	}

	printf("Entre os números gerados, o menor é %d e o maior é %d.\n"
			, min, max);

	return 0;
}
