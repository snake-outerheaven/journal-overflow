/*
   Write a function reverse(s) that reverses the character string s. Use
   it to write a program that reverses its input a line at a time.
*/

#include <stdio.h>

#define MAXLEN 64

int get_line (char[], int);
int str_len (char[]);
void reverse (char[], int);

int
main (void)
{
  char line[MAXLEN];

  while (get_line (line, MAXLEN) > 0)
    {
      reverse (line, MAXLEN);
      printf ("%s", line);
    }

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
str_len (char inp[])
{
  int i = 0;

  if (!inp)
    return 0;

  while (*inp)
    i++, inp++;

  return i;
}

void
reverse (char str[], int siz)
{
  char temp;
  int j = 0, i = 0;

  if (!str || !siz)
    return;

  j = str_len (str);

  j--;

  if (j >= 0 && str[j] == '\n')
    j--;

  while (j > i)
    {
      temp = str[j];
      str[j] = str[i];
      str[i] = temp;
      i++, j--;
    }
}