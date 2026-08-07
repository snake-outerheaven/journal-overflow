#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define MIN 1
#define MAX_TRIES 40

int
main (void)
{
  int num, i, input;

  srand (time (0));
  setlocale (LC_ALL, "pt_BR");

  num = rand () % (MAX - MIN + 1) + MIN;

  for (i = 0; i < MAX_TRIES; i++)
    {
      printf ("Por favor, digite um número entre %d e %d, você tem %d "
              "tentativas: ",
              MIN, MAX, MAX_TRIES - i);
      scanf ("%d", &input);
      if (input == num)
        {
          printf ("Parabens, você acertou o número com %d tentativas!\n",
                  i + 1);
          return 0;
        }
      else if (input > num)
        {
          printf ("O número secreto é menor que %d!\n", input);
          continue;
        }
      else if (input < num)
        {
          printf ("O número secreto é maior que %d!\n", input);
          continue;
        }
    }
  if (input != num)
    printf ("O número era %d! Mais sorte na próxima vez!\n", num), main ();

  return 0;
}
