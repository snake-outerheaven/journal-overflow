// 6)Faça um programa que gere aleatoriamente dez números entre 
// 20 e 50 e apresente a soma destes números.


#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 20
#define MAX 50

int main()
{
	size_t i;
	int num[10] = {0};
	int sum;

	i = sum = 0;

	setlocale(LC_ALL, "pt_BR.UTF-8");

	srand(time(0));

	while(i < 10)
	{
		num[i] = rand() % (MAX - MIN + 1) + MIN;
		printf("Número gerado: %d\n", num[i]);
		sum += num[i];
		i++;
	}

	printf("A soma de todos os números é igual a: %d.\n", sum);

	return 0;
}
