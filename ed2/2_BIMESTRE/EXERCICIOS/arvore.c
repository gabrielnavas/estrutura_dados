#include<stdio.h>

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
	Tree * t;
	t->esq = t->dir = NULL;
	t->info = info;
	return t;
}

void localizaNo(Tree * t, int info, Tree ** e)
{
	if(t != NULL)
	{
		if(info == t->info)
			*e = t;
		else
		{
			localizaNo(t->esq, info, &*e);
			if(*e == NULL)
				localizaNo(t->dir, info, &*e);
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
		localizaNo(*t, info_pai, &aux);
		if(aux != NULL)
		{
			while(aux->info != info_pai)
			{
				if(info < aux->info)
					aux = aux->esq;
				else
					aux = aux->dir;	
			}
			
			if(aux->esq != NULL && lado == 'e')
				aux->esq = criaNo(info);
			else if(aux->dir != NULL && lado == 'd')
				aux->dir = criaNo(info);
			else
				printf("LADO OCUPADO\n");			
		}
		else
			printf("NO NAO EXISTE.\n");
	}	
}

int main(void)
{
	
}
