// -------------------------------------------- lista chamadas e calculos funcao --------------------
struct lista_interna_func
{
	int tipo; //0 calculo - 1 chamada de funcao;
	StrDin * linha;
	
	struct lista_interna_func * prox;	
};
typedef struct lista_interna_func pLinhas_func;

void init_lista_linhas_interna_func(pLinhas_func ** lf)
{
	*lf = NULL;
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

void copy_ListaLinhas_func(pLinhas_func ** destino, pLinhas_func * origin)
{
	StrDin * linha;
	int tipo;
	
	while(origin != NULL)
	{
		init_str(&linha);
		copy_str_rec(&linha, origin->linha);
		
		inserir_lista_linhas_interna_func(&*destino, tipo, linha);
		
		origin = origin->prox;
	}
}

