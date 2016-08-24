/*******************************************************************************

 Ficheiro de implementa��o do Tipo de Dados Abstracto VECTOR (vector.c).
 A estrutura de dados de suporte do vector � uma estrutura, constitu�da pelo
 campo de tipo inteiro NElem para armazenar o n�mero de componentes do vector
 e o campo de tipo ponteiro Vector, para representar a sequ�ncia atribu�da 
 dinamicamente, que vai armazenar as suas componentes reais.

 Autor : Ant�nio Manuel Adrego da Rocha    Data : Janeiro de 2015
 
 Implementation file of the abstract data type VECTOR (vector.c). The data
 structure to store the vector is composed with the integer field NElem for keeping
 the vector's size and the pointer field Vector, that represents the allocated 
 array in dynamic memory, for storing the vector's real components.

*******************************************************************************/

#include <stdio.h>  
#include <stdlib.h>

#include "vector.h"  /* Ficheiro de interface do TDA - ADT Interface file */

/************** Defini��o da Estrutura de Dados Interna do Vector *************/

struct vector
{
  unsigned int NElem;  /* n�mero de componentes do vector - vector's size */
  double *Vector;    /* ponteiro para a sequencia de componentes - pointer to vector's components */
};

/*********************** Controlo Centralizado de Error ************************/

static unsigned int Error = OK;  /* inicializa��o do erro */

static char *ErrorMessages[] = {
                                 "sem erro - Without Error",
                                 "vector(es) inexistente(s) - Vector(s) do not exist",
                                 "memoria esgotada - Out of memory",
                                 "ficheiro inexistente - File does not exist",
                                 "dimensao errada - Wrong size",
                                 "componente inexistente no vector - Component does not exist",
                                 "vectores com dimensoes diferentes - Vectors with different sizes"
                               };

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** N�mero de mensagens de erro previstas no m�dulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alus�o �s Fun��es Auxiliares ************************/

static int ValidVectors (PtVector, PtVector);

/*************************** Defini��o das Fun��es ****************************/

void VectorClearError (void)
{
  Error = OK;
}

int VectorError (void)
{
  return Error;
}

char *VectorErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* n�o h� mensagem de erro - no error message */
}

PtVector VectorCreate (unsigned int pdim)
{
  PtVector Vector;

  /* valida a dimens�o do vector - size validation */
  if (pdim < 1) { Error = BAD_SIZE; return NULL; }

  /* cria o vector nulo - allocating the supporting record (struct) and its supporting array */
  if ((Vector = (PtVector) malloc (sizeof (struct vector))) == NULL)
  { Error = NO_MEM; return NULL; }
  
  if ((Vector->Vector = (double *) calloc (pdim, sizeof (double))) == NULL)
  { free (Vector); Error = NO_MEM; return NULL; }

  Vector->NElem = pdim;     /* armazenamento da dimens�o - storing the size */

  Error = OK;
  return Vector;    /* devolve o vector criado - returning the new vector */
}

void VectorDestroy (PtVector *pvec)
{
  PtVector TmpVector = *pvec;

  /* verifica se o vector existe - verifies if vector exists */
  if (TmpVector == NULL) { Error = NO_VECTOR; return ; }

  /* liberta��o da mem�ria din�mica - free dynamic memory */
  free (TmpVector->Vector);  /* liberta a mem�ria ocupada pelas componentes  - free the supporting array */
  free (TmpVector);    /* liberta a mem�ria ocupada pelo vector - free the supporting record */

  Error = OK;
  *pvec = NULL;  /* coloca a refer�ncia a nulo - free the pointer pointing it to null */
}

PtVector VectorCopy (PtVector pvec)
{
  PtVector Copy; int I;

  /* verifica se o vector existe - verifies if vector exists */
  if (pvec == NULL) { Error = NO_VECTOR; return NULL; }

  /* cria��o do vector copia nulo - creating an empty vector */
  if ((Copy = VectorCreate (pvec->NElem)) == NULL) return NULL;

  /* fazer a copia do vector - copying the components */
  for (I = 0; I < pvec->NElem; I++) Copy->Vector[I] = pvec->Vector[I];

  return Copy;  /* devolve o vector copia - returning the new vector */
}

