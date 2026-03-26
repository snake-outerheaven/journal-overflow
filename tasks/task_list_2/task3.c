// 3)Fazer um programa que apresente quantos números são 
// múltiplos de 7 entre 100 e 500.

#include <locale.h>
#include <stdio.h>

int main()
{
	int i, num, count;

	setlocale(LC_ALL, "pt_BR.UTF-");

	i = 500 - 100 + 1; // i encapsula o número total de itens a serem contados
	num = 100;
	count = 0;

	while(i > 0)
	{
		if(!(num % 7))
		{
			printf("|%d|\n", num);
			count++;
		}

		num++;
		i--;
	}

	printf("Existem %d números divisíveis por 7"
			" entre 100 e 500.\n", count);

	return 0;
}
