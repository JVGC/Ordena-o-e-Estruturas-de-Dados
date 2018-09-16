#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#define BLACK 0
#define RED 1

// NO COM PONTEIRO PARA ESQUERDA, DIREITA E PAI
// E COM A INFORMACAO E A COR DO NO
typedef struct no
{
	struct no *left, *right, *pai;
	int info;
	char color;
}NO_t;



typedef struct {
	NO_t* root;

}tree_t;

tree_t* cria_arvore();
void inserir(tree_t* a, int n); // INSERE n NA ARVORE a
void destroi_arvore(tree_t* a); // DESALOCA A ARVORE a
void in_ordem(NO_t* root); // IMPRIME IN-ORDEM OS NOS DA ARVORE
void pos_ordem(NO_t* root);// IMPRIME POS-ORDEM OS NOS DA ARVORE
void pre_ordem(NO_t* root); // IMPRIME PRE-ORDEM OS NOS DA ARVORE
int Maximo(NO_t* root); // RETORNA O MAIOR VALOR DA ARVORE
int Minimo(NO_t* root); // RETORNA O MENOR VALOR DA ARVORE
void sucessor(NO_t* root, int n, int* FLAG); // RETORNA O SUCESSOR DE n
void predecessor(NO_t* root, int n, int* FLAG); // RETORNA O PREDECESSOR DE n
NO_t* busca(NO_t* root, int n); // PROCURA n NA ARVORE - RETORNA NULL PARA ERRO 

#endif