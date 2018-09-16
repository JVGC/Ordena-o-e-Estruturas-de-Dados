#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"
#include "fila.h"

int main(int argc, char const *argv[])
{
	char OP;
	int n, t;
	NO_t* p;
	tree_t* ABB = cria_arvore();
	fila_t* f;
	do{
		scanf("%c", &OP);
		if(OP == 'I')
		{	
			scanf("%d", &n);
			insere2(ABB, n);
				
		}
		else if(OP == 'Y')
		{
			printf("InOrdem: ");
			in_ordem(ABB->root);
			printf("\n");
			printf("PreOrdem: ");
			pre_ordem(ABB->root);
			printf("\n");
			printf("PosOrdem: ");
			pos_ordem(ABB->root);
			printf("\n");
			printf("Largura: ");
			f = cria_fila();
			insere(f, (*ABB->root));
			largura(f);
			libera_fila(f);
		}
		else if(OP == 'N')
		{	
			printf("InOrdem: ");
			in_ordem(ABB->root);
		}
		else if(OP == 'E')
		{
			printf("PreOrdem: ");
			pre_ordem(ABB->root);
		}
		else if(OP == 'O')
		{
			printf("PosOrdem: ");
			pos_ordem(ABB->root);
		}else if(OP == 'L')
		{
			f = cria_fila();
			insere(f, (*ABB->root));
			printf("Largura: ");
			largura(f);
			libera_fila(f);
		}else if(OP == 'B')
		{
			scanf("%d", &n);
			t = busca(ABB->root, n);
			if(t == -1)
				printf("Nao encontrado");
			else
				printf("Encontrado");
		}
		else if(OP == 'D')
		{
			scanf("%d", &n);
			remover(ABB, n);
		}

		if(OP != 'I' && OP != 'X')
			printf("\n");
		getchar();
	
	}while(OP != 'X');


	return 0;
}
