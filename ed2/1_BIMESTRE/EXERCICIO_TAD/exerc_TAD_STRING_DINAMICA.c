#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>
#include<string.h>

struct stringDin
{
	char ch;
	struct stringDin * prox;
};

typedef struct stringDin StrDin;

void init(StrDin ** str)
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
		reinit_str_rec(&(*str)->prox); //aqui tanto faz? reinit_rec(  (*str)->prox);
		free(*str);
		*str=NULL;
	}
}

void exibir(StrDin * str)
{
	while(str != NULL)
	{
		printf("%c", str->ch);
		str = str->prox;
	}
}

void exibir_rec(StrDin * str)
{
	if(str != NULL)
	{
		printf("%c", str->ch);
		exibir_rec(str->prox);
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
	int count;
	while(str != NULL)
	{
		count ++;
		str=str->prox;
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

void copy_str(StrDin ** dest, StrDin * origin)
{
	while(origin != NULL)
	{
		inserir_char( &(*dest), origin->ch );
		origin = origin->prox;
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

void remover_chars_position(StrDin ** str, int index, int quant)
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

char str_igual(StrDin *str1, StrDin *str2)
{
	while(str1 != NULL && str2 != NULL && str1->ch == str2->ch)
	{
		str1 = str1->prox;
		str2 = str2->prox;
	}
	
	return str1 == str2; // NULL == NULL ?
}

char str_menor(StrDin *str1, StrDin *str2)
{
	return count_str_rec(str1) < count_str_rec(str2);
}

int where_start_local_str(StrDin *str, StrDin *str_sub)
{
	StrDin * str_compara, *aux;
	int index, i, index_aux;
	char achou;
	
	init(&str_compara);
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

int main()
{
	StrDin * str, *str2;
	init(&str);
	init(&str2);
	
	char line1[] = "#";
	int i;
	for(i=0 ; i < strlen(line1); i++)
			inserir_char(&str2, line1[i]);
	
	char *line2 = "void funcao(int x, int y){";
	for(i=0 ; i < strlen(line2); i++)
			inserir_char(&str, line2[i]);
			
	int pos = where_start_local_str(str, str2);
	printf("%d", pos);		
	
    return 0;
}


