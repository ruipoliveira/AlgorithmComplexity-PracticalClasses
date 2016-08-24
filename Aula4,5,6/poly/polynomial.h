/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstrato POLY (polynomial.h).
 O polin�mio � composto pelo seu grau e pelos seus coeficientes reais, sendo
 que um polin�mio com grau n tem n+1 coeficientes. A implementa��o providencia
 um construtor para criar um polin�mio nulo com o grau pretendido. � da
 responsabilidade da aplica��o, invocar o destrutor, para libertar a mem�ria
 atribu�da ao objecto. O m�dulo providencia um controlo centralizado de erro,
 disponibilizando uma fun��o para obter o �ltimo erro ocorrido, uma fun��o para
 obter uma mensagem de erro elucidativa e uma fun��o para limpar o erro.
 Providencia tamb�m opera��es para armazenar e recuperar polin�mios para ficheiros.
 
 Autor : Ant�nio Manuel Adrego da Rocha    Data : Janeiro de 2015
 
 Interface file of the abstract data type POLY (polynomial.h). The polynomial is 
 defined by its degree and the real coefficients stored in an array. The implementation 
 provides a constructor for creating an empty polynomial with the required degree. 
 The application has the responsibility of calling the destructor to release the 
 dynamic memory allocated to the polynomial. The data-type has a central control 
 error mechanism, providing operations for obtaining the last error occurred, for 
 obtaining the correspondent message and for cleaning the error. The data-type has
 also operations to store and retrieve polynomials from text files.


*******************************************************************************/

#ifndef _POLY
#define _POLY

/**************** Defini��o do Tipo Ponteiro para um Polin�mio ****************/

typedef struct poly *PtPoly;

/************************ Defini��o de C�digos de Erro ************************/


#define  OK         0  /* opera��o realizada com sucesso - operation with success */
#define  NO_POLY    1  /* o(s) polin�mio(s) n�o existe(m) - the polynomial(s) do not exist */
#define  NO_MEM     2  /* mem�ria esgotada - out of memory */
#define  NO_FILE    3  /* o ficheiro n�o existe - file does not exist */
#define  BAD_DEGREE 4  /* grau do polin�mio errado - wrong degree */
#define  BAD_INDEX  5  /* coeficiente inexistente no polin�mio - coefficient does not exist in the polynomial */

/*************************** Prot�tipos das Fun��es ***************************/

void PolyClearError (void);
/*******************************************************************************
 Inicializa��o do erro. Error initialization.
*******************************************************************************/

int PolyError (void);
/*******************************************************************************
 Fun��o que devolve o c�digo do �ltimo erro ocorrido. Returns the error code.
*******************************************************************************/

char *PolyErrorMessage (void);
/*******************************************************************************
 Fun��o que devolve uma mensagem esclarecedora da causa do �ltimo erro ocorrido.
 Returns an error message.
*******************************************************************************/

PtPoly PolyCreate (unsigned int pdegree);
/*******************************************************************************
 Cria um polin�mio nulo, de coeficientes reais, com o grau indicado por pdegree.
 Devolve a refer�ncia do polin�mio criado ou NULL, caso n�o consiga criar o
 polin�mio, por falta de mem�ria. Valores de erro: OK ou NO_MEM.
 
 Creates the empty polynomial with the required degree. Returns a reference to the
 new polynomial or NULL if there isn't enough memory. Error codes: OK or NO_MEM.
*******************************************************************************/

void PolyDestroy (PtPoly *ppoly);
/*******************************************************************************
 Destr�i o polin�mio ppoly, caso ele exista, e coloca a sua refer�ncia a NULL.
 Valores de erro: OK ou NO_POLY.
 
 Destroys the polynomial and releases the memory. Error codes: OK or NO_POLY.
*******************************************************************************/

PtPoly PolyCopy (PtPoly ppoly);
/*******************************************************************************
 Copia do polin�mio ppoly, caso ele exista. Devolve a refer�ncia do polin�mio c�pia
 ou NULL, caso n�o consiga fazer a c�pia. Valores de erro: OK, NO_POLY ou NO_MEM.
 
 Copies the polynomial ppoly returning a new polynomial or NULL if there isn't 
 enough memory. Error codes: OK, NO_POLY or NO_MEM.
*******************************************************************************/

int PolyDegree (PtPoly ppoly);
/*******************************************************************************
 Devolve o grau do polin�mio ppoly. Valores de erro: OK ou NO_POLY.
 
 Returns the degree of the polynomial ppoly. Error codes: OK or NO_POLY. 
*******************************************************************************/

