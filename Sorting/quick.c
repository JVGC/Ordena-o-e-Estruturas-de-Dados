#include <stdio.h>
#include <stdlib.h>
#include "quick.h"
#include "utils.h"

// int partition(int* vet, int left, int right, int* c, int* m)
// {
// 	int j, i, pivot;
// 	pivot = (int)(left+right)/2;

// 	for(j = left, i = left; j<= right; j++)
// 	{
// 		*c+=1;
// 		if(vet[j] < vet[pivot])
// 		{
// 			*m +=3;
// 			swap(vet, j, i);
			
// 		}
// 	}
// 	*m+=3;
// 	swap(vet, i, pivot);
// 	return i;
// }

// void quicksort(int* vet, int start, int end, int* c, int* m)
// {
// 	int r;

// 	if(start < end)
// 	{
// 		r = partition(vet, start, end, c, m);
// 		quicksort(vet, start, r-1, c, m);
// 		quicksort(vet, r+1, end, c, m);
// 	}
// }

void quicksort(int* vet, int start, int end, int* c, int* m)
{
	int pivot = end-1;


	if(start >= end)
		return ;

		int i = start;
		int j = end-2;

		while(i < j)
		{
			*c+=2;
			while(vet[i] < vet[pivot])
			{ 
				*c+=1;
				i++;
			}
			while(j >= start && vet[j] > vet[pivot]) 
			{ 
				*c+=1; 
				j--;
			}
			if(i < j)
			{	
				*m+=3;
				swap(vet, i, j);
			}
		}

		*m+=3;
		swap(vet, i, pivot);
		pivot = i;
		quicksort(vet, start, pivot-1, c, m);
		quicksort(vet, pivot+1, end, c , m);
	
}