#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"
#include "fila.h"

tree_t* cria_arvore()
{	
	tree_t* a = (tree_t*) malloc(sizeof(tree_t));

	a->root = NULL;


	return a;
}
void libera_arvore(tree_t* a)
{
	if(a->root == NULL)
	{
		free(a);
		return ;
	}
}

void in_ordem(NO_t* root)
{
	if(root == NULL)
		return ;
	
	in_ordem(root->left);
	
	printf("%d ", root->info);
	
	in_ordem(root->right);
}

void pos_ordem(NO_t* root)
{
	if(root == NULL)
		return ;

	pos_ordem(root->left);
	pos_ordem(root->right);
	
	printf("%d ", root->info);
}

void pre_ordem(NO_t* root)
{
	if(root == NULL)
		return ;
	printf("%d ", root->info);

	pre_ordem(root->left);
	pre_ordem(root->right);
}


NO_t* rotacao_EE(NO_t* desb)
{
	NO_t* aux = desb->right;
	desb->right = aux->left;
	aux->left = desb;
	
	return aux;
}

NO_t* rotacao_DD(NO_t* desb)
{
	NO_t* aux = desb->left;
	desb->left = aux->right;
	aux->right = desb;

	return aux;
}

NO_t* rotacao_DE(NO_t* desb)
{
	desb->right = rotacao_DD(desb->right);
	return rotacao_EE(desb);

}

NO_t* rotacao_ED(NO_t* desb)
{
	desb->left = rotacao_EE(desb->left);
	return rotacao_DD(desb);	
} 

NO_t* insere_AVL(NO_t* root, int x, int* flag)
{
	if(root != NULL)
	{
		if(x < root->info)
		{
			root->left = insere_AVL(root->left, x, flag);
			if(*flag)
			{
				switch(root->fb)
				{
					case -1:
						root->fb = 0;
						*flag = 0;
						break;
					case 0:
						root->fb = 1;
						break;
					case 1:
						if(root->left->fb == 1)
						{
							root = rotacao_DD(root);
							root->right->fb = 0;
							root->fb = 0;
							*flag = 0;
						}else
						{
							root = rotacao_ED(root);
							if(root->fb == 0)
							{
								root->left->fb = 0;
								root->right->fb = 0;
							}else if(root->fb == 1)
							{
								root->left->fb = 0;
								root->right->fb = -1;
								root->fb = 0;
							}else
							{
								root->left->fb = 1;
								root->right->fb = 0;
								root->fb = 0;
							}
							
						}
						*flag = 0;
						break;

				}
			}
		}else if (x > root->info)
		{
			root->right = insere_AVL(root->right, x, flag);
			if(*flag)
			{
				switch(root->fb)
				{
					case 1:
						root->fb = 0;
						*flag = 0;
						break;
					case 0:
						root->fb = -1;
						break;
					case -1:
						if(root->right->fb == -1)
						{
							root = rotacao_EE(root);
							root->left->fb = 0;
							root->fb = 0;
							*flag = 0;
						}else
						{
							root = rotacao_DE(root);
							if(root->fb == 0)
							{
								root->left->fb = 0;
								root->right->fb = 0;
							}else if(root->fb == 1)
							{
								root->left->fb = 0;
								root->right->fb = -1;
								root->fb = 0;
							}else
							{
								root->left->fb = 1;
								root->right->fb = 0;
								root->fb = 0;
							}
							
						}
						*flag = 0;
						break;
				}
			}

		}else{ 
			printf("Chave existente\n");
		}
	}else
	{
		root = (NO_t*) malloc(sizeof(NO_t));
		root->info = x;
		root->left = NULL;
		root->right = NULL;
		root->fb = 0;
		*flag = 1;
	}

	return root;
}

void insere2(tree_t* a, int n)
{
	int flag = 0;
	a->root = insere_AVL(a->root, n, &flag);

}

void largura(fila_t* f)
{
	while(f->inicio != NULL)
	{
		retira(f);
	}	

}	

