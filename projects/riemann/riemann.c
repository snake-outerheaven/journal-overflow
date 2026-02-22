#include "riemann.h"
#include <stddef.h>

double riemann(MathFunc f, const double a, const double b, const size_t steps)
{
    size_t i;

    double base = (b - a) / steps;
    double sum  = 0.0;

    double mid;
    double height;

    for (i = 0; i < steps; i++)
    {
        mid = a + (i + 0.5) * base;
        height = f(mid);
        sum += base * height;
    }

    return sum;
}

