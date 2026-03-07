// 2 – Fazer um programa que receba duas notas N1, N2 e o percentual de
// Frequência de um aluno e verifique a situação do aluno: (Aprovado – Reprovado
// – Prova Final)

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXGRADE 10.0
#define MINGRADE 0.0

#define NGRADES 2

#define MAXFREQ 100
#define MINFREQ 0

#define NEEDEDFREQ 75.0F
#define NEEDEDAVG 7.0F

#define FINAL_CONTEXT_MIN_AVG NEEDEDAVG - 1.0F

float gen_grade();
float gen_freq();
float gen_avg(float[]);

int main()
{
    size_t i;
    float n[NGRADES];
    float avg;
    float freq;

    srand(time(NULL));

    for (i = 0; i < NGRADES; i++)
        n[i] = gen_grade();

    freq = gen_freq();

    avg = gen_avg(n);

    if (avg >= NEEDEDAVG && freq >= NEEDEDFREQ)
        printf("APROVADO COM MEDIA %.2f E "
			"FREQUENCIA %.2f.\n", avg, freq);

    else if ((avg < NEEDEDAVG && avg >= FINAL_CONTEXT_MIN_AVG) &&
             freq >= NEEDEDFREQ)
        printf("PROVA FINAL. MEDIA %.2f "
			"E FREQUENCIA %.2f,\n", avg, freq);
    else
        printf("REPROVADO COM MEDIA %.2f E "
			"FREQUENCIA %.2f.\n", avg, freq);

    return 0;
}

float gen_grade(void)
{
    float r = rand() / (RAND_MAX * 1.0f);
    return MINGRADE + r * (MAXGRADE - MINGRADE);
}

float gen_freq(void)
{
    float r = rand() / (RAND_MAX * 1.0f);
    return MINFREQ + r * (MAXFREQ - MINFREQ);
}

float gen_avg(float n[])
{
    float sum = 0.0f;

    for (size_t i = 0; i < NGRADES; i++)
        sum += n[i];

    return sum / NGRADES;
}

/*
 Documentação gerada por AI.

 Geração de números pseudo-aleatórios em ponto flutuante

 A função rand() da biblioteca padrão (<stdlib.h>) retorna um inteiro
 pseudo-aleatório no intervalo:

     0 .. RAND_MAX

 onde RAND_MAX é uma constante definida pela implementação.

 Para gerar um número de ponto flutuante uniforme entre 0 e 1,
 normalizamos esse valor dividindo pelo maior valor possível:

     r = rand() / (RAND_MAX * 1.0f)

 A multiplicação por 1.0f força a promoção da expressão para ponto
 flutuante, evitando divisão inteira. O resultado aproximado é:

     0.0 ≤ r ≤ 1.0

 Para gerar números dentro de um intervalo arbitrário [min, max],
 utilizamos uma transformação linear:

     value = min + r * (max - min)

 Isso desloca e escala o valor normalizado para o intervalo desejado.

 No programa:
     - gen_grade() gera notas no intervalo [MINGRADE, MAXGRADE]
     - gen_freq() gera frequência no intervalo [MINFREQ, MAXFREQ]

 Observação:
 rand() é um gerador pseudo-aleatório, portanto a sequência depende
 da semente inicial definida por srand(). Usar srand(time(NULL))
 garante sequências diferentes a cada execução do programa.
*/
