#ifndef RIEMANN_H
#define RIEMANN_H
#include <stddef.h>

typedef double (*MathFunc)(double);


double riemann(MathFunc, const double, const double, const size_t);
#endif

