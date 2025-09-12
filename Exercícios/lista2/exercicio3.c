#include <stdio.h>

// objetivo: ler peso e altura de uma pessoa e calcular o IMC (IMC = peso/altura
// ** 2) verifique se o individuo está no peso ideal (IMC >=18.5 && IMC < 25)

int main(void) {
  float peso, altura, imc;

  puts("Digite o peso do paciente:");
  scanf("%fkg", &peso);

  puts("Digite a altura do paciente:");
  scanf("%fm", &altura);

  imc = peso / (altura * altura);

  printf("O imc do paciente é %.2f.\n", imc);

  if (imc >= 18.5F && imc < 25) {
    puts("Paciente no peso ideal.");
  } else {
    puts("Paciente ou está acima ou está abaixo do peso ideal.");
  }

  return 0;
}
