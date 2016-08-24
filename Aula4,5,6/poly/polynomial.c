/*******************************************************************************

 Ficheiro de implementação do Tipo de Dados Abstrato POLINOMIO (polynomial.c).
 A estrutura de dados de suporte do polinómio é uma estrutura, constituída pelo
 campo de tipo inteiro Degree para armazenar o grau do polinómio e o campo de
 tipo ponteiro Poly, para representar a sequência atribuída dinamicamente, que
 vai armazenar os seus coeficientes reais.
 
 Nome : Rui Pedro dos Santos Oliveira                         NMec: 68779

 Implementation file of the abstract data type Poly (polynomial.c). The data
 structure to store the polynomial is composed with the integer field Degree for
 keeping the polynomial's degree and the pointer field Poly, that represents the
 allocated array in dynamic memory, for storing the polynomial's real coefficients.

*******************************************************************************/

#include <stdio.h>  
#include <stdlib.h>
#include <math.h>

#include "polynomial.h"    /* Ficheiro de interface do TDA - ADT Interface file */

/************ Definição da Estrutura de Dados Interna do POLINOMIO ************/

struct poly
{
  unsigned int Degree;  /* grau do polinómio - polynomial degree */
  double *Poly;      /* ponteiro para os coeficientes do polinómio - pointer to polynomial's coefficients */
};

/*********************** Controlo Centralizado de Erro ************************/

static unsigned int Error = OK;  /* inicialização do erro */

static char *ErrorMessages[] = {
                                 "sem erro - Without Error",
                                 "polinomio(s) inexistente(s) - Polynomial(s) do not exist",
                                 "memoria esgotada - Out of memory",
                                 "ficheiro inexistente - File does not exist",
                                 "grau do polinomio errado - Wrong degree",
                                 "coeficiente inexistente no polinomio - Coefficient does not exist"
                               };

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** Número de mensagens de erro previstas no módulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alusão às Funções Auxiliares ************************/

static int ValidPolys (PtPoly, PtPoly);
static void ReducePoly (PtPoly);

/*************************** Definição das Funções ****************************/

void PolyClearError (void)
{
  Error = OK;
}

int PolyError (void)
{
  return Error;
}

char *PolyErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;    /* não há mensagem de erro - no error message */
}

PtPoly PolyCreate (unsigned int pdegree){
  /* insira o seu código - insert your code */
  PtPoly polinomio;

  if((polinomio = (PtPoly) malloc (sizeof (struct poly))) == NULL){
    Error = NO_MEM;
    return NULL;
  }

  if((polinomio->Poly = (double*) calloc ((pdegree+1), sizeof (double))) == NULL){
    free(polinomio);
    Error = NO_MEM;
    return NULL;
  }

  polinomio->Degree = pdegree;

  Error = OK;
  return polinomio;
}

void PolyDestroy (PtPoly *ppol){
  /* insira o seu código - insert your code */
  PtPoly polinomioTemp = *ppol;

  if(polinomioTemp == NULL){
    Error = NO_POLY;
    return;
  }
  free (polinomioTemp->Poly);
  free (polinomioTemp);

  Error = OK;
  *ppol = NULL;
}


PtPoly PolyCopy (PtPoly ppol){
  /* insira o seu código - insert your code */
  PtPoly copia;
  int i;

  if(ppol == NULL){
    Error = NO_POLY;
    return NULL;
  }

  if((copia = PolyCreate (ppol->Degree)) == NULL){
    return NULL;
  }

  for(i=0; i <= ppol->Degree; i++){
    copia->Poly[i] = ppol->Poly[i];
  }

  return copia;
}

int PolyDegree (PtPoly ppol){
  /* insira o seu código - insert your code */
  if(ppol == NULL){
    Error = NO_POLY;
  }

  Error = OK;
  return ppol->Degree;
}

