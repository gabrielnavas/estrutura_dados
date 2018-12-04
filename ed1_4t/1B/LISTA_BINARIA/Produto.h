#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio2.h>

#define ARQ_NAME_PRIMARY "produtos1.bin\0"

struct Produto
{
	char nome[40];
	int quantidade;
	int codigo;
	float preco;
	
	int flag;
};

void cadastrarProduto_interface(char nomeArq[100]);
void buscarProduto_interface(char nomeArq[100]);
void relatorioProdutos_interface(char nomeArq[100]);
void concatenarArqProdutos_Interface(struct NomesArq nomeArq);
int buscarProdutoPrimaryKey(FILE *arqProd, int prodKeyPrimary);
void relatorioProdutos(FILE *arqProd);
int concatenarArqProdutos(char arqNameProd1[100], char arqNameProd2[100]);

void exclusao_interface(char nomeArq[100]);
int excluir(char nomeArq[100], struct Produto produto);
void exclusaoFisica(char arqNameProd1[100]);

void cadastrarProduto_interface(char nomeArq[100])
{	
	struct Produto produto;
	
	FILE *arqProd = fopen(nomeArq, "ab+");
	
	system("cls");
	printf("\n\t0 PARA VOLTAR.");
	printf("\n\tCODIGO: ");
	scanf("%d", &produto.codigo);
	while(produto.codigo != 0)
	{
		int existe = buscarProdutoPrimaryKey(arqProd, produto.codigo);
		if(existe == -1)
		{	
			printf("\n\tNOME: ");
			fflush(stdin); 	gets(produto.nome);
					
			printf("\n\tQUANTIDADE: ");
			scanf("%d", &produto.quantidade);
			
			printf("\n\tPRECO: ");
			scanf("%f", &produto.preco);
			
			produto.flag = 1;
			
			fwrite(&produto, sizeof(Produto), 1, arqProd);
			printf("\n\tCADASTRADO.");
		}
		else
			printf("\n\tPRODUTO JA EXISTE.");
		
		printf("\n\t[ PRESS ENTER ]");
		getch();
		
		system("cls");
		printf("\n\t0 PARA VOLTAR.");
		printf("\n\tCODIGO: ");
		scanf("%d", &produto.codigo);
	}
	
	fclose(arqProd);
}

void venda(char nomeArq[100])
{
	struct Produto produto;
	
	FILE *arqProd = fopen(nomeArq, "rb+");
	
	clrscr();
	printf("\n\t0 PARA VOLTAR.");
	printf("\n\tCODIGO: ");
	scanf("%d", &produto.codigo);
	while(produto.codigo != 0)
	{
		int existe = buscarProdutoPrimaryKey(arqProd, produto.codigo);
		if(existe != -1)
		{
			fseek(arqProd, sizeof(Produto) * existe , 0);
			fread(&produto, sizeof(Produto) , 1, arqProd);
			if(produto.quantidade > 0)
			{
				produto.quantidade--;
				
				buscarProdutoPrimaryKey(arqProd, produto.codigo);
				fseek(arqProd, sizeof(Produto) * existe , 0);
				fwrite(&produto, sizeof(Produto) , 1, arqProd);
				
				int situacaoAtual = buscarProdutoPrimaryKey(arqProd, produto.codigo);
				if(situacaoAtual != -1)
				{
					fseek(arqProd, sizeof(Produto) * situacaoAtual , 0);
					fread(&produto, sizeof(Produto), 1, arqProd);
					printf("\n\tSITUACAO ATUAL: ");
					
					printf("%d\t\t", produto.codigo);
					for(int i=0 ; i < strlen(produto.nome) ; i++) printf("%c", produto.nome[i]);
					printf("\t\t%d", produto.quantidade);
					printf("\t\t%.2f", produto.preco);	
						
					printf("\n\n\tVENDIDO COM SUCESSO.");
				}
			}
			else
			{
				if(produto.quantidade == 0)
					excluir(ARQ_NAME_PRIMARY, produto);
				printf("\n\tPRODUTO ACABOU");	
			}
			 
		}
		else
			printf("\n\tPRODUTO NAO ENCONTRADO");
			
		getch();
		clrscr();
		printf("\n\t0 PARA VOLTAR.");
		printf("\n\tCODIGO: ");
		scanf("%d", &produto.codigo);
	}
	
	fclose(arqProd);
}

void buscarProduto_interface(char nomeArq[100])
{
	Produto produto;
	
	FILE *arqProd = fopen(nomeArq, "rb+");
	
	system("cls");
	printf("\n\t0 PARA VOLTAR.");
	printf("\n\tCODIGO PRODUTO: ");
	scanf("%d", &produto.codigo);
	while(produto.codigo != 0)
	{
		int existe = buscarProdutoPrimaryKey(arqProd, produto.codigo);
		if(existe != -1)
		{
			fseek(arqProd, sizeof(Produto) * existe , 0);
			fread(&produto, sizeof(Produto), 1, arqProd);
			
			printf("\n\n%d\t\t", produto.codigo);
			for(int i=0 ; i < strlen(produto.nome) ; i++) printf("%c", produto.nome[i]);
			printf("\t\t%d", produto.quantidade);
			printf("\t\t%.2f", produto.preco);
			
			printf("\n\n\t[ PRESS ENTER ]");
		}
		else
			printf("\n\n\tNAO EXISTE.");
			
		getch();	
		
		system("cls");
		printf("\n\t0 PARA VOLTAR.");
		printf("\n\tCODIGO PRODUTO: ");
		scanf("%d", &produto.codigo);
	}
	
	fclose(arqProd);
}

