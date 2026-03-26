// 5)Fazer um programa que apresente os N primeiros números da série de Fibonacci (0-1-1-2-3-5...)


#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	size_t i, target;
	int a, b, c;

	setlocale(LC_ALL, "pt_BR.UTF-8");

	srand(time(0));

	a = 0;
	b = 1;

	target = rand() % (47 - 10 + 1) + 10;

	printf("Alvo gerado -> %ld.\n", target);

	for(i = 0; i < target; ++i)
	{
		c = a + b;
		a = b;
		b = c;

		printf("%d\n", c);
	}

	return 0;
}

