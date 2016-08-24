#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void WriteVector (PtVector);

int main (void)
{
	PtVector vector1 = NULL, vector2 = NULL, vector3 = NULL;
	char filename[21]; int st, dim, i; double val;

	system ("clear");
	printf ("\nLer vector do ficheiro - Read vector from a text file\n");
	do
	{
  		printf ("Nome do ficheiro (Filename) -> ");
		st = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (st == 0);
	vector1 = VectorCreateFile (filename);
	printf ("\nVector lido do ficheiro - Vector acquired from text file %s\n", filename);
	WriteVector (vector1);

	printf ("\nLer vector do teclado - Read vector from keyboard\n");
	do
	{
		printf ("Dimensao do vector (vector's size)? "); scanf ("%d", &dim);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (dim <= 0);

	vector2 = VectorCreate (dim);
    	for (i = 0; i < dim; i++)
	{
		do
		{
			printf ("Componente do vector (vector's component)? "); st = scanf ("%lf", &val);
			scanf ("%*[^\n]"); scanf ("%*c");
		} while (st == 0);
		VectorModifyComponent (vector2, i, val);
	}

	printf ("\nVector lido do teclado - Vector acquired from keyboard\n");
	WriteVector (vector2);

	printf ("\nEscrever vector no ficheiro - Storing the vector in a text file\n");
	do
	{
  		printf ("Nome do ficheiro (Filename) -> ");
		st = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (st == 0);
	VectorStoreFile (vector2, filename);

	vector3 = VectorAddition (vector1, vector2);
	printf ("\nVector soma - Sum vector\n");
	WriteVector (vector3);

	VectorDestroy (&vector3);
	vector3 = VectorSubtraction (vector1, vector2);
	printf ("\nVector diferenca - Difference vector\n");
	WriteVector (vector3);
	
	VectorDestroy (&vector3);
	vector3 = VectorMultiplication (vector1, vector2);
	printf ("\nVector produto - Product vector\n");
	WriteVector (vector3);

	val = VectorScalarMultiplication (vector1, vector2);
	printf ("\nProduto escalar dos 2 vectores - Scalar product vector = %f\n", val);

	printf ("\nDestruir os vectores - Releasing the vectors\n");
	VectorDestroy (&vector1);
	VectorDestroy (&vector2);
	VectorDestroy (&vector3);

	WriteVector (vector3);

	return 0;
}

void WriteVector (PtVector pv)
{
  int i, dim = VectorSize (pv);

  if (pv != NULL && dim != 0)
  {  /* escrita no monitor das componentes do vector - writing on screen the vector's components */
    printf ("( ");
    for (i = 0; i < dim-1; i++) printf ("%0.1f , ", VectorObserveComponent (pv, i));
    printf ("%0.1f )\n", VectorObserveComponent (pv, i));
  }
}
