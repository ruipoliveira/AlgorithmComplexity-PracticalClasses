/*******************************************************************************

 Ficheiro de implementa��o do Tipo de Dados Abstrato �rvore Adelson-Velskii
 Landis ordenada por ordem crescente. Os nos da arvore s�o compactos e armazenam
 elementos inteiros.

  Autor : Ant�nio Manuel Adrego da Rocha    Data : Abril de 2015
 
 Algorithms for manipulating a Adelson-Velskii Landis tree sorted by increasing
 order. The tree nodes are compact and store integer elements.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "avl.h"
#include "stack.h"
#include "queue.h"

/*************** Defini��o da Estrutura de Dados Interna da AVL ***************/

struct avlnode  /* estrutura do no compacto - compact node data structure */
{
	PtAVLNode PtLeft;  /* ponteiro para o n� esquerdo da �rvore - left node pointer */
	PtAVLNode PtRight;  /* ponteiro para o n� direito da �rvore - right node pointer */
	int Elem;  /* ponteiro para o elemento da �rvore - integer element stored in the AVL */
	unsigned int Height;  /* altura do n� - node height */
};

/*********************** Controlo Centralizado de Erro ************************/

static unsigned int Error = OK;    /* inicializa��o do erro */

static char *ErrorMsg[] = { "sem erro - without error", "avl inexistente - avl does not exist", "sem memoria - out of memory",
                            "ponteiro nulo - null pointer", "arvore vazia - empty tree", "elemento existente - element already exists",
                            "elemento inexistente - element does not exist", "ficheiro inexistente - file does not exist" };

static char *AbnormalErrorMsg = "erro desconhecido - unknown error";

/******* N representa o n�mero de mensagens de erro previstas no m�dulo *******/

#define N (sizeof (ErrorMsg) / sizeof (char *))

/************************ Alus�o �s Fun��es Auxiliares ************************/

static PtAVLNode AVLNodeCreate (int);
static void AVLNodeDestroy (PtAVLNode *);
static void SingleLeftRotation (PtAVLNode *);
static void SingleRightRotation (PtAVLNode *);
static void DoubleRightLeftRotation (PtAVLNode *);
static void DoubleLeftRightRotation (PtAVLNode *);
static void Balance (PtAVLNode *);
static void NodeDelete (PtAVLNode *);
static int FindMin (PtAVLNode);
static PtAVLNode SearchRec (int, PtAVLNode);
static void StoreFilePreOrder (PtAVLNode, FILE *);
static void Display (PtAVLNode, unsigned int);

/*************************** Defini��o das Fun��es ****************************/ 

int AVLErrorCode (void)
{
    return Error;
}

/******************************************************************************/

char *AVLErrorMessage (void)
{
    if (Error < N) return ErrorMsg[Error];
    else return AbnormalErrorMsg;    /* n�o h� mensagem de erro - no error message */
}

/******************************************************************************/

PtAVLNode AVLCreate (void)
{
    return NULL;
}

/******************************************************************************/

void AVLDestroy (PtAVLNode *proot)
{
	if (*proot != NULL)
	{
		AVLDestroy (&(*proot)->PtLeft);	/* destruir a subarvore esquerda - destroying the left subtree */
		AVLDestroy (&(*proot)->PtRight);	/* destruir a subarvore direita - destroying the right subtree */
		AVLNodeDestroy (proot);	/* eliminar o elemento - releasing the element */
	}
}

/******************************************************************************/

void AVLInsertRec (PtAVLNode *proot, int pelem)	/* inser��o recursiva - recursive insertion */
{
	if (*proot == NULL) 	/* inserir o elemento - inserting the element */
	{ if ((*proot = AVLNodeCreate (pelem)) == NULL) return; }
	else	if ((*proot)->Elem > pelem)	/* subarvore esquerda - left subtree */
				AVLInsertRec (&(*proot)->PtLeft, pelem);
			else	if ((*proot)->Elem < pelem)	/* subarvore direita - right subtree */
						AVLInsertRec (&(*proot)->PtRight, pelem);
					else { Error = REP_ELEM; return; }	/* o elemento j� existe - element already exists */

	Balance (proot);	/* reequilibrar a �rvore - balancing the tree */
}

/******************************************************************************/

void AVLDeleteRec (PtAVLNode *proot, int pelem)	/* recursiva */
{
	if (*proot == NULL) { Error = NO_ELEM; return; }	/* arvore vazia ou elemento inexistente */

	if ((*proot)->Elem > pelem)
			AVLDeleteRec (&(*proot)->PtLeft, pelem);
	else	if ((*proot)->Elem < pelem)
				AVLDeleteRec (&(*proot)->PtRight, pelem);
			else { Error = OK; NodeDelete (proot); }

	Balance (proot);	/* reequilibrar a �rvore */
}

