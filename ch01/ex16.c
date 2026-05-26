/*
        Revise the main routine of the longest-line program so it will
        correctly print the length of arbitrarily long input lines, and as
        much as possible of the text.
*/

#include <stdio.h>

#define MAXLINE 10

int get_line (char[], int);

int
main (void)
{
  int len;
  int i;
  int max;
  char line[MAXLINE];
  char longest[MAXLINE];

  max = 0;

  while ((len = get_line (line, MAXLINE)) > 0)

    if (len > max)
      {
        max = len;
        for (i = 0; i < MAXLINE - 1 && line[i] != '\0'; i++)
          longest[i] = line[i];
        if (max >= MAXLINE)
          {
            longest[MAXLINE - 2] = '\n';
            longest[MAXLINE - 1] = '\0';
          }

        longest[MAXLINE - 1] = '\0';
      }

  if (max > 0)
    printf ("%s", longest);

  printf ("Length: %d\n", max);

  return 0;
}

int
get_line (char s[], int lim)
{
  int c, i;

  for (i = 0; (c = getchar ()) != EOF && c != '\n'; i++)
    if (i < lim - 1)
      s[i] = c;

  if (c == '\n')
    {
      s[i] = c;
      i++;
    }
  s[i] = '\0';
  return i;
}
