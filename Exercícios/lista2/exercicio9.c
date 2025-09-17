// ler um número, e ver se ele é divisível por 7 e por 3.

#include <stdio.h>

int main(void) {
  short x;
  puts(
      "Usuário, digite um número para saber se ele é divisível por 7 e por 3.");
  scanf("%hd", &x);

  if (x % 3 == 0 && x % 7 == 0) {
    printf("%hd é divisível por 7 e por 3.\n", x);
  } else {
    printf("%hd não é divisível por 7 e por 3.\n", x);
  }
}
