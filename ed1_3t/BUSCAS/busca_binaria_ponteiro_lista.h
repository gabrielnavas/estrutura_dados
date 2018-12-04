//BUSCA BINARIA COM PONTEIRO

struct Lista
{
	char info;
	Lista *prox;
};


Lista *buscaBinaria(Lista *cabeca, int key)
{
	if(cabeca != NULL)
	{
		
		int inicio = 0;
		int fim;
		Lista *getFim = cabeca;
		for(fim=0 ; getFim != NULL ; fim++, getFim = getFim->prox);
		int meio = fim/2;
		Lista *noMeio = cabeca;
		for(int i=0 ; i < meio ; i++, noMeio = noMeio->prox);
		
		while(inicio <= fim && noMeio->info != key)
		{
			printf("%d", noMeio->info);
			if(noMeio->info > key)
				fim = meio-1;
			else
				inicio = meio+1;	
			
			meio = (inicio+fim)/2;
			noMeio = cabeca;
			for(int i=0 ; i < meio ; i++, noMeio = noMeio->prox);	
		}
		printf("%d", noMeio->info);
		if(inicio <= fim && noMeio->info == key)
			return noMeio;
	}
	return NULL;	
}