void PolyModifyCoefficient (PtPoly ppol, unsigned int ppos, double pvalue){
  /* insira o seu código - insert your code */
  if(ppol == NULL){
    Error = NO_POLY;
    return;
  }

  if((ppos > ppol->Degree) || (ppos < 0) ){
    Error = BAD_INDEX;
    return;
  }

  Error = OK;
  ppol->Poly[ppos] = pvalue;

}

double PolyObserveCoefficient (PtPoly ppol, unsigned int ppos){
  /* insira o seu código - insert your code */
  if(ppol == NULL){
    Error = NO_POLY;
    return 0;
  }

  if((ppos < 0) || (ppos > ppol->Degree)){
    Error = BAD_INDEX;
    return 0;
  }

  Error = OK;
  return ppol->Poly[ppos];
}

int PolyIsNull (PtPoly ppol){
  /* insira o seu código - insert your code */
  int i;

  if(ppol == NULL){
    Error = NO_POLY;
    return 0;
  }

  Error = OK;

  for(i = 0; i < ppol->Degree; i++){
    if(ppol->Poly[i]){
      return 0; /*polinomio nulo*/
    }
  }
  return 1; /*polinomio nulo*/
}

PtPoly PolyAddition (PtPoly ppol1, PtPoly ppol2){
  /* insira o seu código - insert your code */
  PtPoly resultAdd;
  int i;
  int min = ppol2->Degree;
  int max = ppol1->Degree;
  if(min > max){
    max = ppol2->Degree;
    min = ppol1->Degree;
  }
    
  if(!ValidPolys(ppol1, ppol2)){
    Error = NO_POLY;
    return NULL;
  }

  if((resultAdd = PolyCreate(max)) == NULL){
    Error = NO_MEM;
    return NULL;
  }

  for(i = 0; i <= max; i++){
    resultAdd->Poly[i] = ppol1->Poly[i] + ppol2->Poly[i];
  }
  Error = OK;
  ReducePoly(resultAdd);
  return resultAdd;
}

PtPoly PolySubtraction (PtPoly ppol1, PtPoly ppol2){
  /* insira o seu código - insert your code */
  PtPoly resultSub;
  int i;
  int min = ppol2->Degree;
  int max = ppol1->Degree;
  
  if(min > max){
    max = ppol2->Degree;
    min = ppol1->Degree;
  }
    
  if(!ValidPolys(ppol1, ppol2)){
    Error = NO_POLY;
    return NULL;
  }

  if((resultSub = PolyCreate(max)) == NULL){
    Error = NO_MEM;
    return NULL;
  }

  for(i = 0; i <= max; i++){
    resultSub->Poly[i] = ppol1->Poly[i] - ppol2->Poly[i];
  }
  Error = OK;
  ReducePoly(resultSub);
  return resultSub;

}

PtPoly PolyMultiplication (PtPoly ppol1, PtPoly ppol2){
  /* insira o seu código - insert your code */
  PtPoly resultMul;
  int i, j;
  
  if(!ValidPolys(ppol1, ppol2)){
    Error = NO_POLY;
    return NULL;
  }

  if((resultMul = PolyCreate((ppol1->Degree) + (ppol2->Degree))) == NULL){
    Error = NO_MEM;
    return NULL;
  }

  for(i = 0; i <= ppol1->Degree; i++){
    for (j = 0; j <= ppol2->Degree; j++){
        resultMul->Poly[i+j] += (ppol1->Poly[i] * ppol2->Poly[j]);
    }
  }

  Error = OK;
  return resultMul;
}

int PolyEquals (PtPoly ppol1, PtPoly ppol2){
  /* insira o seu código */

  if(!ValidPolys(ppol1, ppol2)){
    Error = NO_POLY;
    return 0;
  }
  if(ppol1->Degree != ppol2->Degree)
    return 0;
  
  int i;
  for(i = 0; i < ppol1->Degree; i++){
    if(ppol1->Poly[i] != ppol2->Poly[i])
      return 0;
  }
  Error = OK;
  return 1;
}

