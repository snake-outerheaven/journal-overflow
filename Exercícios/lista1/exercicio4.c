/*
    Objetivo: calcular novo salário de um funcionário considerando fator de
   aumento dado pelo usuário

    Observação, salário inicial não deve ser nulo e aumento deve ser real, acima
   de 0% no mínimo

    Versão em portugol:

    float s1 = 0, a1 = 0, s2 = 0;

    faça {
      imprimir("Digite o salário do funcionário\n: ");
      ler("%f",&s1);
      imprimir("Digite o percentual de aumento do salário(Ex: 25%,200%,12%)\n:
   "); ler("%f%%", &a1); } enquanto(s1 <= 0 || a1 <= 0); s2 = s1 * (1+
   (a1/100)); imprimir("O novo salário do funcionário subiu de %.2f para %.2f,
   considerando aumento de %.2f.\n", s1, s2, a1);
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
#include <direct.h>
#include <windows.h>
#endif

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
  int i = 0;

  // obtenho todos os espaços em branco no inicio da string
  while (start <= end && isspace((unsigned char)str[start]))
    start++;

  // obtenho todos os espaços em branco entre a ultima letra até o caracter
  // finalizado '\0'
  while (end >= start && isspace((unsigned char)str[end]))
    end--;

  // cada caracter vai sendo passado para a posição ideal
  //
  // Ex:
  //
  // ___aoba__\0 -> tem len igual a 10, mas só 9 caracteres úteis(\0 indica o
  // fim da string)
  //                onde destes 9, 5 são caracteres vazios, o que se faz que
  //                seja necessário limpar a string, isto é feito através da
  //                estrutura de repetição abaixo, onde cada caractere está
  //                sendo movido uma casa para a esquerda em cada iteração do
  //                loop
  //
  // start sobe até ser igual a 2, e
  while (start <= end)
    str[i++] = str[start++];

  // depois deste loop encontrar seu fim,
  // a string fica da seguinte forma:
  //
  // aoba_____\0
  //
  // todos os espaços foram movidos para a direita, e agora se faz necessário
  // mudar o final da string para a posição 5 para ficar aoba\0, felizmente, i
  // equivale ao indice da casa posterior ao final da string, sendo necessário
  // apenas colocar o caracter finalizador em sua posição
  str[i] = '\0';
}

void salvar(char *nome, float *s1, float *a2, float *s2, char *format) {}
