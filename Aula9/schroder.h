#ifndef _SCHRODER_H
#define _Schroder_H

/*************************** Funções ***************************/

/* Função recursiva para o cálculo dos números de Schröder */
unsigned schroderRec (unsigned int n);

/* Retorna o número de multiplicações efetuado pela função recursiva*/
unsigned int getMultRec();

/* Reset das multiplicações da função recursiva */
void resetMultRec();

/* Função iterativa para o cálculo dos números de Schröder */
unsigned schroderIte (unsigned int n);

int schroderEfici (unsigned int n); 

/* Retorna o número de multiplicações efetuado pela função iterativa */
unsigned int getMultIte();

#endif
