/*
 * Write a program that prints its input one word per line.
 */

#define OUT 1
#define IN 0

#include <stdio.h>

int
main (void)
{
  int c;
  int state = IN;

  while ((c = getchar ()) != EOF)
    {
      if (c == '\n' || c == ' ' || c == '\t')
        {
          if (state == OUT)
	    continue;
	  putchar('\n');
          state = OUT;
        }
      else
        {
	  putchar(c);
	  state = IN;
        }
    }

  return 0;
}

