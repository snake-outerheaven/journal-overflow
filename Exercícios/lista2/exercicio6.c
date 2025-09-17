/* exercicio 6: ler A B C e OP, se OP for 1, exibir A B C em ordem crescente,
 * caso contrário, exibir em ordem decrescente. */

#include <stdio.h>

int main(void) {
  short a, b, c, op;
  puts(
      "Olá usuário, seja bem vindo! Digite quatro números e aguarde o programa "
      "imprimir os três primeiros em ordem crescente se o quarto número for 1, "
      "e decrescente caso seja qualquer outro número. (escrever com um espaço "
      "entre cada número)");
  scanf("%hd %hd %hd %hd", &a, &b, &c, &op);

  if (op == 1) {
    if (a < b && a < c) {
      printf("%hd ", a);
      if (b < c) {
        printf("%hd %hd", b, c);
      } else {
        printf("%hd %hd", c, b);
      }
    } else if (b < a && b < c) {
      printf("%hd ", b);
      if (a < c) {
        printf("%hd %hd", a, c);
      } else {
        printf("%hd %hd", c, a);
      }
    } else {
      printf("%hd ", c);
      if (a < b) {
        printf("%hd %hd", a, b);
      } else {
        printf("%hd %hd", b, a);
      }
    }
  } else {
    if (a > b && a > c) {
      printf("%hd ", a);
      if (b > c) {
        printf("%hd %hd", b, c);
      } else {
        printf("%hd %hd", c, b);
      }
    } else if (b > a && b > c) {
      printf("%hd ", b);
      if (a > c) {
        printf("%hd %hd", a, c);
      } else {
        printf("%hd %hd", c, a);
      }
    } else {
      printf("%hd ", c);
      if (a > b) {
        printf("%hd %hd", a, b);
      } else {
        printf("%hd %hd", b, a);
      }
    }
  }
  return 0;
}
