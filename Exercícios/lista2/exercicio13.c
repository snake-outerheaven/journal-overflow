/* 13 - A confederação brasileira de natação fará o cadastro de atletas por
categoria. Fazer um Algorritmo que leia a idade de um nadador e apresente a sua
categoria segundo as seguintes faixas: Infantil A 5 – 7 anos -- Infantil B 8 –
10 anos -- Juvenil A 11 – 13 anos -- Juvenil B 14 – 17 anos. */

#include <stdio.h>

int main(void) {
  int idade;

  printf("Digite a idade do nadador: ");
  if (scanf("%d", &idade) != 1) {
    fprintf(stderr, "Entrada inválida.\n");
    return 1;
  }

  if (idade >= 5 && idade <= 7) {
    printf("Categoria: Infantil A\n");
  } else if (idade >= 8 && idade <= 10) {
    printf("Categoria: Infantil B\n");
  } else if (idade >= 11 && idade <= 13) {
    printf("Categoria: Juvenil A\n");
  } else if (idade >= 14 && idade <= 17) {
    printf("Categoria: Juvenil B\n");
  } else {
    printf("Sem categoria definida para esta idade.\n");
  }

  return 0;
}
