/*
  Crie um programa em C que tenha as seguintes funcionalidades::
        a) Calcule o enesimo termo de uma P.A.:
        b) Calcule a soma de n termos de uma P.A.:
        c) interpole k numeros em uma P.A.:
        d) Gere uma P.A. de segunda ordem a partir de uma sequencia de 8
  termos. Use um vetor para armazenas a sequencia original. O programa deve ter
  um menu onde o usuario escolha o que quer fazer. O programa podera ter
        funcoes para cada funcionalidade. Envie o arquivo .c no AVA
*/

/* Portado para C89 (ANSI C): todas as declaracoes foram movidas para o
   topo de cada bloco, os "for" nao declaram mais a variavel de controle
   inline e os comentarios de linha (//) foram convertidos para /.. .. / */

#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE(arr)                                                         \
  (sizeof (arr)) / sizeof (arr[0]) /* funcao macro para obter tamanho de      \
                                       vetor de qualquer tipo muito           \
                                       facilmente. */

/* utilidades */
void limpar_input (void);
void limpar_tela (void);
void wait (int ms);
void print_vec (float arr[], size_t siz);
void skip (int ln);

/* funcoes que cumprem os casos de uso da aplicacao definida no trabalho */
float pa (float a1, float r, int n);
float sum_pa (float a1, float r, int n);
float interpol (float a1, float an, int n);

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int
main (void)
{
  int choice;

  float a1, r;
  int n;
  float result;

  float seq[8];

  setlocale (LC_ALL, "pt_BR.UTF-8");

  /*#ifdef _WIN32
    SetConsoleCP (CP_UTF8);
    SetConsoleOutputCP (CP_UTF8);
  #endif
  */

  while (1)
    {
      a1 = r = n = 0;
      limpar_tela ();
      printf ("Calculadora de P.A\n");
      printf ("\n");
      printf ("Por favor, selecione uma das opcoes abaixo: \n");
      printf ("1) Calcule o n-simo termo de uma P.A.\n");
      printf ("2) Calcule a soma de n termos de uma P.A.\n");
      printf ("3) Interpole k numeros em uma P.A\n");
      printf ("4) Gere uma P.A de segunda ordem a partir de uma P.A de 8 "
              "termos.\n");
      printf ("5) Sair\n");

      printf (": ");
      if (scanf ("%d", &choice) != 1)
        {
          limpar_input ();
          continue;
        }

      switch (choice)
        {
        case 1:
          while (1)
            {
              printf ("Digite a1 (n. real), razao (n. real), indice (n. "
                      "inteiro) no seguinte formato: "
                      " n1 n2 n3\n-> ");
              if (scanf ("%f %f %d", &a1, &r, &n) != 3)
                {
                  fprintf (stderr,
                           "Input nao recebido no formato especificado.\n");
                  limpar_input ();
                  continue;
                }
              result = pa (a1, r, n);
              printf ("O resultado da formula do enesimo termo da P.A para a1 "
                      "= %.2f r = %.2f indice "
                      "= %.1d e %.2f\n",
                      a1, r, n, result);
              wait (2000);
              break;
            }
          break;
        case 2:
          while (1)
            {
              printf ("Digite a1 (n. real), razao (n. real), indice (n. "
                      "inteiro) no seguinte formato: "
                      " n1 n2 n3\n-> ");
              if (scanf ("%f %f %d", &a1, &r, &n) != 3)
                {
                  fprintf (stderr,
                           "Input nao recebido no formato especificado.\n");
                  limpar_input ();
                  continue;
                }
              result = sum_pa (a1, r, n);
              printf ("O resultado da formula da soma de todos os elementos "
                      "da PA para a1 = %.2f r = %.2f indice "
                      "= %.1d e %.2f\n",
                      a1, r, n, result);
              wait (2000);
              break;
            }
          break;
        case 3:
          while (1)
            {
              float an, r_interp;
              int i;

              printf ("Digite a1 (n. real), an (n. real) e n termos totais "
                      "(n. inteiro) no formato: n1 n2 n3\n-> ");
              if (scanf ("%f %f %d", &a1, &an, &n) != 3)
                {
                  fprintf (stderr,
                           "Input nao recebido no formato especificado.\n");
                  limpar_input ();
                  continue;
                }

              if (n < 3)
                {
                  fprintf (stderr, "O numero total de termos (n) deve ser "
                                   "maior ou igual a 3.\n");
                  continue;
                }

              r_interp = interpol (a1, an, n);

              printf ("Foram interpolados %d meios aritmeticos com sucesso!\n",
                      n - 2);
              printf ("A razao calculada para a interpolacao e: %.2f\n",
                      r_interp);

              printf ("Sequencia gerada: %.2f", a1);

              for (i = 1; i <= (n - 2); i++)
                printf (" -> %.2f", a1 + (i * r_interp));

              printf (" -> %.2f\n", an);

              wait (1e4);
              break;
            }
          break;
        case 4:
          while (1)
            {
              int i;
              float old_r;
              float r2_ref;
              int valido;
              float new_r;
              float r2;
              float p_termo_pa2;

              valido = 1;

              for (i = 0; i < 8; i++)
                while (1)
                  {
                    printf ("Digite o %d termo da PA de 1a ordem: ", i + 1);
                    if (scanf ("%f", &seq[i]) != 1)
                      {
                        fprintf (stderr,
                                 "Input nao corresponde ao esperado, tente "
                                 "novamente (digite um numero real)\n");
                        wait (7.5e2);
                        continue;
                      }
                    break;
                  }

              print_vec (seq, ARR_SIZE (seq));

              old_r = seq[1] - seq[0];
              r2_ref = 0;

              for (i = 2; i < 8; i++)
                {
                  new_r = seq[i] - seq[i - 1];
                  r2 = new_r - old_r;

                  if (i == 2)
                    r2_ref = r2;
                  else if (fabs (r2 - r2_ref) > 1e-3)
                    {
                      valido = 0;
                      break;
                    }

                  old_r = new_r;
                }

              if (!valido)
                {
                  limpar_tela ();
                  printf ("A sequencia nao e valida, digite novamente!\n");
                  continue;
                }

              p_termo_pa2 = seq[1] - seq[0];

              printf ("%.2f ->", p_termo_pa2);

              for (i = 2; i < 7; i++)
                printf (" %.2f -> ", pa (p_termo_pa2, r2_ref, i));

              printf ("%.2f", pa (p_termo_pa2, r2_ref, 7));

              skip (2);

              printf ("P.A de 2a ordem gerada corretamente!\n");

              wait (1e4);

              break;
            }
          break;
        case 5:
          limpar_tela ();
          printf ("Obrigado por utilizar este sistema!\n");
          wait (750);
          exit (0);
          break;
        default:
          printf ("Opcao invalida! tente novamente\n");
          wait (750);
          break;
        }
    }
  return 0;
}

