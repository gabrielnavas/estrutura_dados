// -------------------------------------------- lista variaveis prototipo funcao --------------------
struct lista_vars_prototipo_func
{
	int tipo; // 0 void - 1 int - 2 float - 3 char - 4 double
	StrDin * nome;
	char pont;
	StrDin * valor;
	
	struct  lista_vars_prototipo_func * prox;
};
typedef struct lista_vars_prototipo_func pVars_prototipo;

void init_lista_vars_argumento_func(pVars_prototipo ** vc)
{
	*vc = NULL;
}

void inserir_lista_vars_argumento_func(pVars_prototipo ** vc, int tipo, char pont, StrDin * nome, StrDin * valor)
{
	pVars_prototipo * novo, *aux;
	
	novo = (pVars_prototipo*) malloc(sizeof(pVars_prototipo));
	novo->tipo = tipo;
	novo->nome = nome;
	novo->pont = pont; //ponteiro?
	novo->valor =valor;
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


void copy_lista_vars_prototipo_all(pVars_prototipo **destino, pVars_prototipo * origin)
{
	StrDin * nome;
	StrDin * valor;
	
	//destino inicido la fora
	while(origin != NULL)
	{
		init_str(&nome);
		copy_str_rec(&nome, origin->nome);
		
		init_str(&valor);
		copy_str_rec(&valor, origin->valor);
		
		inserir_lista_vars_argumento_func(&*destino, origin->tipo, origin->pont , nome, valor);
		
		origin = origin->prox;
	}
}
