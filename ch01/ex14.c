/*
 * write a program to show a histogram of different characters on the input
 */

#include <stddef.h>
#include <stdio.h>

#define ARR_SIZE(ARR) sizeof(ARR) / sizeof(ARR[0])

int
main (void)
{
  size_t x, y;

  size_t ndigits[10] = {0};
  size_t letters[52] = {0};
  int c;

  while ((c = getchar ()) != EOF)
    {

      if (c >= '0' && c <= '9')
        ndigits[c - '0']++;

      if (c >= 'a' && c <= 'z')
        letters[c - 'a']++;

      if (c >= 'A' && c <= 'Z')
        letters[(c - 'A') + 26]++;

      putchar (c);
    }

  for (x = 0; x < ARR_SIZE (ndigits); x++)
    {
      printf("digit %lu: ", x);
      for (y = 0; y < ndigits[x]; ++y)
        printf ("* ");
      printf("\n");
    }

  for (x = 0; x < 26; x++)
    {
      printf("letter %c: ", (int)x + 'a');
      for (y = 0; y < letters[x]; ++y)
        printf ("* ");
      printf("\n");
    }

  for (x = x; x < 52; x++)
    {
      printf("letter %c: ", (int)(x - 26) + 'A');
      for (y = 0; y < letters[x]; ++y)
        printf ("* ");
      printf("\n");
    }

  return 0;
}
