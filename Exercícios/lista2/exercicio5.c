// objetivo: fazer um programa que leia A, B e C e os imprima em ordem
// crescente.


// da pra melhorar e muito, com bubble sort, mas está aceitável por enquanto. (algoritmos de ordenação superiores)
#include <stdio.h>

int main(void) {
  short a, b, c;
  puts("Olá usuário, seja bem vindo! Digite três números e aguarde o programa "
       "imprimi-los em ordem crescente");
  scanf("%hd %hd %hd", &a, &b, &c);
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
  return 0;
}
