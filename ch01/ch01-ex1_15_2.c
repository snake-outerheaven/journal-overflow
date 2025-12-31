#include <stdio.h>

	/*
	 * Repeating exercise to print input to output
	 */

int main()
{
	int c;

	for(;(c = getchar()) != EOF;)
		putchar(c);
	return 0;
}
