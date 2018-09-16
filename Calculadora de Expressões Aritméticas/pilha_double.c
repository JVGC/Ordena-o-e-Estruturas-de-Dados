#include <stdio.h>
#include <stdlib.h>
#include "pilha_double.h"
// INICIALIZA A PILHA


pilha_double* cria_pilha_double()
{
	pilha_double* p = (pilha_double*) malloc(sizeof(pilha_double));

	p->vet = (elem2*) malloc(sizeof(elem2)*100);

	p->topo = 0; // INICIA O VETOR EM 0;

	return p;

}

// LIBERA A PPILHA
void libera_pilha_double(pilha_double* p)
{
	free(p->vet);
	free(p);

}
// EMPILHA
void push_double(pilha_double* p, elem2 x)
{	
	p->topo += 1;
	p->vet[p->topo] = x;
}

// DESEMPILHA
void pop_double(pilha_double* p, elem2* x)
{
	*x = p->vet[p->topo];
	p->topo--;
}