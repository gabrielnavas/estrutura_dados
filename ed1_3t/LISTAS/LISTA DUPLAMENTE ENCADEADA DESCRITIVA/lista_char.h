struct PtPont
{
	char info;
	PtPont *prox, *ante;
};

struct Descritor
{
	PtPont *inicio, *fim;
	int cont;
};

PtPont *criaCaixa(char elem);
void inserirOrdenado(Descritor &desc);
void exibir(Descritor desc);
void iniciar(Descritor &desc);
void removerAll(Descritor &desc);

void removerElem(Descritor &desc)
{
	if(desc.cont > 0)
	{
		printf("\nELEMENTO: ");
		fflush(stdin);	char elem = getche();
		
		while(elem != 27)
		{
			if(desc.inicio->info == elem)
			{
				desc.inicio = desc.inicio->prox;
				delete(desc.inicio->ante);
				desc.inicio->ante = NULL;
				desc.cont--;
			}
			else if(desc.fim->info == elem)
			{
				desc.fim = desc.fim->ante;
				delete(desc.fim->prox);
				desc.fim->prox = NULL;
				desc.cont--;
			}
			else
			{
				PtPont *no = desc.inicio;
				while(no->prox->info != elem && no->prox != NULL)
					no = no->prox;
				
				if(no->prox->info == elem)	
				{
					PtPont *deletar = no->prox;
					deletar->ante->prox = deletar->prox;
					deletar->prox->ante = deletar->ante;
					delete(deletar);	
					
					desc.cont--;
					
					exibir(desc);	
				}
				
			}
			

			fflush(stdin);	elem = getche();
		}	
	}
}

void removerAll(Descritor &desc)
{
	if(desc.cont == 1)
	{
		delete(desc.inicio);
		desc.inicio = NULL;
		desc.fim = NULL;
	}
	else if(desc.cont > 1)
	{
		desc.fim = desc.inicio->prox;
		while(desc.fim != NULL)
		{
			desc.cont--;
			
			delete(desc.inicio);
			
			desc.inicio = desc.fim;
			desc.fim = desc.fim->prox;
		}	
	}
	
}

PtPont *criaCaixa(char elem)
{
	PtPont *nv = new PtPont;
	nv->prox = NULL;
	nv->ante = NULL;
	nv->info = elem;
	
	return nv;
}

void iniciar(Descritor &desc)
{
	desc.inicio = NULL;
	desc.fim = NULL;
	desc.cont=0;
}

void inserirOrdenado(Descritor &desc)
{
	system("cls");
	printf("INSERIR ORDENADO\n");
	fflush(stdin);	int elem = getch();
	while(elem != 27)
	{
		PtPont *novo = criaCaixa(elem);
		if(desc.cont == 0)
		{
			desc.inicio = novo;
			desc.fim = novo;
		}
		else if(desc.inicio->info >= novo->info)
		{
			novo->prox = desc.inicio;
			desc.inicio->ante = novo;
			desc.inicio = novo;
		}
		else if(desc.fim->info <= novo->info)
		{
			novo->ante = desc.fim;
			desc.fim->prox = novo;
			desc.fim = novo;
		}
		else
		{
			PtPont *no = desc.inicio;
			while(no->prox->info < novo->info)
				no = no->prox;
				
			novo->prox = no->prox;
			novo->ante = no;
			no->prox->ante = novo;
			no->prox = novo;				
		}
		
	
		desc.cont++;
		
		printf("\n\n");
		exibir(desc);
		printf("\n\n");
		
		elem = getch();
	}
	
	printf("FIM DE INSErCAO");
}

void exibir(Descritor desc)
{
	if(desc.cont > 0)
	{
		printf("INICIO DA LISTA\n");
		PtPont *no = desc.inicio;
		while(no->prox != NULL)
		{
			printf("[%c]", no->info);
			no = no->prox;
		}
		printf("\nFIM DA LISTA");
	}
	
}
