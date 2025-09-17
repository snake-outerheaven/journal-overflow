// entrar salário bruto e valor da prestação, prestação não pode ultrapassar 30%
// do salário bruto.

#include <stdio.h>
#include <unistd.h> // << este header faz o código só ser
                    //    executado no Linux ou MacOS.
#include <stdlib.h>

void wait(unsigned short ms);
void clear(void); // clear é de sistemas POSIX, no windows é cls

int main(void) {
  float sal, prest;

  clear();

  puts("Caro funcionário, a prefeitura de Contagem criou uma linha de crédito "
       "para seus funcionários. por favor, digite o seu salário bruto e o "
       "valor da prestação de crédito que deseja receber, mas tenha em mente "
       "que o valor não pode ultrapassar 30% do seu salário bruto.");

  wait(750);

  while (1) {
    sal = 0;
    prest = 0;
    printf(
        "Digite aqui abaixo o salário e a prestação, separados por um espaço "
        "(usar . ao invés de , em números fracionários.)\n: ");
    scanf("%f %f", &sal, &prest);
    if (prest > sal * (30.0 / 100.0)) {
      wait(400);
      puts("Valor muito alto, digite novamente.");
      wait(500);
      puts("Limpando tela...");
      wait(750);
      clear();
      continue;
    } else {
      printf(
          "A prestação de valor %.2f poderá ser emitida para o salário bruto "
          "%.2f.\n",
          sal, prest);
      wait(750);
      break;
    }
  }
  return 0;
}

void wait(unsigned short ms) { usleep(ms * 1000); }

void clear(void) { system("clear"); }