int VectorSize (PtVector pvec)
{
  /* verifica se o vector existe - verifies if vector exists */
  if (pvec == NULL) { Error = NO_VECTOR; return 0; }

  Error = OK;
  return pvec->NElem;
}

void VectorModifyComponent (PtVector pvec, unsigned int ppos, double pval)
{
  /* verifica se o vector existe - verifies if vector exists */
  if (pvec == NULL) { Error = NO_VECTOR; return ; }

  /* valida��o do elemento pretendido - validating the element position */
  if ((ppos < 0) || (ppos >= pvec->NElem)) { Error = BAD_INDEX; return ; }

  Error = OK;
  /* escrita do valor na componente pretendida do vector - storing the new value in the component */
  pvec->Vector[ppos] = pval;
}

double VectorObserveComponent (PtVector pvec, unsigned int ppos)
{
  /* verifica se o vector existe - verifies if vector exists */
  if (pvec == NULL) { Error = NO_VECTOR; return 0; }

  /* valida��o do elemento pretendido - validating the element position */
  if ((ppos < 0) || (ppos >= pvec->NElem)) { Error = BAD_INDEX; return 0; }

  Error = OK;
  /* devolve o valor armazenado na componente pretendida do vector - returning the component value */
  return pvec->Vector[ppos];
}

int VectorIsNull (PtVector pvec)
{
  int I;

  /* verifica se o vector existe - verifies if vector exists */
  if (pvec == NULL) { Error = NO_VECTOR; return 0; }
  Error = OK;

  /* verifica��o das componentes do vector - verifying the vector's components */
  for (I = 0; I < pvec->NElem; I++)
    if (pvec->Vector[I]) return 0;

  return 1;  /* o vector � um vector nulo - the vector is empty */
}

PtVector VectorAddition (PtVector pvec1, PtVector pvec2)
{
  PtVector Add; int I;

  /* valida��o dos vectores - validating the existence of the two vectors */
  if (!ValidVectors (pvec1, pvec2)) return NULL;

  /* cria��o do vector soma nulo - creating an empty vector */
  if ((Add = VectorCreate (pvec1->NElem)) == NULL) { Error = NO_MEM; return NULL; }

  /* soma dos dois vectores - adding the respective components of the two vectors */
  for (I = 0; I < pvec1->NElem; I++)
    Add->Vector[I] = pvec1->Vector[I] + pvec2->Vector[I];

  return Add;  /* devolve o vector soma - returning the new vector */
}

PtVector  VectorSubtraction (PtVector pvec1, PtVector pvec2)
{
  PtVector Sub; int I;

  /* valida��o dos vectores - validating the existence of the two vectors */
  if (!ValidVectors (pvec1, pvec2)) return NULL;

  /* cria��o do vector diferen�a nulo - creating an empty vector */
  if ((Sub = VectorCreate (pvec1->NElem)) == NULL) { Error = NO_MEM; return NULL; }

  /* diferen�a dos dois vectores - subtracting the respective components of the two vectors */
  for (I = 0; I < pvec1->NElem; I++)
    Sub->Vector[I] = pvec1->Vector[I] - pvec2->Vector[I];

  return Sub;  /* devolve o vector diferen�a - returning the new vector */
}

PtVector  VectorMultiplication (PtVector pvec1, PtVector pvec2)
{
  PtVector Mult; int I;

  /* valida��o dos vectores - validating the existence of the two vectors */
  if (!ValidVectors (pvec1, pvec2)) return NULL;

  /* cria��o do vector produto nulo - creating an empty vector */
  if ((Mult = VectorCreate (pvec1->NElem)) == NULL) { Error = NO_MEM; return NULL; }

  /* produto dos dois vectores - multiplying the respective components of the two vectors*/
  for (I = 0; I < pvec1->NElem; I++)
    Mult->Vector[I] = pvec1->Vector[I] * pvec2->Vector[I];

  return Mult;  /* devolve o vector produto - returning the new vector */
}

