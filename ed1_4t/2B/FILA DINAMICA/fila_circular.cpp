#include<stdio.h>

struct Elem
{
	int priori;
	char dado;
	
	int tempo;
};

struct TpPont
{
	Elem e;
	TpPont * ant, * prox;	
};

struct Desc
{
	TpPont * inicio, * fim;	
	int cont;
};

void iniciarDesc(Desc &d)
{
	d.inicio = d.fim = NULL;
	d.cont=0;
}

TpPont * caixa(Elem e)
{
	TpPont * novo = new TpPont;
	novo->e = e;
	novo->ant = NULL;
	novo->prox = NULL;
	return novo;
};

void exibirDesc(Desc d)
{
	if(d.inicio != NULL)
	{
		TpPont * aux = d.inicio;
		while(aux != NULL)
		{
			printf("%d %c\n", aux->e.priori, aux->e.dado);
			aux = aux->prox;
		}
	}
	else
		printf("\nNAO HA ELEMENTOS\n");
}

void inserirFila(Desc &d, Elem e)
{
	TpPont * novo = caixa(e);
	
	if(d.cont == 0)
	{
		d.fim = novo;
		d.inicio = novo;
	}	
	else
	{
		novo->ant = d.fim;
		d.fim->prox = novo;
		d.fim = novo;
		
		TpPont * atual = d.fim;
		TpPont * ante = d.fim->ant;
		while(ante != NULL && atual->e.priori < ante->e.priori)
		{
			Elem auxE = atual->e;
			atual->e = ante->e;
			ante->e = auxE;
			
			atual = ante;
			ante = ante->ant;
		}
	}
	
	d.cont++;
}

Elem removerFila(Desc d)
{
	TpPont * del;
	Elem e;
	
	if(d.cont == 1)
	{
		e = d.inicio->e;
		del = d.inicio;
		d.inicio = d.fim = NULL;
	}
	else
	{
		e = d.inicio->e;
		del = d.inicio;
		d.inicio = d.inicio->prox;
		d.inicio->ant=NULL;
	}
	
	delete(del);
	
	return e;		
}

int vazia(Desc d)
{
	return d.cont == 0;
}

int main(void)
{
	Desc desc;
	iniciarDesc(desc);
	
	FILE *arq = fopen("arq_priori.txt", "r");
	
	Elem e;
	int ut=1;
	
	do
	{
		if(ut % 3 == 0 && !feof(arq))
		{
			fscanf(arq, "%d %c %d", &e.priori, &e.dado, &e.tempo);
			inserirFila(desc, e);
		
			printf("\nINSERIU ALGUEM");
		}
		else if(ut % 7 == 0 && !vazia(desc))
		{
			Elem eProc = removerFila(desc);
			for(int i=0 ; i < eProc.tempo ; i++)
			{
				if(ut % 3 == 0 && !feof(arq))
				{
					fscanf(arq, "%d %c %d", &e.priori, &e.dado, &e.tempo);
					inserirFila(desc, e);
					
					printf("\nINSERIU ALGUEM");
				}
				
				ut++;
				printf("\nATENDENDO ALGUEM...");
			}
		}
		
		ut++;
	}while(!feof(arq));
	
	fclose(arq);
}
