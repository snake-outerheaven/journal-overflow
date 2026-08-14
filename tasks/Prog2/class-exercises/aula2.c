#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

/*
	jogo de bingo em C, exercício da revisão.
*/

int
main (void)
{
	int cartela[100], i, x;
	int num = 0;
	int inf = 1;
	int sup = 100;
	int achei = 0;
	setlocale (LC_ALL, "pt_BR.UTF-8");
	srand (time (0));


        num = (rand () % (sup - inf + 1)) + inf;
	cartela[0] = num;
	printf ("%d ", cartela[0]);


	for (i = 1; i < 100 && !achei; i++)
	 {

        	num = (rand () % (sup - inf + 1)) + inf;

		for (x = (i - 1); x > 0 && !achei; x--)
			if (num == cartela[x])
				achei = 1;

		if (!achei)
		 {
			cartela[i] = num;
			printf ("%d ", num);
		 }
		else
			printf ("\nO valor %d foi encontrado na posição %d\n", num, x + 1);
	 }

	for (x = 0; x < i - 1; x++)
	 {
		if ((x % 10) == 0)
			printf ("\n");
                printf ("%d\t", cartela[x]);
	 }


	return 0;
}
