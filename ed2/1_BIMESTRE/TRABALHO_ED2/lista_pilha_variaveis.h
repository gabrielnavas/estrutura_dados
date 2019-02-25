//----------------------------------------------------- pilha de variaveis
struct lista_variaveis_execucao
{
	int endereco;
	StrDin * nome;
	StrDin * valor;
	int valor_endereco;
	char ponteiro;
	
	struct lista_variaveis_execucao * prox;
	
};
typedef struct lista_variaveis_execucao pListaVar;

void init_listas_vars_main(pListaVar ** lvm)
{
	*lvm = NULL;
}

void inserir_listas_vars(pListaVar ** lvm, StrDin * nome, StrDin * valor, int  valor_endereco, char ponteiro)
{
	pListaVar * novo, *aux;
	
	novo = (pListaVar*) malloc(sizeof(pListaVar));
	
	novo->nome = nome;
	novo->valor = valor;
	novo->valor_endereco = valor_endereco;
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

void remover_listas_vars_nome_no_return(pListaVar ** lvm, StrDin * nome) //AQUI O NOME (VAR A DELETAR) SEMPRE EXISTE. NUNCA VAI PRECISAR PROCURAR.
{
	pListaVar * ante, *atual, *aux_del;
	
	ante = NULL;
	atual = *lvm;
	
	while(atual != NULL && !strdin_igual(atual->nome, nome))
	{
		ante = atual;
		atual = atual->prox;
	}
	
	if(ante == NULL)
	{
		aux_del = *lvm;
		*lvm = (*lvm)->prox;
		free(aux_del);
	}
	else
	{
		ante->prox = atual->prox;
		free(atual);
	}
}

void change_valor_valor_lista_listas_vars(pListaVar * lvm, int valor)
{
	char str[20];
	int i;
	
	if(lvm != NULL)
	{
		sprintf(str, "%d", valor);
		reinit_str(&(lvm)->valor);
		
		i=0;
		while(str[i] != '\0' && str[i] != '\n')
			inserir_char(&lvm->valor, str[i++]);
			
//		exibir_str(lvm->valor);	
	}	
}

pListaVar * search_lista_vars_nome_strdin(pListaVar * lvm, StrDin * nome)
{
	while(lvm != NULL && !strdin_igual(lvm->nome, nome))
		lvm = lvm->prox;
	return lvm;	
}

pListaVar * search_lista_vars_nome_char(pListaVar * lvm, char * str)
{
	StrDin * nome_ = NULL;
	
	int i=0;
	while(str[i] != '\n' && str[i] != '\0')
	{
		inserir_char(&nome_, str[i]);
		i++;
	}	
	
	while(lvm != NULL && !strdin_igual(lvm->nome, nome_))
		lvm = lvm->prox;
	
	reinit_str(&nome_);
	return lvm;	
}

pListaVar * search_lista_vars_endereco(pListaVar * lvm, int endereco)
{	
	while(lvm != NULL && lvm->endereco != endereco)
		lvm = lvm->prox;
	
	return lvm;	
}

void exibir_listas_vars(pListaVar * lv)
{
	
	printf("&\tNOME\tVALOR\n");
	while(lv != NULL)
	{
		//printf("%s", (lv->ponteiro==1) ? "*":" ");
		printf("\n%d", lv->endereco);
		printf("\t");
		exibir_str(lv->nome);
		printf("\t");
		if(lv->ponteiro)
			printf("%d", lv->valor_endereco);
		else
			exibir_str(lv->valor);	
		
		lv = lv->prox;
	}
}

