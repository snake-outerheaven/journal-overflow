/*
 * Write a program to copy its input to its output, replacing each string of
 * one or more blanks by a single blank.
 */

#include <stdio.h>

int
main (void)
{
  int c;
  int state;

  while ((c = getchar ()) != EOF)
    {

      if (c == ' ')
	{
	  if (state)
	    continue;
          putchar (' ');
	  state = 1;
        }

      else
	{
	  putchar (c);
	  state = 0;
        }

    }
  return 0;
}

