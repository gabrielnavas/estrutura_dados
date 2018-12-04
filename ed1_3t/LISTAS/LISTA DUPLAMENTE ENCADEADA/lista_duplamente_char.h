
/*
* LISTA DUPLAMENTE ENCADEADA 	
*/

struct Lista
{
	char info;
	Lista *ante, *prox;
};

Lista *novoDado(char dado);
Lista * inserirOrdenado(Lista *cabeca, char info);
Lista * apagar(Lista *cabeca);
Lista *apagarElem(Lista *cabeca, char elem);
Lista * apagarPos(Lista *cabeca, int pos);
int length(Lista *cabeca);
void exibir(Lista *cabeca);

Lista *novoDado(char dado)
{
	Lista *novo = new Lista;
	novo->ante = NULL;
	novo->prox = NULL;
	novo->info = dado;
	
	return novo;
}

int length(Lista *cabeca)
{
	int i=0;
	while(cabeca != NULL)
	{
		i++;
		cabeca = cabeca->prox;
	}
	return i;
}

Lista *buscaBinaria(Lista *cabeca, char chave)
{
	int inicio, fim, meio;
	
	inicio = 0;
	fim = length(cabeca) - 1;
	
	meio = fim/2;
	Lista *ptrMeio = cabeca;
	for(int i=0 ; i < meio ; i++, ptrMeio = ptrMeio->prox);
	
	while(inicio < fim && ptrMeio->info != chave)
	{
		if(ptrMeio->info > chave)
			fim = meio-1;
		else
			inicio = meio+1;
		
		meio = (inicio+fim)/2;
		ptrMeio = cabeca;
		for(int i=0 ; i < meio ; i++, cabeca = cabeca->prox);	
	}
	
	if(inicio < fim && ptrMeio->info == chave)
		return ptrMeio;
	else
		return NULL;	
}

Lista *inserirInicio(Lista *cabeca, char dado)
{
	
}

Lista *inverter(Lista *cabeca)
{
	
	//////////////////////ERRADO!!
	if(cabeca != NULL)
	{
		while(cabeca->prox != NULL)
		cabeca = cabeca->prox;
		
		Lista *listaInvertida = NULL;
		while(cabeca->ante != NULL)
		{
			cabeca = cabeca->ante;
			
			
		}
			
		return 	listaInvertida;
	}
	
	return cabeca;
}

void cat(Lista *cabeca, Lista *cabeca2)
{
	if(cabeca != NULL)
	{
		Lista *no = cabeca;
		while(no->prox != NULL)
			no = no->prox;
		
		if(no->prox == NULL)
		{
			no->prox = cabeca2;
			cabeca2->ante = no;
		}	
	}
}

Lista * inserirOrdenado(Lista *cabeca, char info)
{
	Lista *novo = novoDado(info);
	if(cabeca == NULL)
		cabeca = novo;
	else
	{
		Lista *no = cabeca;
		while(no->prox != NULL && novo->info > no->info)
			no = no->ante->prox;
		
		if(novo->info >= no->info)
		{
			novo->ante = no->prox;
			no->prox = no;
		}
		else if(novo->info < no->info)
		{
			if(no->ante == NULL)
			{
				novo->prox = no;
				no->ante=novo;
				cabeca = novo;
			}
			else
			{
				novo->prox = no;
				novo->ante = no->ante;
				no->ante->prox = novo;
				no->ante = novo;
			}
		}
	}
	
	return cabeca;	 	
}

Lista * apagar(Lista *cabeca)
{
	while(cabeca->prox != NULL)
	{
		cabeca=cabeca->prox;
		delete(cabeca->ante);
	}
	delete(cabeca);
	return NULL;
}

Lista * apagarPos(Lista *cabeca, int pos)
{
	Lista *no = cabeca;
	int i=0;
	while(i < pos && no->prox != NULL)
	{
		no = no->prox;
		i++;
	}	
	
	if(i == pos)
	{
		if(no->ante == NULL)
		{
			cabeca = no->prox;
			cabeca->ante = NULL;
		}
		else if(no->prox == NULL)
			no->ante->prox = NULL;
		else
		{
			no->ante->prox = no->prox;
			no->prox->ante = no->ante;
		}		
		delete(no);
	}
	
	return cabeca;
}

Lista *apagarElem(Lista *cabeca, char elem)
{
	Lista *no = cabeca;
	while(no != NULL && no->info != elem)
		no = no->prox;
	
	if(no->info == elem)
	{
		if(no->ante == NULL)
		{
			cabeca = no->prox;
			cabeca->ante = NULL;
		}
		else if(no->prox == NULL)
			no->ante->prox = NULL;
		else
		{
			no->ante->prox = no->prox;
			no->prox->ante = no->ante;
		}
		delete(no);		
	}
	
	return cabeca;	
}


void exibir(Lista *cabeca)
{
	while(cabeca != NULL)
	{
		printf("%c ", cabeca->info);
		cabeca = cabeca->prox;
	}
}
