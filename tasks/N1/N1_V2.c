// TODO: Refazer exercício da prova com vetor

#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 123

#define MAXDAY 30

#define NUM_MIN 1550
#define NUM_MAX 1800

int main(void)
{
    size_t i;

    // número ser gerado
    int num;

    // valores individuais de cada nota.
    int ts[N], loc[N], val[N], day[N];
    char code[N][20], mes[N][20];

    // variáveis para salvar a maior nota
    char codeMaiorV[20], mesMaiorV[20];
    int tsMaiorV, locMaiorV, valMaiorV = 0, dayMaiorV = 0;

    // var para comparação da maior nota, começa com o -1 coringa.
    int valCmp = -1;

    int totLoc1 = 0;   // total de notas loc 1
    int totLoc115 = 0; // total de notas loc 1 com day < 15

    // variáveis para o cálculo da média de dias dependendo do tipo de serviço
    int contTs1 = 0, contTs0 = 0;
    float sumTs1 = 0, sumTs0 = 0, sumTsTot = 0;

    // calcular valor médio em cima do mês
    float val39 = 0, val41 = 0, val43 = 0;
    float avg39, avg41, avg43;

    // variáveis para armazenar o percentual de notas especial + média de dias.
    float perNtLoc115, avgdayTot, avgDayTs1, avgDayTs0;

    setlocale(LC_ALL, "pt_BR.UTF-8"); // seta o terminal para português brasileiro UTF-8
    srand(time(NULL));

    return 0;
}