int busca(NO_t* root, int x)
{
	if(root == NULL)
		return -1;

	if(x > root->info )
		busca(root->right, x);
	else if(x < root->info )
		busca(root->left, x);
	else
		return 1;

}

NO_t* bal_left(NO_t* p, int* flag)
{
	NO_t* f_right;
	int fb_right;

	switch(p->fb)
	{
		case 1:
			p->fb = 0; // 0, 1 ou -1?
			break;
		case 0:
			p->fb  = -1;
			*flag = 0;
			break;
		case -1:
			f_right = p->right;
			fb_right = f_right->fb;
			if(fb_right <= 0)
			{
				f_right = rotacao_EE(p);
				if(fb_right == 0)
				{
					p->fb = -1;
					f_right->fb = 1;
					*flag = 0;
				}else{
					p->fb = 0;
					f_right->fb = 0;
				}
				p = f_right;
			}else
			{
				p = rotacao_DE(p);
				if(p->fb == 1)
				{
					p->left->fb = 0;
					p->right->fb = -1;
				}else if(p->fb == -1)
				{
					p->left->fb = 1;
					p->right->fb = 0;

				}else
				{
					p->left->fb = 0;
					p->right->fb = 0;
				}
				p->fb = 0;
			}

	}
	return p;
}

NO_t* bal_right(NO_t* p, int* flag)
{
	NO_t* f_left;
	int fb_left;

	switch(p->fb)
	{
		case -1:
			p->fb = 0; // 0, 1 ou -1?
			break;
		case 0:
			p->fb = 1;
			*flag = 0;
			break;
		case 1:
		f_left = p->left;
		fb_left = f_left->fb;
		if(fb_left >= 0)
		{
			f_left = rotacao_DD(p);
			if(fb_left == 0)
			{
				p->fb = 1;
				f_left->fb = -1;
				*flag = 0;
			}else{
				p->fb = 0;
				f_left->fb = 0;
			}
			p = f_left;
		}else
		{
			p = rotacao_ED(p);
			if(p->fb == 1)
			{
				p->left->fb = 0;
				p->right->fb = -1;
			}else if(p->fb == -1)
			{
				p->left->fb = 1;
				p->right->fb = 0;

			}else
			{
				p->left->fb = 0;
				p->right->fb = 0;
			}
			p->fb = 0;
		}

	}
	return p ;
}

NO_t* procura_Min(NO_t* p, NO_t* suc, int* flag)
{
	NO_t* removido;
	if(suc->left != NULL)
	{
		suc->left = procura_Min(p, suc->left, flag);
		if(*flag)
		{
			suc = bal_left(suc, flag);
		}
	}else
	{
		p->info = suc->info;
		removido = suc;
		suc = suc->right;
		*flag = 1;
		free(removido);

	}
	return suc;
}

NO_t* remove_AVL(NO_t* root, int x, int* flag)
{
	NO_t* aux;
	if(root == NULL)
	{
		printf("Nao encontrado");
	}	
	else
	{
		if(root->info > x)
		{
			root->left = remove_AVL(root->left, x, flag);
			if(*flag)
				root = bal_left(root,flag);
		
		}else if(root->info < x)
		{
			root->right = remove_AVL(root->right, x, flag);
			if(*flag)
				root = bal_right(root, flag);
		}else{ // encontrou o elemento
			printf("%d",root->info);
			if(root->right == NULL)
			{
				aux = root;
				root = root->left;
				free(aux);
				*flag = 1;
			}else if (root->left == NULL)
			{
				aux = root;
				root = root->right;
				free(aux);
				*flag = 1;
			}
			else // BUSCA O ELEMENTO MAIS A DIREITA DO NO ESQUERDA
			{
				root->right = procura_Min(root, root->right, flag);
				if(*flag)
					root = bal_right(root, flag);
			}
		}
	
	}	
	return root;
}




void remover(tree_t* a, int n)
{
	int flag = 0;
	a->root = remove_AVL(a->root, n, &flag);
}

