#include <stdio.h>
#include <stdlib.h>


void swap(int* vet, int p1, int p2)
{
	int aux =  vet[p1];
	vet[p1] =  vet[p2];
	vet[p2] =  aux;
}