#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
        jogo de bingo em C, exercício da revisão.
*/

int
main (void)
{
  int cartela[100], i, x;
  int num = 0;
  int inf = 1;
  int sup = 100;
  int achei = 0;
  setlocale (LC_ALL, "pt_BR.UTF-8");
  srand (time (0));

  num = (rand () % (sup - inf + 1)) + inf;
  cartela[0] = num;
  printf ("%d ", cartela[0]);

  for (i = 1; i < 100 && !achei; i++)
    {
      num = (rand () % (sup - inf + 1)) + inf;

      for (x = (i - 1); x >= 0 && !achei; x--)
        if (num == cartela[x])
          achei = 1;

      if (!achei)
        {
          cartela[i] = num;
          printf ("%d ", num);
        }
      else
        printf ("\nO valor %d foi encontrado na posição %d\n", num, x + 1);
    }

  for (x = 0; x < i - 1; x++)
    {
      if ((x % 10) == 0)
        printf ("\n");
      printf ("%d\t", cartela[x]);
    }

  return 0;
}

/*
================== FLUXO DO JOGO DE BINGO ==================

1. INICIALIZAÇÃO:
   - Define o intervalo de números: 1 a 100
   - Inicializa a semente aleatória com time(0)
   - Cria um array 'cartela' para armazenar até 100 números

2. GERAÇÃO DE NÚMEROS:
   - Gera o primeiro número aleatório e o armazena em cartela[0]
   - Para cada posição (1 a 99):
     * Gera um novo número aleatório
     * Verifica se o número já foi sorteado (duplicata)
     * Se duplicata encontrada: interrompe o loop e exibe mensagem
     * Se novo número: adiciona ao array e exibe na tela

3. VALIDAÇÃO DE DUPLICATAS:
   - Compara o novo número com todos os anteriores no array
   - Utiliza a variável 'achei' como flag de controle
   - Se 'achei' = 1, indica que o número já foi sorteado

4. EXIBIÇÃO FINAL:
   - Formata a exibição com 10 números por linha
   - Usa tabulação (\t) para melhor apresentação
   - Mostra todos os números válidos da cartela

5. RESULTADO:
   - Total de números únicos gerados: i - 1
   - Status: Indica se uma duplicata foi encontrada ou se 100 números
     únicos foram sorteados com sucesso

=============================================================
*/
