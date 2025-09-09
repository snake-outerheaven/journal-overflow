#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// objetivo: criar uma algoritmo que recebe o salário mínimo, numero de horas
// trabalhadas, calcular salário bruto e obter o salário líquido considerando
// as seguintes regras:
//
// 1º. Cada hora trabalhada equivale 6% do salário mínimo
// 2°. O salário bruto é igual ao somatório de horas trabalhadas
// 3º. O salário líquido é igual ao salário bruto - 7.5% do próprio salário
// bruto.

// prototipos das funções.
void trim(char *str);
int converter(char *str, float *x);
void wait_posix(unsigned int time);

// main
int main(void) {
  char buf[15] = {};
  float sal_min = 0.0F, sal_br = 0.0F, num_hr = 0.0F, sal_liq = 0.0F,
        imp = 0.0F;

  printf("Administrador, seja bem vindo ao programa que calcula o salário "
         "total de um funcionário.\n");
  wait_posix(750);

  while (true) {
    printf("\n");
    wait_posix(750);
    printf("Por favor, digite o salário mínimo deste funcionário(até 15 "
           "caracteres, digite 0 para encerrar o programa).\n: ");
    fgets(buf, sizeof(buf), stdin);
    trim(buf);
    if (!converter(buf, &sal_min)) {
      continue;
    }

    if (sal_min == 0) {
      printf("Obrigado por utilizar este programa.\n");
      wait_posix(200);
      break;
    }
    printf("Por favor, digite o número de horas trabalhadas (modelo de horas "
           "aceito: 1, 2.5, 7.25)\n: ");
    fgets(buf, sizeof(buf), stdin);
    trim(buf);
    if (!converter(buf, &num_hr)) {
      continue;
    }

    sal_br = num_hr * (sal_min * 0.06);
    imp = sal_br * 0.075;
    sal_liq = sal_br - imp;

    wait_posix(750);
    printf("O funcionário trabalhou %.2f horas, tem salário bruto de %.2f, "
           "imposto foi de %.2f, "
           "salário líquido após desconto do imposto é de %.2f.\n",
           num_hr, sal_br, imp, sal_liq);
  }
  return 0;
}

// implementação das funções.
void wait_posix(unsigned int time) { usleep(time * 1000); }

int converter(char *str, float *x) {
  if (!sscanf(str, "%f", x)) {
    wait_posix(250);
    printf("Falha na conversão.");
    wait_posix(250);
    return 0;
  }
  return 1;
}

void trim(char *str) {
  size_t end = strlen(str);
  size_t start = 0;
  size_t len = 0;

  while (start < end && isspace(str[start]))
    start++;

  while (end > start && isspace(str[end - 1]))
    end--;

  len = end - start;
  memmove(str, str + start, len);
  str[len] = '\0';
}
