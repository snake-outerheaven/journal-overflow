#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// objetivo: obter duas notas, percentual de frequencia e calcular a média, e
// então dizer a situação do aluno.
//
// Possíveis situações:
// aluno está aprovado se a média for maior ou igual a 7.0 e frequencia maior ou
// igual a 75%, prova final se a media for maior igual a 4 e frequencia maior ou
// igual a 75%, reprovado se média menor que quatro ou frequencia menor que 75%

void trim(char *buf);
void wait(unsigned short ms);
bool convert(char *in, float *out);
bool convert_int(char *in, int *out);

int main(void) {
  char buf[20];
  int freq;
  float notas[2], m;
  bool pass;

  puts("Professor, seja bem vindo este programa, aqui, você conseguirá "
       "inserir a n1 e n2, e o percentual de frequência dos alunos e então, "
       "será exibida a situação do aluno neste semestre.");
  wait(750);
  for (int i = 0; i < 2; i++) {
    while (true) {
      printf("Por favor, digite a %dª nota\n: ", i + 1);
      fgets(buf, sizeof(buf), stdin);
      trim(buf);
      if (!convert(buf, &notas[i])) {
        puts("Nota inválida, por favor digite novamente.");
        wait(500);
        continue;
      } else {
        printf("A nota digitada foi %.2f, você confirma isto? (s/n)\n: ",
               notas[i]);
        fgets(buf, sizeof(buf), stdin);
        trim(buf);
        if (strcmp(buf, "s") == 0 || strcmp(buf, "S") == 0) {
          if (notas[i] < 0 || notas[i] > 10) {
            puts("Nota não pode ser maior que 10 e menor que 0, tente "
                 "novamente.");
            wait(500);
            continue;
          }
          puts("Nota confirmada!");
          wait(500);
          break;
        } else {
          puts("Resposta inválida, digite novamente para fins de segurança.");
          wait(500);
          continue;
        }
      }
    }
  }

  m = (notas[0] + notas[1]) / 2.0F;
  if (m < 4.0F) {
    puts("O aluno está reprovado por apresentar média menor que 4.");
    wait(300);
    puts("Encerrando programa...");
    wait(750);
    exit(0);
  }

  while (true) {
    printf("Ok, a média do estudante é %.2f, por favor, digite o percentual de "
           "frequência do aluno (digitar apenas o número, sem o %%)\n: ",
           m);

    fgets(buf, sizeof(buf), stdin);
    trim(buf);
    if (!convert_int(buf, &freq)) {
      puts("Entrada digitada não é válida.");
      wait(500);
      continue;
    } else {
      printf("Gostaria de confirmar o percentual de frequência %d? (s/n)\n: ",
             freq);
      fgets(buf, sizeof(buf), stdin);
      trim(buf);
      if (strcmp(buf, "s") == 0 || strcmp(buf, "S") == 0) {
        puts("Frequência confirmada!");
        wait(500);
        break;
      } else {
        puts("Resposta inválida, digite novamente para fins de segurança.");
        wait(500);
        continue;
      }
    }
  }

  if (m >= 7.0F && freq >= 75)
    puts("Aluno aprovado!");
  else if (m >= 4.0F && freq >= 75)
    puts("Aluno na prova final.");
  else
    puts("Aluno reprovado.");

  return 0;
}

void trim(char *buf) {
  size_t end = strlen(buf);
  if (end == 0) {
    return;
  }
  size_t start = 0;
  end--;
  size_t len;

  while (end >= start && isspace(buf[start]))
    start++;

  while (start <= end && isspace(buf[end]))
    end--;

  len = end - start + 1;
  memmove(buf, buf + start, len);
  buf[len] = '\0';
}

void wait(unsigned short ms) { usleep(ms * 1000); }

bool convert(char *in, float *out) {
  if (!sscanf(in, "%f", out)) {
    return false;
  }
  return true;
}

bool convert_int(char *in, int *out) {
  if (!sscanf(in, "%d", out)) {
    return false;
  }
  return true;
}
