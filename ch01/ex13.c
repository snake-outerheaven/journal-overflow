/*
 * Write a program to print a histogram of the lengths of words in its input.
 *
 * It is easy to draw the histogram with the bars horizontal; vertical orientation is more challenging.
 */

#include <stddef.h>
#include <stdio.h>

#define MAX 32UL

#define OUT 0
#define IN 1

int
main (void)
{
  size_t x, y;
  size_t hist[MAX] = { 0 }; /* it carries the times * will be printed. */
  size_t sizec = 0; /* count until MAX, wrapping around max to 0 (kinda what happens on type overflow) */
  int c;
  int state = OUT;



  while ((c = getchar ()) != EOF)
    {
      if (c == '\n' || c == '\t' || c == ' ')
        {
          if (state == IN)
            hist[(sizec - 1) % MAX]++;
          state = OUT;
          sizec = 0;
        }
      else
        {
          state = IN;
          sizec++;
	}
    }

  for (x = 0; x < MAX; x++)
    {
      printf("Tamanho %lu: ", x+1);
      for (y = 0; y < hist[x]; y++)
        printf ("* ");
      printf("\n");
    }
    
  return 0;
}
