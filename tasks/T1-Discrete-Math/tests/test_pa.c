#include <assert.h>

#include "pa.h"

int
main (void)
{
  const int primeiro = 67;
  const int quantidade = 68;
  const int razao = 100;
  const int ultimo = 6767;
  const int soma = 232356;

  assert (pa_termo (primeiro, 1, razao) == primeiro);
  assert (pa_termo (primeiro, 2, razao) == 167);
  assert (pa_termo (primeiro, quantidade, razao) == ultimo);
  assert (pa_soma (primeiro, ultimo, quantidade) == soma);

  return 0;
}
