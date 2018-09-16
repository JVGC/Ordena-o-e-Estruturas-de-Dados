#include <stdio.h>
#include <stdlib.h>
#include "pilha_char.h"
// INICIALIZA A PILHA

pilha_t* cria_pilha()
{
	pilha_t* p = (pilha_t*) malloc(sizeof(pilha_t));

	if(p!= NULL)
	{
		p->vet = (elem*) malloc(sizeof(elem)*100);

		p->topo = 0; // INICIA O VETOR EM 0; 
	}
	return p;

}

// LIBERA A PPILHA
void libera_pilha(pilha_t* p)
{
	free(p->vet);
	free(p);

}
// EMPILHA
void push(pilha_t* p, elem x)
{	if(p != NULL)
	{	
		p->topo += 1; // AUMENTA O TOPO EM 1, E EMPILHA
		p->vet[p->topo] = x; 
	}
}

// DESEMPILHA e RETORNA O VALOR ENCONTRADO NO TOPO DA PILHA
void pop(pilha_t* p, elem* x)
{
	if(p != NULL)
	{
		*x = p->vet[p->topo];
		p->topo--;
	}
}