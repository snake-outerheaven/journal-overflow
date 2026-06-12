#include <stdio.h>

#define MAXLEN 256
#define TABSIZE 4

int get_line (char line[], int max);
int detab (char line[], int siz);

int
main (void)
{
  char line[MAXLEN];

  while (get_line (line, MAXLEN) > 0)
    {
      detab (line, MAXLEN);
    }

  return 0;
}

int
get_line (char line[], int max)
{
  int c, i;

  i = 0;
  while (i < max - 1 && (c = getchar ()) != EOF && c != '\n')
    {
      line[i] = c;
      i++;
    }
  if (c == '\n')
    {
      line[i] = c;
      i++;
    }
  line[i] = '\0';
  return i;
}

int
detab (char line[], int siz)
{
  int i, x;
  int col;
  int spaces;

  col = 0;
  for (i = 0; i < siz && line[i] != '\0'; i++)
    {
      if (line[i] == '\t')
        {
          spaces = TABSIZE - (col % TABSIZE);
          for (x = 0; x < spaces; x++)
            {
              putchar (' ');
              col++;
            }
        }
      else
        {
          putchar (line[i]);
          if (line[i] == '\n')
            {
              col = 0;
            }
          else
            {
              col++;
            }
        }
    }
  return 0;
}
