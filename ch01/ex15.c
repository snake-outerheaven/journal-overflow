/*
        Rewrite the temperature conversion program of Section 1.2 to use a
        function for conversion.
*/

#include <stdio.h>

double get_fahr (double);

int
main (void)
{
  double fahr, celsius;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  printf ("Celsius\tFahrenheit\n");
  celsius = lower;
  while (celsius <= upper)
    {
      fahr = get_fahr (celsius);
      printf ("%6.2f\t%6.2f\n", celsius, fahr);
      celsius += step;
    }

  return 0;
}

double
get_fahr (double celsius)
{
  return (celsius * 9.0 / 5.0) + 32.0;
}