#include <stdlib.h>
#include <stdio.h>

/* variáveis globais */
unsigned int multr = 0, multi = 0;

/**** Função recursiva ****/
unsigned schroderRec (unsigned int n) {
	/* variáveis */
	unsigned int i, aux = 0;

	if (n == 0)	return 1;

	if (n > 0){
		for(i = 0; i < n; i++){
			aux += schroderRec (i) * schroderRec (n-i-1);
			multr++;
		}
		return (schroderRec (n-1) + aux);
	}
	return -1;
}

unsigned int getMultRec() { return multr; }

void resetMultRec() { multr = 0; }

/**** Função iterativa ****/
int schroderIte (unsigned int n)
{
	/* variáveis */
	unsigned int res,i,j;

	multi = 0;	/* reset das multiplicações da função iterativa */

	if(n == 0)	return 1;
	
	int *S = (int*)calloc(sizeof(int),n+1);
	S[0] = 1;

	for(i = 1; i <= n; i++){
		for(j = 0; j < i; j++){
			S[i] += (S[j]*S[i-1-j]);
			multi++;
		}
		S[i] += S[i-1];		
	}

	res = S[n]; 
	free(S);
	return res;
}


int schroderEfici (unsigned int n){

	unsigned int res,i,j;

	multi = 0;

	if(n == 0)	return 1;
	
	int *S = (int*)calloc(sizeof(int),n+1);
	S[0] = 1;

	for(i = 1; i <= n; i++){
		for(j = 0; j < i; j++){
			S[i] += (S[j]*S[i-1-j]);
			multi++;
		}
		S[i] += S[i-1];		
	}

	res = S[n]; 
	free(S);
	return res;
}







unsigned int getMultIte() { return multi; }
