#include<stdio.h>
#include<stdlib.h>

typedef struct pont Pont;
struct pont
{
	char info;
	Pont * prox;
};

Pont * caixa(char info)
{
	Pont * nova = (Pont*) malloc(sizeof(Pont));
	nova->info = info;
	nova->prox=NULL;
	return nova;
}

void inserir_fila(Pont ** fila, char info)
{
	Pont * aux;
	Pont * nova = caixa(info);
	
	if(*fila == NULL)
		*fila = nova;
	else
	{
		aux = *fila;
		while(aux->prox != NULL)
			aux = aux->prox;
		
		aux->prox = nova;
	}	
}

char remove_elem(Pont ** lista, char info)
{
	char elem='0';
	Pont * p_free;
	Pont * ante;
	
	if(*lista != NULL && (*lista)->info == info)
	{
		p_free = *lista;
		elem = p_free->info;
		*lista = (*lista)->prox;
		free(p_free);
	}
	else
	{
		ante = NULL;
		p_free = *lista;
		while(p_free != NULL && p_free->info != info)
		{
			ante = p_free;
			p_free = p_free->prox;
		}
		
		if(p_free != NULL)
		{
			elem = p_free->info;
			ante->prox = p_free->prox;
			free(p_free);
		}
	}
	
	return elem;
}

void exibir(Pont * fila)
{
	while(fila != NULL)
	{
		printf("%c - ", fila->info);
		fila = fila->prox;
	}
}

void test(Pont ** l)
{
	(*l)->info = '2';
	printf("%c", (*l)->info);
}

int main()
{
	Pont * lista=NULL;
	inserir_fila(&lista, 'b');
	inserir_fila(&lista, 'c');
	inserir_fila(&lista, 'h');
	inserir_fila(&lista, 'e');
	//test(&lista);
	
	
	exibir(lista);
		

	printf("REMOVEU: %c\n\n", remove_elem(&lista, 'b'));
	
	
	exibir(lista);
}
