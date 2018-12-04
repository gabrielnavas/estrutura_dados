//LISTA DO TIPO INT

struct Lista
{
	int char;
	Lista *prox;
};

Lista *inserirOrdenado(Lista *cabeca, char dado);

Lista *removerLista(Lista *cabeca);
Lista *removerElem(Lista *cabeca, char dado);
void exibir(Lista *cabeca);
Lista *cat(Lista *cab1, Lista *cab2);
int length(Lista *cabeca);
Lista *novaCaixa(char dado);
Lista *buscarExaustiva(Lista *cabeca, char dado);
Lista *buscaBinaria(Lista *cabeca, char chave);


Lista *removerLista(Lista *cabeca)
{
	/*
		REMOVE A LISTA TODA;
	*/
	Lista *del, *no=cabeca;
	while(no != NULL)
	{
		del = no;
		no = del->prox;
		delete(del);
	}
	
	return no;
}

Lista *removerElem(Lista *cabeca, char dado)
{
	/*
		REMOVE UM ELEMENTO DA LISTA 
		ATRAVES DE UM DADO PESQUISADO
	*/
	
	if(cabeca != NULL)
	{
		Lista *anterior=NULL;
		Lista *no = cabeca;
		while(no != NULL && no->dado != dado)
		{
			anterior = no;
			no = no->prox;
		}
		if(anterior != NULL)
			anterior->prox = no->prox;
		delete(no);
	}
	
	return cabeca;
}


void exibir(Lista *cabeca)
{
	/*
		EXIBE TODA A LISTA;
	*/
	while(cabeca != NULL)
	{
		printf("%c ", cabeca->dado);
		cabeca = cabeca->prox;
	}
}


Lista *cat(Lista *cab1, Lista *cab2)
{
	/*
		CONCATENA NA LISTA 1;
	*/
	if(cab1 != NULL)
	{
		Lista *no = cab1;
		while(no->prox != NULL)
			no = no->prox;
	
		if(cab2 != NULL)
			no->prox = cab2;
		
	}
	
	return cab1;	
}


int length(Lista *cabeca)
{
	/*
		RETORNA A QUANTIDADE DE ELEMENTOS NA LISTA;
	*/
	int i=0;
	while(cabeca != NULL)
	{
		cabeca = cabeca->prox;
		i++;
	}
	return i;
}


Lista *novaCaixa(int dado)
{
	/*
		RETORNA UM PONTEIRO APONTANDO PARA 
		UM DADO NA MEMORIA
	*/
	Lista *novo = new Lista;
	
	novo->dado = dado;
	novo->prox = NULL;
	
	return novo;
}

Lista *buscarExaustiva(Lista *cabeca, char dado)
{
	/*
		BUSCA UM ELEMENTO 
		MODO EXAUSTIVO
	*/
	while(cabeca != NULL && cabeca->dado != dado)
		cabeca = cabeca->prox;
	
	if(cabeca != NULL)
		return cabeca;
	else
		return NULL;		
}


Lista *inserirOrdenado(Lista *cabeca, char dado)
{
	/*
		INSERE JA ORDENADO
	*/
	Lista *newDado = novaCaixa(dado);

	if(cabeca == NULL)
		cabeca = newDado;
	else
	{
		Lista *no = cabeca;
		Lista *ante = NULL;

		while(no != NULL && newDado->dado > no->dado)
		{
			ante = no;
			no = no->prox;
		}

		if(no != NULL)
		{
			if(ante == NULL)
				cabeca = newDado;
			else
				ante->prox = newDado;
				
			newDado->prox = no;
		}
		else
			ante->prox = newDado;
	}

	return cabeca;
}

int listaLen(Lista *cabeca)
{
	int i=0;
	while(cabeca != NULL)
	{
		cabeca = cabeca->prox;
		i++;
	}
		
		
	return i;	
}

Lista *buscaBinaria(Lista *cabeca, int chave)
{
	/*
		BUSCA BINARIA
	*/
	int inicio, fim, meio;
	
	inicio=0;
	fim = length(cabeca); //TAMANHO TODO DA LISTA
	meio = (fim/2) - 1; //PEGO O MEIO 
	
	Lista *ptMeio=cabeca;// COMECO APONTANDO PARA A CABECA
	for(int i=0 ; i < meio ; i++, ptMeio = ptMeio->prox);// APONTO PARA O MEIO DA LISTA
	
	while(inicio < fim && ptMeio->dado != chave)
	{
		printf("%d", ptMeio->dado);
		if(ptMeio->dado > chave)
			fim = meio-1;
		else
			inicio = meio+1;
		
		meio = ((inicio+fim)/2) -1; //PEGO O MEIO NOVAMENTE
		
		ptMeio=cabeca; //COMECO APONTANDO PARA A CABECA
		for(int i=0 ; i < meio ; i++, ptMeio = ptMeio->prox);	// APONTO PARA O MEIO DA LISTA	
	}
	
	if(inicio < fim && ptMeio->dado == chave)
		return ptMeio;
	else
		return NULL;	
}
