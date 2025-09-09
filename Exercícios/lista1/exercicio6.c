#include <stdio.h>

// objetivo: receber o salário de um funcionário, calcular o valor total a
// receber considerando uma gratificação de 500 reais e o pagamento de uma taxa
// equivalente a 10% do salário total.

int main(void) {
  char numbuf[10];
  float salario;
  while (1) {
    printf("\n");
    printf("Digite o salário do funcionario: ");
    fgets(numbuf, sizeof(numbuf), stdin);

    if (sscanf(numbuf, "%f", &salario) != 1) {
      printf("Entrada inválida\n");
      continue;
    }

    if (salario <= 0) {
      printf("Salario inválido\n");
      continue;
    }

    salario += 500.0F;
    salario -= salario * 0.1F;

    printf("O valor total a receber eh: %.2f\n", salario);
    break;
  }
  return 0;
}

// bem simples, depois vou refatorar para ser um sistema mesmo.
