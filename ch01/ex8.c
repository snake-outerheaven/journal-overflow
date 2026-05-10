/*
 * Write a program to count blanks, tabs, and newlines.
 */

#include <stdio.h>

int
main (void)
{
  int nlc, tbc, bc;
  int c;

  nlc = tbc = bc = 0;

  while ((c = getchar ()) != EOF)
    {
      if (c == '\n')
        nlc++;
      if (c == '\t')
        tbc++;
      if (c == ' ')
        bc++;
      putchar (c);
    }

  printf ("Newline count: %d\tTabulation count: %d\tBlank count: %d\n", nlc,
          tbc, bc);
  return 0;
}
