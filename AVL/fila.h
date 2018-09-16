#ifndef _FILA_H_
#define _FILA_H_

#include "AVL.h"

typedef struct fila fila_t;


typedef struct no{
	struct no* prox;
	NO_t info;
}no_t;


struct fila{
	no_t* inicio;
	no_t* fim;
	int tam;
};

typedef NO_t elem;

fila_t* cria_fila();
void insere(fila_t* l, elem x);
void retira(fila_t* l);
void libera_fila(fila_t* l);



#endif
