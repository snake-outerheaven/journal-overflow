// 5) Dado o exercício 4 calcule o percentual de jovens de cada sexo em cada modalidade.

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MINSPORT 1
#define MAXSPORT 3

#define N 75

int gen_gend();
int gen_age();
int gen_sport();

int gen_percs(int[], int[], float[][2]);


int main()
{
	size_t i, y;
	int gend[N] = {0};
	int sport[N] = {0};
	char *sports[] = {"Basquete", "Futebol", "Vôlei"};
	float percs[MAXSPORT][2] = {0};

	setlocale(LC_ALL, "pt_BR.UTF-8");
	srand(time(0));

	for(i = 0; i < N; ++i)
	{
		gend[i] = gen_gend();
		sport[i] = gen_sport();
	}

	if(!gen_percs(gend, sport, percs))
	{
		puts("Falha ao gerar percentuais.");
		return 1;
	}

	for(i = 0; i < MAXSPORT; ++i)
		for(y = 0; y < 2; ++y)
			printf("O percentual de jovens do gênero %s "
					"no esporte %s "
					"é %.2f.\n",
					(y) ? "Masculino" : "Feminino",
					sports[i],
					percs[i][y]);

	return 0;
}

int gen_sport()
{
	return rand() % MAXSPORT;
}

int gen_gend()
{
	return (rand() % 2 == 0);
}

int gen_percs(int gend[], int sport[], float percs[][2])
{
	size_t i;

	int totalSport[MAXSPORT] = {0};
	int gendCount [MAXSPORT][2] = {0};


	if(!gend || !sport || !percs)
		return 0;

	for(i = 0; i < N; ++i)
	{
		gendCount[sport[i]][gend[i]]++;
		totalSport[sport[i]]++;
	}

	for(i = 0; i < MAXSPORT; ++i)
	{
		if(totalSport[i] > 0)
		{
			percs[i][0] = (float)gendCount[i][0] / totalSport[i];
			percs[i][1] = (float)gendCount[i][1] / totalSport[i];
		}
		else
		{
			percs[i][0] = 0;
			percs[i][1] = 0;
		}

	}

	return 1;
}

