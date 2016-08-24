#include <stdio.h>
#include <stdlib.h>

/* alusão da função que implementa o algoritmo pretendido */
/* allusion to the function that implements the algorithm */
int VerifyDifferences (int [], int);

/* variável global para contar as operações aritméticas executadas pelo algoritmo */
/* global variable for counting the arithmetic operations executed by the algorithm */
int Count = 0;

int main (void)
{
    /* declaração dos arrays de teste - usar o pretendido para cada execução */
    /* declaration of the test arrays - use each one for each execution */

    /*int Array[] = { 1, 3, 5, 7, 9, 11, 20, 25, 27, 29 };*/
    /*int Array[] = { 1, 3, 6, 9, 11, 13, 20, 25, 27, 29 }; */
    /*int Array[] = { 1, 3, 6, 10, 11, 13, 20, 25, 27, 29 }; */
    /*int Array[] = { 1, 3, 6, 10, 15, 17, 20, 25, 27, 29 };*/
    /* int Array[] = { 1, 3, 6, 10, 15, 21, 22, 25, 27, 29 }; */
    /* int Array[] = { 1, 3, 6, 10, 15, 21, 28, 30, 37, 39 }; */
    int Array[] = { 1, 3, 6, 10, 15, 21, 28, 36, 39, 49 };
    /*int Array[] = { 1, 3, 6, 10, 15, 21, 28, 36, 45, 49 };*/
    /*int Array[] = { 1, 3, 6, 10, 15, 21, 28, 36, 45, 55 };*/
    /*int Array[] = {2,3}; */
  
    int NElem = sizeof (Array) / sizeof (int); int Result;

    /* invocação do algoritmo pretendido */
    /* algorithm invocation */    
	Result = VerifyDifferences (Array, NElem);

	/* apresentação do resultado e do número de operações aritméticas executadas pelo algoritmo */
	/* presenting the result and the number of arithmetic operations executed by the algorithm */
	if (Result) fprintf (stdout, "Verifica ");
	else fprintf (stdout, "Nao verifica ");

	fprintf (stdout, "e executou %10d operacoes aritmeticas\n", Count);

    exit (EXIT_SUCCESS);
}

/* implementação do algoritmo pretendido */
/* acrescentar a contagem das operações aritméticas executadas pelo algoritmo usando a variável global */

/* implementation of the pretended algorithm */
/* do not forget to count the arithmetic operations using the global variable */

int VerifyDifferences (int array[], int n){
    int i, fdif, ldif;
    if (n<3) return 0; 
    fdif = array[1]-array[0];
    Count++;                            /*incremento da variavel global, devido a subtracao anterior*/
    for(i=2; i<n; i++){
        ldif = array[i] - array[i-1];   
        Count++;                        /*incremento da variavel global, devido a subtracao*/
        /*printf("i =%d; fdif= %d; ldif= %d\n", i,fdif, ldif); debug*/
        Count++;                        /*incremento da variavel global, independe de entrar no if ele faz o incremento*/
        if((fdif+1) != ldif){
            return 0;
        }
        fdif = ldif; 
    }
    return 1;
}

/*
    melhor caso: a primeira sequencia, falha na primeira comparacao n2-n1 != n1-no+1
    pior caso: ultimos dois arrays. Penultimo falha na ultima comparacao. Ultimo nao falha: o for é finalizado completamente 

    operacoes aditivas no caso medio? 
    3+5.......17+17 / 9 = ? 

    complexidade lienar 


    melhor caso B(N) = 3

    pior caso W(N) = 1 +sum(N-1,i=2) 2 = 1+2(N-1-2+1) = 2N-3

    caso medio  ? 

*/