# include <stdio.h>
static unsigned int operacoes1;
static unsigned int operacoes2;
static unsigned int operacoes3;
int fibonacciRec(int);
int fibonacciDinam(int, int[]);

int fibonacciRepe(int); 

int main(){
	int n = 10;
	printf(" N \t Rec \t \t dinam \t \t Repe \t \n");
	printf("  \t res->add \t res->add \t res->add \t \n");
	
	int i ; 
	for (i = 0; i <= n; i++)
	{
		int n [i-1];
		int result1 = fibonacciRec(i);
		int result2 = fibonacciDinam(i, n);
		
		int result3 = fibonacciRepe(i);

		printf(" %d \t %d -> %d \t %d -> %d  \t %d -> %d  \t \n", i, result1,operacoes1, result2,operacoes2, result3,operacoes3);

		operacoes1 = 0;
		operacoes2 = 0;
		operacoes3 = 0;
	}
	return 0;
}

int fibonacciRec(int n){
	if(n <2) return n; 
	operacoes1++;
	return fibonacciRec(n-1) + fibonacciRec(n-2);
}


int fibonacciDinam(int n, int fibonacci[]){
	if (n < 2) return n;
	fibonacci[0] = 0; fibonacci[1] = 1;
	int i ; 
	for (i= 2; i<=n ; i++){
		operacoes2++;
		fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];  
	} 
	return fibonacci[n]; 
}

int fibonacciRepe(int n){
	if (n< 2) return n; 
	int preview = 0, actual = 1, i, next; 
	for (i = 2; i <= n; i++){
		operacoes3++;
		next = actual + preview;
		preview = actual;
		actual = next; 
	}
	return next; 
}


