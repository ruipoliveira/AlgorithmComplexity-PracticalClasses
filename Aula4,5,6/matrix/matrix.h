/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstracto MATRIX (matrix.h). A matriz �
 identificada pela sua dimens�o, ou seja, pelo n�mero de linhas NL e pelo n�mero
 de colunas NC e armazena elementos reais. A implementa��o providencia um
 construtor para criar uma matriz nula. � da responsabilidade da aplica��o,
 invocar o destrutor, para libertar a mem�ria atribu�da ao objecto. O m�dulo
 providencia um controlo centralizado de erro, disponibilizando uma fun��o para
 obter o �ltimo erro ocorrido, uma fun��o para obter uma mensagem de erro
 elucidativa e uma fun��o para limpar o erro. Providencia tamb�m opera��es para
 armazenar e recuperar matrizes para ficheiros.

 Autor : Ant�nio Manuel Adrego da Rocha    Data : Janeiro de 2015

 Interface file of the abstract data type MATRIX (matrix.h). The matrix is defined
 by its size, that is, by its number of lines NL and its number of columns and stores
 real elements. The implementation provides a constructor for creating an empty
 matrix with the required size. The application has the responsibility of calling
 the destructor to release the dynamic memory allocated to the matrix. The data-type
 has a central control error mechanism, providing operations for obtaining the last
 error occurred, for obtaining the correspondent message and for cleaning the error.
 The data-type has also operations to store and retrieve matrixes from text files.
 
*******************************************************************************/

#ifndef _MATRIX
#define _MATRIX

/***************** Defini��o do Tipo Ponteiro para uma Matriz *****************/

typedef struct matrix *PtMatrix;

/************************ Defini��o de C�digos de Erro ************************/

#define  OK           0  /* opera��o realizada com sucesso - operation with success */
#define  NO_MATRIX    1  /* a(s) matriz(es) n�o existe(m) - matrix(es) do not exist */
#define  NO_MEM       2  /* mem�ria esgotada - out of memory */
#define  NO_FILE      3  /* o ficheiro n�o existe - file does not exist */
#define  BAD_SIZE     4  /* dimens�o errada - wrong size */
#define  BAD_INDEX    5  /* elemento inexistente na matriz - element does not exist in the matrix */
#define  DIF_SIZE     6  /* matrizes com dimens�es diferentes - matrixes with different sizes */
#define  NO_CHAINED   7  /* matrizes n�o encadeadas - matrixes not chained */
#define  NULL_PTR     8  /* ponteiro nulo - null pointer */
#define  NO_SQUARE    9  /* matriz n�o quadrada - matrix not square */
#define  BAD_ROW     10  /* linha inexistente - line does not exist in the matrix */
#define  BAD_COLUMN  11  /* coluna inexistente - column does not exist in the matrix */

/*************************** Prot�tipos das Fun��es ***************************/

void MatrixClearError (void);
/*******************************************************************************
 Inicializa��o do erro. Error initialization.
*******************************************************************************/

int MatrixError (void);
/*******************************************************************************
 Devolve o c�digo do �ltimo erro ocorrido. Returning the error code.
*******************************************************************************/

char *MatrixErrorMessage (void);
/*******************************************************************************
 Devolve uma mensagem esclarecedora da causa do �ltimo erro ocorrido.
 Returning an error message.
*******************************************************************************/

PtMatrix MatrixCreate (unsigned int pnl, unsigned int pnc);
/*******************************************************************************
 Cria uma matriz nula, com pnl linhas e pnc colunas, para armazenar elementos
 reais. Devolve a refer�ncia da matriz criada ou NULL, caso n�o consiga criar
 a matriz. Valores de erro: OK ou NO_MEM.
 
 Creating the empty matrix with the required size. Returns a reference to the
 new matrix or NULL if there isn't enough memory. Error codes: OK or NO_MEM.
*******************************************************************************/

PtMatrix MatrixCreateArray (unsigned int pnl, unsigned int pnc, double *array);
/*******************************************************************************
 Cria uma matriz com pnl linhas e pnc colunas a partir de uma sequ�ncia 
 (com pnl x pnc) elementos que representa uma matriz. Devolve a refer�ncia da
 matriz criada ou NULL, caso n�o consiga criar a matriz.
 Valores de erro: OK, BAD_SIZE, NULL_PTR ou NO_MEM.
 
 Creating a new matrix from an array (with pnl x pnc) elements that represent a
 matrix. Returns a reference to the new matrix or NULL if there isn't enough memory.
 Error codes: OK, BAD_SIZE, NULL_PTR ou NO_MEM.
*******************************************************************************/

