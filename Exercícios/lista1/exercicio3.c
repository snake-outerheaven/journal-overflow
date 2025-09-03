/*
Objetivo: fazer um algoritmo que receba o salário de um funcionário e mostre
o seu novo salário acrescido de 25%

Observação: Salário não pode ser negativo ou nulo

Versão em Portugol:

INICIO
    float s1 = 0, s2 = 0;

    faça {
        imprimir("Digite o salário do funcionário para gerar o novo salário com
aumento de 25%: "); ler("%f", s1); } enquanto (s1 <= 0);

    s2 = s1 * 1.25;
    imprimir("O novo salário do funcionário é: %f\n", s2);
FIM
*/

// Implementação em C

// cabeçalhos são as bibliotecas disponíveis em C para voce usar nos seus
// programas como a maioria dos sistemas operacionais é feito em C, sempre tem
// algumas disponíveis
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32 // se o sistema onde este código for compilado for windows, chama
              // esse cabeçalho
#include <windows.h> // Biblioteca do Windows para funções de sistema
#else
#include <unistd.h> // Biblioteca Unix/Linux/macOS/FreeBSD para funções de sistema
#endif

// Função que implementa espera em milissegundos
void wait(unsigned int time) {
#ifdef _WIN32
  Sleep(time * 1000); // Windows Sleep recebe milissegundos
#else
  usleep(time * 1000); // POSIX usleep recebe microsegundos
#endif
}

// Função que remove espaços em branco ao redor de uma string
void trim(char *str) {
  int end = strlen(str) - 1;
  int start = 0;
  int i = 0;

  while (isspace((unsigned char)str[start]))
    start++;
  while (end >= start && isspace((unsigned char)str[end]))
    end--;
  while (start <= end)
    str[i++] = str[start++];
  str[i] = '\0';
}

int main(void) {
  char nome[100], res[10], buffer[50];
  float s1, s2;
  char *endptr;

  while (1) { // lembra do que eu falei de booleanos, 1 sempre significa verdadeiro, então este é um loop infinito em C
    // Inicializa variáveis
    nome[0] = '\0';
    res[0] = '\0';

    // Solicita nome do funcionário
    printf("\nPor favor, digite o nome do funcionário a ganhar o aumento: ");
    fgets(nome, sizeof(nome), stdin); // lê string do standard input
    trim(nome);

    wait(750);
    printf("Você confirma o nome '%s'? (S/N): ", nome);
    fgets(res, sizeof(res), stdin);
    trim(res);

    if (strcmp(res, "S") != 0 && strcmp(res, "N") != 0) {
      wait(750);
      printf("Resposta inválida, digite novamente.\n");
      continue;
    } else if (strcmp(res, "N") == 0) {
      printf("Ok, digite o nome novamente!\n");
      wait(550);
      continue;
    }

    // Loop para leitura e validação do salário
    while (1) {
      printf("Digite o salário de %s: ", nome);
      fgets(buffer, sizeof(buffer), stdin);
      trim(buffer);

      s1 = strtof(buffer, &endptr); // converte de texto para numero real ( float )

      // eu passo de texto para número real para garantir que o número digitado pelo usuário é seguro
      // para o programa, em C, voce tem que criar todos os algoritmos do 0, então pensar em tudo é
      // essencial.

      // quando a função falha ela retorna o valor parcial da conversão em um
      // ponteiro( variavel que aponta para um lugar da memória do computador)
      // Verifica se strtof deu ruim ou valor <= 0
      if (endptr == buffer || s1 <= 0) {
        printf("Salário inválido! Digite um valor positivo.\n");
        continue;
      }
      break;
    }

    // Confirmação final de nome e salário
    printf("Você confirma o nome '%s' e o salário %.2f? (S/N): ", nome, s1); // onde está %s aparece o nome( string )
                                                                             // e o %f aparece o salário inicial o .2 serve
                                                                             // para mostrar apenas 2 casas decimais
    fgets(res, sizeof(res), stdin);
    trim(res);

    if (strcmp(res, "S") == 0) {
      wait(550);
      printf("Nome e salário confirmados!\n");
      break;
    } else {
      printf("Reiniciando entrada...\n");
      wait(900);
    }
  }

  // Calcula novo salário
  s2 = s1 * 1.25;
  printf("O salário final de %s é %.2f\n", nome, s2);
  return 0;
}