float
pa (float a1, float r, int n)
{
  return a1 + (n - 1) * r;
}

float
sum_pa (float a1, float r, int n)
{
  return ((a1 + pa (a1, r, n)) * n) / 2.0;
}

float
interpol (float a1, float an, int n)
{
  return (an - a1) / (n - 1);
}

#ifdef _WIN32
void
limpar_tela (void)
{
  system ("cls");
}
#else
void
limpar_tela (void)
{
  system ("clear");
}
#endif

#ifdef _WIN32
void
wait (int ms)
{
  Sleep (ms);
}
#else
void
wait (int ms)
{
  struct timespec tm;
  tm.tv_sec = (ms / 1000);
  tm.tv_nsec = (ms % 1000) * 1000000;

  nanosleep (&tm, NULL);
}
#endif

void
limpar_input (void)
{
  int c;
  while ((c = getchar ()) != '\n' && c != EOF)
    ;
}

void
print_vec (float arr[], size_t siz)
{
  int i;

  for (i = 0; i < (int)(siz - 1); i++)
    printf ("%.2f -> ", arr[i]);

  printf ("%.2f", arr[siz - 1]);
  skip (1);
}

void
skip (int ln)
{
  int i;

  for (i = 0; i < ln; i++)
    putchar ('\n');
}
