// -------------------------------------------- lista chamadas e calculos funcao --------------------
struct lista_interna_func
{
	/*0 calculo - 
	1 chamada de funcao - 
	2 printf - 
	3 declaracao variavel - 
	4 - return function -
	5 - chamda de funcao com retorno para variavel
	*/
	int tipo; 
	StrDin * linha;
	
	struct lista_interna_func * prox;	
};
typedef struct lista_interna_func pLinhas_func;

void init_lista_linhas_interna_func(pLinhas_func ** lf)
{
	*lf = NULL;
}

void reinit_lista_linhas_interna_func(pLinhas_func ** lf)
{
	pLinhas_func * aux;
	if(*lf != NULL)
	{
		aux = *lf;
		*lf = (*lf)->prox;
		free(aux);
		reinit_lista_linhas_interna_func(&*lf);
	}
}

void inserir_lista_linhas_interna_func(pLinhas_func ** lf, int tipo, StrDin * linha)
{
	pLinhas_func * novo, *aux;
	
	novo = (pLinhas_func*) malloc(sizeof(pLinhas_func));
	novo->tipo = tipo;
	novo->linha = linha;
	novo->prox = NULL;
	
	if(*lf == NULL)
		*lf = novo;
	else
	{
		aux = *lf;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}	
}

void remover_inicio_linhas_interna_func_no_return(pLinhas_func ** lf)
{
	pLinhas_func * aux;
	
	if(*lf != NULL)
	{
		reinit_str(&(*lf)->linha);
		aux = *lf;
		*lf = (*lf)->prox;
		free(aux);	
	} 
}

void remover_todas_linhas_interna_func_rec(pLinhas_func ** l)
{
	pLinhas_func * aux;
	
	if(*l != NULL)
	{
		aux = *l;
		*l = (*l)->prox;
		free(aux);
		remover_todas_linhas_interna_func_rec(&*l);
	}
}

void remove_inicio_lista_linhas_interna_func(pLinhas_func ** lf)
{
	pLinhas_func * aux;
	
	if(*lf != NULL)
	{
		aux = *lf;
		*lf = (*lf)->prox;
		free(aux);
	}
	
}

char isEmpty_lista_linhas_interna_func(pLinhas_func * lf)
{
	return lf == NULL;
}

void copy_ListaLinhas_func(pLinhas_func ** destino, pLinhas_func * origin)
{
	StrDin * linha;
	int tipo;
	
	while(origin != NULL)
	{
		init_str(&linha);
		copy_str_rec(&linha, origin->linha);
		tipo = origin->tipo;
		
		inserir_lista_linhas_interna_func(&*destino, tipo, linha);
		
		origin = origin->prox;
	}
}

