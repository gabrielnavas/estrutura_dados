#include<stdio.h>
#include<stdlib.h>

struct matesp
{
    int lin, col, valor;
    struct matesp * pl, *pc;
};
typedef struct matesp Matesp;

struct lista
{
    int index;
    Matesp *celula;
    struct lista * prox;
};
typedef struct lista Lista;

void criar_lista(Lista ** l, int index, Lista **l2)
{
    Lista * novo, *ante, *atual;

    if(*l == NULL)
    {
		*l = (Lista*) malloc(sizeof(Lista));
		(*l)->index = index;
		(*l)->celula = NULL;
		(*l)->prox = NULL;
		*l2 = *l;
    }
    else if((*l)->index == index)
		*l2 = *l;
    else
    {
		ante = *l;
		atual=ante->prox;
		while(atual != NULL && atual->index < index)
		{
		    ante = atual;
		    atual = atual->prox;
		}
	
		if(atual != NULL && atual->index == index)
		    *l2 = atual;
		else
		{
		    novo = (Lista*) malloc(sizeof(Lista));
		    novo->index=index;
		    novo->celula = NULL;
		    novo->prox = atual;
		    ante->prox = novo;
		    *l2 = novo;
		}
    }
}

void buscar_mat(Matesp * l1, int col, Matesp **l2)
{
    while(l1 != NULL && l1->col < col)
	l1 = l1->pl;

    if(l1 != NULL && l1->col == col)
	*l2 = l1;
    else
	*l2 = NULL;
}

void inserir(Lista ** listal, Lista ** listac, int lin, int col, int valor)
{
    Lista * auxlista;
    Matesp * auxmat, *novo, *antemat;
    if(lin  >= 0 && col >=0)
    {
		criar_lista(&*listal, lin, &auxlista);
		
		buscar_mat(auxlista->celula, col, &auxmat);
	
		if(auxmat != NULL)
		    auxmat->valor = valor;
		else
		{
		    novo = (Matesp*) malloc(sizeof(Matesp));
		    novo->lin = lin;
		    novo->col = col;
		    novo->valor = valor;
	
		    if(auxlista->celula == NULL)
		    {
				novo->pl = NULL;
				auxlista->celula = novo;
		    }
		    else if(col < auxlista->celula->col)
		    {
				novo->pl = auxlista->celula;
				auxlista->celula = novo;
		    }
		    else
		    {
				antemat = auxlista->celula;
				auxmat = antemat->pl;
				while(auxmat != NULL && auxmat->col < col)
				{
				    antemat = auxmat;
				    auxmat = auxmat->pl;
				}
		
				novo->pl = auxmat;
				antemat->pl = novo;
		    }
	
		    criar_lista(&*listac, col, &auxlista);
	
		    if(auxlista->celula == NULL)
		    {
				novo->pc = NULL;
				auxlista->celula = novo;
		    }
		    else if(lin < auxlista->celula->lin)
		    {
				novo->pc = auxlista->celula;
				auxlista->celula = novo;
		    }
		    else
		    {
				antemat = auxlista->celula;
				auxmat = antemat->pc;
				while(auxmat != NULL && auxmat->lin < lin)
				{
				    antemat = auxmat;
				    auxmat = auxmat->pl;
				}
		
				novo->pc = auxmat;
				antemat->pc = novo;
		    }
		}
    }
}

void libera_nulls(Lista ** l)
{
	Lista * aux, *aux2;
	if(*l != NULL)
	{
	
		if((*l)->celula == NULL)
		{
			aux = *l;
			*l = (*l)->prox;
			free(aux);
		}
		else
		{
			aux2 = *l;
			while(aux2 != NULL)
			{
				if(aux->celula == NULL)
				{
					aux = aux2;
					aux2 = aux2->prox;
					free(aux);
				}
				
				if(aux2 != NULL)
					aux2 = aux2->prox;
			}
		}	
	}
	
}

