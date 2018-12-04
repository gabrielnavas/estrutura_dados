#include<stdio.h>

struct TpPont
{
	char elem;
	TpPont *ant, *prox;
};

TpPont * criaCaixa(char dado)
{
	TpPont * nova = new TpPont;
	nova->da
}

TpPont * inserirOrdenado(TpPont * lista, char dado)
{
	TpPont * nova = criaCaixa(dado);
	
	if(lista==NULL)
		lista->nova;
	else if(lista->elem >= dado)
	{
		nova->prox=lista;
		lista->ant=nova;
	}
	else
	{
		TpPont * p = lista;
		while(p->prox != NULL && dado > p->elem)
			p = p->prox;
		
		if(p->prox=NULL)
		{
			p->prox=nova;
			nova->ant=p;
		}	
		else
		{
			nova->prox=p;
			nova->ant=p->ant;
			p->ant = nova;
			nova->ant->prox=nova;
		}
	}	
	
	return lista;
}
