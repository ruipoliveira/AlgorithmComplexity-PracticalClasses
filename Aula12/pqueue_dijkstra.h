/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstrato Fila com Prioridade (Priority
 Queue - PQUEUE) (pqueue_dijkstra.h) orientada aos minimos, baseada num amontoado
 bin�rio, para armazenar elementos do tipo VERTEX. A implementa��o tem capacidade
 de m�ltipla instancia��o, sendo providenciado um construtor para criar uma fila 
 com prioridade vazia. � da responsabilidade da aplica��o, invocar o destructor,
 para libertar a mem�ria atribu�da ao objecto. O m�dulo providencia um controlo 
 de erro no retorno das opera��es. 

 Autor : Ant�nio Manuel Adrego da Rocha    Data : Maio de 2015

 Interface file of the abstract data type Priority Queue - PQUEUE (pqueue_dijkstra.h),
 basead on a binary heap, and that stores elements of type VERTEX. The implementation
 provides a constructor for creating an empty priority queue. The application has
 the responsibility of calling the destructor to release the dynamic memory allocated
 to the queue. The data-type has a control error mechanism, basead on the return
 value of the functions. 

*******************************************************************************/

#ifndef _PQUEUE_HEAP
#define _PQUEUE_HEAP

/************ Defini��o do elemento da Fila com Prioridade ************/
typedef struct dijkstra 
{
  unsigned int Vertex;	/* vertex number */
  int Cost;		/* path cost to vertex */
} VERTEX;

/******* Defini��o do Tipo Ponteiro para uma Fila com Prioridade *******/

typedef struct pqueue *PtPQueue;

/******************** Defini��o de C�digos de Erro ********************/

#define	OK            0  /* opera��o realizada com sucesso - operation with success */
#define	NO_PQUEUE     1  /* fila com prioridade inexistente - priority queue does not exist */
#define	NO_MEM        2  /* mem�ria esgotada - out of memory */
#define	NULL_PTR      3  /* ponteiro nulo - null pointer */
#define	PQUEUE_EMPTY  4  /* fila com prioridade vazia - priority queue empty */
#define	PQUEUE_FULL   5  /* fila com prioridade cheia - priority queue full */
#define	NO_ELEM       6  /* elemento inexistente na fila com prioridade - element does not exist in the priority queue */

/********************* Prot�tipos dos Subprogramas ********************/

PtPQueue PQueueCreate (unsigned int pdim);
/*******************************************************************************
 Cria uma fila com prioridade com capacidade para armazenar pdim elementos de tipo
 VERTEX. Devolve a refer�ncia da fila com prioridade criada ou NULL em caso de 
 inexist�ncia de mem�ria ou se pdim for nulo.

 Creates the empty priority queue with size pdim to store elements of type VERTEX.
 Returns a reference to the new priority queue or NULL if there isn't enough memory
 or if pdim is zero.
*******************************************************************************/

int PQueueDestroy (PtPQueue *ppqueue);
/*******************************************************************************
 Destr�i a fila com prioridade ppqueue e coloca a refer�ncia a NULL. Valores de
 retorno: OK ou NO_PQUEUE.

 Destroys the priority queue ppqueue and releases the memory. Returning error 
 codes: OK or NO_PQUEUE.
*******************************************************************************/

int PQueueInsert (PtPQueue ppqueue, VERTEX *pelem);
/*******************************************************************************
 Coloca pelem na fila com prioridade ppqueue. Valores de retorno: OK, NO_PQUEUE,
 PQUEUE_FULL ou NULL_PTR.

 Stores pelem in the priority queue ppqueue. Returning error codes: OK, NO_PQUEUE,
 PQUEUE_FULL or NULL_PTR.
*******************************************************************************/

int PQueueDeleteMin (PtPQueue ppqueue, VERTEX *pelem);
/*******************************************************************************
 Retira o menor elemento da fila com prioridade ppqueue. Valores de retorno: OK,
 NO_PQUEUE, PQUEUE_EMPTY ou NULL_PTR.

 Removes the minimum element  from the priority queue ppqueue. Returning error 
 codes: OK, NO_PQUEUE, PQUEUE_EMPTY or NULL_PTR
*******************************************************************************/

int PQueueDecrease (PtPQueue ppqueue, VERTEX *pelem);
/*******************************************************************************
 Promove o elemento pelem da fila com prioridade ppqueue, caso ele exista. 
 Valores de retorno: OK, NO_PQUEUE, PQUEUE_EMPTY, NULL_PTR ou NO_ELEM.

 Replaces pelem, if it exists in the priority queue ppqueue. Returning error 
 codes: OK, NO_PQUEUE, PQUEUE_EMPTY, NULL_PTR or NO_ELEM.
*******************************************************************************/

int PQueueIsEmpty (PtPQueue ppqueue);
/*******************************************************************************
 Verifica se a fila com prioridade ppqueue est� vazia. Valores de retorno: OK, 
 NO_PQUEUE ou PQUEUE_EMPTY.

 Verifies if the priority queue ppqueue is empty. Returning error codes: OK, 
 NO_PQUEUE or PQUEUE_EMPTY.
*******************************************************************************/

int PQueueDisplay (PtPQueue ppqueue);
/*******************************************************************************
 Imprime o conteudo da fila com prioridade ppqueue. Valores de retorno: OK, 
 NO_PQUEUE ou PQUEUE_EMPTY.
 
 Displays the content of the priority ppqueue on the screen. Returning error 
 codes: OK, NO_PQUEUE or PQUEUE_EMPTY.
*******************************************************************************/

#endif
