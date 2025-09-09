#include <stdio.h>
#include <unistd.h>

// objetivo: receber valor, taxa de juros, tempo, e calcular montante em juros
// compostos. OBS: O programa é compatível somente com sistemas POSIX (UNIX,
// Linux, MacOS, FreeBSD, e parecidos.) isso se dá devido ao uso do header
// <unistd.h>, que é único destes sistemas.

// área dos protótipos das funções.
void wait_posix(unsigned int seconds);
int converter(char *buf, float *valor);

int main(void) {
  char buf[50] = {""};
  float valor = 0.0F, taxa = 0.0F, tempo = 0.0F, montante = 0.0F;

  while (1) {
    buf[0] = '\0';
    printf("\n");
    wait_posix(750);
    printf("Digite o valor a ser investido: ");
    fgets(buf, sizeof(buf), stdin);
    if (!converter(buf, &valor)) {
      continue;
    }
    if (valor <= 0) {
      printf("Encerrando...\n");
      wait_posix(1000);
      break;
    }
    wait_posix(1000);
    printf("Digite a taxa de juros: ");
    fgets(buf, sizeof(buf), stdin);
    if (!converter(buf, &taxa)) {
      continue;
    }
    wait_posix(1000);
    printf("Digite o tempo em meses: ");
    fgets(buf, sizeof(buf), stdin);
    if (!converter(buf, &tempo)) {
      continue;
    }
    wait_posix(1000);
    montante = valor + (valor * taxa * tempo / 100);
    printf("Montante: %.2f\n", montante);
  }
  return 0;
}

// area das funções.
void wait_posix(unsigned int seconds) { usleep(seconds * 1000); }

int converter(char *buf, float *valor) {
  if (!sscanf(buf, "%f", valor)) {
    wait_posix(1000);
    printf("Valor inválido!\n");
    return 0;
  }
  return 1;
}