void PolyStoreFile (PtPoly ppol, char *pnomef){
  /* insira o seu código - insert your code */
  /* identico ao VectorStoreFile em vector.c*/
  FILE *PtF;

  /* verifica se o polinomio existe */
  if (ppol == NULL){
    Error = NO_POLY;
    return ;
  }

  /* abertura com validacao do ficheiro para escrita */
  if ((PtF = fopen (pnomef, "w")) == NULL){
    Error = NO_FILE;
    return ;
  }

  /* escrita da dimensão do polinomio no ficheiro */
  fprintf (PtF, "%u\n", ppol->Degree);

  /* escrita das componentes do polinomio no ficheiro */
  unsigned int i;
  for (i = 0; i <= ppol->Degree; i++)
    fprintf (PtF, "%lf\n", ppol->Poly[i]);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro */
}

PtPoly PolyCreateFile (char *pnomef){
  /* insira o seu código - insert your code */
  /* identico ao VectorCreateFile em vector.c*/
  PtPoly polinomio; 
  FILE *PtF;
  unsigned int NElem;

  /* abertura com validacao do ficheiro para leitura */
  if ( (PtF = fopen (pnomef, "r")) == NULL){
    Error = NO_FILE; return NULL;
  }

  /* leitura da dimensão do polinomio do ficheiro e criação do polinomio */
  fscanf (PtF, "%u", &NElem);
  if (NElem < 1){
    Error = BAD_DEGREE; fclose (PtF); return NULL;
  }
  /* criação do polinomio nulo*/
  if ((polinomio = PolyCreate (NElem)) == NULL){
    fclose (PtF);
    return NULL;
  }

  /* leitura das componentes do polinomio do ficheiro */
  unsigned int i;
  for (i = 0; i <= NElem; i++)
    fscanf (PtF, "%lf", polinomio->Poly+i);

  fclose (PtF);  /* fecho do ficheiro */

  return polinomio;  /* devolve o polinomio criado */
}

double PolyEvaluation (PtPoly ppoly, double px){
  /* insira o seu código - insert your code */
  /* referencias: Análise da Complexidade de Algoritmos-pag 156, Algoritmo 5.4*/
  if(ppoly == NULL ){
    Error = NO_POLY;
    return 0; /*se o polinomio nao existir o resultado sera zero*/
  }

  double xpower = 1.0;
  double resultado = ppoly->Poly[0];

  int i;
  for(i = 1; i <= ppoly->Degree; i++){ /*percorrer todo o polinomio */
    xpower *= px;  
    resultado += ppoly->Poly[i] * xpower;
  }

  return resultado;
}

/*******************************************************************************
 Função auxiliar que verifica se os dois polinómios existem. Devolve 1 em caso
 afirmativo e 0 em caso contrário. Valores de erro: OK ou NO_POLY.
  
 Auxiliary function to verify if the two polynomials exist. Returns 1 in 
 affirmative case and 0 otherwise. Error codes: OK or NO_POLY. 
*******************************************************************************/

static int ValidPolys (PtPoly ppoly1, PtPoly ppoly2)
{
  /* verifica se os dois polinómios existem - verifies if the two polynomials exist */
  if ((ppoly1 == NULL) || (ppoly2 == NULL)) { Error = NO_POLY; return 0; }

  Error = OK;
  return 1;  /* os dois polinómios existem - they exist */
}

/*******************************************************************************
 Função auxiliar que reduz o polinómio ao menor grau possível. Valores de erro:
 NO_POLY.
  
 Auxiliary function to reduce the polynomial to its least degree. Error codes: NO_POLY. 
  
*******************************************************************************/

static void ReducePoly (PtPoly ppoly)
{
  unsigned int Degree;

  /*verifica se o polinómio existe - verifies if the polynomial exists*/
  if (ppoly == NULL) { Error = NO_POLY; return ; }

  Degree = ppoly->Degree;

  while (Degree > 0 && ppoly->Poly[Degree] == 0.0) Degree--;

  if (Degree != ppoly->Degree)
     ppoly->Poly = (double *) realloc (ppoly->Poly, (Degree+1) * sizeof (double));

  ppoly->Degree = Degree;
  Error = OK;
}

