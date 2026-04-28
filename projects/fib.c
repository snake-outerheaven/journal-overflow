#include <stdio.h>
#include <stdlib.h>


int
main(int argc, char *argv[])
{
  size_t i;
  unsigned long a = 1, b = 1, prox;
  int n;


  if (argc < 2)
    {
      printf("Use: %s (iteration number)\n", argv[0]);
      return EXIT_FAILURE;
    }

  n = atoi(argv[1]); // converte argumento de linha de comando

  if (n <= 0)
    {
      printf("Please insert a arg bigger than 0.\n");
      return EXIT_FAILURE;
    }

  for(i = 0; i < (size_t)n; ++i)
    {
      printf("%lu ", a);
      prox = a + b;
      a = b;
      b = prox;
    }

  putchar('\n');
  
  return EXIT_SUCCESS;
}
