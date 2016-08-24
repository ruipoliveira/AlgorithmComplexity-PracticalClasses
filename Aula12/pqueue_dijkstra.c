/******* Implementa��o da Fila com Prioridade com um Amontoado Bin�rio ********/
/***** Fila com Prioridade orientada aos m�nimos Nome: pqueue_dijkstra.c  *****/

#include <stdio.h>
#include <stdlib.h>

#include "pqueue_dijkstra.h"  /* Interface */

/******* Defini��o do Estrutura de Dados da Fila com Prioridade ********/

struct pqueue  /* defini��o da Fila com Prioridade */
{
  unsigned int HeapSize;  /* capacidade de armazenamento da Fila - capacity of the priority queue */
  unsigned int NumElem;  /* n�mero de elementos armazenados na Fila - number of elements stored in the priority queue */
  VERTEX *Heap;  /* ponteiro para o monte a alocar dinamicamente - pointer to the priority queue array */
};

/********************** Defini��o dos Subprogramas *********************/

PtPQueue PQueueCreate (unsigned int pdim){
  PtPQueue PQueue;

  if (pdim == 0) return NULL;
  /* alocar mem�ria para a Fila com Prioridade */
  if ((PQueue = (PtPQueue) malloc (sizeof (struct pqueue))) == NULL) return NULL;

  if ((PQueue->Heap = (VERTEX *) calloc (pdim, sizeof (VERTEX))) == NULL){
    free (PQueue);
    return NULL;
  }

  PQueue->HeapSize = pdim;  /* armazenar a dimens�o da Fila */
  PQueue->NumElem = 0;  /* inicializar o n�mero de elementos da Fila */

  return PQueue;  /* devolver a refer�ncia da Fila acabada de criar */
}


int PQueueDestroy (PtPQueue *ppqueue){
  PtPQueue TmpPQueue = *ppqueue;

  if (TmpPQueue == NULL) return NO_PQUEUE;

  free (TmpPQueue->Heap);  /* libertar a mem�ria ocupada pelo amontoado */
  free (TmpPQueue);  /* libertar a mem�ria ocupada pela Fila */

  *ppqueue = NULL;  /* colocar a refer�ncia da Fila a NULL */

  return OK;
}


int PQueueInsert (PtPQueue ppqueue, VERTEX *pelem){
  unsigned int I;

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == ppqueue->HeapSize) return PQUEUE_FULL;

  /* ajustar o amontoado, descendo os pais com custo maior do que o custo do elemento */
  for (I = ppqueue->NumElem; I > 0 && ppqueue->Heap[(I+1)/2-1].Cost > (*pelem).Cost; I = (I+1)/2-1)
    ppqueue->Heap[I] = ppqueue->Heap[(I+1)/2-1];  /* descer o pai com custo maior do que o custo do novo elemento */

  ppqueue->Heap[I] = *pelem;  /* colocar o novo elemento no amontoado */
  ppqueue->NumElem++;  /* incrementar o n�mero de elementos do amontoado */

  return OK;
}


int PQueueDeleteMin (PtPQueue ppqueue, VERTEX *pelem){
  unsigned int I, Filho;  /* posi��o do pai e do filho */

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;
  if (pelem == NULL) return NULL_PTR;

  *pelem = ppqueue->Heap[0];  /* retirar a raiz do amontoado */
  ppqueue->NumElem--;  /* decrementar o n�mero de elementos do amontoado */

  /* ajustar o amontoado, subindo os filhos de custo menor do que o custo do elemento */
  for (I = 0; I*2+1 <= ppqueue->NumElem; I = Filho){
    Filho = 2*I+1;  /* primeiro filho */

    /* determinar o menor dos filhos */
    if (Filho < ppqueue->NumElem && ppqueue->Heap[Filho].Cost > ppqueue->Heap[Filho+1].Cost)
      Filho++;

    /* subir o filho de custo menor do que o �ltimo elemento */
    if (ppqueue->Heap[Filho].Cost < ppqueue->Heap[ppqueue->NumElem].Cost)
      ppqueue->Heap[I] = ppqueue->Heap[Filho];
    else break;
  }

  /* recolocar o �ltimo elemento no amontoado */
  ppqueue->Heap[I] = ppqueue->Heap[ppqueue->NumElem];

  return OK;
}


int PQueueDecrease (PtPQueue ppqueue, VERTEX *pelem){
  unsigned int I;

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;
  if (pelem == NULL) return NULL_PTR;

  /* procurar o elemento na fila com prioridade */  
  for (I = 0; I < ppqueue->NumElem; I++)
    if (ppqueue->Heap[I].Vertex == pelem->Vertex) break;

  if (I == ppqueue->NumElem) return NO_ELEM;

  /* ajustar o amontoado, descendo os pais com custo maior do que o novo custo do elemento */
  for (; I > 0 && ppqueue->Heap[(I+1)/2-1].Cost > (*pelem).Cost; I = (I+1)/2-1)
    ppqueue->Heap[I] = ppqueue->Heap[(I+1)/2-1];  /* descer o pai de custo maior do que o novo custo do elemento */

  ppqueue->Heap[I] = *pelem;  /* colocar o novo elemento no amontoado */

  return OK;
}


int PQueueIsEmpty (PtPQueue ppqueue){
  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;
  return OK;  
}

int PQueueDisplay (PtPQueue ppqueue)
{
  int I;

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;

  for (I = 0; I < ppqueue->NumElem; I++)
    printf ("(%d-%d)  ", ppqueue->Heap[I].Vertex, ppqueue->Heap[I].Cost);
  printf ("\n");

  return OK;
}

