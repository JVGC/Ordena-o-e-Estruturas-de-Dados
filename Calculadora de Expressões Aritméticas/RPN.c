#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha_char.h"
#include "pilha_double.h"
#include "RPN.h"






// FUNÇÃO AUXILIAR PARA CRIAR A STRUCT
RPN_t* cria_notacao()
{
	RPN_t* RPN = (RPN_t*) malloc(sizeof(RPN_t));
	RPN->notacao = (double*) malloc(sizeof(double)*50);
	RPN->tam = 0;
	
	return RPN;
}

int Verifica_Parenteses(char* exp)
{
	pilha_t* parenteses = cria_pilha(); // CRIA UMA PILHA PARA AUXILIAR NA VERIFICAÇÃO DOS PARENTESES

	int tam = strlen(exp);
	int i;
	char c;
	for(i = 0; i < tam; i++)
	{
		// SE HOUVER UMA ABERTURA DE PARENTESES, EMPILHA ELE
		if(exp[i] == '(')
			push(parenteses, exp[i]);
		// SE HOUVER UM FECHAMENTO DE PARENTESES 
		if(exp[i] == ')')
		{	// SE NÃO HOUVER NADA NA PILHA, QUER DIZER QUE HOUVE UM FECHAMENTO MAS SEM ABERTURA, ENTÃO RETORNA ERRO
			if(parenteses->topo <= 0)
				return FAIL;
			pop(parenteses, &c);// SE TA TUDO CERTO, DESEMPILHA A PILHA
		}
	}
	// SE NO FINAL DA EXPRESSÃO, HOUVER ALGO NA PILHA, QUER DIZER QUE HOUVER UMA ABERTURA SEM FECHAMENTO, ENTÃO RETORNA ERRO
	if(parenteses->topo > 0)
	{
		libera_pilha(parenteses);	
		return -1;
	}
	libera_pilha(parenteses);
	return SUCESS;
}

RPN_t* ConToRPN(char* exp) // Convencional to RPN(NOTAÇÃO POLONESA REVERSA)
{
	pilha_t* operadores = cria_pilha(); // PILHA PARA AUXILIAR NA HORA DE PRIORIZAR OS OPERADORES
	RPN_t* RPN = cria_notacao();
	
	int i;

	char aux; // VARIAVEL AUXILIAR
	char aux2[10]; // VETOR AUXILIAR PARA TRASNFORMAR NÚMEROS QUE ESTÃO EM CHAR PARA FLOAT/DOUBLE
	int k = 0;


	
	// FAZ ESSE FOR ENQUANTO NÃO CHEGAR NO FINAL DA EXPRESSÃO(PERCORRENDO A EXPRESSÃO)
	for(i = 0; exp[i] != ';'; i++)
	{ 
		// SE FOR + OU -(TEM A MESMA PRIORIDADE), ENTÃO TENHO QUE PASSAR TODOS OS * E / PARA A NOTAÇÃO ANTES, DE EMPILHÁ-LOS
		if(exp[i] == '+' || exp[i] == '-')
		{	// RODA ENQUANTO HOUVER * OU / NA PILHA
			while(operadores->vet[operadores->topo] == '*' || operadores->vet[operadores->topo] == '/')
			{	
				// DESEMPILHA, E PASSA ELES PARA O VETOR FINAL DA NOTAÇÃO
				pop(operadores, &aux);
				if(aux == '*')
					RPN->notacao[RPN->tam] = MULT;
				if(aux == '/')
					RPN->notacao[RPN->tam] = DIV;
				RPN->tam++; // AUMENTA O TAMANHO DO VETOR
				if(operadores->topo == 0)
					break;

			}	
			push(operadores, exp[i]); // EMPILHA O + OU O -
		}
		else if(exp[i] ==  '*' ||  exp[i] == '/') // SE FOR * OU / (COMO AMBOS TEM A MAIOR PRIORIDADE NESSE CASO), ENTÃO EMPILHA
			push(operadores, exp[i]);
		else if(exp[i] >= 48 && exp[i] <= 57) // SE ESTIVER ENTRE ESSES 48 E 57, QUER DIZER QUE É UM NÚMERO
		{	
			// VOU GUARDANDO OS NÚMEROS E O '.'(CASO HOUVER), NUMA STRING AUXILIAR
			while((exp[i] > 47 && exp[i] < 58) || exp[i] == '.')
			{
				
				aux2[k] = exp[i];
				k++;
				i = i +1;
			}
			// O WHILE PERCORRE UMA CASA A MAIS DA STRING, ENTÃO TENHO QUE SUBTRAIR UM DO i, PORQUE ELE PODE PULAR ALGUMA COISA NA EXPRESSÃO
			i--; 
			aux2[k] = '\0'; // INDICO O FINAL DA STRING
			RPN->notacao[RPN->tam] = atof(aux2); // TRANSFORMO A STRING PARA FLOAT/DOUBLE, E COLOCO NA NOTAÇÃO
			RPN->tam++;
			k = 0; // ZERO O k PARA NÃO INTEFERIR O NO PRÓXIMO NÚMERO
		}
		else if(exp[i] == '(')
		{	// EMPILHO A ABERTURA DE PARENTESES NA PILHA
			push(operadores, exp[i]);
		}// SE HOUVER UM FECHAMENTO
		else if(exp[i] == ')')
		{
			// VOU PASSAR TODOS OS OPERADORES QUE ESTÃO NA PILHA PARA O VETOR DA NOTAÇÃO, ATÉ ENCONTRAR UMA ABERTURA DE PARENTESES 
			while(operadores->vet[operadores->topo] != '(')
			{
				pop(operadores, &aux);
				
				if(aux == '*')
					RPN->notacao[RPN->tam] = MULT;
				if(aux == '/')
					RPN->notacao[RPN->tam] = DIV;
				if(aux ==  '+')
					RPN->notacao[RPN->tam] = SUM;
				if(aux == '-')
					RPN->notacao[RPN->tam] = SUB;
				RPN->tam++;
			}
			pop(operadores, &aux);	// NO FINAL, EU TIRO A ABERTURA DA PILHA
		}	
		else if(exp[i] == ',')
			break; // SE HOUVER UMA ",", QUER DIZER QUE A EXPRESSÃO CHEGOU AO FINAL TAMBÉM, E QUE NESSE CASO, NÃO HAVERÁ MAIS EXPRESSÕES
		
	}	
	// NO FINAL DA EXPRESSÃO, PASSA TODOS OS OPERADORES DA PILHA PARA A NOTAÇÃO
	while(operadores->topo > 0)
	{
		pop(operadores, &aux);
		
		if(aux == '*')
			RPN->notacao[RPN->tam] = MULT;
		if(aux == '/')
			RPN->notacao[RPN->tam] = DIV;
		if(aux ==  '+')
			RPN->notacao[RPN->tam] = SUM;
		if(aux == '-')
			RPN->notacao[RPN->tam] = SUB;
		RPN->tam++;
	}	
	libera_pilha(operadores);

	return RPN; // RETORNA A NOTAÇÃO PRONTA

} 

