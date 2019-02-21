//----------------------------------------------------- pilha de variaveis
struct lista_variaveis_execucao
{
	int endereco;
	StrDin * nome;
	StrDin * valor;
	char ponteiro;
	
	struct lista_variaveis_execucao * prox;
	
};
typedef struct lista_variaveis_execucao pListaVar;

void init_listas_vars_main(pListaVar ** lvm)
{
	*lvm = NULL;
}

void inserir_listas_vars(pListaVar ** lvm, StrDin * nome, StrDin * valor, char ponteiro)
{
	pListaVar * novo, *aux;
	
	novo = (pListaVar*) malloc(sizeof(pListaVar));
	
	novo->nome = nome;
	novo->valor = valor;
	novo->ponteiro = ponteiro;
	novo->prox = NULL;
	
	
	if(*lvm == NULL)
	{
		novo->endereco = 100;
		*lvm = novo;
	}
		
	else
	{
		aux = *lvm;
		while(aux->prox != NULL)
			aux = aux->prox;
		
		novo->endereco = aux->endereco + 4;	
		aux->prox = novo;	
	}		
}

pListaVar * search_lista_vars(pListaVar * lvm, StrDin * nome)
{
	char igual;
	
	exibir_str(nome);
	while(lvm != NULL && !strdin_igual(lvm->nome, nome))
		lvm = lvm->prox;
	
	return lvm;	
}

void exibir_listas_vars(pListaVar * lv)
{
	while(lv != NULL)
	{
		printf("%s", (lv->ponteiro==1) ? "*":" ");
		exibir_str(lv->nome);
		exibir_str(lv->valor);
		
		printf("\n");
		lv = lv->prox;
	}
}

