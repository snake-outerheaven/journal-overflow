#include <stddef.h>

#include "pa.h"

int
pa_termo (int a1, int n, int r)
{
  return a1 + (n - 1) * r;
}

int
pa_soma (int a1, int an, int n)
{
  return ((an + a1) * n) / 2;
}

int
pa_interpolar (int primeiro, int ultimo, int k, int interpolados[])
{
  int quantidade_termos = k + 1;
  int diferenca;
  int razao;

  if (k < 1 || interpolados == NULL)
    return 0;

  diferenca = ultimo - primeiro;
  if (diferenca % quantidade_termos != 0)
    return 0;

  razao = diferenca / quantidade_termos;
  for (int indice = 0; indice < k; indice++)
    interpolados[indice] = primeiro + (indice + 1) * razao;

  return 1;
}