// COM A NOTAÇÃO PRONTA
double resolve_notacao(RPN_t* RPN)
{
	if(RPN == NULL)
		return -1;
	// SEMPRE HAVERÁ DOIS NÚMEROS NA PILHA

	pilha_double* resultado = cria_pilha_double(); // CRIA UMA PILHA DE DOUBLE
	int i;
	double x, y; // VARIAVES AUXILIARES QUE IRÃO FAZER AS OPERAÇÕES

	// PERCORRE A NOTAÇÃO
	for(i = 0; i<RPN->tam; i++)
	{   // SE HOUVER UMA MULTIPLICAÇÃO, DESEMPILHA A PILHA DUAS VEZES, E FAZ A MULTIPLICAÇÃO ENTRE OS DOIS NUMEROS
		if(RPN->notacao[i] == MULT) // MULTIPLICACAO
		{
			pop_double(resultado, &x);
			pop_double(resultado, &y);
			push_double(resultado, y*x); // EMPILHA O RESULTADO
		}
		 // SE HOUVER UMA DIVISÃO, DESEMPILHA A PILHA DUAS VEZES, E FAZ A DIVISÃO ENTRE OS DOIS NUMEROS
		else if(RPN->notacao[i] == DIV) // DIVISAO
		{
			pop_double(resultado, &x);
			pop_double(resultado, &y);
			// SE O DENOMINADOR(x) FOR 0, RETORNA EXPRESSÃO INCORRETA POIS NÃO HÁ DIVISÃO POR 0
			if(x==0)
			{
				printf("Expressao incorreta\n");
				return FAIL;
			}
			push_double(resultado, y/x);// EMPILHA O RESULTADO
		}	
		 // SE HOUVER UMA SOMA, DESEMPILHA A PILHA DUAS VEZES, E FAZ A SOMA ENTRE OS DOIS NUMEROS
		else if(RPN->notacao[i] == SUM) // SOMA
		{
			pop_double(resultado, &x);
			pop_double(resultado, &y);
			push_double(resultado, y+x); // EMPILHA O RESULTADO

		}
		 // SE HOUVER UMA SUBTRAÇÃO, DESEMPILHA A PILHA DUAS VEZES, E FAZ A SUBTRAÇÃO ENTRE OS DOIS NUMEROS
		else if(RPN->notacao[i] == SUB) // SUBTRACAO
		{
			pop_double(resultado, &x);
			pop_double(resultado, &y);
			push_double(resultado, y-x); // EMPILHA O RESULTADO
		}else
		// EMPILHA TODOS OS NUMEROS
			push_double(resultado, RPN->notacao[i]);
	}	
	double result =resultado->vet[resultado->topo];
	
	libera_pilha_double(resultado);
	
	printf("%.2lf\n",result); // PRINTA O RESULTADO
	
	return SUCESS;


}