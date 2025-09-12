#include <ctype.h>
#include <math.h>
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

int main(void) {
  char buf[10];
  float lados[3];
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
