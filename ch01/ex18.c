/*
   Write a program to remove trailing blanks and tabs from each line of
   input, and to delete entirely blank lines.
*/

#include <stdio.h>

#define MAXLINE 64

int get_line (char ln[], int siz);
int trim (char[]);

int
main (void)
{
  char ln[MAXLINE] = { 0 };

  while (get_line (ln, MAXLINE) > 0)
    if (trim (ln) > 0)
      printf ("%s", ln);

  return 0;
}

int
get_line (char ln[], int siz)
{
  int l, i;

  for (i = 0; i < siz - 2 && (((l = getchar ()) != EOF)) && l != '\n'; i++)
    ln[i] = l;

  if (l == '\n')
    {
      ln[i] = l;
      ln[++i] = '\0';
    }
  else
    ln[i] = '\0';

  return i;
}

int
trim (char s[])
{
  int i;

  for (i = 0; s[i] != '\0'; i++)
    ;

  i--; /* remove \0*/

  while (i >= 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
    i--;

  if (i < 0)
    return 0;

  s[i + 1] = '\n';
  s[i + 2] = '\0';

  return i + 2;
}