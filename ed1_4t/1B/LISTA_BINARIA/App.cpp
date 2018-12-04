#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio2.h>



#include "Produto.h"

char menuPrincipal();
void logicPrincipal();
void changeNameArq(char name1[100], char name2[100]);

char menuPrincipal(void)
{	
	textcolor(10);
	printf("\n\n\tESCOLHA.");
	
	textcolor(11);
	printf("\n\n\t[ 0 ] - SAIR.");
	printf("\n\t[ 1 ] - CADASTRAR.");
	printf("\n\t[ 2 ] - BUSCAR.");
	printf("\n\t[ 3 ] - RELATORIO.");
	printf("\n\t[ 4 ] - EXCLUSAO LOGICA.");
	printf("\n\t[ 5 ] - VENDA.");
	printf("\n\t[ 6 ] - CONCATENAR PRODUTOS.");
	
	textcolor(15);
	printf("\n\n\n\n\n\t[ * ] - NOME: GABRIEL NAVAS, RA: 261741888");
	printf("\n\t[ * ] - NOME: JEFFERSON PULHEIS RA: 261640160");
	
	return toupper(getch());
}

void logicPrincipal()
{	
	char op;
	do
	{
		//exclusaoFisica(ARQ_NAME_PRIMARY);
		system("cls");
						
		op = menuPrincipal();
		
		if(op == '1') cadastrarProduto_interface(ARQ_NAME_PRIMARY);

		else if(op == '2') buscarProduto_interface(ARQ_NAME_PRIMARY);
		
		else if(op == '3') relatorioProdutos_interface(ARQ_NAME_PRIMARY);
		
		else if(op == '4') exclusao_interface(ARQ_NAME_PRIMARY);
		
		else if(op == '5') venda(ARQ_NAME_PRIMARY);
		
		else if(op == '6') concatenarArqProdutos_Interface(ARQ_NAME_PRIMARY);
		
	}while(op != '0');
}

int main(void)
{
	logicPrincipal();
}
