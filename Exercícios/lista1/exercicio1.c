/*
  Objetivo: ler duas notas, fazer a média entre elas e exibir em tela.

  Observação: Notas propriamente ditas estão sempre entre 0 e 10.

   Versão portugol

   INICIO
    float n1,n2,M;
    faça {
     n1 = 0.0;
     n2 = 0.0;
     ler("%f %f", n1,n2);
    } enquanto (n1 < 0.0 ou n2 < 0.0 ou n1 > 10.0 ou n2 > 10.0)
    M = (n1+n2) / 2.0;
    mostrar_em_tela("Média é %f\n", M);
   FIM
 */

// implementação em C

#include <stdio.h> // biblioteca padrão de leitura e saída

int main(void) {
  float n1 = 0, n2 = 0, m = 0; // em C, variáveis inicializadas sem receber
                               // valores recebem valores aleatórios
  do {
    printf("Digite as notas da seguinte maneira (n1 n2), com um espaço entre "
           "as notas\n: ");
    scanf("%f %f", &n1, &n2);
  } while (n1 < 0.0 || n2 < 0.0 || n1 > 10.0 || n2 > 10.0);
  m = (n1 + n2) / 2.0;
  printf("A média é %.2f.", m);
  // .2 significa que o numero vai exibir apenas 2 casas depois da virgula
  // válido até 6
  return 0; // fim do programa
}
