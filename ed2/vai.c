#include<stdio.h>
#include<stdlib.h>

typedef struct pont Pont;
struct pont
{
	char info;
	Pont * prox;
};

Pont * caixa_fila(char info);
Pont * inserir_fila(Pont * fila, char info);
Pont * remover(Pont * fila, char info);
Pont * buscar_fila(Pont * fila, char info);

void exibir_lista(Pont * lista);

// ---> NAO RECURSIVO
void bubble_sort_nao_rec(Pont * fila);

// ---


// ---> RECURSIVO
void maior_menor_fila(Pont * ante, Pont * inicio);
void check_tl(Pont * fila, int tl);
void bubble_sort_rec(Pont * fila);
// ---

int main()
{
	Pont  * fila=NULL;
	fila = inserir_fila(fila, 'z');
	fila = inserir_fila(fila, 'h');
	fila = inserir_fila(fila, 'f');
	
	fila = inserir_fila(fila, 'd');
	fila = inserir_fila(fila, 'b');
	fila = inserir_fila(fila, 'a');
	
	bubble_sort_rec(fila);
	
	printf("antes - > ");
	exibir_lista(fila);
	
	fila = remover(fila, 'z');
	fila = remover(fila, 'd');
	fila = remover(fila, 'a');
	
	//bubble_sort_nao_rec(fila);
	
	
	
	printf("\n\ndepois - > ");
	exibir_lista(fila);
}

Pont * caixa_fila(char info)
{
	Pont * novo = (Pont*) malloc(sizeof(info));
	novo->info = info;
	novo->prox = NULL;
	return novo;
}

Pont * inserir_fila(Pont * fila, char info)
{
	Pont * novo = caixa_fila(info);

	if(fila == NULL)
		fila = novo;
	else
	{
		Pont * aux = fila;
		while(aux->prox != NULL)
			aux = aux->prox;

		aux->prox = novo;
	}

	return fila;
}

Pont * remover(Pont * fila, char info)
{
	Pont * ante = NULL;
	Pont * p_free = fila;

	if(p_free != NULL && p_free->info == info)
	{
		fila = fila->prox;
		free(p_free);
	}
	else
	{
		while(p_free != NULL && p_free->info != info)
		{
			ante = p_free;
			p_free = p_free->prox;
		}

		if(p_free != NULL)
		{
			ante->prox = p_free->prox;
			free(p_free);
		}
	}

	return fila;
}

Pont * buscar_fila(Pont * fila, char info)
{
	Pont * p_search=fila;
	while(p_search != NULL && p_search->info != info)
		p_search = p_search->prox;

	return p_search;
}

int len_fila(Pont * fila)
{
	Pont * p_aux = fila;
	int tl;
	for(tl=0 ; p_aux != NULL ; tl++)
		p_aux = p_aux->prox;

	return tl;
}

// ---> bubble_sort  NAO RECURSIVO
void bubble_sort_nao_rec(Pont * fila)
{
	if(fila != NULL && fila->prox != NULL)
	{
		int tl = len_fila(fila);

		char aux;
		Pont * ante;
		Pont * atual;
		int i;
		for(i=0 ; i < tl ; i++)
		{
			ante = fila;
			atual = fila->prox;

			while(atual != NULL)
			{
				if(ante->info > atual->info)
				{
					aux = ante->info;
					ante->info = atual->info;
					atual->info = aux;
				}

				ante=atual;
				atual = atual->prox;
			}
		}
	}
}
// ---

// ---> bubble_sort  RECURSIVO
void maior_menor_fila(Pont * ante, Pont * atual)
{
	if(atual != NULL)
	{
		if(ante->info > atual->info)
		{
			char aux = ante->info;
			ante->info = atual->info;
			atual->info = aux;
		}
		
		maior_menor_fila(atual, atual->prox);
	}
}

void check_tl(Pont * fila, int tl)
{
	if(tl > 0)
	{
		Pont * ante = fila;
		Pont * atual = fila->prox;
		
		maior_menor_fila(ante, atual);
		
		
		check_tl(fila, tl-1);
	}
}

void bubble_sort_rec(Pont * fila)
{
	if(fila != NULL && fila->prox != NULL)
	{
		int tl = len_fila(fila);
		check_tl(fila, tl);
	}
}

// ---

void exibir_lista(Pont * lista)
{
	printf("lista - { ");

	Pont * p_aux=lista;
	while(p_aux != NULL)
	{
		printf("[%c] ", p_aux->info);
		p_aux = p_aux->prox;
	}

	printf("}");
}










