/*1) Fazer um algoritmo para ler a idade(17 a 45) e o sexo (1 - M ou 0 -F) de 20
indivíduos e calcular a média de idade de cada grupo. */
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  unsigned long sex;
  unsigned long age;
} subject;

bool trim(char *buf);
void wait(unsigned short ms);
void clear(void);

int main(void) {
  int male_count = 0, female_count = 0;
  unsigned long male_sum = 0, female_sum = 0;
  char buf[15];
  subject person[20];

  clear();
  puts("Usuário, por favor, digite o gênero (1=M, 0=F) e a idade de 20 "
       "pessoas.");
  wait(1000);

  for (int i = 0; i < 20; i++) {
    while (true) {
      printf("Pessoa %d (ex: 1 25): ", i + 1);
      if (!fgets(buf, sizeof buf, stdin) || !trim(buf)) {
        puts("Entrada vazia, digite novamente.");
        continue;
      }
      if (sscanf(buf, "%lu %lu", &person[i].sex, &person[i].age) == 2) {
        if (person[i].sex != 0 && person[i].sex != 1) {
          puts("Gênero inválido, digite 0 ou 1.");
          continue;
        }
        printf("Confirmar (S/N)? (Reconhecido: %lu %lu): ", person[i].sex,
               person[i].age);
        if (!fgets(buf, sizeof buf, stdin) || !trim(buf)) {
          puts("Entrada vazia, digite novamente.");
          continue;
        }
        if (!strcmp(buf, "S")) {
          printf("Ok, dados da pessoa %d confirmados!\n", i + 1);
          break;
        } else if (!strcmp(buf, "N")) {
          puts("Reiniciando entrada dessa pessoa...");
          continue;
        } else {
          puts("Entrada inválida, tente de novo.");
          continue;
        }
      } else {
        puts("Digite exatamente dois números positivos, separados por espaço.");
      }
    }
    (person[i].sex == 1) ? (male_sum += person[i].age, male_count++)
                         : (female_sum += person[i].age, female_count++);
  }

  puts("\nTabela de valores:");
  printf("| Gênero | Idade |\n");
  for (int i = 0; i < 20; i++) {
    printf("|   %c    |  %lu  |\n", person[i].sex ? 'M' : 'F', person[i].age);
  }

  double male_avg = male_count ? (double)male_sum / male_count : 0.0;
  double female_avg = female_count ? (double)female_sum / female_count : 0.0;

  printf("\nMédia Masculina: %.2f\n", male_avg);
  printf("Média Feminina: %.2f\n", female_avg);

  puts("Fim do programa.");
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
  return len > 0;
}

void wait(unsigned short ms) { usleep(1000 * ms); }
void clear(void) { system("clear"); }
