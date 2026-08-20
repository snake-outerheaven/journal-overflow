#include <assert.h>
#include <stdio.h>

#include "pa.h"
#include "utils.h"

int
main (void)
{
  int primeiro = 2;
  int quantidade = 5;
  int razao = 3;
  int ultimo = pa_termo (primeiro, quantidade, razao);

  utils_inicializar_aleatorio ();
  int aleatorio = utils_natural_aleatorio (10);

  assert (ultimo == 14);
  assert (pa_soma (primeiro, ultimo, quantidade) == 40);
  assert (aleatorio >= 1 && aleatorio <= 10);

  printf ("All clear!\n");

  return 0;
}