void PolyModifyCoefficient (PtPoly ppoly, unsigned int ppos, double pvalue);
/*******************************************************************************
 Armazena pvalue no �ndice ppos, do polin�mio ppoly. Valores de erro: OK, NO_POLY
 ou BAD_INDEX.
 
 Stores the value pval in the position ppos of the polynomial ppoly.
 Error codes: OK, NO_POLY or BAD_INDEX.
*******************************************************************************/

double PolyObserveCoefficient (PtPoly ppoly, unsigned int ppos);
/*******************************************************************************
 Devolve o valor armazenado no �ndice ppos do polin�mio ppoly. Valores de erro: 
 OK, NO_POLY ou BAD_INDEX.

 Returns the value in the position ppos of the polynomial ppoly.
 Error codes: OK, NO_POLY or BAD_INDEX.
*******************************************************************************/

int PolyIsNull (PtPoly ppoly);
/*******************************************************************************
 Verifica se o polin�mio ppoly � um polin�mio nulo. Devolve 1 em caso afirmativo 
 e 0 em caso contr�rio. Valores de erro: OK ou NO_POLY.
 
 Verifies if polynomial ppoly is empty (all coefficients are zero). Returns 1 in affirmative
 case and 0 otherwise. Error codes: OK or NO_POLY.
*******************************************************************************/

PtPoly PolyAddition (PtPoly ppoly1, PtPoly ppoly2);
/*******************************************************************************
 Soma os dois polin�mios ppoly1 e ppoly2. Devolve a refer�ncia do polin�mio soma 
 ou NULL, caso n�o consiga fazer a adi��o. Valores de erro: OK, NO_POLY ou NO_MEM.
 
 Polynomial addition returning a new polynomial. Error codes: OK, NO_POLY or NO_MEM.

*******************************************************************************/

PtPoly PolySubtraction (PtPoly ppoly1, PtPoly ppoly2);
/*******************************************************************************
 Subtrai os dois polin�mios ppoly1 e ppoly2. Devolve a refer�ncia do polin�mio 
 diferen�a ou NULL, caso n�o consiga fazer a subtrac��o. Valores de erro: OK, 
 NO_POLY ou NO_MEM.

 Polynomial subtraction returning a new polynomial. Error codes: OK, NO_POLY or NO_MEM.
*******************************************************************************/

PtPoly PolyMultiplication (PtPoly ppoly1, PtPoly ppoly2);
/*******************************************************************************
 Multiplica os dois polin�mios ppoly1 e ppoly2. Devolve a refer�ncia do polin�mio 
 produto ou NULL, caso n�o consiga fazer a multiplica��o. Valores de erro: OK, 
 NO_POLY ou NO_MEM.
 
 Polynomial multiplication returning a new polynomial. Error codes: OK, NO_POLY or NO_MEM.
*******************************************************************************/

int PolyEquals (PtPoly ppoly1, PtPoly ppoly2);
/*******************************************************************************
 Compara se os dois polin�mios ppoly1 e ppoly2 s�o id�nticos. Devolve 1 em caso 
 afirmativo e 0 em caso contr�rio. Valores de erro: OK ou NO_POLY.

 Verifies if two polynomials are equal (same degree and all coefficients are equal).
 Returns 1 in affirmative case and 0 otherwise. Error codes: OK or NO_POLY.
*******************************************************************************/

void PolyStoreFile (PtPoly ppoly, char *pfname);
/*******************************************************************************
 Armazena o polin�mio ppoly, caso ele exista, no ficheiro pfname. O ficheiro tem 
 na primeira linha o grau do polin�mio, seguido dos coeficientes, um por linha.
 Valores de erro: OK, NO_POLY ou NO_FILE.
 
 Stores polynomial ppoly in text file pfname. Error codes: OK, NO_POLY or NO_FILE.
*******************************************************************************/

PtPoly PolyCreateFile (char *pfname);
/*******************************************************************************
 Cria um polin�mio a partir de informacao lida do ficheiro pfname. Devolve a
 refer�ncia do polin�mio criado ou NULL, caso n�o consiga criar o polin�mio.
 Valores de erro: OK, NO_FILE ou NO_MEM.

 Creates a new polynomial from text file pfname. Returns a reference to the new
 polynomial or NULL if there isn't enough memory. Error codes: OK, NO_FILE or NO_MEM.
*******************************************************************************/

double PolyEvaluation (PtPoly ppoly, double px);
/*******************************************************************************
 Devolve o valor do pol�n�mio ppoly para o argumento px. Valores de erro: 
 OK ou NO_POLY.
 
 Returnes the value of polynomial ppoly for the argument px. Error codes: OK or NO_POLY.
*******************************************************************************/

#endif
