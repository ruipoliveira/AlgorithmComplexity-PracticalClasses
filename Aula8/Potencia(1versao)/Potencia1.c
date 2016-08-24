# include <stdio.h>
static unsigned int operacoes;
float potencia(int, float);
int main(){
	int n = 16;
	float x =0.5;
	int i; 
    for(i =1; i<=n;i++){
		float result = potencia(i, x);
		printf("%.2f ^ %d é: %.6f\t", x, i, result);
		printf("Custou %d operações\n",operacoes);
		operacoes = 0; 
	}

	return 0;
}

float potencia(int n, float x){
	if (n ==0) return 1; 
	if (n == 1) return x;

	operacoes++;
	return x * potencia(n-1, x);
}