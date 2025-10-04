/*
 * dado o exercício 4 calcule o percentual de jovens de cada gênero em cada
 * modalidade
 */

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STD_WAIT 750
#define P_TOTAL 50

bool trim(char *buf);
void wait_ms(unsigned ms);
void clear(void);

int main(void) {
  char buf[15], *endptr;
  float m = 0, f = 0, pm1, pm2, pm3, pf1, pf2, pf3, m1 = 0, m2 = 0, m3 = 0,
        f1 = 0, f2 = 0, f3 = 0, v1, v2;

  printf("Caro usuário, digite o gênero (M = 0, F = 1) e o esporte favorito "
         "(Futebol = 1, Basquete = 2, Vôlei = 3) de %d pessoas.\n",
         P_TOTAL);

  wait_ms(1000);

  for (int i = 0; i < P_TOTAL; i++) {
    while (true) {
      printf("Por favor, digite agora o gênero e o o esporte favorito da %d "
             "pessoa: ",
             i + 1);
      if (!fgets(buf, sizeof(buf), stdin) && !trim(buf)) {
        puts("Programa não possui acesso pleno ao standard input, "
             "desligando...");
        wait_ms(STD_WAIT);
        exit(EXIT_FAILURE);
      }
      endptr = buf; // endptr aponta para o primeiro caracter de buf
      errno = 0;
      v1 = strtof(endptr, &endptr);
      v2 = strtof(endptr, &endptr);

      if (errno == ERANGE) {
        puts("Número fora de alcance!");
        wait_ms(STD_WAIT);
        continue;
      }
      if (v1 != 0 && v1 != 1 || v2 < 1 || v2 > 3) {
        puts("Valores inválidos!");
        wait_ms(STD_WAIT);
        continue;
      }
      break;
    }

    if (v1)
      f++;
    else
      m++;

    if (v2 == 1) {
      if (v1)
        f1++;
      else
        m1++;
    } else if (v2 == 2) {
      if (v1)
        f2++;
      else
        m2++;
    } else {
      if (v1)
        f3++;
      else
        m3++;
    }
  }
  pm1 = m > 0 ? (m1 / m) * 100.0F : 0.0F;
  pm2 = m > 0 ? (m2 / m) * 100.0F : 0.0F;
  pm3 = m > 0 ? (m3 / m) * 100.0F : 0.0F;
  pf1 = f > 0 ? (f1 / f) * 100.0F : 0.0F;
  pf2 = f > 0 ? (f2 / f) * 100.0F : 0.0F;
  pf3 = f > 0 ? (f3 / f) * 100.0F : 0.0F;

  printf("\nResultados:\n");
  if (m > 0) {
    printf("Homens em Futebol: %.2f%%\n", pm1);
    printf("Homens em Basquete: %.2f%%\n", pm2);
    printf("Homens em Vôlei: %.2f%%\n", pm3);
  } else {
    printf("Nenhum homem entrevistado.\n");
  }
  if (f > 0) {
    printf("Mulheres em Futebol: %.2f%%\n", pf1);
    printf("Mulheres em Basquete: %.2f%%\n", pf2);
    printf("Mulheres em Vôlei: %.2f%%\n", pf3);
  } else {
    printf("Nenhuma mulher entrevistada.\n");
  }
}

bool trim(char *buf) {
  size_t start = 0, end = strlen(buf);
  if (end == 0)
    return false;
  end--;
  while (start <= end && isspace((unsigned char)buf[start]))
    start++;
  while (end >= start && isspace((unsigned char)buf[end]))
    end--;
  size_t len = end - start + 1;
  memmove(buf, buf + start, len);
  buf[len] = '\0';
  return true;
}

void wait_ms(unsigned ms) { usleep(ms * 1000); }
void clear(void) { system("clear"); }