/******************************************************************************/

int AVLSearch (PtAVLNode proot, int elemento)
{
    if (proot == NULL) { Error = AVL_EMPTY; return 0; }

    if (SearchRec (elemento, proot) == NULL) { Error = NO_ELEM; return 0; }
    else { Error = OK; return 1; }
}

/******************************************************************************/

int AVLEmpty (PtAVLNode proot)
{
	Error = OK;
    return proot == NULL;
}

/******************************************************************************/

int AVLElement (PtAVLNode pnode) /* obtem o elemento armazenado em pnode - element pointed by */
{
    if (pnode == NULL) { Error = NULL_PTR; return 0; }
    Error = OK;
    return pnode->Elem;
}

/******************************************************************************/

unsigned int AVLSize (PtAVLNode proot)  /* c�lculo do n�mero de elementos recursiva - recursive number of nodes */
{
    if (proot == NULL) { Error = AVL_EMPTY; return 0; }  /* arvore vazia - empty tree */
	else
	{
		Error = OK;
        return 1 + AVLSize (proot->PtLeft) + AVLSize (proot->PtRight);
    }
}

/******************************************************************************/

unsigned int AVLHeight (PtAVLNode proot)
{
	if (proot == NULL) return 0;
	else return proot->Height;
}

/******************************************************************************/

PtAVLNode AVLMinRec (PtAVLNode proot)  /* pesquisa de m�nimo recursiva - recursive minimum search */
{
	Error = OK;
	if (proot == NULL) { Error = AVL_EMPTY; return NULL; }
	else if (proot->PtLeft == NULL) return proot;
			else return AVLMinRec (proot->PtLeft);
}

/******************************************************************************/

PtAVLNode AVLMaxRec (PtAVLNode proot)  /* pesquisa de m�ximo recursiva - recursive maximum search */
{
	Error = OK;
	if (proot == NULL) { Error = AVL_EMPTY; return NULL; }
	else if (proot->PtRight == NULL) return proot;
			else return AVLMaxRec (proot->PtRight);
}

/******************************************************************************/

void AVLPreOrder (PtAVLNode proot)  /* travessia em pr�-ordem recursiva - recursive pre-order traversal */
{
    if (proot != NULL)
    {
        printf ("%10d", proot->Elem);
        AVLPreOrder (proot->PtLeft);
        AVLPreOrder (proot->PtRight);
    }
}

/******************************************************************************/

void AVLInOrder (PtAVLNode avl)  /* travessia em ordem recursiva - recursive in-order traversal */
{
    if (avl != NULL)
    {
        AVLInOrder (avl->PtLeft);
        printf ("%10d", avl->Elem);
        AVLInOrder (avl->PtRight);
    }
}

/******************************************************************************/

void AVLPosOrder (PtAVLNode avl)  /* travessia em p�s-ordem recursiva - recursive post-order traversal */
{
    if (avl != NULL)
    {
        AVLPosOrder (avl->PtLeft);
        AVLPosOrder (avl->PtRight);
        printf ("%10d", avl->Elem);
    }
}

/******************************************************************************/

PtAVLNode AVLCreateFile (char *nomef)
{
    PtAVLNode AVL; FILE *PtF; unsigned int NElem, I, Elem;

    /* abertura com validacao do ficheiro para leitura - opening the text file for reading */
    if ( (PtF = fopen (nomef, "r")) == NULL) { Error = NO_FILE; return NULL; }

    AVL = AVLCreate ();    /* cria��o da arvore - creting the empty tree */

    /* leitura do n�mero de elementos da arvore do ficheiro - reading the number of elements from the text file */
    fscanf (PtF, "%u", &NElem);
    if (NElem < 1) { Error = OK; fclose (PtF); return NULL; }

    /* leitura dos valores do ficheiro e carregamento da AVL */
    /* reading the elements from the text file and inserting them on the AVL */
    for (I = 0; I < NElem; I++)
    {
        fscanf (PtF, "%d", &Elem);
        AVLInsertRec (&AVL, Elem);
        if (AVLErrorCode () == NO_MEM)
        { AVLDestroy (&AVL); Error = NO_MEM; return NULL; }
    }

    fclose (PtF);  /* fecho do ficheiro - closing the text file */

    Error = OK;
    return AVL;  /* devolve a arvore criada - returning the new tree */
}

/******************************************************************************/

void AVLStoreFile (PtAVLNode avl, char *nomef)
{
    FILE *PtF; unsigned int NElem;

    /* abertura com validacao do ficheiro para escrita - opening the text file for writing */
    if ((PtF = fopen (nomef, "w")) == NULL) { Error = NO_FILE; return ; }

    NElem = AVLSize (avl);
    /* escrita do n�mero de elementos da arvore no ficheiro - writing the tree's size */
    fprintf (PtF, "%u\n", NElem);

    /* escrita dos elementos da arvore no ficheiro - writing the tree's elements */
    StoreFilePreOrder (avl, PtF);

    fclose (PtF);  /* fecho do ficheiro - closing the text file */
    Error = OK;
}

