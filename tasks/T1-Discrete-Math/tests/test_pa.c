#include <assert.h>
#include <limits.h>

#include "pa.h"

int
main (void)
{
  const int primeiro = 67;
  const int quantidade = 68;
  const int razao = 100;
  const int ultimo = 6767;
  const int soma = 232356;
  const int iniciais_segunda_ordem[3] = { 1, 2, 4 };
  const int iniciais_terceira_ordem[4] = { 0, 1, 8, 27 };
  int segunda_ordem[8];
  int terceira_ordem[7];
  int interpolados[3];
  int interpolados_decrescentes[2];

  assert (pa_termo (primeiro, 1, razao) == primeiro);
  assert (pa_termo (primeiro, 2, razao) == 167);
  assert (pa_termo (primeiro, quantidade, razao) == ultimo);
  assert (pa_soma (primeiro, ultimo, quantidade) == soma);

  assert (pa_gerar_ordem (iniciais_segunda_ordem, 2, 8, segunda_ordem) == 1);
  assert (segunda_ordem[0] == 1);
  assert (segunda_ordem[1] == 2);
  assert (segunda_ordem[2] == 4);
  assert (segunda_ordem[3] == 7);
  assert (segunda_ordem[4] == 11);
  assert (segunda_ordem[5] == 16);
  assert (segunda_ordem[6] == 22);
  assert (segunda_ordem[7] == 29);

  assert (pa_gerar_ordem (iniciais_terceira_ordem, 3, 7, terceira_ordem) == 1);
  assert (terceira_ordem[4] == 64);
  assert (terceira_ordem[5] == 125);
  assert (terceira_ordem[6] == 216);
  assert (pa_gerar_ordem (iniciais_segunda_ordem, 2, 2, segunda_ordem) == 0);
  assert (pa_gerar_ordem (iniciais_segunda_ordem, 0, 8, segunda_ordem) == 0);

  {
    const int iniciais_overflow[2] = { INT_MAX, INT_MIN };
    assert (pa_gerar_ordem (iniciais_overflow, 1, 3, segunda_ordem) == 0);
  }

  assert (pa_interpolar (10, 30, 3, interpolados) == 1);
  assert (interpolados[0] == 15);
  assert (interpolados[1] == 20);
  assert (interpolados[2] == 25);

  assert (pa_interpolar (20, 5, 2, interpolados_decrescentes) == 1);
  assert (interpolados_decrescentes[0] == 15);
  assert (interpolados_decrescentes[1] == 10);

  assert (pa_interpolar (10, 30, 2, interpolados) == 0);
  assert (pa_interpolar (10, 30, 0, interpolados) == 0);
  assert (pa_interpolar (INT_MAX, INT_MIN, 2, interpolados) == 1);
  assert (interpolados[0] == 715827882);
  assert (interpolados[1] == -715827883);

  return 0;
}
