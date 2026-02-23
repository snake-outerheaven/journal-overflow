#include "derivative.h"
#include <stdio.h>
#include <unistd.h>

void skip(void)
{
	putchar('\n');
	putchar('\n');
}

static __inline__ double square(double x)
{
	return (x * x);
}

static __inline__ double cube(double x)
{
	return (x * x * x);
}

int main(void)
{
	double x = 2.0;
	double result_1;
	double result_2;

	MathFunc fx = square;
	MathFunc gx = cube;


	puts("This is a program that yields derivatives using the Finite"
			" difference algo in the C programming language.");

	skip();

	printf("Calculating the derivative for x^2 when x ="
			" %.2lf.\n", x);

	result_1 = derivative(fx, x, DX);
	result_2 = derivative(gx, x, DX);

	skip();

	printf("Here are the approximate derivatives yielded: %.6lf for x^2 and %.6lf for x^3.\n"
			, result_1, result_2);

	return 0;
}
