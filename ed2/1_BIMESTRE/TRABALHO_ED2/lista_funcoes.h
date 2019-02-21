// -------------------------------------------- lista funcoes --------------------
struct lista_funcoes
{
	int tipo; // 0 void - 1 int - 2 float - 3 char - 4 double
	int linha;
	StrDin * nome;
	
	pVars_prototipo * pListaVars_prototipo;
	pLinhas_func * pListaLinhas_func;	
	
	
	struct lista_funcoes *prox;
};
typedef struct lista_funcoes pListaFunc;

void init_lista_func(pListaFunc ** ls)
{
	*ls = NULL;
}

void inserir_lista_func(pListaFunc ** ls, int linha, int tipo, StrDin * nome, pVars_prototipo * vars_parametro, 
	pLinhas_func * pListaLinhas_func)
{
	pListaFunc * novo, *aux;
	
	novo = (pListaFunc*) malloc(sizeof(pListaFunc));
	novo->prox  = NULL;
	novo->tipo = tipo;
	novo->linha = linha;
	novo->nome = nome;
	//exibir_str(nome);
	novo->pListaVars_prototipo = vars_parametro;
	novo->pListaLinhas_func = pListaLinhas_func;
	
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

void mostrar_lista_funcao(pListaFunc * pLista_Funcoes)
{
	pVars_prototipo * pListaVars_prototipo;
	pLinhas_func * pListaLinhas_func;

	while(pLista_Funcoes != NULL)
	{
		printf("linha: %d - ", pLista_Funcoes->linha);
		
		// 0 void - 1 int - 2 float - 3 char - 4 double
		switch(pLista_Funcoes->tipo)
		{
			case 0: printf("void "); break;
			case 1: printf("int "); break;
			case 2: printf("float "); break;
			case 3: printf("char "); break;
			case 4: printf("double "); break;
		}	
		
		exibir_str(pLista_Funcoes->nome);
		printf("(");
		
		pListaVars_prototipo = pLista_Funcoes->pListaVars_prototipo;
		while(pListaVars_prototipo != NULL)
		{
			switch(pListaVars_prototipo->tipo)
			{
				case 0: printf("void"); break;
				case 1: printf("int"); break;
				case 2: printf("float"); break;
				case 3: printf("char"); break;
				case 4: printf("double"); break;
			}
			
			printf("%s", (pListaVars_prototipo) ? " *" : " ");
			
			exibir_str(pListaVars_prototipo->nome);
			
			pListaVars_prototipo = pListaVars_prototipo->prox;
			
			if(pListaVars_prototipo != NULL)
				printf(", ");
		}
		printf(")");
		printf("{\n");
		
		pListaLinhas_func = pLista_Funcoes->pListaLinhas_func;
		while(pListaLinhas_func != NULL)
		{
			printf("%d", pListaLinhas_func->tipo);
			exibir_str(pListaLinhas_func->linha);
			printf("\n");
			
			pListaLinhas_func = pListaLinhas_func->prox;
		}
		
		printf("}\n\n");
		pLista_Funcoes = pLista_Funcoes->prox;
	}
}

