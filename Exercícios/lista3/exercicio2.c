/*2) Fazer um algoritmo que ler a produção (120 a 350) e a linha de produção (1
ou 2) de 50 operários a calcule a média de produção geral e de cada linha. */

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  unsigned int prod;
  unsigned int line;
} Worker;

bool trim(char *buf);
void wait(unsigned short ms);
void clear(void);

int main(void) {
  float mg = 0.0F, m1 = 0.0F, m2 = 0.0F;
  int sg = 0, s1 = 0, s2 = 0, workercounter = 0, l1 = 0, l2 = 0, lg = 0;
  char buf[15];
  bool line, confirm;
  Worker workers[50], *start = &workers[0], *end = &workers[50];

  clear();
  puts("Usuário, seja bem vindo, este programa irá avaliar os seguintes dados "
       "dos operadores da fábrica: Linha de produção e a produção, que serão "
       "inseridos por você, para então serem imprimidas em tela a média de "
       "produção geral e individual de cada linha de produção.  ");

  wait(750);

  for (Worker *p = start; p < end; p++) {
    workercounter++;
    while (true) {
      printf("Por favor, digite a linha de produção (1 ou 2) e o total de "
             "produção do %dº trabalhador (Ex: 1 650)\n: ",
             workercounter);
      if (!fgets(buf, sizeof(buf), stdin) || !trim(buf)) {
        puts("Entrada inválida, digite novamente.");
        wait(750);
        clear();
        continue;
      }
      if (!sscanf(buf, "%u %u", &p->line, &p->prod)) {
        puts("Não foi possível realizar a conversão da entrada para os "
             "números.");
        wait(750);
        clear();
        continue;
      }
      if (p->line != 1 && p->line != 2) {
        puts("Só há a linha 1 e 2 de produção na fábrica.");
        wait(750);
        continue;
      }
      if (p->line == 1) {
        line = true; // usar ? para somar p->line em sg
      } else {
        line = false;
      }
      printf("Deseja confirmar os dados do %dº trabalhador? \nDados lidos "
             "pelo programa -> Linha de produção: %u | Total de produção: "
             "%u\n: ",
             workercounter, p->line, p->prod);

      if (!fgets(buf, sizeof(buf), stdin) || !trim(buf)) {
        puts("Entrada inválida, digite novamente.");
        wait(750);
        clear();
        continue;
      }
      if (toupper((unsigned char)buf[0]) == 'S' && buf[1] == '\0')
        confirm = true;
      else
        confirm = false;
      if (confirm) {
        sg += p->prod, lg++;
        line ? (s1 += p->prod, l1++) : (s2 += p->prod, l2++);
        break;
      } else {
        clear();
        continue;
      }
    }
  }
  if (lg)
    mg = sg / (float)lg;
  if (l1)
    m1 = s1 / (float)l1;
  if (l2)
    m2 = s2 / (float)l2;

  printf("\nMédia geral:  %.2f\n", mg);
  printf("Média linha 1: %.2f\n", m1);
  printf("Média linha 2: %.2f\n", m2);

  return 0;
}

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
