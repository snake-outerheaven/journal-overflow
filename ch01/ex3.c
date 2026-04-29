#include <stdio.h>

/*
 *  Modify the temperature conversion program to print a heading above the table.
 */

int
main(void)
{
  int fahr, celsius;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  fahr = lower;

  printf("Celsius\tFahrenheit\n");

  while (fahr <= upper)
    {
      celsius = 5 * (fahr - 32) / 9; /* this is done to force proper integer division */
      printf("%d\t%d\n", celsius, fahr);
      fahr += step;
    }
  return 0;
}

