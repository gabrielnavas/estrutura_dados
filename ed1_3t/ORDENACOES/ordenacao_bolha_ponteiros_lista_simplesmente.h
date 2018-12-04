//ORDENACAO BOLHA LISTA SIMPLESMENTE

struct Lista
{
	char info;
	Lista *prox;
};

Lista * ordenacao(Lista *cabeca)
{
	if(cabeca != NULL)
	{	
		Lista *ante, *atual, *fim;
		atual = cabeca;
		fim = cabeca->prox;
		while(atual->prox != NULL)
		{
	        if(atual->info > fim->info)
	        {
	            int aux = atual->info;
	            atual->info = fim->info;
	            fim->info = aux;
	        }
	
	        atual = fim;
	        fim = fim->prox;
	    }
	    fim = atual;
	
	    while(fim->info != cabeca->info)
	    {
	        ante = cabeca;
	        atual = ante->prox;
	        while(atual != fim)
	        {
	            if(ante->info > atual->info)
	            {
	                char aux = ante->info;
	                ante->info = atual->info;
	                atual->info = aux;
	            }
	            
	            ante = atual;
	            atual = atual->prox;
	        }
	        fim = ante;
	    }
	}
    return cabeca;
}
