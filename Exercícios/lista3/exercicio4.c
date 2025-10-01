#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STD_WAIT 750
#define TOTAL_PEOPLE 75

typedef struct {
  int gender;
  int fav_esp;
  int age;
} Person;

bool trim(char *buf);
void wait_ms(unsigned ms);
void clear(void);

int main(void) {
  char buf[50], *convptr;
  int count_gender[2] = {0, 0};
  int sum_gender[2] = {0, 0};
  int count_sport[3] = {0, 0, 0};
  int sum_sport[3] = {0, 0, 0};

  Person people[TOTAL_PEOPLE];

  printf("Registro de %d jovens: gênero (M=1, F=0), idade (12-17) e esporte "
         "favorito (1=Basquete,2=Futebol,3=Vôlei)\n",
         TOTAL_PEOPLE);
  wait_ms(500);
  puts("Aguarde para começar...");
  wait_ms(1500);

  for (int i = 0; i < TOTAL_PEOPLE; i++) {
    while (true) {
      printf(
          "Digite gênero, idade e esporte do %dº jovem (ou 'q' para sair):\n> ",
          i + 1);
      if (!fgets(buf, sizeof(buf), stdin) || !trim(buf)) {
        puts("Entrada inválida.");
        wait_ms(STD_WAIT);
        continue;
      }

      if (buf[0] == 'q' || buf[0] == 'Q')
        exit(EXIT_SUCCESS);

      convptr = buf;
      errno = 0;
      int gender = (int)strtol(convptr, &convptr, 10);
      int age = (int)strtol(convptr, &convptr, 10);
      int fav_esp = (int)strtol(convptr, &convptr, 10);

      if (errno == ERANGE) {
        puts("Número fora do alcance!");
        wait_ms(STD_WAIT);
        continue;
      }

      if ((gender != 0 && gender != 1) || age < 12 || age > 17 ||
          (fav_esp < 1 || fav_esp > 3)) {
        puts("Valores inválidos. Gênero: 0 ou 1; Idade: 12-17; Esporte: 1-3.");
        wait_ms(STD_WAIT);
        continue;
      }

      people[i].gender = gender;
      people[i].age = age;
      people[i].fav_esp = fav_esp;
      break;
    }

    sum_gender[people[i].gender] += people[i].age;
    count_gender[people[i].gender]++;
    sum_sport[people[i].fav_esp - 1] += people[i].age;
    count_sport[people[i].fav_esp - 1]++;
  }

  for (int j = 0; j < 2; j++)
    printf("Média de idade %s: %.2f\n", j == 0 ? "meninas" : "meninos",
           count_gender[j] ? (float)sum_gender[j] / count_gender[j] : 0.0f);

  const char *sports[] = {"Basquete", "Futebol", "Vôlei"};
  for (int j = 0; j < 3; j++)
    printf("Média de idade de %s: %.2f\n", sports[j],
           count_sport[j] ? (float)sum_sport[j] / count_sport[j] : 0.0f);

  return 0;
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
