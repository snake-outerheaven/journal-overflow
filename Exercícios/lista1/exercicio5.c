#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <unistd.h>
#else
#include <windows.h>
#endif

// objetivo: receber o salário de um funcionário, calcular novo salário
// considerando gratificação de 30% do valor inicial - 7% do total.

// protótipos de funções
void limpar_tela(void);
void wait(unsigned short int time);
void trim(char *str);

// main

int main(void) {
  char nome[100] = {""}, numbuf[15] = {""}, respbuf[5] = {""};
  float s1 = 0, a = 0, s2 = 0;
  bool verifyresp = false, verifyyes = false, verifyno = false;

  limpar_tela();

  printf("Administrador, seja bem vindo ao sistema de gerenciamento de "
         "funcionários.\n");

  wait(750);
  while (true) {
    printf("Por favor, digite o nome do funcionário. (até 100 caracteres)\n: ");
    fgets(nome, sizeof(nome), stdin);
    trim(nome);
    if (strlen(nome) == 0) {
      printf("Nome inválido. Por favor, tente novamente.\n");
      wait(1500);
      limpar_tela();
      continue;
    }
    printf("Por favor, digite o salário atual do funcionário. (até 14 "
           "caracteres)\n: ");
    fgets(numbuf, sizeof(numbuf), stdin);
    trim(numbuf);
    if (strlen(numbuf) == 0 || !sscanf(numbuf, "%f", &s1)) {
      printf("Houve um erro ao receber o salário atual do funcionário.\n");
      wait(760);
      printf("Será necessário realizar uma nova operação de registro.\n");
      wait(760);
      continue;
    }
    wait(750);

    do {

      printf("Dados obtidos do funcionário: \nNome: %s\nSalário atual: %.2f\n",
             nome, s1);
      printf("Os dados são válidos? (s/n)\n: ");
      fgets(respbuf, sizeof(respbuf), stdin);
      trim(respbuf);
      if (strcmp(respbuf, "n") == 0) {
        verifyno = true;
        verifyresp = true;
      } else if (strcmp(respbuf, "s") == 0) {
        verifyyes = true;
        verifyresp = true;
      } else {
        printf("Resposta inválida. Por favor, tente novamente.\n");
        wait(750);
        verifyresp = false;
      }
    } while (!verifyresp);
    if (verifyyes) {
      printf("Certo, aguarde para prosseguir.\n");
      wait(750);
      break;
    } else if (verifyno) {
      printf("Certo, aguarde para realizar nova operação de registro.\n");
      wait(750);
      continue;
    }
  }
  a = s1 * (30.0F / 100.0F);
  s2 = s1 + a;
  printf("Salário de %s antes de ser cobrado a taxa de 7%% é de %.2f\n", nome,
         s2);
  s2 = s2 - (s2 * 0.07F); // este trecho se colocado na linha 87 causa
                          // comportamento indefinido.
  printf("O salário de %s agora é de %.2f\n", nome, s2);
  wait(750);
  printf("Obrigado por usar este programa!\n");
  return 0;
}

// campo das funções

void limpar_tela() {
#ifdef _WIN32
  system("cls");
#elif __linux__
  system("clear");
#else
  printf("\033[2J\033[H");
#endif
}

void wait(unsigned short int time) {
#ifdef __linux__
  usleep(time * 1000);
#else
  Sleep(time * 1000);
#endif
}

void trim(char *str) {
  size_t end = (short int)strlen(str) - 1;
  size_t start = 0;
  size_t len = 0;

  while (start <= end && isspace((unsigned char)str[start])) {
    start++;
  }

  while (end >= start && isspace((unsigned char)str[end])) {
    end--;
  }

  len = end - start + 1;

  memmove(str, str + start, len);

  str[len] = '\0';
}
