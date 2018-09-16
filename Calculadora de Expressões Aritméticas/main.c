#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RPN.h"

int main()
{
	int i, j;
	char exp[100]; // EXPRESSÃO NA FORMA CONVENCIONAL
	RPN_t* RPN; // PONTEIRO PARA A NOTAÇÃO POLONESA REVERSA
	double resultado;
	while(1)
	{	
		fgets(exp, 100, stdin); // LE A EXPRESSÃO
		if(Verifica_Parenteses(exp) == FAIL) // SE OS PARENTESES NÃO ESTIVEREM CERTOS
			printf("Expressao incorreta\n");
		else // SE ESTIVER TUDO CERTO
		{	
			RPN = ConToRPN(exp); // CONVERTE PARA RPN
			resolve_notacao(RPN); // E RESOLVE A NOTAÇÃO, JÁ PRINTANDO O SEU RESULTADOS
		}
		int tam = strlen(exp); 
		if(exp[tam-1] == ',')// SE NO FINAL DA EXPRESSÃO HOUVER UMA ',', ENTÃO FOI A ULTIMA EXPRESSÃO A SER LIDA
			break;
	}
	free(RPN->notacao);
	free(RPN);
	return 0;
}