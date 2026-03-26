// 7)Gere aleatoriamente 30 números entre -10 e 30, em seguida
// apresente a sua média.


#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 30
#define MIN (-10)
#define QUANT 30

int main()
{
	size_t i;
	int num[QUANT] = {0};
	float sum ,avg;

	i = sum = 0;

	setlocale(LC_ALL, "pt_BR.UTF-8");
	
	srand(time(0));

	while(i < QUANT)
	{
		num[i] = rand() % (MAX - MIN) + MIN;
		printf("Número gerado: %d\n", num[i]);
		sum += num[i];
		++i;
	}

	// calcular média e apresentar
	
	avg = sum / QUANT;

	printf("A média dos %d números gerados entre %d e %d"
			" é %.2f.\n", QUANT, MIN, MAX, avg);

	return 0;
}
