// -------------------------------------------- lista funcoes --------------------
struct lista_funcoes
{
	int tipo; // 0 void - 1 int - 2 float - 3 char - 4 double
	int linha;
	int cont_execucao; //total de linhas executadas
	int cont_linhas; //total de linhas na funcao
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

void inserir_lista_func_fim(pListaFunc ** ls, int linha, int cont_linhas, int tipo, StrDin * nome, pVars_prototipo * vars_parametro, 
	pLinhas_func * pListaLinhas_func)
{
	pListaFunc * novo, *aux;
	
	novo = (pListaFunc*) malloc(sizeof(pListaFunc));
	novo->prox  = NULL;
	novo->tipo = tipo;
	novo->linha = linha;
	novo->cont_linhas = cont_linhas;
	novo->cont_execucao = 0;
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


void inserir_lista_func_inicio(pListaFunc ** ls, int linha, int cont_linhas, int tipo, StrDin * nome, pVars_prototipo * vars_parametro, 
	pLinhas_func * pListaLinhas_func)
{
	pListaFunc * novo, *aux;
	
	novo = (pListaFunc*) malloc(sizeof(pListaFunc));
	novo->tipo = tipo;
	novo->linha = linha;
	novo->cont_linhas = cont_linhas;
	novo->cont_execucao = 0;
	novo->nome = nome;
	//exibir_str(nome);
	novo->pListaVars_prototipo = vars_parametro;
	novo->pListaLinhas_func = pListaLinhas_func;
	
	novo->prox  = *ls;
	*ls = novo;
}

void remover_inicio_func_no_return(pListaFunc ** pListaFuncChamadas)
{
	pListaFunc * aux;
	
	if(*pListaFuncChamadas != NULL)
	{
		reinit_lista_vars_argumento_func_rec(&(*pListaFuncChamadas)->pListaVars_prototipo);
		remover_todas_linhas_interna_func_rec(&(*pListaFuncChamadas)->pListaLinhas_func);
		reinit_str(&(*pListaFuncChamadas)->nome);
		
		aux = *pListaFuncChamadas;
		*pListaFuncChamadas = (*pListaFuncChamadas)->prox;
		free(aux);
		
	}
}

pListaFunc * buscar_lista_funcao_nome_chars(pListaFunc * l, char * nome)
{
	StrDin * str;
	int i;
	
	init_str(&str);
	for(i=0 ; nome[i] != '\0' && nome[i] != '\n' ;i++ )
		inserir_char(&str, nome[i]);
	
	while(l != NULL && !strdin_igual(l->nome, str))
		l = l->prox;
		
	reinit_str(&str);	
		
	return l;	
}

pListaFunc * copy_funcao(pListaFunc * origin)
{
	pListaFunc * nova_func;
	StrDin * nome;
	int tipo, linha;
	pVars_prototipo * lista_prototipo;
	pLinhas_func * listaLinhas_func;
	int cont_linhas;
	int cont_execucao;
	
	init_lista_func(&nova_func);
	init_str(&nome);
	init_lista_vars_argumento_func(&lista_prototipo);
	init_lista_linhas_interna_func(&listaLinhas_func);
	
	cont_linhas = origin->cont_linhas;
	tipo = origin->tipo;
	linha = origin->linha;
	copy_str_rec(&nome, origin->nome);
	copy_lista_vars_prototipo_all(&lista_prototipo, origin->pListaVars_prototipo);
	copy_ListaLinhas_func(&listaLinhas_func, origin->pListaLinhas_func);
	
	inserir_lista_func_inicio(&nova_func, linha, cont_linhas, tipo, nome, lista_prototipo, listaLinhas_func);
	return nova_func;
}

char isEmpty_lista_funcoes(pListaFunc * pLista_Funcoes)
{
	return pLista_Funcoes == NULL;
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
			exibir_str(pListaLinhas_func->linha);
			printf("\n");
			
			pListaLinhas_func = pListaLinhas_func->prox;
		}
		
		printf("}\n\n");
		pLista_Funcoes = pLista_Funcoes->prox;
	}
}



