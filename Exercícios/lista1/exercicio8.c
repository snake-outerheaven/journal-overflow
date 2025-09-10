#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// objetivo: receber o ano de nascimento de uma pessoa, receber um ano alvo e
// calcular a idade da pessoa neste ano.

// protótipo das funções
int converter(char *buf, int *ano);
void trim(char *str);
void wait_posix(unsigned int time);

// main
int main(void) {
  char buf[15];
  int ano_nascimento, ano_alvo;

  wait_posix(750);

  while (true) {
    printf("Digite o ano de nascimento: ");
    fgets(buf, sizeof(buf), stdin);
    trim(buf);
    if (converter(buf, &ano_nascimento) == -1) {
      wait_posix(750);
      printf("Ano de nascimento inválido.\n");
      wait_posix(100);
      printf("Aguarde para digitar novamente\n");
      wait_posix(500);
      continue;
    }

    printf("Digite o ano alvo: ");
    fgets(buf, sizeof(buf), stdin);
    trim(buf);
    if (converter(buf, &ano_alvo) == -1) {
      wait_posix(750);
      printf("Ano alvo inválido.\n");
      wait_posix(100);
      printf("Aguarde para digitar novamente\n");
      wait_posix(500);
      continue;
    }

    int idade = ano_alvo - ano_nascimento;
    printf("A idade da pessoa em %d será %d anos.\n", ano_alvo, idade);

    printf("Deseja calcular novamente? (s/n): ");
    fgets(buf, sizeof(buf), stdin);
    trim(buf);
    if (buf[0] != 's' && buf[0] != 'S') {
      break;
    }
  }
}

// area das funções
int converter(char *buf, int *ano) {
  if (!sscanf(buf, "%d", ano)) {
    printf("Erro ao converter o ano.\n");
    return -1;
  }
  return 0;
}

void trim(char *str) {
  size_t end = strlen(str) - 1;
  size_t start = 0;
  size_t len = 0;

  while (start < end && isspace(str[start])) {
    start++;
  }

  while (end > start && isspace(str[end])) {
    end--;
  }

  len = end - start + 1;
  memmove(str, str + start, len + 1);
}

void wait_posix(unsigned int time) { usleep(time * 1000); }
