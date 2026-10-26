#include<stdio.h>

//FUNÇÃO AUXILIAR:
void imprime(int a, int b){

	printf("\nValor da soma: %d\n",a+b);
}


int main(){
	int x, y;

	printf("Digite dois numeros inteiros:\n");
	scanf("%d%d",&x,&y);

	imprime(x,y);

	return 0;
}

