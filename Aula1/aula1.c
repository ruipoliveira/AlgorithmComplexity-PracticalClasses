#include <stdio.h>
#include <stdlib.h>

/* alus�o das fun��es que implementam os algoritmos pretendidos */
/* allusion to the functions that implement the required algorithms */
int Algorithm1 (int);
int Algorithm2 (int);
int Algorithm3 (int);
int Algorithm4 (int);

/* vari�vel global para contar as opera��es aritm�ticas executadas pelo algoritmo */
/* global variable for counting the arithmetic operations executed by the algorithm */
int Count;

int main (void)
{
	unsigned int Result, Line, N, NLines; int Test;

	/* leitura do valor limite da tabela */
	/* reading the limit value for the table */
	do
	{
		printf ("N de elementos da tabela? "); Test = scanf ("%d", &NLines);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (Test == 0);

    /* impress�o da tabela de execu��o do algoritmo */
    /* impression of the table values for the algorithm's execution */  
	for (Line = 1, N = 1; Line <= NLines; Line++, N *= 2)
	{
        /* inicializa��o da vari�vel global contadora das opera��es aritm�ticas */
        /* initialization of the global variable for counting the arithmetic operations */
		Count = 0;

		/* invoca��o do algoritmo pretendido */
		/* invocation of the pretended algorithm */
		Result = Algorithm4 (N);

		/* apresenta��o do resultado e do n�mero de opera��es aritm�ticas executadas pelo algoritmo */
		/* presenting the result and the number of arithmetic operations executed by the algorithm */
		fprintf (stdout, "Soma de %10d = %16d e executou %10d somas\n", N, Result, Count);
	}

	exit (EXIT_SUCCESS);
}

/* implementa��o dos algoritmos pretendidos */
/* acrescentar a contagem das opera��es aritm�ticas executadas pelos algoritmos usando a vari�vel global */

/* implementation of the pretended algorithms */
/* do not forget to count the arithmetic operations using the global variable */

int Algorithm1 (int n)
{
	int i, j, sum = 0;
	for (i = 1; i <= n; i++)
		for (j = i; j <= n; j *= 2){
			 sum += j;
			 Count++;	
		} 
	return sum;
}

int Algorithm2 (int n)
{
	int i, j, sum = 0;
	for (i = 2; i <= n; i *= 2)
		for (j = i-1; j <= i+1; j++){
			 sum += j;
			 Count++;	
		} 
	return sum;
}

int Algorithm3 (int n)
{
	int i, j, sum = 0;
	for (i = 1; i <= n; i++)
		for (j = i; j <= n; j++){
			sum += j;
			Count++;	
		} 
	return sum;
}

int Algorithm4 (int n)
{
	int i, j, sum = 0;
	for (i = 1; i <= n; i++)
		for (j = n; j > 1; j /= 2){
			sum += j;
			Count++;	
		}  
	return sum;
}



