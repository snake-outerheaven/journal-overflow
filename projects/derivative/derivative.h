#ifndef DERIVATIVE_H
#define DERIVATIVE_H

/*
 * DX (Step Size):
 * Enclosed in parentheses to ensure the macro is treated as a
 * single unit, preventing precedence issues during text substitution.
 * A value of 1e-10 is a balanced choice for double precision.
 */
#define DX (1e-10)

typedef double (*MathFunc) (double);

/*
 * This function calculates the numerical first derivative of a
 * mathematical function using the Central Finite Difference formula.
 *
 * The use of 'static __inline__' allows the compiler to embed the
 * arithmetic logic directly into the calling code (inlining).
 * This eliminates function call overhead (stack handling) and,
 * combined with the 'static' keyword, prevents "multiple definition"
 * errors during the linking process when included in multiple files.
 *
 * Parameters:
 * f: A function pointer to the mathematical function (MathFunc).
 * x: The point x at which the derivative (slope) is evaluated.
 * h: The step size or differentiation interval (typically DX).
 *
 * Returns:
 * The estimated numerical derivative (slope) of f at the point x.
 */
static __inline__ double derivative(MathFunc f, double x, double h)
{
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

#endif
