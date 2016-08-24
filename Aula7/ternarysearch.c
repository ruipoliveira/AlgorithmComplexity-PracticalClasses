/*******************************************************************************

 Algoritmos de pesquisa ternária (quatro versões repetitivas).

 Autor : António Manuel Adrego da Rocha    Data : Março de 2014

*******************************************************************************/
# include <stdio.h>
# include <math.h>



static int comp; 
int TernarySearchV1 (int[], int, int); 
int TernarySearchV2 (int[], int, int); 
int TernarySearchV3 (int[], int, int); 
int TernarySearchV4 (int[], int, int); 


int main(int argc, char const *argv[]){
int k, i, n;

	printf("Valor de k: ");
	scanf("%d", &k);

	n = pow(3,k); 

	n = n*2 - 1;

	printf("N = %d\n", n);
	int array[n];

	for(i = 0; i < n; i++){
		array[i] = i*2;
	}

	int value;
	printf("Valor a pesquisar: ");
	scanf("%d", &value);

	if(TernarySearchV1(array, n, value) >= 0)
		printf("[V1]Valor encontrado em %d comparacoes \n", comp);

	else
		printf("[V1]Valor nao encontrado em %d comparacoes\n", comp);

	
	if(TernarySearchV3(array, n, value) >= 0)
		printf("[V3]Valor encontrado em %d comparacoes\n", comp);
	else
		printf("[V3]Valor nao encontrado em %d comparacoes\n", comp);

	
	if(TernarySearchV4(array, n, value) >= 0)
		printf("[V4]Valor encontrado em %d comparacoes\n", comp);
	else
		printf("[V4]Valor nao encontrado em %d comparacoes\n", comp);
	
	return 0;
}



int TernarySearchV1 (int array[], int n, int value)
{
    int min, max, nelem, fpivot, spivot;
    comp = 0;
	min = 0;
	max = n-1;

	while (min <= max)
	{
		nelem = max - min + 1;
		if (nelem % 3 == 0) 
		{
			fpivot = min + (nelem / 3) - 1;
			spivot = min + (2 * nelem / 3) - 1;
		}
		else
		{
			fpivot = min + (nelem / 3);
			spivot = min + (2 * nelem / 3);
		}
		
		if (array[fpivot] == value){
			comp++;
			return fpivot;
		}

		else if (array[fpivot] > value){
			max = fpivot - 1;
			comp +=2;
		}
			
		else if (array[spivot] == value){
			comp +=3;
			return spivot;
		} 
		
		else if (array[spivot] > value)
		{
			min = fpivot + 1; 
			max = spivot - 1;
			comp +=4;
		}
		else {
			min = spivot + 1;
			comp +=4;
		}
			
	}

	return -1;
}


int TernarySearchV2 (int array[], int n, int value)
{
    int min, max, nelem, fpivot, spivot;
    comp = 0;
	min = 0;
	max = n-1;

	while (min < max)
	{
		nelem = max - min + 1;
		fpivot = min + (nelem / 3);
		spivot = min + (2 * nelem / 3);

		if (array[fpivot] > value){
			max = fpivot - 1;
			comp++;
		} 
			
		else if (array[spivot] > value)
		{
			min = fpivot;
			max = spivot - 1;
			comp +=2;
		}
				
		else{
			min = spivot;
			comp +=2;
		} 
			
	}
	comp++;
	if (array[min] == value) 
		return min;
	else 
		return -1;
}

int TernarySearchV3 (int array[], int n, int value)
{
    int min, max, nelem, fpivot, spivot;
    comp = 0;
	min = 0;
	max = n-1;

	while (min <= max)
	{
		nelem = max - min + 1;
		if (nelem % 3 == 0) 
		{
			fpivot = min + (nelem / 3) - 1;
			spivot = min + (2 * nelem / 3) - 1;
		}
		else
		{
			fpivot = min + (nelem / 3);
			spivot = min + (2 * nelem / 3);
		}

		if (array[fpivot] == value){
			comp++;
			return fpivot;
		} 
		
		else if (array[fpivot] > value) {
			max = fpivot - 1;
			comp +=2;
		}
				
		else
		{
			comp +=3;
			if (array[spivot] > value)
			{
				min = fpivot + 1; max = spivot - 1;
			}
			else
			{
				comp++;
				if (array[spivot]  == value) 
					return spivot;
				else 
					min = spivot + 1;
			}
		}
	}

	return -1;
}

int TernarySearchV4 (int array[], int n, int value)
{
    int min, max, nelem, fpivot, spivot;
    comp = 0;
	min = 0;
	max = n-1;

	while (min <= max)
	{
		nelem = max - min + 1;
		if (nelem % 3 == 0) 
		{
			fpivot = min + (nelem / 3) - 1;
			spivot = min + (2 * nelem / 3) - 1;
		}
		else
		{
			fpivot = min + (nelem / 3);
			spivot = min + (2 * nelem / 3);
		}
		comp++;
		if (array[fpivot] >= value)
		{
			comp++;
			if (array[fpivot] == value) 
				return fpivot;
			
			max = fpivot - 1;
		}
		else
		{
			comp++;
			if (array[spivot] >= value)
			{
				comp++;
				if (array[spivot] == value) 
					return spivot;
				
				min = fpivot + 1; 
				max = spivot - 1;
			}
			else 
				min = spivot + 1;
		}
	}

	return -1;
}