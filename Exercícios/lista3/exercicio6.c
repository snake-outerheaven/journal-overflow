/*
 *
 * Uma empresa de manutenção de equipamentos deseja fazer um estudo em relação
 * um conjunto de 250 Ordens de Serviço executadas, com os seguintes dados: o
 * Número da OS(1354- 1603) a quantidade de dias previstos par a entrega, a
 * quantidade de dias gastos e o tipo do serviço (1 – Manutenção ou 2 – Reparo)
 * . Faça um algoritmo que leros dados e calcule: O percentual de ordens de
 * serviço de cada tipo entregue fora do prazo e o número da OS com maior
 * atraso.
 */

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int trim(char *buf);
int wait(unsigned ms);
int clear(void);

#define STD_WAIT 750

int main(void) {
  char buf[15];
  int nos, qprev, qreal, ts;
  int total = 250, i = 0;
  int nos_maior;
  float p1m, p2m;
}

int trim(char *buf) {
  size_t end = strlen(buf);

  if (!end) {
    return 1;
  }

  size_t start = 0;
  size_t len;
  end--;

  while (start <= end && isspace((unsigned char)buf[start]))
    start++;

  while (end >= start && isspace((unsigned char)buf[end]))
    end--;

  len = end - start + 1;
  memmove(buf, buf + start, len);
  buf[len] = '\0';
  return 0;
}

int wait(unsigned ms) {
  if (usleep(ms * 1000) != 0) {
    return 1;
  }
  return 0;
}

int clear(void) {
  if (system("clear") == -1) {
    return 1;
  }
  return 0;
}
