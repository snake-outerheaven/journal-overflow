/*
Write a program entab that replaces strings of blanks by the minimum number of
tabs and blanks to achieve the same spacing. Use the same tab stops as for
detab. When either a tab or a single blank would suffice to reach a tab stop,
which should be given preference?
*/

#include <stdio.h>

#define MAXLEN 128
#define TABSIZE 8

int get_line (char[], int);
int entab (char[]);

int
main (void)
{
  char ln[MAXLEN];

  while (get_line (ln, MAXLEN) > 0)
    entab (ln);

  return 0;
}

int
get_line (char ln[], int max)
{
  int c, i;

  c = i = 0;

  while (i < max - 1 && (c = getchar ()) != EOF && c != '\n')
    {
      ln[i] = c;
      i++;
    }
  if (c == '\n')
    {
      ln[i] = c;
      i++;
    }
  ln[i] = '\0';
  return i;
}

int
entab (char ln[])
{
  int i, pos = 0;
  int spaceCount = 0;

  for (i = 0; ln[i] != '\0'; ++i)
    {
      if (ln[i] == ' ')
        {
          spaceCount++;
          pos++;

          if (pos % TABSIZE == 0)
            {
              putchar ('\t');
              spaceCount = 0;
            }
        }
      else
        {
          while (spaceCount > 0)
            {
              putchar (' ');
              spaceCount--;
            }
          putchar (ln[i]);
          if (ln[i] == '\n')
            pos = 0;
          else
            pos++;
        }
    }

  return 0;
}