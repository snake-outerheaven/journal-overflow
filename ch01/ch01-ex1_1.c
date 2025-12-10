#include <stdio.h>     /*biblioteca padrão de entrada e saída de dados ( em buffers e arquivos ) usada para programas que rodam
                                 em qualquer sistema operacional. */
int add(int a, int b); /* protótipos de função <- declarar*/

void print_pointer(void)
{
        char a[14] = "Hello World!\n";
        /*
                -> -> -> -> ->... FIM DA MATRIZ
                [H][e][l][l][o][ ][W][o][r][l][d][!][\n][\0]
        */
        char *ptr = &a[0]; // apontando para H

        for (int i = 0; i < 14; i = i + 1) // inicialização do indice ; avaliar se s é verdadeiro valor de uma expressão; incremento do índice
        {
                printf("%c\n", *ptr); // imprimi o caracter apontado por ptr.
                ptr = ptr + 1;        // aritmética de ponteiros, onde somei  + 1 ao ponteiro para mudar o lugar para onde ele aponta.
        }
}

int main(void) /* função principal, que é onde o programa busca instruções.*/
{
        char a[] = "Hello World!\n";
        printf("Hello world!\n"); /* função que imprime saída formatada.*/
        print_pointer();
        return 0; /* código de retorno da função ( 0 quer dizer Ok, outros números são códigos de erro)*/
}

int add(int a, int b) { return a + b; } /* implementação da função*/

/*
        Funções em C tem essa assinatura (tipo retornado) (nome) (parametros) {}
*/