#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "pa.h"

static void
limpar_entrada (void)
{
  int caractere;

  do
    caractere = getchar ();
  while (caractere != '\n' && caractere != EOF);
}

static int
ler_inteiro (const char *mensagem, int *valor)
{
  printf ("%s", mensagem);
  if (scanf ("%d", valor) != 1)
    {
      limpar_entrada ();
      printf ("Entrada invalida.\n");
      return 0;
    }

  limpar_entrada ();
  return 1;
}

static void
executar_termo (void)
{
  int primeiro;
  int indice;
  int razao;

  if (!ler_inteiro ("Primeiro termo (a1): ", &primeiro)
      || !ler_inteiro ("Indice do termo (n): ", &indice)
      || !ler_inteiro ("Razao: ", &razao))
    return;

  if (indice < 1)
    {
      printf ("O indice n deve ser positivo.\n");
      return;
    }

  printf ("Enesimo termo: %d\n", pa_termo (primeiro, indice, razao));
}

static void
executar_soma (void)
{
  int primeiro;
  int ultimo;
  int quantidade;

  if (!ler_inteiro ("Primeiro termo: ", &primeiro)
      || !ler_inteiro ("Ultimo termo: ", &ultimo)
      || !ler_inteiro ("Quantidade de termos: ", &quantidade))
    return;

  printf ("Soma: %d\n", pa_soma (primeiro, ultimo, quantidade));
}

static void
executar_interpolacao (void)
{
  int primeiro;
  int ultimo;
  int quantidade;
  int *interpolados;

  if (!ler_inteiro ("Primeiro termo: ", &primeiro)
      || !ler_inteiro ("Ultimo termo: ", &ultimo)
      || !ler_inteiro ("Quantidade de termos a interpolar: ", &quantidade))
    return;

  if (quantidade < 1)
    {
      printf ("A quantidade deve ser positiva.\n");
      return;
    }

  interpolados = malloc ((size_t)quantidade * sizeof (*interpolados));
  if (interpolados == NULL)
    {
      printf ("Nao foi possivel alocar memoria.\n");
      return;
    }

  if (!pa_interpolar (primeiro, ultimo, quantidade, interpolados))
    printf ("Nao e possivel interpolar esses termos.\n");
  else
    {
      printf ("Termos interpolados:");
      for (int indice = 0; indice < quantidade; indice++)
        printf (" %d", interpolados[indice]);
      printf ("\n");
    }

  free (interpolados);
}

static void
executar_ordem (void)
{
  int ordem;
  int quantidade;
  int *iniciais;
  int *resultado;

  if (!ler_inteiro ("Ordem da P.A.: ", &ordem)
      || !ler_inteiro ("Quantidade total de termos: ", &quantidade))
    return;

  if (ordem < 1 || quantidade < 1 || ordem >= quantidade)
    {
      printf ("A quantidade deve ser maior que a ordem.\n");
      return;
    }

  iniciais = malloc ((size_t)(ordem + 1) * sizeof (*iniciais));
  resultado = malloc ((size_t)quantidade * sizeof (*resultado));
  if (iniciais == NULL || resultado == NULL)
    {
      printf ("Nao foi possivel alocar memoria.\n");
      free (iniciais);
      free (resultado);
      return;
    }

  printf ("Digite os %d termos iniciais.\n", ordem + 1);
  for (int indice = 0; indice <= ordem; indice++)
    if (!ler_inteiro ("Termo: ", &iniciais[indice]))
      {
        free (iniciais);
        free (resultado);
        return;
      }

  if (pa_gerar_ordem (iniciais, ordem, quantidade, resultado))
    {
      printf ("Progressao:");
      for (int indice = 0; indice < quantidade; indice++)
        printf (" %d", resultado[indice]);
      printf ("\n");
    }
  else
    printf ("Nao foi possivel gerar a progressao: overflow ou parametros "
            "invalidos.\n");

  free (iniciais);
  free (resultado);
}

static void
exibir_menu (void)
{
  printf ("\n=== Progressao Aritmetica ===\n");
  printf ("1. Calcular o enesimo termo\n");
  printf ("2. Calcular a soma dos termos\n");
  printf ("3. Interpolar termos\n");
  printf ("4. Gerar P.A. de ordem n\n");
  printf ("0. Sair\n");
}

int
menu_executar (void)
{
  int opcao;

  for (;;)
    {
      exibir_menu ();
      if (!ler_inteiro ("Opcao: ", &opcao))
        continue;

      switch (opcao)
        {
        case 0:
          return 0;
        case 1:
          executar_termo ();
          break;
        case 2:
          executar_soma ();
          break;
        case 3:
          executar_interpolacao ();
          break;
        case 4:
          executar_ordem ();
          break;
        default:
          printf ("Opcao invalida.\n");
          break;
        }
    }
}