void MatrixDestroy (PtMatrix *pmatrix);
/*******************************************************************************
 Destr�i a matriz pmatrix, caso ela exista, e coloca a sua refer�ncia a NULL.
 Valores de erro: OK ou NO_MATRIX.
 
 Destroys the matrix and releases the memory. Error codes: OK or NO_MATRIX.
*******************************************************************************/

PtMatrix MatrixCopy (PtMatrix pmatrix);
/*******************************************************************************
 Copia a matriz pmatrix, caso ela exista. Devolve a refer�ncia da matriz criada ou 
 NULL, caso n�o consiga criar a matriz. Valores de erro: OK, NO_MATRIX ou NO_MEM.
 
 Copies the matrix pmatrix returning a new matrix or NULL if there isn't enough 
 memory. Error codes: OK, NO_MATRIX or NO_MEM.
*******************************************************************************/

void MatrixSize (PtMatrix pmatrix, unsigned int *pnl, unsigned int *pnc);
/*******************************************************************************
 Devolve a dimens�o da matriz pmatrix, caso ela exista. Valores de erro: OK, 
 NO_MATRIX ou NULL_PTR.
 
 Returning the size of the matrix pmatrix - number of lines in pnl and number of
 columns in pnc. Error codes: OK, NO_MATRIX ou NULL_PTR. 
*******************************************************************************/

void MatrixModifyElement (PtMatrix pmatrix, unsigned int pl, unsigned int pc, double pval);
/*******************************************************************************
 Armazena pval na linha pl e na coluna pc da matriz pmatrix. Valores de erro: OK, 
 NO_MATRIX ou BAD_INDEX.
 
 Storing the value pval in the line pl and in columns pc of the matrix pmatrix.
 Error codes: OK, NO_MATRIX or BAD_INDEX (in alternative BAD_ROW / BAD_COLUMN).
*******************************************************************************/

double MatrixObserveElement (PtMatrix pmatrix, unsigned int pl, unsigned int pc);
/*******************************************************************************
 Devolve o valor armazenado na linha pl e na coluna pc da matriz pmatrix.
 Valores de erro: OK, NO_MATRIX ou BAD_INDEX.
 
 Returning the value in the line pl and in columns pc of the matrix pmatrix.
 Error codes: OK, NO_MATRIX or BAD_INDEX (in alternative BAD_ROW / BAD_COLUMN).
*******************************************************************************/

PtMatrix MatrixTranspose (PtMatrix pmatrix);
/*******************************************************************************
 Calcula a matriz transposta da matriz pmatrix. Devolve a refer�ncia da matriz
 transposta ou NULL, caso n�o consiga fazer a opera��o. Valores de erro: OK, 
 NO_MATRIX ou NO_MEM.
 
 Creating the transpose matrix of matrix pmatrix. Returns a reference to the new
 matrix or NULL if there isn't enough memory. Error codes: OK, NO_MATRIX or NO_MEM.
*******************************************************************************/
 
