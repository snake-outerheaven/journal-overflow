/*
 * Dado o exercício 2 faça outro algoritmo que calcule o percentual de operários
 * de cada linha de produção e o percentual de operários que produziram mais de
 * 300 peças.
 */

/*
 * Nota: falta fazer a checagem da conversão de tipos, confirmar dados em cada
 * iteração do loop e somar contadores depois do loop infinito de validação.
 */

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CONT 5

// declaração das funções
bool trim(char *buf);
void wait(unsigned short ms);
void clear(void);

typedef struct {
  // atributos
  unsigned line;
  unsigned parts;
} Worker; // o operário, no contexto do programa

int main(void) {
  char buf[15], *conv;
  bool line; // ? true : false;
  int workercounter = 0;
  float p1, p2, p3, c1 = 0.0F, c2 = 0.0F, c3 = 0.0F, c = 0.0F;
  Worker Workers[CONT], *start = &Workers[0], *end = &Workers[CONT];

  printf("Usuário, seja bem vindo ao programa, aqui voce digitará os seguintes "
         "atributos de %d operários: linha de produção e o número de peças "
         "produzidas. O "
         "programa então revelará o percentual de operários em cada linha de "
         "produção e o percentual de operários que produziram mais de 300 "
         "peças.\n",
         CONT);

  for (Worker *w = start; w < end; w++) {
    workercounter++;
    while (true) {
      wait(750);
      printf("Por favor, digite a linha de produção e a produção total do %dº "
             "operário ( digitar exatamente: linha prod )\n(Entre q para "
             "sair)\n: ",
             workercounter);
      if (!fgets(buf, sizeof(buf), stdin) || !trim(buf)) {
        puts("Entrada inválida.");
        wait(750);
        clear();
        continue;
      }
      if (!strcmp(buf, "q") || !strcmp(buf, "Q"))
        exit(EXIT_SUCCESS);
      errno = 0;
      w->line = (unsigned)strtoul(buf, &conv, 10);
      if (errno == ERANGE) {
        puts("Falha de conversão, número de linha é muito alto para a "
             "conversão de texto para número.");
        wait(750);
        continue;
      } else if (*conv != '\0' && !isspace(*conv)) {
        puts("Não houve valores digitados que pudessem ser convertidos, tente "
             "novamente.");
        wait(750);
        clear();
        continue;
      }
      errno = 0;
      w->parts = (unsigned)strtoul(conv, &conv, 10);
      if (errno == ERANGE) {
        puts("Falha de conversão, número de peças e muito alto para conversão "
             "de texto para número.");
        wait(750);
        continue;
      } else if (*conv != '\0' && !isspace((unsigned)*conv)) {
        puts("Não houve valores digitados que pudessem ser convertidos, tente "
             "novamente.");
        wait(750);
        clear();
        continue;
      }
      /*if (!sscanf(buf, "%u %u", &w->line, &w->parts)) {
      puts("Não foi possível fazer a atribuição dos valores ao operário da "
           "iteração atual, repetindo entrada de dados.");
      wait(750);
      continue;
      }   <==== trecho inválido
      */
      if (w->line != 1 && w->line != 2) {
        puts("Só existem as linhas 1 e 2 de produção.");
        wait(750);
        clear();
        continue;
      }
      if (w->line == 1) {
        line = true;
      } else {
        line = false;
      }

      printf(
          "Gostaria de confirmar os dados lidos pelo programa?\nDados do %dº "
          "operário: %u %u\n: ",
          workercounter, w->line, w->parts);
      if (!fgets(buf, sizeof(buf), stdin) || !trim(buf)) {
        puts("Entrada não reconhecida.");
        wait(750);
        puts("Digite novamente.");
        wait(750);
        clear();
        continue;
      }
      if (!strcmp(buf, "S") || !strcmp(buf, "s")) {
        puts("Valores confirmados!");
        wait(750);
        break;
      } else {
        puts("Reiniciando loop por segurança");
        wait(750);
        clear();
        continue;
      }
    }
    if (w->parts > 300)
      c3++;
    line ? c1++ : c2++;
    c++;
  }
  p1 = (c1 / c) * 100;
  p2 = c2 / c * 100;
  p3 = c3 / c * 100;

  printf("Foram calculados os seguintes percentuais:\nPercentual de operários "
         "da linha 1 -> %.1f%%\nPercentual da linha 2 -> %.1f%%\nPercentual de "
         "operários com produção maior que 300 peças -> %.1f%%\n",
         p1, p2, p3);
  wait(1500);
  return 0;
}

// implementação das funções.
bool trim(char *buf) {
  size_t end = strlen(buf);
  if (end == 0)
    return false;
  end--;
  size_t start = 0;
  while (start <= end && isspace((unsigned char)buf[start]))
    start++;
  while (end >= start && isspace((unsigned char)buf[end]))
    end--;
  size_t len = end - start + 1;
  memmove(buf, buf + start, len);
  buf[len] = '\0';
  return true;
}

void wait(unsigned short ms) { usleep(1000 * ms); }
void clear(void) { system("clear"); }
