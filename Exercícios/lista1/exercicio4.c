/*
    Objetivo: calcular novo salário de um funcionário considerando fator de
   aumento dado pelo usuário

    Observação, salário inicial não deve ser nulo e aumento deve ser real, acima
   de 0% no mínimo

    Versão em portugol:

    INICIO

    float s1 = 0, a1 = 0, s2 = 0;

    faça {
      imprimir("Digite o salário do funcionário\n: ");
      ler("%f",&s1);
      imprimir("Digite o percentual de aumento do salário(Ex:
   25%,200%,12%)\n:"); ler("%f%%", &a1); } enquanto(s1 <= 0 || a1 <= 0); s2 = s1
   * (1+(a1/100)); imprimir("O novo salário do funcionário subiu de %.2f para
   %.2f, considerando aumento de %.2f.\n", s1, s2, a1); FIM
*/

// implementação C

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <sys/stat.h>
#include <unistd.h>
#else
#include <sys/stat.h>
#include <windows.h>
#endif

// área dos macros
#ifdef _WIN32
#define MKDIR(path) _mkdir(path)
#define DIR_SEP "\\"
#define STAT _stat
#define STAT_STRUCT struct _stat
#define IS_DIR(mode) ((mode) & _S_IFDIR)
#else
#define MKDIR(path) mkdir(path, 0755)
#define DIR_SEP "/"
#define STAT stat
#define STAT_STRUCT struct stat
#define IS_DIR(mode) S_ISDIR(mode)
#endif

void limpar_tela(void) {
#ifdef _WIN32
  system("cls");
#elif __linux__
  system("clear");
#else
  printf("\033[2J\033[H");
#endif
}

void wait(unsigned int time) {
#ifdef __linux__
  usleep(time * 1000);
#else
  Sleep(time * 1000);
#endif
}

void trim(char *str) {
  int end = (int)strlen(str) - 1;
  int start = 0;
  size_t len = 0;

  while (start <= end && isspace((unsigned char)str[start]))
    start++;

  while (end >= start && isspace((unsigned char)str[end]))
    end--;

  len = end - start + 1; // abc\0 <- pega a posição para colocar o \0

  memmove(str, str + start,
          len); // <- função de string.h que serve para manipular bytes.
                //    essa função move bytes internamente em um array
                //    por mover bytes, serve para array de qualquer tipo
  str[len] = '\0';
}

int salvar(const char *nome, float *s1, float *a1, float *s2) {

  const char *dir = "logs";
  STAT_STRUCT st;

  if (STAT(dir, &st) != 0) {
    if (MKDIR(dir) == -1) {
      perror("Erro ao criar diretório");
      return -1;
    }
  } else if (!IS_DIR(st.st_mode)) {
    fprintf(stderr, "Erro: '%s' existe mas não é um diretório\n", dir);
    return -1;
  }

  char path[512];
  if (snprintf(path, sizeof(path), "%s" DIR_SEP "ex4_log.txt", dir) >=
      (int)sizeof(path)) {
    fprintf(stderr, "Erro: caminho do arquivo muito longo\n");
    return -1;
  }

  FILE *f = fopen(path, "a+");
  if (!f) {
    perror("Erro ao abrir arquivo");
    return -1;
  }

  if (fprintf(f,
              "Nome do funcionário: %s | Salário inicial: %.2f | Percentual de "
              "aumento: %.2f%% | Salário final: %.2f\n",
              nome, *s1, *a1, *s2) < 0) {
    perror("Erro ao escrever no arquivo");
    fclose(f);
    return -1;
  }

  fclose(f);

  printf("Abaixo serão mostradas as ultimas sessões.\n");
  printf("Abrindo arquivo...\n");

  wait(750);

  f = fopen(path, "r");

  char linha[256];
  while (fgets(linha, sizeof(linha), f)) {
    printf("%s", linha);
  }

  fclose(f);
  return 0;
}

void clean_stdin(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int verify_trun(char *str, size_t bufsize) {
  size_t len = strlen(str);

  if (len == 0)
    return 0;

  if (str[len - 1] != '\n') {
    wait(750);
    fprintf(stderr, "String truncada!\n"); // adicionado \n
    clean_stdin();
    return 1;
  }

  str[len - 1] = '\0';
  return 0;
}

int main(void) {
  char nome[100], buffer[15], *endptr;
  float s1, a1, s2;

  do {
    nome[0] = '\0';
    buffer[0] = '\0';
    s1 = 0.0;
    a1 = 0.0;

    limpar_tela();
    printf("\n");
    wait(750);

    printf("Bem vindo administrador, por favor, aguarde...");

    wait(900);

    printf("Digite o nome do funcionário a receber o aumento. (máximo de 100 "
           "caracteres)\n: ");
    fgets(nome, sizeof(nome), stdin);
    if (verify_trun(nome, sizeof(nome)) != 0) {
      continue;
    }
    trim(nome);
    wait(500);
    printf("Digite o salário atual de %s. (salário deve possuir até 15 "
           "caracteres.)\n: ",
           nome);
    fgets(buffer, sizeof(buffer), stdin);
    if (verify_trun(buffer, sizeof(buffer)) != 0) {
      continue;
    }
    trim(buffer);
    s1 = strtof(buffer, &endptr);

    if (endptr == buffer) {
      wait(750);
      fprintf(stderr, "Salário inválido, reiniciando loop.\n"); // adicionado \n
      continue;
    }

    buffer[0] = '\0';

    printf("Digite a porcentagem de aumento do salário %.2f de %s. (Máximo de "
           "15 caracteres)\n: ",
           s1, nome);
    fgets(buffer, sizeof(buffer), stdin);

    if (verify_trun(buffer, sizeof(buffer)) != 0) {
      continue;
    }
    trim(buffer);

    a1 = strtof(buffer, &endptr);

    if (endptr == buffer) {
      fprintf(stderr, "Aumento inválido. Reiniciando loop.\n"); // adicionado \n
      wait(750);
      continue;
    }

  } while (s1 <= 0 || a1 <= 0);

  s2 = s1 * (1 + (a1 / 100));

  printf("O salário de %s depois do aumento é %.2f.\n", nome, s2);

  printf("Aguarde para ver as ultimas sessões.\n");
  wait(750);

  if (salvar(nome, &s1, &a1, &s2) != 0) {
    wait(750);
    printf(
        "Não foi possível salvar a sessão do programa, anote em um papel.\n");
    return 0;
  }

  return 0;
}
