// -------------------------------------------- lista variaveis prototipo funcao --------------------
struct lista_vars_prototipo_func
{
	int tipo; // 0 void - 1 int - 2 float - 3 char - 4 double
	StrDin * nome;
	char pont;
	StrDin * valor;
	int endereco;
	int valor_endereco;
	
	struct  lista_vars_prototipo_func * prox;
};
typedef struct lista_vars_prototipo_func pVars_prototipo;

void init_lista_vars_argumento_func(pVars_prototipo ** vc)
{
	*vc = NULL;
}

void inserir_lista_vars_argumento_func(pVars_prototipo ** vc, int endereco, int valor_endereco, int tipo, char pont, StrDin * nome, StrDin * valor)
{
	pVars_prototipo * novo, *aux;
	
	novo = (pVars_prototipo*) malloc(sizeof(pVars_prototipo));
	novo->tipo = tipo;
	novo->nome = nome;
	novo->pont = pont; //ponteiro?
	novo->valor =valor;
	novo->endereco = endereco;
	novo->valor_endereco = valor_endereco;
	novo->prox = NULL;
	
	if(*vc == NULL)
		*vc = novo;
	else
	{
		aux = *vc;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}	
}

pVars_prototipo * search_lista_vars_argumento_func_chars(pVars_prototipo * vc, char * nome)
{
	while(vc != NULL && !str_igual(vc->nome, nome))
		vc = vc->prox;
		
	return vc;	
}

void remover_inicio(pVars_prototipo **vc)
{
	pVars_prototipo * aux;
	
	if(*vc != NULL)
	{
		reinit_str(&(*vc)->nome);
		reinit_str(&(*vc)->valor);
		
		aux = *vc;
		*vc = (*vc)->prox;
		free(aux);
	}
}

void reinit_lista_vars_argumento_func_rec(pVars_prototipo **vc)
{
	pVars_prototipo * aux;
		
	if(*vc != NULL)
	{
		reinit_str(&(*vc)->nome);
		reinit_str(&(*vc)->valor);
		
		aux = *vc;
		*vc = (*vc)->prox;
		free(aux);
		
		reinit_lista_vars_argumento_func_rec(&*vc);
	}
}

void copy_lista_vars_prototipo_all(pVars_prototipo **destino, pVars_prototipo * origin)
{
	StrDin * nome;
	StrDin * valor;
	int endereco;
	int valor_endereco;
	
	//destino inicido la fora
	while(origin != NULL)
	{
		endereco = origin->endereco;
		valor_endereco = origin->valor_endereco;
			
		init_str(&nome);
		copy_str_rec(&nome, origin->nome);
		
		init_str(&valor);
		copy_str_rec(&valor, origin->valor);
		
		inserir_lista_vars_argumento_func(&*destino, endereco, valor_endereco, origin->tipo, origin->pont , nome, valor);
		
		origin = origin->prox;
	}
}
