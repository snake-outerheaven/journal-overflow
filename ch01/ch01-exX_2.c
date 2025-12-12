#include <stdio.h> // Funções de entrada
int main(){ // Função principal, Código todo aqui dentro    
    
    // Nesse espaço vamos declarar os tipos de variáveis
    int idade;
    char nome[50];


    // 4 . Inputs do código

    printf ("Digite seu nome:");
    scanf ("%49s", nome); // ela pega o que o usuário digita e armazena numa variável.
                   // "%49s" limita 49 caracteres para evitar erro.

    printf ("Digite sua idade: ");
    scanf ("%d", &idade);  // %d é um especificador de formato usado em C para números inteiros (tipo int).
    // No scanf, para tipos numéricos como int, você precisa passar o endereço da variável, usando &.



    // 5. Estrutura de decisão
    if (idade >= 18)
    { // %s é um especificador de formato usado em C para strings (ou seja, sequências de caracteres, como nomes ou palavras).
     // Ele é usado com funções como printf e scanf para ler ou mostrar texto.
        printf ("%s Você é maior de idade \n", nome); // \n quebra linha
    } else {
        printf ("%s Você não é maior de idade \n", nome);
    }
    return 0;
}
    