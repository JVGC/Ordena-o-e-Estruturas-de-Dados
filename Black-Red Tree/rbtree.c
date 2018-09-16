#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

// ALOCA MEMORIA PARA A ARVORE
tree_t* cria_arvore()
{
	tree_t* t = (tree_t*) malloc(sizeof(tree_t));
	t->root = NULL;

	return t;
}
// LIBERA CADA UM DOS NOS DA ARVORE
void libera_arvore(NO_t* root)
{
	if(root != NULL)
	{
		libera_arvore(root->left);
		libera_arvore(root->right);
		free(root);
	}
}
// LIBERA TODA A MEMORIA DA ARVORE
void destroi_arvore(tree_t* a)
{
	libera_arvore(a->root);
	free(a);
}



// ROTACIONA A ARVORE PARA A ESQUERDA A PARTIR NO DO DESBALANCEADO
void rotacao_EE(tree_t* a, NO_t* desb)
{
	NO_t* aux = desb->right;
	desb->right = aux->left;
	
	if(aux->left != NULL)
		aux->left->pai = desb;
	
	aux->pai = desb->pai;
	
	if(desb->pai == NULL)
		a->root = aux;
	else if(desb == desb->pai->left)
		desb->pai->left = aux;
	else if(desb == desb->pai->right) 
		desb->pai->right = aux;

	aux->left = desb;
	desb->pai = aux;
	
}
// ROTACIONA A ARVORE PARA A DIREITA A PARTIR NO DO DESBALANCEADO
void rotacao_DD(tree_t* a, NO_t* desb)
{
	NO_t* aux = desb->left;
	desb->left = aux->right;
	if(aux->right != NULL)
		aux->right->pai = desb;
	aux->pai = desb->pai;
	if(desb->pai == NULL)
		a->root = aux;
	else if(desb == desb->pai->right)
		desb->pai->right = aux;
	else if(desb == desb->pai->left) 
		desb->pai->left = aux;

	aux->right = desb;
	desb->pai = aux;

}

void balanceamento_RB(tree_t* a, NO_t* root)
{
	NO_t* uncle; // NO PARA O TIO
	// ENQUANTO EU NAO ESIVER NA RAIZ, E HAVER DOIS NOS VERMELHOS SEGUIDOS
	while(root->pai != NULL && root->pai->color == RED)
	{
		
		if(root->pai == root->pai->pai->right) // PAI DO NO EH O FILHO DIREITO
		{
			uncle = root->pai->pai->left; // O TIO EH O FILHO ESQUERDO
			// SE O TIO EXISTIR E FOR VERMELHO
			if(uncle != NULL && uncle->color == RED)
			{
				// TROCA AS CORES DO AVO, DO PAI E DO TIO;
				uncle->color = BLACK;
				uncle->pai->color = RED;
				root->pai->color = BLACK;
				
				root = uncle->pai; // MOVE O ROOT PARA O AVÔ
			
			}else // SE NAO EH VERMELHO, ENTAO O TIO EH PRETO
			{	// SE O NO EH FILHO ESQUERDO, COMO O PAI EH FILHO DIREITO
				// HA NECESSIDADE DE HAVER UMA ROTACAO 'DE'
				// SE NAO, A ROTACAO EH SIMPLES PARA A ESQUERDA
				if(root == root->pai->left) 
				{
					root = root->pai; // SOBE O NO PARA O PAI, E ROTACIONA PARA A DIREITA
					rotacao_DD(a, root);
				}
				// TROCA A COR DO PAI E DO AVO DO NO, E ROTACIONA PARA A ESQUERDA
				root->pai->color = BLACK;
				root->pai->pai->color = RED;
				rotacao_EE(a, root->pai->pai);
				
				
			}
		}else if(root->pai == root->pai->pai->left) // PAI DO NO EH O FILHO ESQUERDO
		{
			uncle = root->pai->pai->right;// O TIO EH O FILHO ESQUERDO
			
			// SE O TIO EXISTIR E FOR VERMELHO
			if(uncle != NULL  && uncle->color == RED)
			{
				// TROCA AS CORES DO AVO, DO PAI E DO TIO;
				uncle->color = BLACK;
				uncle->pai->color = RED;
				root->pai->color = BLACK;
				
				root = uncle->pai; // MOVE O ROOT PARA O AVO
			
			}else
			{
				// SE O NO EH FILHO DIREITO, COMO O PAI EH FILHO ESQUERDO
				// HA NECESSIDADE DE HAVER UMA ROTACAO 'ED'
				// SE NAO, A ROTACAO EH SIMPLES PARA A ESQUERDA
				if(root == root->pai->right) // SE O NO EH FILHO DIREITO
				{
					root = root->pai;
					rotacao_EE(a, root);
				}
				// TROCA A COR DO PAI E DO AVO DO NO, E ROTACIONA PARA A DIREITA
				root->pai->color = BLACK;
				root->pai->pai->color = RED;
				rotacao_DD(a, root->pai->pai);
				
				
			}
			
		}
	}
	// COLOCO A RAIZ PARA PRETO DE NOVO,
	// PARA CASO ELA TENHA SIDO ALTERADA
	a->root->color= BLACK;

	// COM ISSO, TODAS AS REGRAS DA ARVORE RUBRO NEGRA FORAM MANTIDAS
	// E A ARVORE FICA BALANCEADA
}


