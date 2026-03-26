// 4)Fazer um programa que receba o intervalo (a, b) e um número c, 
// apresente quantos são os múltiplos de c no intervalo.

#include <locale.h>
#include <stdio.h>

int main()
{
	int a, b, c;
	int temp, count;

	count = 0;

	setlocale(LC_ALL, "pt_BR.UTF-8");

	printf("Digite a: ");
	scanf("%d", &a);

	printf("Digite b: ");
	scanf("%d", &b);

	printf("Digite c: ");
	scanf("%d", &c);

	temp = a + 1;

	while(temp < b)
	{
		if(!(temp % c))
			count++, printf("%d\n", temp);

		temp++;
	}

	printf("Existem %d números divisíveis por %d no intervalo aberto"
			" entre %d e %d.\n",
			count, c, a, b);

	return 0;
}
