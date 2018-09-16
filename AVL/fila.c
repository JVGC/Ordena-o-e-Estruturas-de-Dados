#include <stdio.h>
#include <stdlib.h>
#include "fila.h"



fila_t* cria_fila()
{
	fila_t* l = (fila_t*) malloc(sizeof(fila_t));
	l->inicio = NULL;
	l->fim = NULL;
	l->tam =0;

	return l;
}

void insere(fila_t* l, elem x)
{
	no_t* p = (no_t*) malloc(sizeof(no_t));
	p->info = x;
	p->prox = NULL;
	if(l->fim != NULL)
		l->fim->prox = p;
	l->fim = p;

	if(l->inicio == NULL)
	{
		l->inicio = p;
	}
	l->tam++;
}

void retira(fila_t* l)
{
	no_t* aux;
	aux = l->inicio;
	if(aux->info.left != NULL)
		insere(l, (*aux->info.left));
	if(aux->info.right != NULL)
		insere(l, (*aux->info.right));
	printf("%d ", aux->info.info);
	l->inicio = l->inicio->prox;
	free(aux);
	l->tam--;
}

void libera_fila(fila_t* l)
{
	no_t* p;
	while(l->inicio != NULL)
	{
		p = l->inicio;
		l->inicio = l->inicio->prox;
		free(p);
	}
	free(l);
}