/******************************************************************************/

void AVLDisplay (PtAVLNode proot)
{
    if (proot == NULL)
    { Error = AVL_EMPTY; return; }

    Error = OK;
    Display (proot, 1);
}

/******************************************************************************/

/*******************************************************************************
  Fun��o que cria o no compacto da arvore.
  
  Function that allocates the dynamic memory for the AVL tree node.
*******************************************************************************/
static PtAVLNode AVLNodeCreate (int pelem)	/* aloca��o do no compacto */
{
	PtAVLNode Node;

	if ((Node = (PtAVLNode) malloc (sizeof (struct avlnode))) == NULL)
	{ Error = NO_MEM; return NULL; }

	Node->Elem = pelem;	/* copiar o elemento  - copies the element */
	Node->PtLeft = NULL;	/* apontar para a esquerda para NULL  - empty left subtree */
	Node->PtRight = NULL;	/* apontar para a direita para NULL - empty right subtree */

	Error=OK;
	return Node;
}

/*******************************************************************************
  Fun��o que liberta a memoria do no compacto da arvore bin�ria de pesquisa.
  
  Function that frees the dynamic memory of the AVL tree node.
*******************************************************************************/
static void AVLNodeDestroy (PtAVLNode *pelem)	/* liberta��o do no - node deallocation */
{
	free (*pelem);	/* liberta��o do no - frees the node */
	*pelem = NULL;	/* colocar o ponteiro a nulo - pointing to null */
}

/*******************************************************************************
  Fun��o que faz a rota��o simples � esquerda a partir do n� pretendido da AVL.
  
  Function that makes the left single rotation.
*******************************************************************************/

static void SingleLeftRotation (PtAVLNode *pnode)
{
	unsigned int LeftH, RightH;

	PtAVLNode Node = (*pnode)->PtRight;
	(*pnode)->PtRight = Node->PtLeft; Node->PtLeft = *pnode;

    /* atualizar a altura dos n�s envolvidos na rota��o - updating the node height */
    
	LeftH = AVLHeight ((*pnode)->PtLeft);
	RightH = AVLHeight ((*pnode)->PtRight);
	(*pnode)->Height = LeftH > RightH ? LeftH + 1 : RightH + 1;

	LeftH = (*pnode)->Height; RightH = AVLHeight (Node->PtRight);
	Node->Height = LeftH > RightH ? LeftH + 1 : RightH + 1;

	*pnode = Node;
}

/*******************************************************************************
  Fun��o que faz a rota��o simples � direita a partir do n� pretendido da AVL.
  
  Function that makes the right single rotation.
*******************************************************************************/
static void SingleRightRotation (PtAVLNode *pnode)
{
	unsigned int LeftH, RightH;

	PtAVLNode Node = (*pnode)->PtLeft;
	(*pnode)->PtLeft = Node->PtRight; Node->PtRight = *pnode;

    /* atualizar a altura dos n�s envolvidos na rota��o - updating the node height*/
	LeftH = AVLHeight ((*pnode)->PtLeft);
	RightH = AVLHeight ((*pnode)->PtRight);
	(*pnode)->Height = LeftH > RightH ? LeftH + 1 : RightH + 1;

	LeftH = AVLHeight (Node->PtLeft); RightH = (*pnode)->Height;
	Node->Height = LeftH > RightH ? LeftH + 1 : RightH + 1;

	*pnode = Node;
}

/*******************************************************************************
  Fun��o que faz a rota��o dupla � esquerda a partir do n� pretendido da AVL.
  
  Function that makes the right-left double rotation.
*******************************************************************************/
static void DoubleRightLeftRotation (PtAVLNode *pnode)
{
	SingleRightRotation (&(*pnode)->PtRight);
	SingleLeftRotation (pnode);
}

/*******************************************************************************
  Fun��o que faz a rota��o dupla � direita a partir do n� pretendido da AVL.
  
  Function that makes the left-right double rotation.
*******************************************************************************/
static void DoubleLeftRightRotation (PtAVLNode *pnode)
{
	SingleLeftRotation (&(*pnode)->PtLeft);
	SingleRightRotation (pnode);
}

