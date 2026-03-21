// 4) Faça um programa que gere aleatoriamente o sexo(1 - M ou 0 - F) a idade
// (12 a 17)e o esporte preferido (1 – Basquete, 2 – Futebol ou 3 – Vôlei) de um
// grupo de 75 jovens e calcule: a média de idade dos jovens que preferem cada
// esporte e a média das idades dos meninos e das meninas.

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXAGE 17
#define MINAGE 12

#define MINSPORT 1
#define MAXSPORT 3

#define N 75

typedef struct Jovem
{
    int gender;
    int age;
    int sport;
} Jovem;

int gen_gend();
int gen_age();
int gen_sport();

int gen_avg(Jovem *, float[], float[]);

int main()
{
    Jovem j[N] = {0};
    size_t i;
    float avgSport[MAXSPORT] = {0};
    float avgGend[2] = {0};
    char *sports[3] = {"Basquete", "Futebol", "Vôlei"};

    setlocale(LC_ALL, "pt_BR.UTF-8");

    srand(time(0));

    for (i = 0; i < N; ++i)
    {
        j[i].age = gen_age();
        j[i].gender = gen_gend();
        j[i].sport = gen_sport();
    }

    if (!gen_avg(j, avgSport, avgGend))
    {
        puts("Falha ao gerar médias.");
        return 1;
    }

    for (i = 0; i < MAXSPORT; ++i)
        printf("Média de idades para o esporte %s: %.2f.\n", sports[i],
               avgSport[i]);

    for (i = 0; i < 2; ++i)
        printf("Média de idade para %s %s: %.2f.\n", (i) ? "os" : "as",
               (i) ? "Meninos" : "Meninas", avgGend[i]);

    return 0;
}

int gen_gend()
{
    return rand() % 2;
}

int gen_age()
{
    return rand() % (MAXAGE - MINAGE + 1) + MINAGE;
}

int gen_sport()
{
    return rand() % (MAXSPORT - MINSPORT + 1) + MINSPORT;
}

int gen_avg(Jovem *j, float sportAvg[], float sportGend[])
{
    size_t i;
    int sumSport[3] = {0};
    int totalSport[3] = {0};
    int sumGend[2] = {0};
    int totalGend[2] = {0};

    if (!j || !sportAvg || !sportGend)
        return 0;

    for (i = 0; i < N; i++)
    {
        (j[i].gender) ? (sumGend[1] += j[i].age, totalGend[1]++)
                      : (sumGend[0] += j[i].age, totalGend[0]++);
        switch (j[i].sport)
        {
        case 1:
            totalSport[0]++;
            sumSport[0] += j[i].age;
            break;

        case 2:
            totalSport[1]++;
            sumSport[1] += j[i].age;
            break;
        case 3:
            totalSport[2]++;
            sumSport[2] += j[i].age;
            break;
        }
    }

    for (i = 0; i < 2; i++)
        (totalGend[i] > 0) ? (sportGend[i] = (float)sumGend[i] / totalGend[i])
                           : (sportGend[i] = 0.0F);

    for (i = 0; i < MAXSPORT; ++i)
        (totalSport[i] > 0) ? (sportAvg[i] = (float)sumSport[i] / totalSport[i])
                            : (sportAvg[i] = 0.0F);

    return 1;
}
