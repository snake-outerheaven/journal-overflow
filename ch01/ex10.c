/*
 * Write a program which replaces tabs for \t, backspaces for \b and
 * backslashes as \\
 */

#include <stdio.h>

int
main (void)
{
  int c;

  while ((c = getchar ()) != EOF)
    {
      if (c == '\t')
        printf ("\\t");
      else if (c == '\b')
        printf ("\\b");
      else if (c == '\\')
        printf ("\\\\");
      else
        putchar (c);
    }

  puts ("EOF pressed, end of program.");

  return 0;
}
