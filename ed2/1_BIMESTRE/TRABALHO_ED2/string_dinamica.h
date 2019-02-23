// --------------------------------------------- string dinamica ---------------------------
struct stringDin
{
	char ch;
	struct stringDin * prox;
};
typedef struct stringDin StrDin;

void init_str(StrDin ** str)
{
	*str = NULL;
}

void reinit_str(StrDin ** str)
{
	StrDin * aux;
	
	while(*str != NULL)
	{
		aux = *str;
		*str = (*str)->prox;
		free(aux);	
	}
}

void reinit_str_rec(StrDin ** str)
{
	if(*str != NULL)
	{
		reinit_str_rec(&(*str)->prox);
		free(*str);
		*str=NULL;
	}
}


void exibir_str_rec(StrDin * str)
{
	if(str != NULL)
	{
		printf("%c", str->ch);
		exibir_str_rec(str->prox);
	}
}

void exibir_reverso_rec(StrDin * str)
{
	if(str != NULL)
	{
		exibir_reverso_rec(str->prox);
		printf("%c", str->ch);
	}
}

int count_str_rec(StrDin * str)
{
	if(str != NULL)
		return count_str_rec(str->prox) + 1;
}

int count_str(StrDin * str)
{
	int count=0;
	while(str != NULL)
	{
		count++;
		str=str->prox;
	}
	
	return count;
}


void exibir_str(StrDin * str)
{
	while(str != NULL)
	{
		//printf("%d", count_str(str));
		printf("%c", str->ch);
		str = str->prox;
	}
}



void inserir_char(StrDin ** str, char ch)
{
	StrDin * novo, * aux;
	
	novo = (StrDin*) malloc(sizeof(StrDin));
	novo->prox = NULL;
	novo->ch = ch;
	
	if(*str == NULL)
		*str = novo;
	else
	{
		aux = *str;
		while(aux->prox != NULL)
			aux = aux->prox;
		
		aux->prox = novo;				
	}	
}

void inserir_string(StrDin ** strdin, char *str_static)
{
	int i;
	for(i=0 ; str_static[i] != '\0' && str_static[i] != '\n' ;i++)
		inserir_char(&*strdin, str_static[i]);
}


StrDin * vetchar_to_strDin(char *str)
{
	StrDin * novo = NULL;
	
	int i=0;
	while(str[i] != '\n' && str[i] != '\0')
	{
		inserir_char(&novo, str[i]);
		i++;
	}	
	return novo;	
}

void copy_str(StrDin ** dest, char * origin)
{
	int i;
	
	i=0;
	while(i < strlen(origin))
	{
		inserir_char( &(*dest), origin[i] );
		i++;
	}
}

void copy_str_rec(StrDin ** dest, StrDin * origin)
{
    if(origin != NULL)
    {
		inserir_char(&(*dest), origin->ch);
		origin = origin->prox;
    }
}

void concat_2str(StrDin * str1, StrDin * str2, StrDin ** str_out)
{
    while(str2 != NULL)
    {
		inserir_char(&str1, str2->ch);
		str2 = str2->prox;
    }

    *str_out = NULL;
    copy_str_rec(&(*str_out), str1);
}

void remover_chars_posicao(StrDin ** str, int index, int quant)
{
    // O INDEX CONTA COMO DELETADO TAMBEM?? OU EH APARTIR DE INDEX?
    StrDin *aux, *ante;
    int i, tl;
    
    //tl = count_str_rec(str);

    if(index == 0)
    {
		i=0;
		while(*str != NULL && i < quant)
		{
		    aux = *str;
		    *str = (*str)->prox;
		    free(aux);
		    i++;
		}
    }
    else
    {
		i=0;
		ante=NULL;
		aux = *str;
		while(aux != NULL && i < index)
		{
		    ante = aux;
		    aux = aux->prox;
		    i++;
		}
	
		i=0;
		while(aux != NULL && i < quant)
		{
		    ante->prox = aux->prox;
		    free(aux);
		    i++;
	
		    aux = ante->prox;
		}
    }
}

void insere_sub_string(StrDin ** str, StrDin * str_sub, int index)
{
	int i;
	StrDin *aux, *ante, *str_sub_f;
	
	if(index == 0)
	{
		aux = str_sub;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = *str;
		*str = str_sub;	
	}
	else if(index > 0)
	{
		i=0;
		aux = *str;
		ante = NULL;
		while(aux != NULL && i < index)
		{
			ante = aux;
			aux = aux->prox;
			i++;
		}
		
		str_sub_f = str_sub;
		while(str_sub_f->prox != NULL)
			str_sub_f = str_sub_f->prox;
		
		ante->prox = str_sub;	
		str_sub_f->prox = aux;
	}
}

char strdin_igual(StrDin *str1, StrDin *str2)
{
	while(str1 != NULL && str2 != NULL &&
		str1->ch == str2->ch)
	{
		str1 = str1->prox;
		str2 = str2->prox;
	}
	
	if(str1 == NULL && str2 == NULL) //igual
		return 1;
	return 0;	
}

char str_igual(StrDin *str1, char *str2) //nao funciona.
{
	int i;
	
	i=0;
	while(str1 != NULL && i < strlen(str2) && str1->ch == str2[i])
	{
		str1 = str1->prox;
		i++;
	}
	
	return str1 == NULL && i == strlen(str2); // NULL == NULL ?
}

char str_menor(StrDin *str1, StrDin *str2)
{
	return count_str_rec(str1) < count_str_rec(str2);
}

int onde_comeca_strdin_local(StrDin *str, StrDin *str_sub)
{
	StrDin * str_compara, *aux;
	int index, i, index_aux;
	char achou;
	
	init_str(&str_compara);
	i = 0;
	index = -1;
	achou = 0;
		
	do
	{
		aux = str_sub;
		
		if(str->ch == aux->ch)
		{
			index_aux = i;
			while(str != NULL && aux != NULL && str->ch == aux->ch)
			{
				inserir_char(&str_compara, str->ch);
				str = str->prox;
				aux = aux->prox;
				i++;
			}
			
			if(strdin_igual(str_compara, str_sub))
			{
				achou = 1;
				index = index_aux;
			}
				
			reinit_str_rec(&str_compara);		
		}
		
		if(str != NULL)
		{
			str = str->prox;
			i++;
		}
			
	}while(str != NULL && aux != NULL && !achou);
	
	return index;
}


int onde_comeca_str_local(StrDin *str, char *str_sub) //fazer depois
{
	StrDin * str_compara, *aux;
	int index, i, index_aux;
	char achou;
	
	init_str(&str_compara);
	i = 0;
	index = -1;
	achou = 0;
		
	do
	{
		if(i < strlen(str_sub) && str->ch == str_sub[i])
		{
			index_aux = i;
			while(str != NULL && i < strlen(str_sub) && str->ch == str_sub[i])
			{
				inserir_char(&str_compara, str_sub[i]);
				str = str->prox;
				i++;
			}
			
			if(str_igual(str_compara, str_sub))
			{
				achou = 1;
				index = index_aux;
			}
				
			reinit_str_rec(&str_compara);		
		}
		
		if(str != NULL)
		{
			str = str->prox;
			i++;
		}
			
	}while(str != NULL && aux != NULL && !achou);
	
	return index;
}


