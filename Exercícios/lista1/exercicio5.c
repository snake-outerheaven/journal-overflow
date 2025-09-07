#include <ctype.h>
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
  char nome[100] = {""}, buffer[15] = {""};
  float s1 = 0, a = s1 * (30.0 / 100.0), s2 = 0;

  
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
  short int end = (short int)strlen(str) - 1;
  short int start = 0;
  short int len = 0;

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
