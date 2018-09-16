#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "heap.h"

#define ROOT 0;

void heapsort(int* vet, int n, int* c, int* m)
{
	int i;

	build_max_heap(vet, n, c, m);
	for(i = n-1; i > 0; i--)
	{
		swap(vet, 0, i);
		(*m)+=3;
		max_heapify(vet, i, 0, c, m);
	}
}

void max_heapify(int* vet, int n, int position, int* c, int* m)
{
	int largestId, leftId, rightId;

	largestId = position;
	leftId = position*2+2;
	rightId = position*2+1;

	(*c)+=1;
	if(leftId < n && vet[leftId] > vet[largestId])
		largestId = leftId;
	
	(*c)+=1;
	if(rightId < n && vet[rightId] > vet[largestId])
		largestId = rightId;

	if(largestId != position)
	{
		(*m)+=3;
		swap(vet, largestId, position);
		max_heapify(vet, n, largestId, c, m);
	}

}

void build_max_heap(int* vet, int n, int* c, int* m)
{
	int i;
	for(i = n/2-1; i>=0; i--)
		max_heapify(vet, n, i, c, m);
}