double  VectorScalarMultiplication (PtVector pvec1, PtVector pvec2)
{
  int I; double Prod = 0.0;

  /* valida��o dos vectores - validating the existence of the two vectors */
  if (!ValidVectors (pvec1, pvec2)) return 0;

  /* c�lculo do produto escalar - calculating the scalar product */
  for (I = 0; I < pvec1->NElem; I++)
    Prod += pvec1->Vector[I] * pvec2->Vector[I];

  Error = OK;
  return Prod;  /* devolve o produto escalar - returning the scalar product */
}

int  VectorEquals (PtVector pvec1, PtVector pvec2)
{
  int I;

  /* valida��o dos vectores - validating the existence of the two vectors */
  if (!ValidVectors (pvec1, pvec2)) return 0;
  Error = OK;

  /* compara��o das componentes dos dois vectores - comparing the respective components */
  for (I = 0; I < pvec1->NElem; I++)
    if (pvec1->Vector[I] != pvec2->Vector[I]) return 0;

  return 1;  /* os vectores s�o iguais - the two vectors are equall */
}

void VectorStoreFile (PtVector pvec, char *pnomef)
{
  FILE *PtF; unsigned int I;

  /* verifica se o vector existe - verifies if vector exists */
  if (pvec == NULL) { Error = NO_VECTOR; return ; }

  /* abertura com validacao do ficheiro para escrita - opening the text file for writing */
  if ((PtF = fopen (pnomef, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita da dimens�o do vector no ficheiro - writing the vector's size */
  fprintf (PtF, "%u\n", pvec->NElem);

  /* escrita das componentes do vector no ficheiro - writing the vector's components */
  for (I = 0; I < pvec->NElem; I++) fprintf (PtF, "%lf\n", pvec->Vector[I]);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro - closing the text file */
}

PtVector VectorCreateFile (char *pnomef)
{
  PtVector Vector; FILE *PtF; unsigned int NElem, I;

  /* abertura com validacao do ficheiro para leitura - opening the text file for reading */
  if ( (PtF = fopen (pnomef, "r")) == NULL) { Error = NO_FILE; return NULL; }

  /* leitura da dimens�o do vector do ficheiro - reading the vector's size from the text file */
  fscanf (PtF, "%u", &NElem);
  if (NElem < 1) { Error = BAD_SIZE; fclose (PtF); return NULL; }

  /* cria��o do vector nulo - creating an empty vector */
  if ((Vector = VectorCreate (NElem)) == NULL) { fclose (PtF); return NULL; }

  /* leitura das componentes do vector do ficheiro - reading the vector's components from the text file */
  for (I = 0; I < NElem; I++) fscanf (PtF, "%lf", Vector->Vector+I);

  fclose (PtF);  /* fecho do ficheiro - closing the text file */

  return Vector;  /* devolve o vector criado - returning the new vector */
}

/*******************************************************************************
 Fun��o auxiliar que verifica se os dois vectores podem ser operados, ou seja,
 se existem e se t�m a mesma dimens�o. Devolve 1 em caso afirmativo e 0 em caso
 contr�rio. Valores de erro: OK, NO_VECTOR ou DIF_SIZE.
 
 Auxiliary function to verify if the two vectors can be operated, that is, if they
 exist and have the same size. Returns 1 in affirmative case and 0 otherwise.
 Error codes: OK, NO_VECTOR or DIF_SIZE. 
*******************************************************************************/
static int ValidVectors (PtVector pvec1, PtVector pvec2)
{
  /* verifica se os dois vectores existem - verifies if the two vectors exist */
  if ((pvec1 == NULL) || (pvec2 == NULL)) { Error = NO_VECTOR; return 0; }

  /* verifica se a dimens�o dos dois vectores � igual - verifies if they have the same size */
  if (pvec1->NElem != pvec2->NElem) { Error = DIF_SIZE; return 0; }

  Error = OK;
  return 1;  /* os dois vectores existem e t�m a mesma dimens�o - they exist and have the same size */
}
