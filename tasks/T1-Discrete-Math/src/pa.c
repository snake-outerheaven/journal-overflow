#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "pa.h"

static int
somar_int64 (int64_t primeiro, int64_t segundo, int64_t *resultado)
{
  if ((segundo > 0 && primeiro > INT64_MAX - segundo)
      || (segundo < 0 && primeiro < INT64_MIN - segundo))
    return 0;

  *resultado = primeiro + segundo;
  return 1;
}

static int
subtrair_int64 (int64_t primeiro, int64_t segundo, int64_t *resultado)
{
  if ((segundo < 0 && primeiro > INT64_MAX + segundo)
      || (segundo > 0 && primeiro < INT64_MIN + segundo))
    return 0;

  *resultado = primeiro - segundo;
  return 1;
}

int
pa_termo (int a1, int n, int r)
{
  int64_t resultado = (int64_t)a1 + ((int64_t)n - 1) * r;

  if (resultado < INT_MIN || resultado > INT_MAX)
    return 0;

  return (int)resultado;
}

int
pa_soma (int a1, int an, int n)
{
  int64_t resultado = ((int64_t)an + a1) * n / 2;

  if (resultado < INT_MIN || resultado > INT_MAX)
    return 0;

  return (int)resultado;
}

int
pa_interpolar (int primeiro, int ultimo, int k, int interpolados[])
{
  int64_t quantidade_termos;
  int64_t diferenca;
  int64_t razao;

  if (k < 1 || interpolados == NULL)
    return 0;

  quantidade_termos = (int64_t)k + 1;
  diferenca = (int64_t)ultimo - primeiro;
  if (diferenca % quantidade_termos != 0)
    return 0;

  razao = diferenca / quantidade_termos;
  for (int indice = 0; indice < k; indice++)
    {
      int64_t valor = (int64_t)primeiro + (indice + 1) * razao;
      if (valor < INT_MIN || valor > INT_MAX)
        return 0;
      interpolados[indice] = (int)valor;
    }

  return 1;
}

int
pa_gerar_ordem (const int iniciais[], int ordem, int quantidade,
                int resultado[])
{
  int64_t *diferencas;
  int64_t *trabalho;
  int64_t *proxima;

  if (iniciais == NULL || resultado == NULL || ordem < 1 || quantidade < 1
      || ordem >= quantidade)
    return 0;

  diferencas = malloc ((size_t)(ordem + 1) * sizeof (*diferencas));
  trabalho = malloc ((size_t)(ordem + 1) * sizeof (*trabalho));
  proxima = malloc ((size_t)(ordem + 1) * sizeof (*proxima));
  if (diferencas == NULL || trabalho == NULL || proxima == NULL)
    {
      free (diferencas);
      free (trabalho);
      free (proxima);
      return 0;
    }

  for (int indice = 0; indice <= ordem; indice++)
    {
      trabalho[indice] = iniciais[indice];
      resultado[indice] = iniciais[indice];
    }

  diferencas[0] = iniciais[ordem];
  for (int nivel = 1; nivel <= ordem; nivel++)
    {
      for (int indice = 0; indice <= ordem - nivel; indice++)
        if (!subtrair_int64 (trabalho[indice + 1], trabalho[indice],
                             &proxima[indice]))
          {
            free (diferencas);
            free (trabalho);
            free (proxima);
            return 0;
          }
      diferencas[nivel] = proxima[ordem - nivel];
      {
        int64_t *temporario = trabalho;
        trabalho = proxima;
        proxima = temporario;
      }
    }

  for (int indice = ordem + 1; indice < quantidade; indice++)
    {
      for (int nivel = ordem - 1; nivel >= 1; nivel--)
        if (!somar_int64 (diferencas[nivel], diferencas[nivel + 1],
                          &diferencas[nivel]))
          {
            free (diferencas);
            free (trabalho);
            free (proxima);
            return 0;
          }
      if (!somar_int64 (diferencas[0], diferencas[1], &diferencas[0]))
        {
          free (diferencas);
          free (trabalho);
          free (proxima);
          return 0;
        }
      if (diferencas[0] < INT_MIN || diferencas[0] > INT_MAX)
        {
          free (diferencas);
          return 0;
        }
      resultado[indice] = (int)diferencas[0];
    }

  free (diferencas);
  free (trabalho);
  free (proxima);

  return 1;
}
