#include <ctype.h>
#include <stdio.h>
#include <string.h>

// objetivo: receber o salário de um funcionário, calcular o valor total a
// receber considerando uma gratificação de 500 reais e o pagamento de uma taxa
// equivalente a 10% do salário total.

void trim(char *str);

int main(void) {
  char numbuf[10];
  float salario;
  while (1) {
    printf("\n");
    printf("Digite o salário do funcionario: ");
    fgets(numbuf, sizeof(numbuf), stdin);
    trim(numbuf);

    if (!sscanf(numbuf, "%f", &salario)) {
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

void trim(char *buf) {
  size_t end = strlen(buf) - 1;
  size_t start = 0;
  size_t len = 0;

  while (start < end && isspace(buf[start]))
    start++;

  while (end > start && isspace(buf[end]))
    end--;

  len = end - start + 1;
  memmove(buf, buf + start, len);
  buf[len] = '\0';
}
