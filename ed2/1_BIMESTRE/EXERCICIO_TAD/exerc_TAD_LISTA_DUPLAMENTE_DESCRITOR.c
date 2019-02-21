#include<stdio.h>
#include<stdlib.h>


struct lista
{
    char info;
    struct lista *ante, *prox;
};

typedef struct lista Lista;

struct descritor
{
    Lista * inicio, *fim;
};

typedef struct descritor Descritor;

void init(Descritor *d)
{
    (*d).inicio= (*d).fim = NULL;
}

void inserir_fim(Descritor *d, char info)
{
    Lista *novo;

    novo = (Lista*) malloc(sizeof(Lista));
    novo->info = info;
    novo->prox = novo->ante = NULL;

    if(is_empty(d))
	(*d).inicio = (*d).fim = novo;
    else
    {
	(*d).fim->prox = novo;
	novo->ante = d.fim;
	(*d).fim = novo;
    }
}

void inserir_inicio(Descritor *d, char info)
{
    Lista * novo;

    novo = (Lista*) malloc(sizeof(Lista));
    novo->info = info;
    novo->prox = novo->ante = NULL;

    if(is_empty(d))
	(*d).inicio = (*d).fim = novo;
    else
    {
	novo->prox = (*d).inicio;
	(*d).inicio->ante = novo;
	(*d).inicio = novo;
    }
}

int main(int argv, char *argc[])
{
    Descritor desc;

    init(&desc);

    printf("%d %d\n\n", desc.inicio, desc.fim);
    return 0;
}
