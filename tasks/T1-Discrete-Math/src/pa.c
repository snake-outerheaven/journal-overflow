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
