/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstracto VECTOR (vector.h). O vector �
 composto pela sua dimens�o e pelas suas componentes reais. A implementa��o
 providencia um construtor para criar um vector nulo com a dimens�o pretendida.
 � da responsabilidade da aplica��o, invocar o destrutor, para libertar a
 mem�ria atribu�da ao objecto. O m�dulo providencia um controlo centralizado de
 erro, disponibilizando uma fun��o para obter o �ltimo erro ocorrido, uma fun��o
 para obter uma mensagem de erro elucidativa e uma fun��o para limpar o erro.
 Providencia tamb�m opera��es para armazenar e recuperar vectores para ficheiros.

 Autor : Ant�nio Manuel Adrego da Rocha    Data : Janeiro de 2015
 
 Interface file of the abstract data type VECTOR (vector.h). The vector is defined
 by its size and the real components stored in an array. The implementation provides
 a constructor for creating an empty vector with the required size. The application
 has the responsibility of calling the destructor to release the dynamic memory 
 allocated to the vector. The data-type has a central control error mechanism, 
 providing operations for obtaining the last error occurred, for obtaining the 
 correspondent message and for cleaning the error. The data-type has also operations
 to store and retrieve vectors from text files.

*******************************************************************************/

#ifndef _VECTOR
#define _VECTOR

/****************** Defini��o do Tipo Ponteiro para um VECTOR *****************/

typedef struct vector *PtVector;

/************************ Defini��o de C�digos de Erro ************************/

#define  OK         0  /* opera��o realizada com sucesso - operation with success */
#define  NO_VECTOR  1  /* o(s) vector(es) n�o existe(m) - vector(s) do not exist */
#define  NO_MEM     2  /* mem�ria esgotada - out of memory */
#define  NO_FILE    3  /* o ficheiro n�o existe - file does not exist */
#define  BAD_SIZE   4  /* dimens�o do vector errada - wrong size */
#define  BAD_INDEX  5  /* elemento inexistente no vector - element does not exist in the vector */
#define  DIF_SIZE   6  /* vectores com dimens�es diferentes - vectors with different sizes */

/*************************** Prot�tipos das Fun��es ***************************/

void VectorClearError (void);
/*******************************************************************************
 Inicializa��o do erro. Error initialization.
*******************************************************************************/

int VectorError (void);
/*******************************************************************************
 Devolve o c�digo do �ltimo erro ocorrido. Returning the error code.
*******************************************************************************/

char *VectorErrorMessage (void);
/*******************************************************************************
 Devolve uma mensagem esclarecedora da causa do �ltimo erro ocorrido.
 Returning an error message.
*******************************************************************************/

PtVector VectorCreate (unsigned int pdim);
/*******************************************************************************
 Cria um vector nulo, de componentes reais, com a dimens�o indicada por pdim.
 Devolve a refer�ncia do vector criado ou NULL, caso n�o consiga criar o vector,
 por falta de mem�ria. Valores de erro: OK, BAD_SIZE ou NO_MEM.

 Creating the empty vector with the required size. Returns a reference to the
 new vector or NULL if there isn't enough memory. Error codes: OK, BAD_SIZE or NO_MEM.
*******************************************************************************/

void VectorDestroy (PtVector *pvector);
/*******************************************************************************
 Destr�i o vector pvector, caso ele exista, e coloca a sua
 refer�ncia a NULL. Valores de erro: OK ou NO_VECTOR.
 
 Destroys the vector and releases the memory. Error codes: OK or NO_VECTOR.
*******************************************************************************/

PtVector VectorCopy (PtVector pvector);
/*******************************************************************************
 Copia o vector pvector, caso ele exista. Devolve a refer�ncia do vector c�pia ou 
 NULL, caso n�o consiga fazer a c�pia. Valores de erro: OK, NO_VECTOR ou NO_MEM.
 
 Copies the vector returning a new vector or NULL if there isn't enough memory.
 Error codes: OK, NO_VECTOR or NO_MEM.
*******************************************************************************/

int VectorSize (PtVector pvector);
/*******************************************************************************
 Devolve a dimens�o do vector pvector. Valores de erro: OK ou NO_VECTOR.
 
 Returning the size of the vector pvector. Error codes: OK or NO_VECTOR. 
*******************************************************************************/

