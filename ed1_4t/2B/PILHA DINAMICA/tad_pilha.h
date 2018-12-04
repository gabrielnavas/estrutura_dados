#include<stdio.h>

struct TpPilha
{
	char dado;
	TpPilha * prox;
};

TpPilha * inicia(TpPilha * p)
{
	return NULL;
}

char elemTopo(TpPilha * p)
{
	return p->dado;
}

char vazia(TpPilha *p)
{
	return p == NULL;
}

char retirar(TpPilha * p)
{
	char aux = p->dado;
	TpPilha *pAux = p;
	p = p->prox;
	delete(pAux);
	return aux;
}

TpPilha * inserir(TpPilha * p, char dado)
{
	TpPilha *novo = new TpPilha;
	novo->dado = dado;
	
	novo-> = p;
	p = novo;
	return p;	
}

void exibir(TpPilha *p)
{
	while(p != NULL)
	{
		printf("%c", p->dado);
		p=p->prox;
	}
}

int main(void)
{
	
}
