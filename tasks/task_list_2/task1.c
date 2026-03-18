// 1) Fazer um programa que gere aleatoriamente que leia a idade(17 a 45) e o
// sexo (1 - M ou 2 -F) de 20 indivíduos e calcule a média de idade de cada
// grupo.

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_AGE 17
#define MAX_AGE 45

#define QUANTITY 20

#define MALE 1
#define FEMALE 2

int gen_age();
int gen_gender();

void gen_avg(int[], int[], float[]);

int main()
{
    size_t i;
    float avg[2];
    int age[QUANTITY], gender[QUANTITY];

    setlocale(LC_ALL, "pt_BR.UTF-8");

    srand(time(NULL));

    for (i = 0; i < QUANTITY; i++)
        age[i] = gen_age();

    for (i = 0; i < QUANTITY; i++)
        gender[i] = gen_gender();

    gen_avg(age, gender, avg);

    for (i = 0; i < 2; i++)
        printf("Média do grupo dos/as %s: %.2f.\n", (i) ? "Mulheres" : "Homens",
               avg[i]);

    return 0;
}

int gen_age()
{
    return (rand() % (MAX_AGE - MIN_AGE + 1)) + MIN_AGE;
}

int gen_gender()
{
    return rand() % (FEMALE - MALE + 1) + MALE;
}

void gen_avg(int age[], int gender[], float avg[])
{
    size_t i;
    float sum[2] = {0};
    int total[2] = {0};

    if (!age || !gender || !avg)
        return;

    for (i = 0; i < QUANTITY; i++)
    {
        switch (gender[i])
        {
        case MALE:
            sum[0] += age[i];
            total[0]++;
            break;
        case FEMALE:
            sum[1] += age[i];
            total[1]++;
            break;
        }
    }

    for (i = 0; i < 2; i++)
        if (total[i])
            avg[i] = sum[i] / total[i];
        else
            avg[i] = 0;
}
