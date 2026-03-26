// 2)Fazer um programa que apresente todos os múltiplos de 4 entre 1 
// e 100 inclusive.

#include <stdio.h>

int main()
{
	int i, num;

	num = i = 1;

	while(i <= 100)
	{
		if(!(num % 4))
			printf("|%d|\n", num);

		num++, i++;
	}

	return 0;
}