void relatorioProdutos_interface(char nomeArq[100])
{
	struct Produto produto;
	
	system("cls");
	
	FILE *arqProd = fopen(nomeArq, "rb+");
	
	relatorioProdutos(arqProd);
	
	fclose(arqProd);
	
	printf("\n\t[ PRESS ENTER FOR BACK ]");
	getch();
}

void exclusao_interface(char nomeArq[100])
{
	struct Produto produto;
	
	system("cls");
	printf("\n\t0 PARA VOLTAR.");
	printf("\n\tCODIGO: ");
	scanf("%d", &produto.codigo);
	while(produto.codigo != 0)
	{
		int excluiu = excluir(nomeArq , produto);
		if(excluiu)
			printf("\n\tEXCLUIU COM SUCESSO.");
		else
			printf("\n\tCODIGO NAO EXISTE.");
			
		getch();
		
		system("cls");
		printf("\n\t0 PARA VOLTAR.");
		printf("\n\tCODIGO: ");
		scanf("%d", &produto.codigo);
	}
}

int excluir(char nomeArq[100], struct Produto produto)
{	
	FILE *arq = fopen(nomeArq, "rb+");
	
	int flag=0;
	
	int existe = buscarProdutoPrimaryKey(arq, produto.codigo);
	if(existe != -1)
	{
		fseek(arq, sizeof(Produto) * existe , 0);
		fread(&produto, sizeof(Produto) , 1, arq);
		produto.flag=0;
		
		existe = buscarProdutoPrimaryKey(arq, produto.codigo);
		
		fseek(arq, sizeof(Produto) * existe , 0);
		fwrite(&produto, sizeof(Produto) , 1, arq);
		
		flag=1;
	}
	
	fclose(arq);
	
	return flag;
}

void concatenarArqProdutos_Interface(char nomeArq[100])
{
	char nomeArqSecundario[100];
	
	system("cls"); 
	
	printf("\n\tDEIXE EM BRANCO PARA VOLTAR.");
	textcolor(LIGHTGREEN); printf("\n\t[ * ] NOME DO ARQUIVO SECUNDARIO: ");
	fflush(stdin); gets(nomeArqSecundario);
	while(strcmp(nomeArqSecundario, "") != 0)
	{
		int allRight = concatenarArqProdutos(nomeArq, nomeArqSecundario);
		
		textcolor(YELLOW);
		if(allRight)
			printf("\n\n\tARQUIVOS CONCATENADOS COM SUCESSO.");
		else
			printf("\n\n\tARQUIVOS NAO EXISTE.");
			
		printf("\n\n\t[ PRESS ENTER ]");	
		getch();
		
		
		system("cls");
		printf("\n\tDEIXE EM BRANCO PARA VOLTAR.");
		textcolor(LIGHTGREEN); printf("\n\t[ * ] NOME DO ARQUIVO SECUNDARIO: ");
		fflush(stdin); gets(nomeArqSecundario);	
	}
}

int buscarProdutoPrimaryKey(FILE *arqProd, int prodKeyPrimary)
{
	fseek(arqProd, 0, 0);
	Produto produto;
	
	fread(&produto, sizeof(Produto), 1, arqProd);
	while(!feof(arqProd) && prodKeyPrimary != produto.codigo)
		fread(&produto, sizeof(Produto), 1, arqProd);
		
	if(produto.codigo == prodKeyPrimary && produto.flag == 1)
		return (ftell(arqProd) / sizeof(Produto)) -1;
	
	return -1;				
}

void relatorioProdutos(FILE *arqProd)
{
	Produto produto;
		
	printf("CODIGO\t\tNOME\t\tQUANTIDADE\tPRECO\n\n");
	
	if(!feof(arqProd))
	{
		fread(&produto, sizeof(Produto), 1, arqProd);
		while(!feof(arqProd))
		{
			if(produto.flag == 1)
			{
				printf("%d\t\t", produto.codigo);
				for(int i=0 ; i < strlen(produto.nome) ; i++) printf("%c", produto.nome[i]);
				printf("\t\t%d", produto.quantidade);
				printf("\t\t%.2f\n", produto.preco);
			}
			
			fread(&produto, sizeof(Produto), 1, arqProd);
		}
	}
}

void exclusaoFisica(char arqNameProd1[100])
{
	FILE *arqOld = fopen(arqNameProd1, "rb");
	
	char auxName[200];
	strcat(auxName, "_aux");
	
	FILE *arqNew = fopen(arqNameProd1, "wb");
	
	if(arqOld != NULL && arqNew != NULL)
	{
		struct Produto produto;
		
		fread(&produto, sizeof(Produto),1 , arqOld);
		while(!feof(arqOld))
		{
			if(produto.flag == 0)
				fwrite(&produto, sizeof(Produto),1 , arqNew);
				
			fread(&produto, sizeof(Produto),1 , arqOld);
		}
		
		fclose(arqOld);
		fclose(arqNew);
	}
	
	remove(arqNameProd1);
	rename(auxName, arqNameProd1);
}

int concatenarArqProdutos(char arqNameProd1[100], char arqNameProd2[100])
{
	struct Produto produto;
	
	FILE *arqProd1 = fopen(arqNameProd1, "ab+");
	FILE *arqProd2 = fopen(arqNameProd2, "rb");
	
	if(arqProd1 != NULL && arqProd2 != NULL)
	{
		fread(&produto, sizeof(Produto), 1, arqProd2);
		while(!feof(arqProd2))
		{
			int existe = buscarProdutoPrimaryKey(arqProd1, produto.codigo);
			if(existe == -1 && produto.flag == 1)
				fwrite(&produto, sizeof(Produto), 1, arqProd1);
			
			fread(&produto, sizeof(Produto), 1, arqProd2);
		}
		
		fclose(arqProd1);
		fclose(arqProd2);
		
		return 1;
	}
	
	return 0;
}
