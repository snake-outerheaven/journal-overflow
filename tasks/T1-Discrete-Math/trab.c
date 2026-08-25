/*
  Crie um programa em C que tenha as seguintes funcionalidades::
        a) Calcule o enésimo termo de uma P.A.:
        b) Calcule a soma de n termos de uma P.A.:
        c) interpole k números em uma P.A.:
        d) Gere uma P.A. de segunda ordem a partir de uma sequência de 8
  termos. Use um vetor para armazenas a sequência original. O programa deve ter
  um menu onde o usuário escolha o que quer fazer. O programa poderá ter
        funções para cada funcionalidade. Envie o arquivo .c no AVA
*/

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// utilidades
void limpar_input (void);
void limpar_tela (void);
void wait (int ms);

// funções que cumprem os casos de uso da aplicação definida no trabalho
float pa (float a1, float r, int n);

int
main (void)
{
  int choice;

  setlocale (LC_ALL, "pt_BR.UTF-8");

  while (1)
    {
      limpar_tela ();
      printf ("Calculadora de P.A\n");
      printf ("\n");
      printf ("Por favor, selecione uma das opções abaixo: \n");
      printf ("1) Calcule o n-simo termo de uma P.A.\n");
      printf ("2) Calcule a soma de n termos de uma P.A.\n");
      printf ("4) Interpole k números em uma P.A\n");
      printf ("5) Gere uma P.A de segunda ordem a partir de uma P.A de 8 "
              "termos.\n");
      printf ("6) Sair\n");

      printf (": ");
      if (scanf ("%d", &choice) != 1)
        {
          limpar_input ();
          continue;
        }

      switch (choice)
        {
        case 1:
          float a1, r;
          int n;
          float result;
          a1 = r = n = 0;
          while (1)
            {
              printf ("Digite a1 (nº real), razão (nº real), indice (nº "
                      "inteiro) no seguinte formato: "
                      " n1 n2 n3\n-> ");
              if (scanf ("%f %f %d", &a1, &r, &n) != 3)
                {
                  fprintf (stderr,
                           "Input não recebido no formato especificado.\n");
                  limpar_input ();
                  continue;
                }
              result = pa (a1, r, n);
              printf ("O resultado da fórmula para a1 = %.2f r = %.2f indice "
                      "= %.1d é %.2f\n",
                      a1, r, n, result);
              wait (2000);
              break;
            }
          break;
        case 6:
          limpar_tela ();
          printf ("Obrigado por utilizar este sistema!\n");
          wait (750);
          exit (0);
          break;
        default:
          printf ("Opção inválida! tente novamente\n");
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
