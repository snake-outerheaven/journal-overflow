/*
Write a program to print all input lines that are longer than 80 characters.
*/

#include <stdio.h>

#define MAXLINE 128

int get_line (char[], int);

int
main (void)
{
  char line[MAXLINE] = { 0 };
  int len;

  while ((len = get_line (line, MAXLINE)) > 0)
    {
      if (len > 80)

        printf ("%s", line);
    }

  return 0;
}

int
get_line (char line[], int siz)
{
  int c, i = 0;

  /*siz - 2 is used to ensure that line will always have \n\0 at the end.*/

  for (i = 0; i < (siz - 2) && ((c = getchar ()) != EOF) && c != '\n'; i++)
    line[i] = c;

  if (c == '\n')
    {
      line[i] = '\n';
      line[++i] = '\0';
    }
  else
    line[i] = '\0';

  return i;
}
