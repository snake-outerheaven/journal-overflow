/*
 Objetivo: Escrever um algoritmo que receba o peso e a altura e calcule o seu
 IMC

 Observação: Tanto peso quanto altura não podem ser negativos nem nulos


 Versão em portugol


 INICIO

 float peso = 0, altura = 0, imc = 0;
 faça {
   imprimir("Por favor, digite o peso e a altura do paciente (escrever"
 " da seguinte maneira:"peso altura", com espaço entre os valores )\n: ");
   ler("%f %f", &peso, &altura);
 } enquanto(peso <= 0 ou altura <= 0);
 imc = peso/(altura*altura);
 imprimir("O IMC do paciente é: %f", imc);

 FIM
   */

// implementação em C

#include <stdio.h>

int main(void) {
  float peso = 0, altura = 0, imc = 0;
  do {
    printf("Por favor, digite o peso e a altura do paciente (escrever da "
           "seguinte maneira: 'peso altura', com espaço entre os valores)\n: ");
    scanf("%f %f", &peso, &altura);
  } while (peso <= 0 || altura <= 0);
  imc = peso / (altura * altura);
  printf("O imc do paciente é %.2f", imc);
  return 0;
}
