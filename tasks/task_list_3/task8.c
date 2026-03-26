// 8) Um hospital está fazendo um estudo referente um conjunto de 100 pacientes atendidos em sua emergência, 
// para isso faça um programa que gere aleatoriamente o 
// tipo de atendimento(0– Clinica Geral ou 1 – Ortopedia) 
// a origem (0 – Particular ou 1 – Plano de Saúde) e 
// a idade dos pacientes(0- 90). 
// Calcule o percentual de atendimentos de cada tipo, 
// a média de idade dos pacientes de cada origem 
// e o percentual de pacientes da Clínica geral com idade superior a 60 ano.

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MINAGE 0
#define MAXAGE 90

#define N 100

int gen_type();
int gen_origin();
int gen_age();

int main()
{
	size_t i;
	int tipo, origem, idade;
	int totT0 = 0, totT1 = 0;
	int totO0 = 0, totO1 = 0;
	int tot60 = 0;
	int sum1 = 0, sum2 = 0;
	float avg1, avg2;
	float perc1, perc2, perc60;

	setlocale(LC_ALL, "pt_BR.UTF-8");
	srand(time(0));

	for(i = 0; i < N; i++)
	{
		tipo = gen_type();
		origem = gen_origin();
		idade = gen_age();

		if(tipo == 0)
			totT0++; // total de pacientes da clinica

		else
			totT1++; // total de pacientes

		if(origem == 0)
			sum1 += idade, totO0++;
			// acumula idade e conta os pacientes
			// do particular
		else
			sum2 += idade, totO1++;
			// acumula idade e conta os pacientes
			// do plano


		if(tipo == 0 && idade > 60)
			tot60++;
	}

	// calcula médias
	avg1 = (totO0 > 0) ? (float)sum1 / totO0 : 0;
	avg2 = (totO1 > 0) ? (float)sum2 / totO1 : 0;

	// calcula percentuais
	perc1 = (float)totT0 / N * 100;
	perc2 = (float)totT1 / N * 100;
	perc60 = (float)tot60 / N * 100;

	puts("");
	puts("");
	puts("");

	puts("-----Avaliação dos dados processados----");

	printf("Média de idades "
			"da origem Particular: %.1f%%.\n",
			avg1);

	printf("Média de idades "
			"da origem Plano de Saúde: %.1f%%.\n",
			avg2);

	printf("Percentual de pacientes "
			"do tipo Clinica Geral: %.1f%%.\n",
			perc1);

	printf("Percentual de pacientes "
			"do tipo Ortopedia: %.1f%%.\n",
			perc2);

	printf("Percentual de pacientes "
			"do tipo Clinica Geral "
			"com mais de 60 anos: %.1f%%.\n",
			perc60);

	return 0;
}

int gen_type()
{
	return ((rand() % 2 ) == 0);
}


int gen_origin()
{
	return ((rand() % 2 ) == 0);
}

int gen_age()
{
	return rand() % (MAXAGE - MINAGE + 1) + MINAGE;
}

