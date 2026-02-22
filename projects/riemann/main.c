#include "riemann.h"
#include <stddef.h>
#include <stdio.h>

void skip(void)
{
	putchar('\n');
	putchar('\n');
}

double square(double value)
{
	return value * value;
}

double cube(double value)
{
	return value * value * value;
}


int main(void)
{
	size_t steps = 1e10;
	double a = 0.0;
	double b = 10.0;

	MathFunc f1 = square;
	MathFunc f2 = cube;

	double result_1 = 0.0;
	double result_2 = 0.0;

	puts("This is a program that yields integrals using the Riemann algo "
			"in the C programming language.");

	skip();

	printf("Calculating the integrals for x^2 and x^3, on the closed "
			"interval between %.0lf and %.0lf"
			" using %zu steps.\n", a, b, steps);


	skip();


	result_1 = riemann(f1, a, b, steps);
	result_2 = riemann(f2, a, b, steps);

	skip();

	printf("Here are the approximate integrals yielded: %.6lf for x^2 and %.6lf for x^3.\n"
			, result_1, result_2);

	return 0;
}
