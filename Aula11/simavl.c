#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "avl.h"

int main (void)
{
	PtAVLNode avl, node; int value, error; char op;

	system ("clear");
	avl = AVLCreate ();

  	do
	{
		printf ("Inserir-Inserting/Remover-Removing/Terminar-Terminating-> ");
		scanf ("%c", &op);
		scanf ("%*[^\n]"); scanf ("%*c");
		op = toupper (op);
	} while (op != 'I' && op != 'R' && op != 'T');

	while (op != 'T')
	{
  		printf ("Valor (Value) -> ");
		scanf ("%d", &value);
		scanf ("%*[^\n]"); scanf ("%*c");

		if (op == 'I')
		{
			AVLInsertRec (&avl, value);
			if ((error = AVLErrorCode ()) != OK) printf ("Erro a inserir (Error in inserting) -> %s\n", AVLErrorMessage ());
		}
		else	if (op == 'R')
			{
				AVLDeleteRec (&avl, value);
				if ((error = AVLErrorCode ()) != OK) printf ("Erro a remover (Error in removing) -> %s\n", AVLErrorMessage ());
			}
			else
			{
				printf ("Erro na operacao escolhida - Error on the chosen operation\n");
				error = 1;
			}

		if (!error)
		{
			printf ("--------------------------------------------------------------------------------------------\n");
			if (AVLEmpty (avl)) printf ("\nArvore vazia! - Empty tree!\n");
			else AVLDisplay (avl);
  			printf ("--------------------------------------------------------------------------------------------\n");
		}

  		printf ("Inserir-Inserting/Remover-Removing/Terminar-Terminating-> ");
		scanf ("%c", &op);
		scanf ("%*[^\n]"); scanf ("%*c");
		op = toupper (op);
	}

	system ("clear");
	printf ("--------------------------------------------------------------------------------------------\n");
	if (AVLEmpty (avl)) printf ("Arvore vazia! - Empty tree!\n");
	else
    {
        AVLDisplay (avl);
	    printf ("--------------------------------------------------------------------------------------------\n");
	    printf ("Numero de nos da arvore (number of nodes) = %d\n", AVLSize (avl));
	    printf ("Altura da arvore (tree height) = %d\n", AVLHeight (avl));    
    }
	printf ("--------------------------------------------------------------------------------------------\n");

	node = AVLMinRec (avl);
	if (AVLErrorCode ()) printf ("Menor elemento da arvore (minimum element) = %s\n", AVLErrorMessage ());
	else printf ("Menor elemento da arvore (minimum element) = %d\n", AVLElement (node));

	node = AVLMaxRec (avl);
	if (AVLErrorCode ()) printf ("Maior elemento da arvore (maximum element) = %s\n", AVLErrorMessage ());
	else printf ("Maior elemento da arvore (maximum element) = %d\n", AVLElement (node));

	AVLDestroy (&avl);

	return 0;
}