PtMatrix MatrixAddition (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Soma as duas matrizes pmatrix1 e pmatrix2. Devolve a refer�ncia da matriz soma ou NULL,
 caso n�o consiga fazer a adi��o. Valores de erro: OK, NO_MATRIX, DIF_SIZE ou NO_MEM.
 
 Matrix addition returning a new matrix. Error codes: OK, NO_MATRIX, DIF_SIZE or NO_MEM.
*******************************************************************************/

PtMatrix MatrixSubtraction (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Subtrai as duas matrizes pmatrix1 e pmatrix2. Devolve a refer�ncia da matriz diferen�a
 ou NULL, caso n�o consiga fazer a subtrac��o. Valores de erro: OK, NO_MATRIX, 
 DIF_SIZE ou NO_MEM.
 
 Matrix subtraction returning a new matrix. Error codes: OK, NO_MATRIX, DIF_SIZE or NO_MEM.
*******************************************************************************/

PtMatrix MatrixMultiplication (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Multiplica as duas matrizes pmatrix1 e pmatrix2 usando o algoritmo directo. Devolve
 a refer�ncia da matriz produto ou NULL, caso n�o consiga fazer a multipli��o.
 Valores de erro: OK, NO_MATRIX, NO_CHAINED ou NO_MEM.

 Matrix multiplication returning a new matrix. Error codes: OK, NO_MATRIX, NO_CHAINED or NO_MEM.
*******************************************************************************/

PtMatrix MatrixMultByScalar (PtMatrix pmat, double pvalue);
/*******************************************************************************
 Multiplica a matriz pmatrix pelo escalar pvalue. Devolve a refer�ncia da matriz
 produto ou NULL, caso n�o consiga fazer a multipli��o.
 Valores de erro: OK, NO_MATRIX ou NO_MEM.
 
 Matrix multiplication by a scalar returning a new matrix. Error codes: OK, NO_MATRIX or NO_MEM.
*******************************************************************************/

double MatrixDeterminant (PtMatrix pmatrix);
/*******************************************************************************
 Calcula e devolve o determinante da matriz pmatrix, caso ela seja quadrada, usando 
 o algoritmo de elimina��o de Gauss. Valores de erro: OK, NO_MATRIX, NO_SQUARE ou NO_MEM.
 
 Calculating the determinante of the matrix pmatrix if and oly if it is square,
 using the Gauss algorithm. Error codes: OK, NO_MATRIX, NO_SQUARE or NO_MEM. 
*******************************************************************************/

int MatrixIsSquare (PtMatrix pmatrix);
/*******************************************************************************
 Determina se a matriz pmatrix � uma matriz quadrada. Devolve 1 em caso 
 afirmativo e 0 no caso contr�rio. Valores de erro: OK ou NO_MATRIX.
 
 Verifies if matrix is square. Returns 1 in affirmative case and 0 otherwise.
 Error codes: OK or NO_MATRIX.
*******************************************************************************/

int MatrixEquals (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Compara se as duas matrizes pmatrix1 e pmatrix2 s�o id�nticas. Devolve 1 em caso 
 afirmativo e 0 em caso contr�rio. Valores de erro: OK, NO_MATRIX ou DIF_SIZE.

 Verifies if two matrixes are equal (same size and all elements are equal).
 Returns 1 in affirmative case and 0 otherwise. Error codes: OK, NO_MATRIX or DIF_SIZE.
*******************************************************************************/

void MatrixExchangeRow (PtMatrix pmatrix, unsigned int pk, unsigned int pl);
/*******************************************************************************
 Altera a matriz pmatrix, permutando as linhas pk e pl, tendo em aten��o que as
 linhas devem ser referenciadas de 1 a NL. Valores de erro: OK, NO_MATRIX ou BAD_ROW.
 
 Change matrix by permuting lines pk and pl, considering that the lines are numbered
 from 1 to NL. Error codes: OK, NO_MATRIX or BAD_ROW.
*******************************************************************************/

void MatrixExchangeColumn (PtMatrix pmatrix, unsigned int pk, unsigned int pc);
/*******************************************************************************
 Altera a matriz pmatrix, permutando as colunas pk e pc, tendo em aten��o que as
 colunas devem ser referenciadas de 1 a NC. Valores de erro: OK, NO_MATRIX ou BAD_COLUMN.
 
 Change matrix by permuting columns pk and pl, considering that the columns are
 numbered from 1 to NC. Error codes: OK, NO_MATRIX or BAD_COLUMN.
*******************************************************************************/

void MatrixStoreFile (PtMatrix pmatrix, char *pfname);
/*******************************************************************************
 Armazena a matriz pmatrix, caso ela exista, no ficheiro pfname. O ficheiro tem na 
 primeira linha o n�mero de linhas e o n�mero de colunas da matriz, seguido das 
 linhas de elementos da matrix. Valores de erro: OK, NO_MATRIX ou NO_FILE.
 
 Storing matrix pmatrix in text file pfname. The first line of the file is the
 number of lines followed by the number of columns. The following lines are the
 elements separated by spaces. Error codes: OK, NO_MATRIX or NO_FILE.
*******************************************************************************/

PtMatrix MatrixCreateFile (char *pfname);
/*******************************************************************************
 Cria uma matriz a partir de informa��o lida do ficheiro pfname. Devolve a
 refer�ncia da matriz criada ou NULL, caso n�o consiga criar a matriz.
 Valores de erro: OK, NO_FILE, BAD_SIZE ou NO_MEM.
 
 Creating a new matrix from text file pfname. Returns a reference to the new matrix
 or NULL if there isn't enough memory. Error codes: OK, NO_FILE, BAD_SIZE or NO_MEM. 
*******************************************************************************/

#endif
