#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// objetivo: um carro custa ao consumidor o preço de fabrica + impostos e
// comissão do revendedor. Fazer um algoritmo que receba o preço e o percentual
// de impostos e comissão do revendedor. e exiba o preço final do carro
// acompanhado do valor dos impostos e comissão do revendedor.

void trim(char *str);
int converter(char *str, float *x);
void wait_posix(unsigned int time);

int main(void) {
  char buf[15];
  float preco = 0.0F, impostos = 0.0F, comissao = 0.0F;

  printf("Administrador, este programa possui a finalidade de calcular o preço "
         "final de um carro, impostos e comissão do revendedor.\n");
  wait_posix(250);
  printf("Faça bom uso do programa!\n");

  while (1) {
    printf("Digite o preço do carro (digite 0 para sair).\n: ");
    fgets(buf, sizeof(buf), stdin);
    trim(buf);
    if (!converter(buf, &preco))
      continue;

    if (preco == 0.0F) {
      printf("Obrigado por usar este programa!\n");
      wait_posix(650);
      break;
    }

    printf("Digite o percentual de impostos (digite apenas a parte numérica, "
           "sem o %%)\n: ");
    fgets(buf, sizeof(buf), stdin);
    trim(buf);
    if (!converter(buf, &impostos))
      continue;

    printf(
        "Digite o percentual de comissão do revendedor (digite apenas a parte "
        "numérica, sem o %%)\n: ");
    fgets(buf, sizeof(buf), stdin);
    trim(buf);
    if (!converter(buf, &comissao))
      continue;

    float preco_final =
        preco + (preco * impostos / 100) + (preco * comissao / 100);
    printf("Preço final do carro: %.2f R$.\n", preco_final);
    printf("Valor dos impostos: %.2f\n R$.", preco * impostos / 100);
    printf("Valor da comissão do revendedor: %.2f R$.\n",
           preco * comissao / 100);
  }
}

void wait_posix(unsigned int time) { usleep(time * 1000); }

int converter(char *str, float *x) {
  if (!sscanf(str, "%f", x)) {
    wait_posix(250);
    printf("Falha na conversão.");
    wait_posix(250);
    return 0;
  }
  return 1;
}

void trim(char *str) {
  size_t end = strlen(str) - 1;
  size_t start = 0;
  size_t len = 0;

  while (start < end && isspace(str[start]))
    start++;

  while (end > start && isspace(str[end]))
    end--;

  len = end - start + 1;
  memmove(str, str + start, len);
  str[len] = '\0';
}
