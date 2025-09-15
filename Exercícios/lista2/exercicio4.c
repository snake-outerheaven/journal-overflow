#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// aviso: unistd.h é header específico para acessar API de sistemas operacionais
// que seguem o padrão POSIX (Linux, MacOS, BSDs, e outros sistemas baseados em
// UNIX).

// objetivo: receber lados de um triângulo, determinar se o triângulo criado com
// os lados do usuário existe, se sim, determinar o seu tipo.

bool convert_float(char *in, float *out);
void trim(char *buf);
void wait(unsigned short ms);
int check_triangle(float *a, float *b, float *c);

int main(void) {
  char buf[10];
  float lados[3];
  int result;

  wait(500);
  puts("Olá usuário, seja bem vindo! O objetivo deste programa é avaliar se os "
       "3 números reais que você digitar podem formar um triângulo, e se o "
       "triângulo for possível, haverá uma afirmativa, e logo após será "
       "informado o tipo deste triângulo");
  wait(250);
  puts("Dito isso, vamos começar.");

  while (true) {
    for (int i = 0; i < 3; i++) {
      while (true) {
        printf(
            "Por favor, digite o %dº lado (até 10 caracteres e ponto ao invés "
            "de vírgula)\n: ",
            i + 1);
        fgets(buf, sizeof(buf), stdin);
        trim(buf);
        if (!convert_float(buf, &lados[i])) {
          puts("Valor não pode ser convertido em um número real, por favor "
               "digite novamente");
          continue;
        }
        printf("Gostaria de confirmar o número digitado %.2f? ", lados[i]);
        fgets(buf, sizeof(buf), stdin);
        trim(buf);
        if (strcmp(buf, "s") == 0 || strcmp(buf, "S") == 0) {
          wait(750);
          printf("Ok, número %.2f confirmado!\n", lados[i]);
          break;
        } else {
          puts("Resposta negativa ou inválida digitada, por favor, digite "
               "novamente.");
          continue;
        }
      }
    }
    result = check_triangle(&lados[0], &lados[1], &lados[2]);
    switch (result) {
    case 0:
      puts("Não é possível formar um triângulo com esses lados. Tente "
           "novamente.");
      continue;
    case 1:
      puts("Erro interno: ponteiro inválido.");
      return 1;
    case 2:
      puts("Erro: algum lado é inválido (<= 0).");
      continue;
    case 3:
      if (lados[0] == lados[1] && lados[1] == lados[2]) {
        puts("Triângulo equilátero!");
      } else if (lados[0] == lados[1] || lados[0] == lados[2] ||
                 lados[1] == lados[2]) {
        puts("Triângulo isósceles!");
      } else {
        puts("Triângulo escaleno!");
      }
      break;
    }
  }
  return 0;
}

bool convert_float(char *in, float *out) {
  if (!sscanf(in, "%f", out))
    return false;
  return true;
}

void trim(char *buf) {
  size_t end = strlen(buf);
  if (end == 0) {
    return;
  }
  size_t start = 0;
  size_t len;
  end--;

  while (end > start && isspace(buf[start]))
    start++;

  while (start < end && isspace(buf[end]))
    end--;

  len = end - start + 1;
  memmove(buf, buf + start, len);
  buf[len] = '\0';
}

void wait(unsigned short ms) { usleep(ms * 1000); }

int check_triangle(float *a, float *b, float *c) {
  if (!a || !b || !c) {
    return 1;
  }
  // dereferencio os ponteiros, obtendo os valores do endereço de memória(&var)
  float x = *a;
  float y = *b;
  float z = *c;

  if (x <= 0 || y <= 0 || z <= 0) {
    return 2;
  }

  if ((x + y > z) && (x + z > y) && (y + z > x)) {
    return 3;
  }

  return 0;
}
