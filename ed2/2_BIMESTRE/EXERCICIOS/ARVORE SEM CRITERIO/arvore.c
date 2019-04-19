#include<stdio.h>
#include<stdlib.h>

struct tree
{
	int info;
	struct tree * dir, *esq;
};
typedef struct tree Tree;

void init(Tree ** t)
{
	*t = NULL;
}

Tree * criaNo(char info)
{
	Tree * t = (Tree*) malloc(sizeof(info));
	t->esq = t->dir = NULL;
	t->info = info;
	return t;
}

void localizaNo(Tree * no, int info, Tree ** e)
{
	if(no != NULL)
	{
		if(info == no->info)
			*e = no;
		else
		{
			localizaNo(no->esq, info, &*e);
			if(*e == NULL)
				localizaNo(no->dir, info, &*e);
		}	
	}
}
		

void insere(Tree ** t, int info, int info_pai, char lado)
{
	Tree * aux;
	
	if(*t == NULL)
		*t = criaNo(info);
	else
	{
		aux = NULL;
		localizaNo(*t, info_pai, &aux);
		if(aux != NULL)
		{
			if(aux->esq == NULL && lado == 'e')
				aux->esq = criaNo(info);
			
			else if(aux->dir == NULL && lado == 'd')
				aux->dir = criaNo(info);
			else
				printf("LADO OCUPADO\n");			
		}
		else
			printf("NO NAO EXISTE.\n");
	}	
}

void exibir(Tree * no, int * n)
{
	int i;
	
	if(no != NULL)
	{
		(*n)++;
		
		exibir(no->dir, &*n);
		for(i=0 ; i < 5* (*n) ; i++)
			printf(" ");
			
		printf("%d\n", no->info);
		
		exibir(no->esq, &*n);
		(*n)--;
	}
}

int main(void)
{
	Tree * raiz;
	init(&raiz);
	
	insere(&raiz, 1, 0, ' ');
	insere(&raiz, 2, 1, 'e');
	insere(&raiz, 3, 2, 'e');
	insere(&raiz, 4, 2, 'd');
	insere(&raiz, 6, 1, 'd');
	insere(&raiz, 5, 6, 'e');
	insere(&raiz, 7, 6, 'd');
	
	int n=-1;
	exibir(raiz, &n);
}
