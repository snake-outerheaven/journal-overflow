#include <stdio.h>

/*
 * Exercício 3:
 *
 * Escrever um programa que recebe nome, e ano de nascimento,
 * calculando a idade utilizando o ano atual (2026 no período
 * que este código é escrito)
 */

/*
 * O macro define aqui, é usado para definir um símbolo
 * que é substituido pelo compilador em tempo de pré processamento
 * sendo sua sintaxe:
 *
 *
 * #define SIMBOLO VAL
 *
 * ele é muito útil para evitar a presença de números mágicos,
 * estes, são números arbitrários que tornam difícil a leitura
 * e modularidade do problema computacional a ser resolvido.
 *
 */

#define MAXNAME 30

#define ANO 2026


int main(void)
{
	/*
	 * o = {0} é uma forma de inicializar
	 * rapidamente todos os elementos de
	 * um array sem a necessidade de
	 * um loop for
	 */

	char nome[MAXNAME] = {0};

	int ano_nascimento = 0;

	printf("Usuário, digite o seu nome abaixo\n"
		       "(ele deve conter %d letras): ", MAXNAME);

	scanf("%s", nome);

	printf("%s, digite o seu ano de nascimento: ", nome);
	scanf("%d", &ano_nascimento);

	printf("%s, voce tem %d anos em %d.\n"
			, nome, ANO - ano_nascimento, ANO);

	return 0;
}

