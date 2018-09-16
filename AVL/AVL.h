#ifndef _TREE_H_

#define _TREE_H_

struct NO{
	int info;
	struct NO* left, *right;
	int fb;
};

typedef struct NO NO_t;

struct tree{
	NO_t* root;

};

typedef struct tree tree_t;

tree_t* cria_arvore();
void insere2();
void remover();
int busca();
void pre_ordem();
void pos_ordem();
void in_ordem();
void largura();
void libera_arvore();


#endif