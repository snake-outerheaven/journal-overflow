#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// verificar se tres valores obtidos podem ser os
// lados de um triangulo.

// alerta: o código só pode ser executado em sistemas que seguem o padrão POSIX
// ( Linux, MacOS, UNIX, FreeBSD e similares.)

// protótipo das funções

void wait_posix(unsigned int ms);
void trim(char *buf);
int converter(char *buf, float *x);
int confirm(float *a, float *b, float *c);

int main(void) {
  char buf[15] = {}, respbuf[5] = {};
  float lados[3] = {}, a, b, c;
  bool resp_val = false;

  wait_posix(750);
  puts("Usuário, este é um programa que recebe tres valores digitados por você "
       "e verifica se estes poderiam formar um triângulo.");

  wait_posix(500);

  for (int i = 0; i < 3; i++) {
    resp_val = false;
    while (!resp_val) {
      printf("\n");
      buf[0] = '\0';
      wait_posix(750);
      printf(
          "Por favor, digite o %dº lado do triângulo (até 15 caracteres)\n: ",
          i + 1);
      fgets(buf, sizeof(buf), stdin);
      trim(buf);
      if (!converter(buf, &lados[i])) {
        continue;
      }
      printf("Gostaria de confirmar o lado %.2f? (s/n)\n: ", lados[i]);
      fgets(respbuf, sizeof(respbuf), stdin);
      trim(respbuf);
      printf("%s\n", respbuf);
      wait_posix(3500);
      if (strcmp(respbuf, "s") == 0 || strcmp(respbuf, "S") == 0) {
        wait_posix(750);
        puts("Lado confirmado!");
        resp_val = true;
      } else {
        wait_posix(750);
        puts("Resposta negativa ou inválida digitada! Aguarde para digitar o "
             "lado novamente.");
        wait_posix(1000);
        continue;
      }
    }
  }
  a = lados[0];
  b = lados[1];
  c = lados[2];

  if (!confirm(&a, &b, &c)) {
    printf("Não é possível fazer o triângulo %.2f, %.2f, %.2f.\n", a, b, c);
  } else {
    printf("O triângulo %.2f, %.2f, %.2f existe!\n", a, b, c);
  }
  return 0;
}

void wait_posix(unsigned int ms) { usleep(ms * 1000); }

void trim(char *buf) {
  size_t end = strlen(buf) - 1;
  size_t start = 0;
  size_t len = 0;

  while (end >= start && isspace(buf[start]))
    start++;

  while (start <= end && isspace(buf[end]))
    end--;

  len = end - start + 1;
  memmove(buf, buf + start, len);
  buf[len] = '\0';
}
int converter(char *str, float *x) {
  if (!sscanf(str, "%f", x)) {
    wait_posix(250);
    puts("Falha na conversão.");
    wait_posix(250);
    return 0;
  }
  return 1;
}

int confirm(float *a, float *b, float *c) {
  if (*a >= *b + *c) {
    return 0;
  }
  if (*b >= *a + *c) {
    return 0;
  }
  if (*c >= *a + *b) {
    return 0;
  }
  return 1;
}
