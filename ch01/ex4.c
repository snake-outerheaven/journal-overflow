#include <stdio.h>

/*
 * Write a program to print the corresponding Celsius to Fahrenheit table.
 */

int
main(void)
{
  int fahr, celsius;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  celsius = lower;


  printf("|\tCelsius\tFahrenheit\t|\n");

  while (celsius <= upper)
    {
      fahr = 9 * (celsius + 32) / 5;
      printf("|\t%d\t%d\t|\n", celsius, fahr);
      celsius += step;
    }

  return 0;
}