// INSERE n NA ARVORE a
void inserir(tree_t* a, int n)
{
	// DOIS NOS AUXILIARES ONDE aux COMECA NA RAIZ DA ARVORE
	NO_t* aux = a->root;
	NO_t* ant;
	// SE A RAIZ FOR NULA, EU ALOCO MEMORIA, CRIO O NO, E RETORNO
	// A RAIZ SEMPRE EH PRETA
	if(aux == NULL)
	{
		a->root = (NO_t*) malloc(sizeof(NO_t));
		a->root->info = n;
		a->root->color = BLACK;
		a->root->left = NULL;
		a->root->right = NULL;
		a->root->pai = NULL;
		return ;
	}
	// SE A RAIZ JA ESTIVER PREENCHIDA, ENTRO NO WHILE
	while(aux != NULL)
	{
		ant = aux; // ANT GUARDA O NO ATUAL PARA SABER DEPOIS QUEM EH O PAI
		// SE n FOR MAIOR QUE O NO, VAI PARA A DIREITA, SENAO, VAI PARA A ESQUERDA
		if(n > aux->info)
		{
			aux = aux->right; 
		}else if(n < aux->info)
		{
			aux = aux->left; 
		}
	
	}
	// ALOCO MEMORIA NO AUX
	// TODO NOVO NO CRIADO, COM EXCECAO DA RAIZ, EH VERMELHO
	// LIGO O NO ant COM aux
	aux = (NO_t*) malloc(sizeof(NO_t));
	aux->info = n;
	aux->color = RED;
	aux->left = NULL;
	aux->right = NULL;
	aux->pai = ant;
	if(n > ant->info)
		ant->right = aux;
	else
		ant->left = aux;
	// AGORA CHAMO PARA BALANCEAR A ARVORE A PARTIR DO NO QUE ALOQUEI	
	balanceamento_RB(a, aux);


}
// IMPRIME A ARVORE IN-ORDEM
void in_ordem(NO_t* root)
{
	if(root == NULL)
		return ;
	
	in_ordem(root->left);
	
	printf("%d ", root->info);
	
	in_ordem(root->right);
}
// IMPRIME A ARVORE POS-ORDEM
void pos_ordem(NO_t* root)
{
	if(root == NULL)
		return ;

	pos_ordem(root->left);
	pos_ordem(root->right);
	
	printf("%d ", root->info);
}
// IMPRIME A ARVORE PRE-ORDEM
void pre_ordem(NO_t* root)
{
	if(root == NULL)
		return ;
	printf("%d ", root->info);

	pre_ordem(root->left);
	pre_ordem(root->right);
}
// RETORNA O MAIOR VALOR DA ARVORE
int Maximo(NO_t* root)
{
	if(root != NULL)
	{
		if(root->right != NULL)
			return Maximo(root->right);
		else 
			return root->info;
	}
}
// RETORNA O MENOR VALOR DA ARVORE
int Minimo(NO_t* root)
{
	if(root != NULL)
	{
		if(root->left != NULL)
			return Minimo(root->left);
		else 
			return root->info;
	}

}
// BUSCA O NO NA ARVORE
NO_t* busca(NO_t* root, int n)
{
	if(root == NULL)
		return NULL;

	if(n > root->info)
		return busca(root->right, n);
	else if(n < root->info)
		return busca(root->left, n);
	else
		return root;
}
// O PREDECESSOR RETORNA O MENOR NUMERO MAIS PROXIMO DE n
void predecessor(NO_t* root, int n, int* FLAG)
{
	if(root == NULL)
		return ;
	// CHAMA O NO A DIREITA
	predecessor(root->right, n, FLAG);
	// SE O NO EM QUE ESTOU FOR IGUAL A n
	// MUDO A FLAG PARA 1
	if(root->info == n)
		*FLAG = 1; // ALTERO A FLAG
	// SE A FLAG FOE 1, E O NO EM QUE ESTOU FOR MENOR QUE n
	// PRINTO O NO, SETO A FLAG PARA 0 E RETORNO PARA AS CHAMADAS ANTERIORES
	if(*FLAG == 1 && root->info < n)
	{
		printf("%d\n", root->info);
		*FLAG = 0;
		return ;
	}
	
	// CHAMO O NO A ESQUERDA
	predecessor(root->left, n, FLAG);

}
// O PREDECESSOR RETORNA O MAIOR NUMERO MAIS PROXIMO DE n
void sucessor(NO_t* root, int n, int* FLAG)
{
	if(root == NULL)
		return ;
	// CHAMA O NO A ESQUERDA
	sucessor(root->left, n, FLAG);
	// SE A FLAG FOE 1, E O NO EM QUE ESTOU FOR MENOR QUE n
	// PRINTO O NO, SETO A FLAG PARA 0 E RETORNO PARA AS CHAMADAS ANTERIORES
	if(*FLAG == 1 && root->info > n)
	{
		printf("%d\n", root->info);
		*FLAG = 0;
		return ;
	}

	// SE O NO EM QUE ESTOU FOR IGUAL A n
	// MUDO A FLAG PARA 1
	if(root->info == n)
		*FLAG = 1;

	

	// CHAMO O NO A DIREITA
	sucessor(root->right, n, FLAG);

}