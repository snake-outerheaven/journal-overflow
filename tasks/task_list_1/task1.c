// 1 - Fazer um programa que receba três valores e verifique se estes podem ser os lados de um triângulo.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 80

#define MIN 0

int main()
{
	int lados[3];
	size_t i;

	srand(time(NULL));

	for(i = 0; i < 3; i++)
		lados[i] = rand() % (MAX - MIN + 1) + MIN;


	if(lados[0] < lados[1] + lados[2] && lados[1] < lados[0] + lados[2]
			&& lados[2] < lados[1] + lados[0])

		printf("É possível construir um triângulo com os lados"
				" %d, %d, %d.\n", lados[0], lados[1], lados[2]);

	else
		printf("Não é possível construir um triângulo com os lados %d, %d, %d.\n"
				, lados[0], lados[1], lados[2]);

	return 0;
}
