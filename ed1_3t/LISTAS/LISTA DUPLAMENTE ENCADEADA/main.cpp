#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>

#include "lista_duplamente_char.h"

/*
 * FEITO PARA TESTAR A LISTA DUPLAMENTE ENCADEADA
*/

//ABCDEFGHIJKLIMOQRSTUVXWYZ

void endl()
{
	/*
	* PULAR LINHA
	*/
	printf("\n");
}

/*

char menu()
{
	system("cls");
	
	printf("[ 0 ] - SAIR.");
	printf("[ 1 ] - INSERIR ORDENADO.");
	printf("[ 2 ] - DELETAR TUDO.");
	printf("[ 3 ] - DELETAR TUDO RECURSIVO.");
	printf("[ 4 ] - DELETAR POR POSICAO.");
	printf("[ 5 ] - DELETAR ELEMENTO.");
	printf("[ 6 ] - EXIBIR LISTA.");
	printf("[ 7 ] - EXIBIR QUANTIDADE DE ELEMENTOS.");
	printf("[ 8 ] - BUSCA EXAUSTIVA.");
	printf("[ 9 ] - BUSCA BINARIA.");
	
	return getch();
}

Lista * inserir(Lista *lista)
{
	system("clear");
	
	printf("DADO A INSERIR: ");
	char dado;
	scanf("%c", &dado);
	while(dado != 27)
	{
		lista = inserirOrdenado(lista, dado);
			
		printf("DADO A INSERIR: ");
		scanf("%c", &dado);
	}
	
	return lista;
}

Lista * delPos(Lista *lista)
{
	system("clear");
	
	printf("POSICAO A DELETAR: ");
	int pos;
	scanf("%d", &pos);
	while(pos != 27)
	{
		lista = apagarPos(lista, pos);
			
		printf("POSICAO A DELETAR: ");
		scanf("%d", &pos);
	}
	
	return lista;
}

Lista * delElem(Lista *lista)
{
	system("clear");
	
	printf("ELEMENTO A DELETAR: ");
	char dado;
	scanf("%c", &dado);
	while(dado != 27)
	{
		lista = apagarElem(lista, dado);
			
		printf("POSICAO A DELETAR: ");
		scanf("%c", &dado);
	}
	
	return lista;
}

void exibirLista(Lista *lista)
{
	system("clear");
	
	printf("\nLISTA:");
	
	printf("\n\nFIM, PRESS ENTER");
	getch();
}

void exibirQntElementos(Lista *lista)
{
	system("clear");
	
	printf("\nQUANTIDADE DE ELEMENTOS: %d", 
	getch();
}

char escolherOp(Lista *lista, char op)
{	
	switch(op)
	{
		case '1':
			lista = inserir(lista);
			break;
			
		case '2':
			lista = apagar(lista);
			break;
			
		case '3':
			lista = apagarRec(lista);
			break;
			
		case '4':
			lista = delPos(lista); 
			break;
			
			
		case '5':
			lista = delElem(lista);
			break;
			
			
		case '6':
			exibirLista(lista);
			break;
			
			
		case '7':
			break;
			
			
		case '8':
			break;
			
			
		case '9':
			break;
			
			
		case '10':
			break;
			
	}
}
*/

int main(void)
{
	Lista *lista = NULL;
	
	lista = inserirOrdenado(lista, 'h');
	lista = inserirOrdenado(lista, 'c');
	lista = inserirOrdenado(lista, 'b');
	
	
	exibir(lista);
	
	Lista *achouDado = buscaBinaria(lista, 'w');
	if(achouDado != NULL)
		printf("ACHOU");
	else
		printf("NAO ACHOU");
		
	Lista *lista2 = inverter(lista);
	exibir(lista2);		
}
