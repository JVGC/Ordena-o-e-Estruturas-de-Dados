
#include <stdio.h>
#include <stdlib.h>
#include "insertion.h"

void insertionsort(int* vet, int n, int* c, int* m)
{
	int i, j, key;

	for(i = 1; i < n; i++)
	{
		j=i;
		*m += 1;
		key = vet[j];

		*c += 1;
		while(j > 0 && key < vet[j-1])
		{	
			*m += 1;
			*c += 1;
			vet[j] = vet[j-1];
			j--;
		}
		*m += 1;
		vet[j] = key;
	}


}