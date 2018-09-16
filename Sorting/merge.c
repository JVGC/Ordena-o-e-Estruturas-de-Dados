#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "merge.h"
#include "utils.h"

void merge(int* vet, int start, int mid, int end, int* c, int* m)
{
	int i, j, k;
	int *left, *right;
	int nleft, nright;

	nleft = mid-start+2; // +2 PRO INT_MAX
	nright = end- mid +1; // +1 PRO INT_MAX

	left = (int*) malloc(sizeof(int)*nleft);
	right = (int*) malloc(sizeof(int)*nright);

	for(i = 0; i < nleft-1; i++)
	{
		(*m) += 1;
		left[i] = vet[i];
	}
	
	left[i] = INT_MAX;

	for(j = 0; j <nright-1; j++)
	{	
		(*m) += 1;
		right[j] = vet[j];
	}
	right[j] = INT_MAX;

	i = j = k = 0;

	for(k = start; k <= end; k++)
	{
		if(i < nleft && left[i] <= right[j])
		{
			(*c) += 1;
			(*m) += 1;
			vet[k] = left[i];
			i++;
		}else if(j < nright)
		{	
			(*m) += 1;
			vet[k] = right[j];
			j++;
		}else
		{
			(*c) += 1;
		}
	}

	free(right);
	free(left);
}

void mergesort(int* vet, int start, int end, int* c, int* m)
{
	if(start >= end)
		return ;
	int mid = (start+end)/2;

	mergesort(vet, start, mid, c, m);
	mergesort(vet, mid+1, end, c, m);
	merge(vet, start, mid, end, c, m);

}