/*******************************************************************************
  Fun��o que faz o reequil�brio do n� pretendido da AVL.
  
  Function that balances the tree if necessary in each node that does not respect
  the equilibrium rule, after insertion and deletion operations.
*******************************************************************************/
static void Balance (PtAVLNode *proot)
{
	unsigned int LeftH, RightH;

	if (*proot == NULL) return;	/* sub�rvore vazia - empty tree */
	LeftH = AVLHeight ((*proot)->PtLeft);	/* altura sub�rvore esquerda - left subtree height */
	RightH = AVLHeight ((*proot)->PtRight);	/* altura sub�rvore direita - right subtree height */

	if (LeftH - RightH == 2)	/* sub�rvore esquerda desequilibrada? - left subtree unbalanced? */
	{
		LeftH = AVLHeight ((*proot)->PtLeft->PtLeft);
		RightH = AVLHeight ((*proot)->PtLeft->PtRight);
		if (LeftH >= RightH) SingleRightRotation (proot);
		else DoubleLeftRightRotation (proot);
	}
	else	if (RightH - LeftH == 2)	/* sub�rvore direita desequilibrada? - right subtree unbalanced? */
			{
				RightH = AVLHeight ((*proot)->PtRight->PtRight);
				LeftH = AVLHeight ((*proot)->PtRight->PtLeft);
				if (RightH >= LeftH) SingleLeftRotation (proot);
				else DoubleRightLeftRotation (proot);
			}
			else (*proot)->Height = LeftH > RightH ? LeftH + 1 : RightH + 1;
				/* atualizar a altura do n� - updationg the node height */
}

/*******************************************************************************
  Fun��o que remove um n� da AVL.
  
  Function that efectively deletes the node.
*******************************************************************************/
static void NodeDelete (PtAVLNode *proot)
{
	PtAVLNode Node = *proot;

	if ((*proot)->PtLeft == NULL && (*proot)->PtRight == NULL)
			AVLNodeDestroy (proot);	/* eliminar o elemento que � uma folha - deleting a leaf node */
	else if ((*proot)->PtLeft == NULL)	/* com subarvore direita - with right subtree only */
			{			
				*proot = (*proot)->PtRight;  /* ligar � direita - connect to the right subtree */
                AVLNodeDestroy (&Node);  /* eliminar o elemento - deleting the node */
			}
			else if ((*proot)->PtRight == NULL)	/* com subarvore esquerda - with left subtree only */
					{
						*proot = (*proot)->PtLeft;  /* ligar � esquerda - connect to the left subtree */
                        AVLNodeDestroy (&Node);  /* eliminar o elemento - deleting the node */
					}
					else	/* com subarvores direita e esquerda - with both right and left subtrees */
					{	/* substituir pelo menor elemento da subarvore direita - replacing by the minimum element of the right subtree */
						(*proot)->Elem = FindMin ((*proot)->PtRight);
							/* remover o menor elemento da subarvore direita - deleting the minimum element of the right subtree */
						AVLDeleteRec (&(*proot)->PtRight, (*proot)->Elem);
					}
}

/*******************************************************************************
  Fun��o repetitiva que pesquisa o no minimo que se encontra na arvore a
  partir do no indicado.
  
  Repetitive function that searches the minimum element of a tree that starts in
  the given node.
*******************************************************************************/
static int FindMin (PtAVLNode proot)
{
	PtAVLNode Node = proot;

	while (Node->PtLeft != NULL) Node = Node->PtLeft;
	return Node->Elem;	/* devolve uo elemento - returns the minimum element */
}

/*******************************************************************************
  Fun��o recursiva que pesquisa o elemento pretendido na arvore.
*******************************************************************************/
static PtAVLNode SearchRec (int elemento, PtAVLNode no)
{
    if (no == NULL) return NULL;

    if (no->Elem > elemento) return SearchRec (elemento, no->PtLeft);
    else if (no->Elem < elemento) return SearchRec (elemento, no->PtRight);
         else return no;
}

/*******************************************************************************
  Fun��o recursiva que escreve num ficheiro os elementos da AVL em pr�-ordem.

  Recursive function that makes a pre-order traversal of the tree and writes its
  elements in a text file.
*******************************************************************************/
static void StoreFilePreOrder (PtAVLNode avl, FILE *fich)
{
    if (avl != NULL)
    {
        fprintf (fich, "%d\n", avl->Elem);

        StoreFilePreOrder (avl->PtLeft, fich);
        StoreFilePreOrder (avl->PtRight, fich);
    }
}

/*******************************************************************************
  Fun��o recursiva que escreve os elementos da AVL de forma hier�rquica.
  
  Recursive function that prints the tree elements in a hierarchical way.
*******************************************************************************/
static void Display (PtAVLNode proot, unsigned int plevel)
{
	unsigned int i;

	if (proot == NULL)
	{
		for (i = 0; i < plevel; i++) printf ("\t");
		printf ("*\n");
        return;
	}

	Display (proot->PtRight, plevel+1);

	for (i = 0; i < plevel; i++) printf ("\t");

	printf ("%d\n", proot->Elem);	/* imprimir o elemento - printing the element */

	Display (proot->PtLeft, plevel+1);
}

