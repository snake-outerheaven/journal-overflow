/*11 – Faça um algoritmo para calcular o IMC de um indivíduo após a leitura de
seu peso e altura. Em seguida classifique-o pela tabela : IMC abaixo de 18,5
Abaixo do peso IMC de 18,5 até 24,9 Peso Normal, IMC de 25 até 29,9 Sobre Peso
IMC de 30 até 34,9 Obesidade Grau 1, IMC de 35 ate 39,9 Obesidade Grau 2, A
partir 40 Obesidade Mórbida.  */

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool convert_float(char *in, float *out);
void wait(unsigned short ms);
void trim(char *buf);
void clear();

int main(void) {
  char buf[15];
  float peso, altura, imc;

  wait(500);

  puts("Olá usuário, este programa receberá um peso e uma altura, calculará o "
       "IMC e exibirá a classificação do IMC.");

  while (true) {
    peso = 0.0F;
    altura = 0.0F;

    printf("Por favor, digite o peso. (até 15 caracteres)\n: ");
    fgets(buf, sizeof(buf), stdin);
    trim(buf);
    if (!convert_float(buf, &peso)) {
      continue;
    }

    printf("Certo, agora digite a altura. (até 15 caracteres)\n: ");
    fgets(buf, sizeof(buf), stdin);
    trim(buf);
    if (!convert_float(buf, &altura)) {
      continue;
    }

    printf("Confirma peso: %.1f e altura: %.2f? (s/n)\n: ", peso, altura);
    fgets(buf, sizeof(buf), stdin);
    trim(buf);
    if (strcmp(buf, "S") == 0 || strcmp(buf, "s") == 0) {
      puts("Certo, peso e altura confirmados, continuando programa...");
      wait(1000);
    } else {
      puts("Entrada não confirmada, por favor, digite os valores novamente.");
      wait(500);
      continue;
    }

    imc = peso / pow((double)altura, 2.0);

    printf("O IMC é: %.2f e recebe a classificação: ", imc);

    if (imc < 18.5F) {
      puts("Abaixo do peso");
    } else if (imc < 25.0F) {
      puts("Peso Normal");
    } else if (imc < 30.0F) {
      puts("Sobrepeso");
    } else if (imc < 35.0F) {
      puts("Obesidade Grau 1");
    } else if (imc < 40.0F) {
      puts("Obesidade Grau 2");
    } else {
      puts("Obesidade Mórbida");
    }

    break;
  }

  return 0;
}

bool convert_float(char *in, float *out) {
  if (!sscanf(in, "%f", out)) {
    wait(500);
    fprintf(stderr, "%s não é capaz de ser convertido!\n", in);
    return false;
  }
  return true;
}

void wait(unsigned short ms) { usleep(ms * 1000); }

void trim(char *buf) {
  size_t end = strlen(buf);
  if (end == 0)
    return;
  size_t start = 0;
  size_t len;
  end--;

  while (end > start && isspace(buf[start]))
    start++;
  while (start < end && isspace(buf[end]))
    end--;

  len = end - start + 1;
  memmove(buf, buf + start, len);
  buf[len] = '\0';
}

void clear() { system("clear"); }
