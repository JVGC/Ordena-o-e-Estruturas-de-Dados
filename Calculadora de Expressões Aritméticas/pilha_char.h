#ifndef _PILHA_CHAR_H_
#define _PILHA_CHAR_H_

typedef char elem; 
typedef struct pilha pilha_t;


struct pilha{
	elem* vet; // vetor de elementos da pilha
	int topo; // topo da pilha
};


pilha_t* cria_pilha(); // CRIA A PILHA
void push(pilha_t* p, elem x); // EMPILHA
void pop(pilha_t* p, elem* x); // DESEMPILHA
void libera_pilha(pilha_t* p); // LIBERA A PILHA

#endif