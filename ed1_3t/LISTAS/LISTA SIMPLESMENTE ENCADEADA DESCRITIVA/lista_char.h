struct PtPont
{
	char info;
	PtPont *prox;
};

struct Descritiva
{
	int cont;
	PtPont *inicio, *fim;	
};

PtPont *criaCaixa(char dado)
{
	PtPont *novo = new PtPont;
	novo->prox = NULL;
	novo->info = dado;
	
	return novo;
}

void iniciarDesc(Descritiva &desc)
{
	desc.cont=0;
	desc.inicio=NULL;
	desc.fim = NULL;
}

void inserirOrdenado(Descritiva &desc)
{
	system("cls");
	
	printf("INSERIR ORDENADO\n\n");
	char elem = getche();
	while(elem != 27)
	{
		PtPont *novoDado = criaCaixa(elem);
		
		if(desc.cont == 0)
		{
			desc.inicio = novoDado;
			desc.fim = novoDado;
		}
		else if(desc.inicio->info >= novoDado->info)
		{
			novoDado->prox = desc.inicio;
			desc.inicio = novoDado;
		}
		else if(desc.fim->info <= novoDado->info)
		{
			desc.fim->prox = novoDado;
			desc.fim = novoDado;
		}
		else
		{
			PtPont *no = desc.inicio;
			while(no->prox->info < novoDado->info)
				no = no->prox;
			
			novoDado->prox = no->prox;
			no->prox = novoDado;	
		}
		
		desc.cont++;
		
		fflush(stdin);	elem = getche();
	}
}

void exibir(Descritiva desc)
{
	printf("INICIO EXIBICAO DA LISTA: ");
	PtPont *no = desc.inicio;
	while(no != NULL)
	{
		printf("[%c]", no->info);
		no = no->prox;
	}
	
	printf("\n\nFIM DA EXIBICAO DA LISTA.");
}
