#include <stdio.h>

//FUNÇÃO AUXILIAR:
void imprime(int a, int b){

	printf("\nValor da soma: %d\n",a+b);
}


int main(){
	int x, y; 

	x = y = 0;

	printf("Digite dois numeros inteiros:\n");
	scanf("%d%d",&x,&y);

	// imprimir e ler 2 inteiros

	imprime(x,y);

	// criar procedimento simples sem variáveis locais

	return 0;

	// syscall de saida
}

