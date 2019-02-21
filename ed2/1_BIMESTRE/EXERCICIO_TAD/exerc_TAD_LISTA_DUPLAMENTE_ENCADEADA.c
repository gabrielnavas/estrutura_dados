#include<stdio.h>
#include<stdlib.h>

struct lista
{
    char info;
    struct lista * prox, * ante;
};
typedef struct lista Lista;

void init(Lista **lista);
void insere_inicio(Lista **lista, char info);
void insere_final(Lista **lista, char info);
Lista *buscar_rec(Lista * lista, char info);
Lista *buscar(Lista * lista, char info);
char excluir(Lista ** lista, char info);
char is_empty(Lista * lista);
void show_all_elements(Lista * lista);

int main(int argv, char *argc[])
{
    Lista * l;
    init(&l);

    insere_inicio(&l, 'a');
    insere_inicio(&l, 'b');
    insere_inicio(&l, 'y');
    insere_inicio(&l, 'w');

    excluir(&l, 'b');

    
    printf("%s", (buscar_rec(l, 'p') == NULL) ? "nao achou\n" : "achou\n");

    insere_final(&l, 'k');
    insere_final(&l, 'r');
    insere_final(&l, 'u');
    insere_final(&l, 'o');

    show_all_elements(l);    

}

void init(Lista **lista)
{
    *lista = NULL;
}

void insere_inicio(Lista **lista, char info)
{
    Lista *novo;
    
    novo = (Lista*) malloc(sizeof(Lista));
    novo->ante = novo->prox = NULL;
    novo->info = info;
    novo->prox = *lista;
    *lista = novo;
}

void insere_final(Lista **lista, char info)
{
    Lista *novo, *aux;
    
    novo = (Lista*) malloc(sizeof(Lista));
    novo->info = info;
    novo->prox = novo->ante = NULL;

    if(*lista == NULL)
	*lista = novo;
    else
    {
	aux = *lista;
	while(aux->prox != NULL)
	    aux = aux->prox;
	aux->prox = novo;
	novo->ante = aux;
    }
}

Lista * buscar(Lista * lista, char info)
{
    while(lista != NULL && lista->info != info)
	lista = lista->prox;

    return lista;
}

Lista * buscar_rec(Lista * lista, char info)
{
    if(lista != NULL && lista->info != info)
	return buscar_rec(lista->prox, info);
    else
	return lista;
}

char excluir(Lista ** lista, char info)
{
    Lista *ante, *atual;

    ante=NULL;
    atual=*lista;

    if(*lista != NULL)
    {
	if((*lista)->info == info)
	{
	    *lista = (*lista)->prox;
	    free(atual);
	    if(*lista != NULL)
		(*lista)->ante = NULL;
	}
	else
	{
	    while(atual != NULL && atual->info != info)
	    {
		ante = atual;
		atual = atual->prox;
	    }

	    if(atual != NULL)
	    {
		ante->prox = atual->prox;
		if(atual->prox != NULL)
		    atual->prox->ante = ante;
		free(atual);
	    }
	}
    }
}

char is_empty(Lista * lista)
{
    return lista == NULL;
}

void show_all_elements(Lista * lista)
{
    printf("LIST = {");
    while(lista != NULL)
    {
	printf(" %c ", lista->info);
	lista = lista->prox;
    }

    printf("};");
}

