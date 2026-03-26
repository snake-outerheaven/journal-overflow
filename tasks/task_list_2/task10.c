// 10)Faça um programa que gere um número inteiro positivo par N
// menor que 100 e imprima todos os números pares de 0 até N em
// ordem crescente.


#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50
#define MIN 0

int main()
{
	int i, n;

	setlocale(LC_ALL, "pt_BR.UTF-8");
	srand(time(0));

	i = 0;
	n = (rand() % (MAX - MIN) + MIN) * 2;

	printf("Número gerado: %d\n", n);

	while(i <= n)
	{
		printf("%d\n", i);
		i += 2;
	}

	return 0;
}
