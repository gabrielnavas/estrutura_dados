#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>
#include<string.h>

//#include "string_dinamica.h"
//#include "lista_string_dinamica.h"

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

void copy_strdin(StrDin ** dest, StrDin * origin)
{
	while(origin != NULL)
	{
		inserir_char( &(*dest), origin->ch );
		origin = origin->prox;
	}
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
	while(str1 != NULL && str2 != NULL && str1->ch == str2->ch)
	{
		str1 = str1->prox;
		str2 = str2->prox;
	}
	
	return str1 == str2; // NULL == NULL ?
}

char str_igual(StrDin *str1, char *str2)
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


// -------------------------------------------- lista variaveis prototipo funcao --------------------
struct lista_vars_prototipo_func
{
	StrDin * tipo;
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

void inserir_lista_vars_argumento_func(pVars_prototipo ** vc, StrDin * tipo, char pont, StrDin * nome, StrDin * valor)
{
	pVars_prototipo * novo, *aux;
	
	novo = (pVars_prototipo*) malloc(sizeof(pVars_prototipo));
	novo->tipo = tipo;
	novo->nome = nome;
	novo->pont = pont; //ponteiro?
	novo->valor =valor;
	
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

// -------------------------------------------- lista variaveis internas funcao --------------------
struct lista_vars_interna_func
{
	StrDin * tipo;
	StrDin * nome;
	char pont; //ponteiro??
	StrDin * valor;
	
	struct lista_vars_interna_func * prox;	
};
typedef struct lista_vars_interna_func pVars_interno;

void init_lista_vars_interna_func(pVars_interno ** vc)
{
	*vc = NULL;
}

void inserir_lista_vars_interna_func(pVars_interno ** vi, StrDin * tipo, char pont, StrDin * nome, StrDin * valor)
{
	pVars_interno * novo, *aux;
	
	novo = (pVars_interno*) malloc(sizeof(pVars_interno));
	novo->tipo = tipo;
	novo->nome = nome;
	novo->pont = pont; //ponteiro?
	novo->valor =valor;
	
	if(*vi == NULL)
		*vi = novo;
	else
	{
		aux = *vi;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}	
}

// -------------------------------------------- lista funcoes --------------------
struct lista_funcoes
{
	int linha;
	StrDin * nome;
	StrDin * tipo_retorno;
	char pont;
	
	pVars_prototipo * pVars_prototipo;
	pVars_interno * pVars_interno;	
	
	
	struct lista_funcoes *prox;
};
typedef struct lista_funcoes pListaFunc;

void init_lista_func(pListaFunc ** ls)
{
	*ls = NULL;
}

void inserir_lista_func(pListaFunc ** ls, int linha, StrDin * tipo_retorno, char pont, 
	StrDin * nome, pVars_prototipo * vars_cab, pVars_interno * vars_inter)
{
	pListaFunc * novo, *aux;
	
	novo = (pListaFunc*) malloc(sizeof(pListaFunc));
	novo->prox  = NULL;
	novo->linha = linha;
	novo->tipo_retorno = tipo_retorno;
	novo->pont = pont;
	novo->nome = nome;
	novo->pVars_prototipo = vars_cab;
	novo->pVars_interno = vars_inter;
	
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

//----------------------------------------------------- programa


//------------------------------------------------------ montar lista de funcao-------------------------
char eh_funcao(char *string)
{
	if(
		(strstr(string, "int") != NULL ||
		strstr(string, "char") != NULL ||
		strstr(string, "void") != NULL ||
		strstr(string, "float") != NULL ||
		strstr(string, "double") != NULL) && 
		strstr(string, "(") != NULL && 
		strstr(string, ")") != NULL
	)
		return 1;
		
	return 0;	
}

void get_tipo_retorno_funcao(char *string, StrDin ** pTipo, int * pos)
{
	while(*pos < strlen(string) && string[*pos] != ' ')
	{
		inserir_char(&*pTipo, string[*pos]);
		*pos++;
	}
}

void get_nome_funcao(char *string, StrDin ** nome_func, int * pos)
{
	while(*pos < strlen(string) && string[*pos] != '(')
	{
		inserir_char(&*nome_func, string[*pos]);
		*pos++;
	}
}

void get_todas_variaveis_argumento(char *string, pVars_prototipo ** vars_cab, int * pos)
{
	//inicia la fora o vars_cab
	StrDin * tipo;
	StrDin * nome;
	StrDin * valor;
	int i;
	char pont;
	char lixo[5];
	
	init_str(&tipo);
	init_str(&nome);
	init_str(&valor);
	
		
	strcpy(lixo, "lixo");
	i=0;
	for(i=0 ; i < 5 ; i++)
		inserir_char(&valor, lixo[i]);
		
	
	while(*pos < strlen(string) && string[*pos] != ')')
	{
		while(*pos < strlen(string) && string[*pos] != ',' && string[*pos] != ')')
		{
			//pega tipo aqui
			while(*pos < strlen(string) && string[*pos] != ' ')
			{
				inserir_char(&tipo, string[*pos]);
				*pos++;
			}
			
			if(string[*pos] != '*')
				pont=1;
				
			while(*pos < strlen(string) && string[*pos] != ' ')
			{
				inserir_char(&nome, string[*pos]);
				*pos++;
			}	
		}
		
		if(strlen(string) == ',' || strlen(string) == ')')
		{
			inserir_lista_vars_cabecalho_func(&*vars_cab, tipo, pont, nome, valor);
		}
	}		
}

void montar_listas_funcao(pListaFunc ** pLista_Funcoes)
{
	//VARS FUNCAO;
	pVars_prototipo *prototipo_func;
	StrDin * pTipo_func;
	StrDin * pNome;
	pVars_prototipo * pVars_argumentos;
	pVars_interno * pVars_interna;
	
	init_lista_vars_interna_func(&pVars_interna);
	init_lista_vars_argumento_func(&pVars_argumentos);
	init_str(&pTipo);
	init_str(&pNome);
	
	get_tipo_retorno_funcao(line_read, &pTipo_func, &pos_line);
	get_nome_funcao(line_read, &pNome, &pos_line)
	get_todas_variaveis_argumento(line_read, pVars_argumentos, *pos_line);
	
	inserir_lista_func(&*pFuncoes, linha, pTipo_func, 0, pNome_func, pVars_argumentos, pVars_interna);
	
	
	//liberar MEMORIA?

}

void ler_arquivo(char file_name[], pListaFunc ** pLista_Funcoes)
{
	//pLista_Funcoes iniciei la fora
	FILE * arq;
	
	char line_read[1000];
	int pos_line;
	

	arq = fopen(file_name, "r");
	
	fgets(line_read, 1000, arq);
	while(!feof(arq))
	{
		pos_line=0;
		
		if(eh_funcao(line_read))
		{
			montar_listas_funcao(&*pLista_Funcoes);
		}
			
			
		fgets(line, 1000, arq);
	}
		
		
	fclose(arq);	
}



int main()
{
	pListaFunc * funcoes;
	init_lista_func(&funcoes);

	
	ler_arquivo("programa_ler.c", &funcoes);
		
	
    return 0;
}


