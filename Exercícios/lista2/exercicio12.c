/* 12 - A CEF concederá um crédito especial com juros de 2% aos seus clientes de
acordo com o saldo médio no último ano. Fazer um algoritmo que leia o saldo
médio de um cliente e calcule o valor do crédito de acordo com a tabela a
seguir. Imprimir uma mensagem informando o saldo médio e o valor de crédito. De
0 a 500 Nenhum crédito - De 501 a 1000 30% do valor do saldo médio - De 1001 a
3000 40% do valor do saldo médio - Acima de 3001 50% do valor do saldo médio */

#include <stdio.h>

int main(void) {
  float saldo, credito;

  puts("Usuário, digite o seu saldo e veja o valor do crédito que está "
       "disponível para você");

  scanf("%f", &saldo);

  if (0.0F < saldo && saldo < 500.0F) {
    printf("Para o seu saldo R$ %.1f não há crédito disponível.\n", saldo);
  } else if (501.0F < saldo && saldo < 1000.0F) {
    credito = saldo * (30.0F / 100.0F);
    printf("O crédito disponível para o saldo R$ %.1f é de R$  %.1f.\n", saldo,
           credito);
  } else if (1001.0F < saldo && saldo < 3000.0F) {
    credito = saldo * (40.0F / 100.0F);
    printf("O crédito disponível para o saldo R$ %.1f é de R$ %.1f.", saldo,
           credito);
  } else {
    credito = saldo * (50.0F / 100.0F);
    printf("O crédito disponível para o saldo R$ %.1f é de R$ %.1f.", saldo,
           credito);
  }
  return 0;
}
