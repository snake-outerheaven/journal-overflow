#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define MIN 1
#define MAX_TRIES 99
#define ARR_SIZE(buf) (sizeof (buf) / sizeof (buf[0]))

int
main (void)
{
  char buf[64], *YES[] = { "s", "sim", "y", "yes" };
  int i, x, num, input;
  srand (time (0));
  setlocale (LC_ALL, "pt_BR.UTF-8");

  while (1)
    {
      num = rand () % (MAX - MIN + 1) + MIN;
      for (i = 0; i < MAX_TRIES; ++i)
        {
          printf ("Digite um número entre %d e %d (%d tentativas restantes): ",
                  MIN, MAX, MAX_TRIES - i);
          if (!fgets (buf, sizeof buf, stdin))
            return 0;
          if (sscanf (buf, "%d", &input) != 1)
            {
              printf ("Entrada inválida.\n");
              continue;
            }
          if (input == num)
            {
              printf ("Parabéns — acertou em %d tentativas!\n", i + 1);
              break;
            }
          printf ("O número é %s que %d!\n", input > num ? "menor" : "maior",
                  input);
        }
      printf ("Jogar novamente? (s/n): ");

      if (!fgets (buf, sizeof buf, stdin))
        break;

      for (x = 0; x < ARR_SIZE (YES); ++x)
        if (strcmp (buf, YES[x]) == 0)
          break;
    }

  return 0;
}
