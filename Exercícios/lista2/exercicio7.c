/* objetivo: ler dois números, soma-los, se o resultado for maior que 20,
 * imprimi-lo somado de 8, caso seja menor, imprimi-lo decrescido de 5.*/

#include <stdio.h>

int main(void) {
  short a, b;
  puts("Usuário, por favor digite dois números.");
  scanf("%hd %hd", &a, &b);

  if (a + b > 20) {
    printf("%hd\n", a + b + 8);
  } else {
    printf("%hd\n", a + b - 5);
  }
  return 0;
}
