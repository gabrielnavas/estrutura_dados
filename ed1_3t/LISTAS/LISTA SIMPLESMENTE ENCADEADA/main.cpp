#include<stdio.h>

#include "lista_simplemente_int.h"

void endl()
{
	/*
	* PULAR LINHA
	*/
	printf("\n");
}

char menu()
{
	/*
		MENU RETORNANDO A OPCAO
	
	*/
	system("cls");
	
	printf("[ 0 ] - SAIR.");
	printf("\n[ 1 ] - INSERIR ORDENADO.");
	printf("\n[ 2 ] - DELETAR TUDO.");
	printf("\n[ 3 ] - DELETAR TUDO RECURSIVO.");
	printf("\n[ 4 ] - DELETAR POR POSICAO.");
	printf("\n[ 5 ] - DELETAR ELEMENTO.");
	printf("\n[ 6 ] - EXIBIR LISTA.");
	printf("\n[ 7 ] - EXIBIR QUANTIDADE DE ELEMENTOS.");
	printf("\n[ 8 ] - BUSCA EXAUSTIVA.");
	printf("\n[ 9 ] - BUSCA BINARIA.");
	
	return getch();
}

Lista * inserir(Lista *lista)
{
	system("clear");
	
	printf("\nDADO A INSERIR: ");
	char dado;
	scanf("%c", &dado);
	while(dado != 27)
	{
		lista = inserirOrdenado(lista, dado);
			
		printf("\nDADO A INSERIR: ");
		scanf("%c", &dado);
	}
	
	return lista;
}

Lista * delPos(Lista *lista)
{
	system("clear");
	
	printf("\nPOSICAO A DELETAR: ");
	int pos;
	scanf("%d", &pos);
	while(dado != 27)
	{
		lista = apagarPos(lista, pos);
			
		printf("\nPOSICAO A DELETAR: ");
		scanf("%d", &pos);
	}
	
	return lista;
}

Lista * delElem(Lista *lista)
{
	system("clear");
	
	printf("\nELEMENTO A DELETAR: ");
	char dado;
	scanf("%c", &dado);
	while(dado != 27)
	{
		lista = apagarElem(lista, dado);
			
		printf("\nPOSICAO A DELETAR: ");
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
int main(void)
{
	Lista *lista = NULL;
}
