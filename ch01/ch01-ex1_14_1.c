#include <stdio.h>


	/*
	 * 	Book example that shows a power function
	 *
	 * 	From part 1.7
	 */


int power(int a, int b);


int main(void) {
	int i;

	for(i = 0; i < 10; i++)
		printf("%d %d %d\n",i,power(2,i),power(-3,i));
	return 0;
}



int power(int base, int n) {
	int i, p;

	p = 1;
	for(i = 0; i < n; i++)
		p = p * base;
	return p;
}
