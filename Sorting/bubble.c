#include <stdio.h>
#include <stdlib.h>
#include "bubble.h"
#include "utils.h"



void bubblesort(int* vet, int n, int* c, int* m)
{

	int i, j;

	for(i=0; i<n; i++)
	{
		for(j = 0; j < i; j++)
		{	
			*c += 1;
			if(vet[j] > vet[j+1])
			{
				*m += 3; 
				swap(vet, j, j+1);
			}
		}
	}

}

