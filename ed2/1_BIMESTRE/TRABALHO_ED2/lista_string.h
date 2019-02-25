struct lista_de_string
{
	StrDin * str;
	struct lista_de_string * prox;
};
typedef struct lista_de_string pListaString;

void init_lista_string(pListaString ** ls)
{
	*ls = NULL;
}

void inserir_lista_string_strdin(pListaString ** ls, StrDin * str)
{
	pListaString * novo, * aux;
	
	novo = (pListaString*) malloc(sizeof(pListaString));
	novo->str = str;
	novo->prox = NULL;
	
	if(*ls == NULL)
		*ls = novo;
	else
	{
		aux = *ls;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;	
	}	
}

void exibir_lista_string(pListaString * ls)
{
//	StrDin * str;
	
	while(ls != NULL)
	{
		exibir_str(ls->str);
		ls = ls->prox;
	}
}
