#include <stdlib.h>
#include <time.h>

#include "utils.h"

void
utils_inicializar_aleatorio (void)
{
  srand ((unsigned int)time (NULL));
}

int
utils_natural_aleatorio (int limite)
{
  if (limite < 1)
    return 1;

  return (rand () % limite) + 1;
}
