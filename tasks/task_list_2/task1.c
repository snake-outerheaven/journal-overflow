// 1) Fazer um programa que apresente uma sequência de números
//    entre 20 e 50 inclusive.

#include <stdio.h>

int main()
{
	int i, num;

	i = 0;
	num = 20;

	while(i <= 30)
	{
		printf("|%d|\n", num);
		num++, i++;
	}

	return 0;
}

