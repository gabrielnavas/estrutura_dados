#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>

typedef struct TpProduto Produto;

struct Pt_Produto
{
	struct PtProduto * prox;
	
	int cod;
	char * name;
	float preco;
	int qntd;
};

typedef struct Pt_Produto PtProduto;

PtProduto * create_caixa_produto(int cod, char * name, float preco, int qntd)
{
	PtProduto * nova = malloc(sizeof(PtProduto));
	
	nova->cod=cod;
	//nova->name=malloc(sizeof(100));
	nova->name=name;
	nova->preco=preco;
	nova->qntd=qntd;
	nova->prox=NULL;
	
	return nova;
}

PtProduto * inserir_produto_lista_ordenada(PtProduto * prod_lista, int cod, char * name, float preco, int qntd)
{
	PtProduto * novo = create_caixa_produto(cod, name, preco, qntd);
	
	if(prod_lista == NULL)
		prod_lista = novo;
	else
	{
		PtProduto * ante= NULL;
		PtProduto * atual = prod_lista;
		while(atual != NULL && strcmp(prod_lista->name, atual->name) > 0)
		{
			ante = atual;
			atual = atual->prox;
		}
		
		if(ante == NULL)
		{
			novo->prox = prod_lista;
			prod_lista = novo;
		}
		else if(atual == NULL)
			ante->prox = novo;
		else
		{
			novo->prox = atual;
			ante->prox = novo;
		}		
	}		
	
	return prod_lista;			
}

PtProduto * buscar_produto_lista(PtProduto * lista, int cod)
{
	PtProduto * aux = lista;
	while(aux != NULL && aux->cod != cod)
		aux = aux->prox;
		
	if(aux == NULL)
		return NULL;
	
	return aux;	
}

void exibir_produto_lista(PtProduto * lista)
{
	PtProduto * aux = lista;
	while(aux != NULL)
	{
		printf("%d - ", lista->cod);
		
		register int i; for(i=0 ; i < strlen(aux->name) ; i++) 
			printf("%c", aux->name[i]);
			
		printf(" - %.2f - %d\n", lista->preco, lista->qntd);	
		
		aux = aux->prox;
	}
}

char verifica_dados(int cod, char * name, float preco, int qntd)
{
	char tudo_certo = 1;
	
	if(cod <= 0)
		tudo_certo=0;
	
	else if(strcmp(&name, "") == 0)
		tudo_certo=0;
	
	else if(preco == 0.0)
		tudo_certo=0;
	
	else if(qntd == 0)
		tudo_certo=0;
		
	return tudo_certo;	 			
}

PtProduto * inserir_dados_produto_lista(PtProduto * lista)
{
	int cod, qntd;
	char * name;
	float preco;
	
	system("cls; clear");
	
	printf("COD: ");
	scanf("%d", &cod);
	while(cod != 0)
	{
		if(buscar_produto_lista(lista, cod) == NULL)
		{
			printf("NOME: ");
			fflush(stdin);	gets(&name);
			
			printf("QUANTIDADE: ");
			scanf("%d", &qntd);
			
			printf("PRECO: ");
			scanf("%f", &preco);
			
			
			if(verifica_dados(cod, name, preco, qntd))
			{
				lista = inserir_produto_lista_ordenada(lista, cod, name, preco, qntd);
				printf("\n\nINSERIDO.\n");
			}
				
			else
			{
				printf("DADOS INCOMPLETOS");
				getch();
			}	
		}
		else
		{
			printf("\nPRODUTO JA CADASTRADO. [ PRESS ENTER ]");
			getch();
		}
			
		printf("\n\nCOD: ");
		scanf("%d", &cod);
	}
	
	return lista;
}

PtProduto * inserir_dados_produto_lista(PtProduto * lista)
{
	
}

char menu_produto_lista()
{
	char op;
	
	system("cls; clear");
	
	printf("[ * ] - OPCOES\n\n");
	
	printf("\n[ 0 ] - SAIR.");
	printf("\n[ 1 ] - INSERIR PRODUTO.");
	printf("\n[ 2 ] - REMOVER PRODUTO.");
	printf("\n[ 3 ] - BUSCAR PRODUTO.");
	printf("\n[ 4 ] - EXIBIR PRODUTOS.");
	printf("\n[ 5 ] - REMOVER TODOS PRODUTOS.");
	
	return getch();
}

PtProduto * logica_menu_produto_lista(char op, PtProduto * produto_lista)
{
	switch(op)
	{
		case '1':	produto_lista = inserir_dados_produto_lista(produto_lista);
					break;
					
		case '2':	//remover_dados_produto_lista();
					break;
					
		case '3':	//buscar_dados_produto_lista();
					break;
					
		case '4':	//exibir_dados_produto_lista();
					break;
					
		case '5':	//remover_todos_produtos();
					break;
					
		case '0':	return;
					break;
					
		default:	printf("\nENTRE COM UMA OPCAO DO MENU.");
					break;			
	}
	
	return produto_lista;
}

int main(void)
{	
	PtProduto * lista = NULL;
	
	lista = logica_menu_produto_lista(menu_produto_lista(), lista);
	exibir_produto_lista(lista);
}