void VectorModifyComponent (PtVector pvector, unsigned int ppos, double pval);
/*******************************************************************************
 Armazena pval no �ndice ppos do vector pvector.
 Valores de erro: OK, NO_VECTOR ou BAD_INDEX.
 
 Storing the value pval in the position ppos of the vector pvector.
 Error codes: OK, NO_VECTOR or BAD_INDEX.
*******************************************************************************/

double VectorObserveComponent (PtVector pvector, unsigned int ppos);
/*******************************************************************************
 Devolve o valor armazenado no �ndice ppos do vector pvector.
 Valores de erro: OK, NO_VECTOR ou BAD_INDEX.
 
 Returning the value in the position ppos of the vector pvector.
 Error codes: OK, NO_VECTOR or BAD_INDEX.
*******************************************************************************/

int VectorIsNull (PtVector pvector);
/*******************************************************************************
 Verifica se o vector pvector � um vector nulo. Devolve 1 em caso afirmativo e 0
 em caso contr�rio. Valores de erro: OK ou NO_VECTOR.
 
 Verifies if vector pvector is empty (all components are zero). Returns 1 in 
 affirmative case and 0 otherwise. Error codes: OK or NO_VECTOR.
*******************************************************************************/

PtVector VectorAddition (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Soma os dois vectores pvector1 e pvector2. Devolve a refer�ncia do vector soma ou NULL,
 caso n�o consiga fazer a adi��o. Valores de erro: OK, NO_VECTOR, DIF_SIZE ou NO_MEM.
 
 Vector addition returning a new vector. Error codes: OK, NO_VECTOR, DIF_SIZE or NO_MEM.
*******************************************************************************/

PtVector VectorSubtraction (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Subtrai os dois vectores pvector1 e pvector2. Devolve a refer�ncia do vector 
 diferen�a ou NULL, caso n�o consiga fazer a subtrac��o. Valores de erro: OK, 
 NO_VECTOR, DIF_SIZE ou NO_MEM.

 Vector subtraction returning a new vector. Error codes: OK, NO_VECTOR, DIF_SIZE or NO_MEM.
*******************************************************************************/

PtVector VectorMultiplication (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Faz o produto vectorial dos dois vectores pvector1 e pvector2. Devolve a refer�ncia 
 do vector produto ou NULL, caso n�o consiga fazer a multiplica��o. Valores de 
 erro: OK, NO_VECTOR, DIF_SIZE or NO_MEM.

 Vector multiplication returning a new vector. Error codes: OK, NO_VECTOR, DIF_SIZE or NO_MEM.
*******************************************************************************/

double VectorScalarMultiplication (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Devolve o produto escalar dos dois vectores pvector1 e pvector2, ou 0, caso n�o 
 possa realizar o produto. Valores de erro: OK, NO_VECTOR ou DIF_SIZE.
 
 Scalar vector multiplication. Error codes: OK, NO_VECTOR or DIF_SIZE.
*******************************************************************************/

int VectorEquals (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Compara se os dois vectores pvector1 e pvector2 s�o id�nticos. Devolve 1 em caso 
 afirmativo e 0 em caso contr�rio. Valores de erro: OK, NO_VECTOR ou DIF_SIZE.

 Verifies if two vector are equal (same size and all components are equal).
 Returns 1 in affirmative case and 0 otherwise. Error codes: OK, NO_VECTOR or DIF_SIZE.
*******************************************************************************/

void VectorStoreFile (PtVector pvector, char *pfname);
/*******************************************************************************
 Armazena o vector pvector, caso ele exista, no ficheiro pfname. O ficheiro tem na 
 primeira linha o n�mero de componentes do vector, seguido das componentes, uma 
 por linha. Valores de erro: OK, NO_VECTOR ou NO_FILE.
 
 Storing vector pvector in text file pfname. Error codes: OK, NO_VECTOR or NO_FILE.
*******************************************************************************/

PtVector VectorCreateFile (char *pfname);
/*******************************************************************************
 Cria um vector a partir de informa��o lida do ficheiro pfname. Devolve a
 refer�ncia do vector criado ou NULL, caso n�o consiga criar o vector.
 Valores de erro: OK, NO_FILE, BAD_SIZE ou NO_MEM.
 
 Creating a vector from text file pfname. Returns a reference to the new vector
 or NULL if there isn't enough memory. Error codes: OK, NO_FILE, BAD_SIZE or NO_MEM.
*******************************************************************************/

#endif
