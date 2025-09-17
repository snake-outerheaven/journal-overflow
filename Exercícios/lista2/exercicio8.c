// escrever um algoritmo que leia um número e imprima uma das mensagens: "é
// múltiplo de 3" ou "Não é multiplo de 3". Sabendo que na expressão (A=b%3) a
// receberá o resto da divisão de B por 3.

#include <stdio.h>

int main(void) {
  short a, b;
  puts("Usuário, digite um número para saber se é divisível por 3.");
  scanf("%hd", &b);
  a = b % 3;
  if (a == 0) {
    puts("O número é divisível por 3.");
  } else {
    puts("O número não é divisível por 3.");
  }
}