void buscar_lista(Lista * l, int index, Lista **l2)
{
	while(l != NULL && l->index < index)
		l = l->prox;
		
	if(l != NULL && l->index == index)
		*l2 = l;
	else
		*l2 = NULL;		
}

void excluir(Lista ** listal, Lista ** listac, int lin, int col)
{
	Lista * auxlista;
	Matesp * ante, * atual, *matdel;
	if(lin >= 0 && col >= 0)
	{
		buscar_lista(*listal, lin, &auxlista);
		if(auxlista != NULL)
		{
			matdel = NULL;
			
			if(auxlista->celula->col == col)
			{
				matdel = auxlista->celula;
				auxlista->celula = auxlista->celula->pl;
			}
			else
			{
				ante = auxlista->celula;
				atual = ante->pl;
				while(atual != NULL && atual->col < col)
				{
					ante = atual;
					atual = atual->pl;
				}
				
				if(atual != NULL && atual->col == col)
				{
					matdel = atual;
					ante->pl = atual->pl;	
				}
			}
			
			buscar_lista(*listac, col, &auxlista);
			if(auxlista != NULL)
			{
				if(auxlista->celula->lin == lin)
				{
					matdel = auxlista->celula;
					auxlista->celula = auxlista->celula->pc;
				}
				else
				{
					ante = auxlista->celula;
					atual = ante->pc;
					while(atual != NULL && atual->lin < lin)
					{
						ante = atual;
						atual = atual->pc;
					}
					
					if(atual != NULL && atual->lin == lin)
					{
						matdel = atual;
						ante->pc = atual->pc;
					}
				}
				
				if(matdel != NULL)
				{
					free(matdel);
					libera_nulls(&*listal);
					libera_nulls(&*listac);
				}		
			}
		}
	}
}

void excluir_range(Lista ** listal, Lista ** listac, int lini, int linf, int coli, int colf)
{
	while(lini <= linf)
	{
		while(coli <= colf)
		{
			excluir(&*listal, &*listac, lini, coli);	
			coli++;
		}
		lini++;
	}
}

void exibir_lista(Lista * l)
{
	Matesp * aux;
	while(l != NULL)
	{
		aux = l->celula;
		while(aux != NULL)
		{
			printf("- [%d] ", aux->valor);
			aux = aux->pl;
		}
		printf("\n");
		l = l->prox;
	}
}

void soma(Lista * listal1, Lista * listal2, Lista ** listal3, Lista ** listac3)
{
	Matesp * auxl1, *auxl2;
	
	while(listal1 != NULL && listal2 != NULL)
	{
		auxl1 = listal1->celula;
		auxl2 = listal2->celula;
		while(auxl1 != NULL && auxl2 != NULL)
		{
			inserir(&*listal3, &*listac3, auxl1->lin, auxl1->col, auxl1->valor + auxl2->valor);
			
			auxl1 = auxl1->pl;
			auxl2 = auxl2->pl;
		}
		
		listal1 = listal1->prox;
		listal2 = listal2->prox;
	}
}

int main(void)
{
	Lista *listal1=NULL;
	Lista * listac1=NULL;
	
	Lista *listal2=NULL;
	Lista * listac2=NULL;
	
	Lista *listal3=NULL;
	Lista * listac3=NULL;
	
	int i, j;
	for(i=0 ; i < 3 ; i++)
		for(j=0 ; j < 3 ; j++)
			inserir(&listal1, &listac1, i, j, i+j);
	
	for(i=0 ; i < 3 ; i++)
		for(j=0 ; j < 3 ; j++)
			inserir(&listal2, &listac2, i, j, j+i);
			
	soma(listal1, listal2, &listal3, &listac3);
	
//	excluir_range(&listal, &listac, 1, 1, 5, 9);
	
	exibir_lista(listal1);
	printf("\n\n");
	exibir_lista(listal2);
	printf("\n\n");
	exibir_lista(listal3);
}
