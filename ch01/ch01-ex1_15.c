#include <stdio.h>

	/*
	 *	Rewrite exercise 1_3.c with a temperature convertion function.
	 */


float cels(float);


int main() {

	float fahr;

	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;
	fahr = (float)lower;

	while(fahr <= upper) {
		printf("%.0f\t->\t%.2f\n", fahr, cels(fahr));
		fahr += step;
	}
	puts("Done.");
	return 0;
}

float cels(float fahr) {
	return (5.0/9.0) * (fahr - 32.0);
}

