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
  int interpolados[3];
  int interpolados_decrescentes[2];

  assert (pa_termo (primeiro, 1, razao) == primeiro);
  assert (pa_termo (primeiro, 2, razao) == 167);
  assert (pa_termo (primeiro, quantidade, razao) == ultimo);
  assert (pa_soma (primeiro, ultimo, quantidade) == soma);

  assert (pa_interpolar (10, 30, 3, interpolados) == 1);
  assert (interpolados[0] == 15);
  assert (interpolados[1] == 20);
  assert (interpolados[2] == 25);

  assert (pa_interpolar (20, 5, 2, interpolados_decrescentes) == 1);
  assert (interpolados_decrescentes[0] == 15);
  assert (interpolados_decrescentes[1] == 10);

  assert (pa_interpolar (10, 30, 2, interpolados) == 0);
  assert (pa_interpolar (10, 30, 0, interpolados) == 0);

  return 0;
}
