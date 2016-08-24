#include <stdio.h>
#include "schroder.h"

int main(void)
{
	/* variáveis */
	unsigned int i, res, resRec, resIte, contRec, contIte;
	
		
	printf("                                \t                    MULTIPLICAÇÕES                      \n");
	printf("      n              S(n)       \t   Função Recursiva           Função Iterativa          \n");

	for (i = 0; i <= 12; i++)
	{	
		resetMultRec();	/* reset das multiplicações da função recursiva */

		resRec = schroderRec(i);
		resIte = schroderIte(i);

		contRec = getMultRec();
		contIte = getMultIte();

		if(resRec != resIte)
			res = 0;

		else
			res = resRec;

		printf("  %-10u   %-17u\t   %-24u   %-24u  \n", i, res, contRec, contIte);
	}
	
	return 0;
}
