#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

void skip()
{
	putchar('\n');
	putchar('\n');
}

void quicksort(int *item, int left, int right)
{
	register int i, j;
	int x, y;

	i = left, j = right;
	x = item[(right + left) / 2];

	do
	{
		while(x > item[i] && i < right)
			i++;

		while(x < item[j] && j > left)
			j--;

		if(i <= j)
		{
			y = item[i];
			item[i] = item[j];
			item[j] = y;
			i++, j--;
		}
	} while(i <= j);

	if(left < j)
		quicksort(item, left, j);
	if(right > i)
		quicksort(item, i, right);

}

void quick(int *item, int count)
{
	quicksort(item, 0, count - 1);
}

int main()
{
	int i;
	int array[MAX];

	srand(time(NULL));

	for(i = 0; i < MAX; i++)
	{
		array[i] = rand() % MAX;
	}


	for(i = 0; i < MAX; i++)
		printf("|\t%d\t|\n", array[i]);

	quick(array, MAX);

	for(i = 0; i < 2; i++)
		skip();


	for(i = 0; i < MAX; i++)
		printf("|\t%d\t|\n", array[i]);

	return 0;
}
