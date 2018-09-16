#ifndef _PILHA2_H
#define _PILHA2_H

typedef double elem2;

struct pilha2{
	elem2* vet; // vetor de elementos da pilha
	int topo; // topo da pilha
};
typedef struct pilha2 pilha_double;



pilha_double* cria_pilha_double(); // CRIA A PILHA E RETORNA UM PONTEIRO PARA A PILHA
void push_double(pilha_double* p, elem2 x); // EMPILHA UM DOUBLE NA PILHA
void pop_double(pilha_double* p, elem2* x); // DESEMPILHA
void libera_pilha_double(pilha_double* p); // LIBERA A PILHA CRIADA

#endif