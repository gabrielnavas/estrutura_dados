struct Elem
{
	int tempoAtendimento;
	int tempoUt;
	char priori;
	int id;	
};

struct TpPont
{
	Elem e;
	TpPont *ante, *prox;
};

struct Descritor
{
	int cont;
	int totAtend;
	
	TpPont * inicio, *fim;
};

void iniciar(Descritor &d)
{
	d.cont= d.totAtend = 0;
	d.inicio = d.fim = NULL;
}

TpPont * criarCaixa(Elem e)
{
	TpPont * novo = new TpPont;
	novo->e = e;
	novo->ante = novo->prox = NULL;
}

void inserir(Descritor &d, Elem e)
{
	TpPont * novo = criarCaixa(e);
	
	if(d.cont == 0)
		d.inicio = d.fim = novo;
	else
	{
		novo->ante = d.fim;
		d.fim->prox = novo;
		d.fim = novo;
		
		TpPont * ante = d.fim->ante;
		TpPont * atual = d.fim;
		while(ante != NULL && atual->e.priori < ante->e.priori)
		{
			Elem eAux = atual->e;
			atual->e = ante->e;
			ante->e = eAux;	
			
			atual = ante;
			ante = ante->ante;		
		}
	}	
	
	d.cont++;
}

Elem remover(Descritor &d)
{
	Elem elem = d.inicio->e;
	TpPont * del = d.inicio;
	if(d.cont == 1)
		d.inicio = d.fim = NULL;
	else
	{
		d.inicio = d.inicio->prox;
		d.inicio->ante = NULL;
	}
	delete(del);
	d.cont--;
	return elem;
}

Elem elemInicio(Descritor d)
{
	return d.inicio->e;
}

Elem elemFim(Descritor d)
{
	return d.fim->e;
}

int vazia(Descritor d)
{
	return d.cont == 0;
}

void exibir(Descritor d)
{
	TpPont * aux = d.inicio;
	Elem elem;
	while(aux != NULL)
	{
		elem = aux->e;
		printf("%d %d %c\n", elem.id, elem.tempoAtendimento, elem.priori);
		aux = aux->prox;
	}
}

void gravarFilaArquivo(FILE *arq, Descritor d)
{
	TpPont * aux = d.inicio;
	while(aux != NULL)
	{
		Elem elem = aux->e;
		fprintf(arq, "%d %d %c\n", elem.id, elem.tempoAtendimento, elem.priori);
		aux = aux->prox;
	}
}
