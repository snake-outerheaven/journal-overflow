/*
        Fazer um exercício com uma matriz quadrada e exibir:

        Diagonal principal
        Diagonal secundária
        Elementos acima e abaixo das diagonais
        Todos os quadrantes
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

void
skip (size_t num)
{
  size_t i;

  for (i = 0; i < num; i++)
    putchar ('\n');

  return;
}

void gen_mat (int[][MAX], size_t, size_t, size_t);
void print_mat (int[][MAX], size_t, size_t);
void print_primary_dig (int[][MAX], size_t);
void print_secondary_dig (int[][MAX], size_t, size_t);
void print_above_below (int[][MAX], size_t, size_t);
void print_quadrants (int[][MAX], size_t, size_t);

int
main (void)
{
  int mat[MAX][MAX] = { 0 };

  srand (time (0));

  puts ("GERANDO MATRIZ");
  skip (1);

  gen_mat (mat, MAX, MAX, 10);

  puts ("IMPRIMINDO MATRIZ");
  skip (1);

  print_mat (mat, MAX, MAX);

  skip (2);

  puts ("IMPRIMINDO DIAGONAL PRIMÁRIA");
  skip (1);

  print_primary_dig (mat, MAX);

  skip (2);

  puts ("IMPRIMINDO DIAGONAL SECUNDÁRIA");
  skip (1);

  print_secondary_dig (mat, MAX, MAX);

  skip (2);

  puts ("IMPRIMINDO ELEMENTOS ACIMA E ABAIXO");
  skip (1);

  print_above_below (mat, MAX, MAX);

  skip (2);

  puts ("IMPRIMINDO QUADRANTES");
  skip (1);

  print_quadrants (mat, MAX, MAX);

  skip (2);

  return 0;
}

void
gen_mat (int mat[][MAX], size_t lim1, size_t lim2, size_t rand_lim)
{
  size_t i, j;

  for (i = 0; i < lim1; ++i)
    for (j = 0; j < lim2; ++j)
      mat[i][j] = rand () % rand_lim + 1;

  return;
}

void
print_mat (int mat[][MAX], size_t lim1, size_t lim2)
{
  size_t i, j;

  for (i = 0; i < lim1; ++i)
    {
      for (j = 0; j < lim2; ++j)
        printf ("|%d|\t", mat[i][j]);
      printf ("\n");
    }
  return;
}

void
print_primary_dig (int mat[][MAX], size_t lim)
{
  size_t i;

  for (i = 0; i < lim; i++)
    printf ("|%2d|\t", mat[i][i]);

  putchar ('\n');

  return;
}

void
print_secondary_dig (int mat[][MAX], size_t lim1, size_t lim2)
{
  size_t i, j;

  for (i = 0; i < lim1; i++)
    for (j = 0; j < lim2; ++j)
      if ((i + j) == MAX - 1)
        printf ("|%2d|\t", mat[i][j]);

  putchar ('\n');

  return;
}

void
print_above_below (int mat[][MAX], size_t lim1, size_t lim2)
{
  size_t i, j;

  puts ("Acima da diagonal principal:");
  for (i = 0; i < lim1; i++)
    {
      for (j = 0; j < lim2; j++)
        if (j > i)
          printf ("|%d|\t", mat[i][j]);
        else
          printf ("\t");
      printf ("\n");
    }

  skip (1);

  puts ("Abaixo da diagonal principal:");
  for (i = 0; i < lim1; i++)
    {
      for (j = 0; j < lim2; j++)
        if (i > j)
          printf ("|%d|\t", mat[i][j]);
        else
          printf ("\t");
      printf ("\n");
    }

  return;
}

void
print_quadrants (int mat[][MAX], size_t lim1, size_t lim2)
{
  size_t i, j;
  size_t mid1 = lim1 / 2;
  size_t mid2 = lim2 / 2;

  puts ("Quadrante 1 (Superior Esquerdo):");
  for (i = 0; i < mid1; i++)
    {
      for (j = 0; j < mid2; j++)
        printf ("|%d|\t", mat[i][j]);
      printf ("\n");
    }

  skip (1);

  puts ("Quadrante 2 (Superior Direito):");
  for (i = 0; i < mid1; i++)
    {
      for (j = mid2; j < lim2; j++)
        printf ("|%d|\t", mat[i][j]);
      printf ("\n");
    }

  skip (1);

  puts ("Quadrante 3 (Inferior Esquerdo):");
  for (i = mid1; i < lim1; i++)
    {
      for (j = 0; j < mid2; j++)
        printf ("|%d|\t", mat[i][j]);
      printf ("\n");
    }

  skip (1);

  puts ("Quadrante 4 (Inferior Direito):");
  for (i = mid1; i < lim1; i++)
    {
      for (j = mid2; j < lim2; j++)
        printf ("|%d|\t", mat[i][j]);
      printf ("\n");
    }

  return;
}
