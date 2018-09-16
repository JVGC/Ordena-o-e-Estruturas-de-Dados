#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

int main()
{
	int nOP, n, i; // NUMERO DE OPERACOES, NUMERO, E VARIAVEL AUXILIAR
	int OP, FLAG =0; // OPERACAO, E A FLAG

	tree_t* a = cria_arvore(); // CRIO A ARVORE
	// LEIO O NUMERO DE OPERACOES
	scanf("%d", &nOP);

	for(i = 0; i < nOP; i++)
	{
		// A CADA PASSAGEM, LEIO A OPERACAO
		scanf("%d", &OP);
		// SE OP == 1, INSIRO NA ARVORE
		if(OP == 1)
		{
			scanf("%d", &n);
			inserir(a, n);

		}else if(OP == 2) // RETORNO O SUCESSOR DO NUMERO
		{
			scanf("%d", &n);
			// SE O NUMERO FOR O MAIOR DA ARVORE, NAO HA SUCESSOR
			if(n == Maximo(a->root))
				printf("erro\n");
			else
				sucessor(a->root, n, &FLAG);
		}else if(OP == 3) // RETORNO O PREDECESSOR DO NUMERO
		{
			scanf("%d", &n);
			// SE O NUMERO FOR O MENOR DA ARVORE, NAO HA PREDECESSOR
			if(n == Minimo(a->root))
				printf("erro\n");
			else
				predecessor(a->root, n, &FLAG);
		}else if(OP == 4) // RETORNO O MAIOR NUMERO DA ARVORE
		{
			n = Maximo(a->root);
			printf("%d\n", n);
		}else if(OP == 5) // RETORNO O MENOR NUMERO DA ARVORE
		{
			n = Minimo(a->root);
			printf("%d\n", n);
		}else if(OP == 6) // IMPRIMO EM PRE ORDEM
		{
			pre_ordem(a->root);
			printf("\n");
		}else if(OP == 7) // IMPRIMO EM IN ORDEM
		{
			in_ordem(a->root);
			printf("\n");
		}else if(OP == 8) // IMPRIMO EM POS ORDEM
		{
			pos_ordem(a->root);
			printf("\n");
		}
	}

	destroi_arvore(a); // LIBERO A MEMORIA ALOCADA NA ARVORE

	return 0;

}