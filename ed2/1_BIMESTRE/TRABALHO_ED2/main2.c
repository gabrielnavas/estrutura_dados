#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "meuconio.h"
#include "string_dinamica.h"
#include "variaveis_prototipo_funcao.h"
#include "chamadas_calculos_funcao.h"


#include "lista_pilha_variaveis.h" //para guardar lista de variaveis
#include "lista_funcoes.h" // para guardar lista de declaracoes de funcoes e funcoes de chamada;
#include "lista_string.h" //para guardar printf's



//----------------------------------------------------- programa

char eh_inicio_funcao(char *string)
{
	if((strstr(string, "void") != NULL ||
		strstr(string, "char") != NULL ||
		strstr(string, "int") != NULL  ||
		strstr(string, "float") != NULL ||
		strstr(string, "double") != NULL) &&
		strstr(string, "(") != NULL &&
		strstr(string, ")") != NULL &&
		strstr(string, ";") == NULL  &&
		strstr(string, "main") == NULL )
		return 1;
	return 0;	
}

//calcula1(A,B,C,D);
char eh_chamada_de_funcao(char *string)
{
	if( strstr(string, "void") == NULL &&
		strstr(string, "char") == NULL &&
		strstr(string, "int") == NULL  &&
		strstr(string, "float") == NULL &&
		strstr(string, "double") == NULL &&
		strstr(string, "(") != NULL &&
		strstr(string, ")") != NULL &&
		strstr(string, ";") != NULL)
		return 1;
	return 0;	
}

char eh_main(char *string)
{
	if(strstr(string, "(") != NULL &&
		strstr(string, ")") != NULL &&
		strstr(string, "int") != NULL &&
		strstr(string, "main") != NULL &&
		strstr(string, ";") == NULL)
		return 1;
	return 0;	
}

char eh_calculo_in_funcao(char *string)
{
	if(strstr(string, "=") != NULL && 
		strstr(string, ";") != NULL && 
		strstr(string, "char") == NULL &&
		strstr(string, "int") == NULL  &&
		strstr(string, "float") == NULL &&
		strstr(string, "double") == NULL)
		return 1;
	return 0;	
}

char eh_printf(char *string)
{
	if(strstr(string, "printf") != NULL )
		return 1;
	return 0;	
}

char eh_declaracao_variavel_atribuicao(char *string)
{
	if(	(strstr(string, "char") != NULL ||
		strstr(string, "int") != NULL  ||
		strstr(string, "float") != NULL ||
		strstr(string, "double") != NULL) ||
		strstr(string, "=") != NULL ||
		strstr(string, ",") != NULL  &&
		strstr(string, "(") == NULL &&
		strstr(string, ")") == NULL &&
		strstr(string, ";") != NULL )
		return 1;
	return 0;	
}

char eh_algum_tipo_variavel_declaracao(char * string)
{
	if(	(strstr(string, "char") != NULL ||
		strstr(string, "int") != NULL  ||
		strstr(string, "float") != NULL ||
		strstr(string, "double") != NULL) )
		return 1;
	return 0;
}

char eh_variavel(char *string)
{
	if(	(strstr(string, "=") != NULL ||
		strstr(string, ",") != NULL )&&
		strstr(string, ";") != NULL )
		return 1;
	return 0;	
}

char eh_variavel_printf(char *string)
{
	int i;
	char variavel=1;
	if(string[0] >= '0' && string[0] <= '9')
		variavel=0;
	else
	{
		i=1;
		while(string[i] != '\0' && variavel)
		{
			if(string[i] == '_')
				i++;
			else if(string[i] >= '0' && string[i] <= '9')
				i++;
			else if(string[i] >= 'A' && string[i] <= 'Z')
				i++;
			else if(string[i] >= 'a' && string[i] <= 'z')
				i++;
			else 
				variavel =0;	
		}
		
	}
	return variavel;	
}

void int_to_chars(char *chars, int valor)
{
	sprintf(chars, "%d", valor);
}

void get_todas_variaveis_argumento(char *string, pVars_prototipo ** vars_cab, int * pos)
{
	//inicia la fora o vars_cab
	StrDin * aux_tipo;
	int tipo;
	StrDin * nome;
	StrDin * valor;
	int i;
	char pont;
	char lixo[5];
	
	pont=0;
	init_str(&aux_tipo);
	init_str(&nome);
	init_str(&valor);
	
		
	strcpy(lixo, "lixo");
	for(i=0 ; i < 5 ; i++)
		inserir_char(&valor, lixo[i]);
		
	while(string[*pos] == ' ')
		(*pos)++;

	while(*pos < strlen(string) && string[*pos] != ')')
	{
		pont=0;
		//pega tipo aqui
		while(*pos < strlen(string) && string[*pos] != ' ')
		{
//			exibir_str(aux_tipo);
//			printf("\n\n%d %c", *pos, string[*pos]);
			inserir_char(&aux_tipo, string[*pos]);
			(*pos)++;
		}
		// 0 void - 1 int - 2 float - 3 char - 4 double
		if(str_igual(aux_tipo, "void")) 
			tipo = 0;
		else if(str_igual(aux_tipo, "int"))
			tipo = 1;
		
		else if(str_igual(aux_tipo, "float"))
			tipo = 2;
		
		else if(str_igual(aux_tipo, "char"))
			tipo = 3;
			
		else if(str_igual(aux_tipo, "double"))
			tipo = 4;	
		reinit_str(&aux_tipo);
		
		while(string[*pos] == ' ')
			(*pos)++;
		
		//parametro por referencia?
		if(string[*pos] == '*')
			pont=1;
		
		while(string[*pos] == ' '|| string[*pos] == '*')
			(*pos)++;			
						   	  	  			  		   	   			   	  	  		
		//pega nome
		while(*pos < strlen(string) && string[*pos] != ' ' && string[*pos] != ',' && string[*pos] != ')')
		{
//			exibir_str(nome);
//			printf("\n\n%d %c", *pos, string[*pos]);
			inserir_char(&nome, string[*pos]);
			(*pos)++;
		}	
		
		while(string[*pos] == ' ')
			(*pos)++;
		
//		printf("\n\n");
//		exibir_str(aux_tipo);
//		printf("%c", (pont == 1) ? '*':' ');
//		exibir_str(nome);
		
		if(string[*pos] == ',' || string[*pos] == ')')
		{
			inserir_lista_vars_argumento_func(&*vars_cab, 0, tipo, pont, nome, valor);
//			printf("\n\n%d %c\n", *pos, string[*pos]);
			if(string[*pos] == ',')
				(*pos)++;
		}
		
		//DESREFERENCIO, POIS JA APONTEI ALI EM CIMA.
		init_str(&aux_tipo);
		init_str(&nome);
		
		init_str(&valor);
		for(i=0 ; i < 5 ; i++)
			inserir_char(&valor, lixo[i]);
		
		while(string[*pos] == ' ')
			(*pos)++;
	}
	
	//acaba no )		
}



void ler_funcao(pListaFunc ** pLista_Funcoes, char * line_read, /*int * pos_line, */int * linha_atual, FILE * arq)
{	
	//VARS FUNCAO;
	int pos_line;
	int linha_inicio_funcao_implementacoes;
	int pTipo_func;
	StrDin * aux_tipoFunc;
	StrDin * pNome_func;
	int cont_linhas=0;
	pVars_prototipo * pVars_argumentos;
	pLinhas_func * pLinhas_interna;
	
	init_lista_linhas_interna_func(&pLinhas_interna);
	init_lista_vars_argumento_func(&pVars_argumentos);
	init_str(&pNome_func);
	init_str(&aux_tipoFunc);
	pos_line=0;
	
	//----------------------------------PEGA TIPO
	while(line_read[pos_line] != ' ')
	{
//		exibir_str(aux_tipoFunc);
//		printf("\n%d %c\n", *pos_line, line_read[*pos_line]);
		inserir_char(&aux_tipoFunc, line_read[pos_line]);
		pos_line++;
	}
	linha_inicio_funcao_implementacoes = *linha_atual;//APAGA!---------------------------------------------------------------------
	
	// 0 void - 1 int - 2 float - 3 char - 4 double
	if(str_igual(aux_tipoFunc, "void")) 
		pTipo_func = 0;
	else if(str_igual(aux_tipoFunc, "int"))
		pTipo_func = 1;
	
	else if(str_igual(aux_tipoFunc, "float"))
		pTipo_func = 2;
	
	else if(str_igual(aux_tipoFunc, "char"))
		pTipo_func = 3;
		
	else if(str_igual(aux_tipoFunc, "double"))
		pTipo_func = 4;	
	reinit_str(&aux_tipoFunc);
	
	// -------------ESPACO ENTRE TIPO E NOME
	while(line_read[pos_line] == ' ')
		pos_line++;
	
	//-------------------------PEGA NOME
	while(line_read[pos_line] != '(')
	{
		inserir_char(&pNome_func, line_read[pos_line]);
		pos_line++;
	}
	
	linha_inicio_funcao_implementacoes = *linha_atual;//APAGA!---------------------------------------------------------------------
	// POS ( DOS ARGUMENTOS
	pos_line++;
	
	//---------------------------------PEGA VARIAVEIS DO ARGUMENTO ////
	get_todas_variaveis_argumento(line_read, &pVars_argumentos, &pos_line);
	
	
	
	// ----------------------------- PEGA IMPLEMENTACAO DA FUNCAO ----- ///
	
	//CHEGAR NO FINAL DA LINHA
	while(pos_line < strlen(line_read) && line_read[pos_line] != ')' &&
	line_read[pos_line] != '{')
	{
//			printf("\n%d %c\n", pos_line, line_read[pos_line]);
		pos_line++;
	}
		
	linha_inicio_funcao_implementacoes = *linha_atual;//APAGA!---------------------------------------------------------------------
	fgets(line_read, 100, arq);
	(*linha_atual)++;
	pos_line=0;
	
	//pega linha abre chave
	if(strstr(line_read, "{") != NULL)
	{
	
		fgets(line_read, 100, arq);
//		printf("\nposline=%d\n", (*linha_atual));
		(*linha_atual)++;
		pos_line=0;
		
	}
	
	linha_inicio_funcao_implementacoes = (*linha_atual);
	
//	exibir_str(pNome_func);
//	printf("\n%d %c\n", pos_line, line_read[pos_line]);
//	printf("%d", *linha_atual);
	//posicao atual onde inicia as implementacoes da funcao
	

	//le ate nao chegar o final da funcao
	//0 calculo - 1 chamda de funcao - 2 printf
	while(strstr(line_read, "}") == NULL)
	{
		if(eh_calculo_in_funcao(line_read))
			inserir_lista_linhas_interna_func(&pLinhas_interna, 0, vetchar_to_strDin(line_read));
		
		else if(eh_chamada_de_funcao(line_read))
			inserir_lista_linhas_interna_func(&pLinhas_interna, 1, vetchar_to_strDin(line_read));
			
		else if(eh_printf(line_read))
			inserir_lista_linhas_interna_func(&pLinhas_interna, 2, vetchar_to_strDin(line_read));
			
		else if(eh_declaracao_variavel_atribuicao(line_read))	
			inserir_lista_linhas_interna_func(&pLinhas_interna, 3, vetchar_to_strDin(line_read));
		
		fgets(line_read, 100, arq);
		(*linha_atual)++;
	}
	
	//acaba funcao ja na linha seguinte desta funcao
	if(strstr(line_read, "}") != NULL)
	{
		fgets(line_read, 1000, arq);
		(*linha_atual)++;
		cont_linhas++;
		pos_line=0;
	}
	
	//insere na lista de funcoes;
	inserir_lista_func_fim(&*pLista_Funcoes, linha_inicio_funcao_implementacoes, cont_linhas, pTipo_func, pNome_func, pVars_argumentos, pLinhas_interna, NULL);
}


void ler_todas_funcoes(char file_name[], pListaFunc ** pLista_Funcoes)
{
	//pLista_Funcoes iniciei la fora
	FILE * arq;
	
	char line_read[100];
	int pos_line, linha_atual;
	
	arq = fopen(file_name, "r");
	linha_atual=0;
	
	fgets(line_read, 100, arq);
	while(!feof(arq) && !eh_main(line_read))
	{
		//pos_line=0;
		
		if(eh_inicio_funcao(line_read))
			ler_funcao( &*pLista_Funcoes, line_read, /*&pos_line, */&linha_atual, arq);
			
		fgets(line_read, 100, arq);
		linha_atual++;
	}
			
	fclose(arq);	
}


//------------------------------------------- leitura de arquivo -------------------

void printar_arquivo_tela_pos_atual(char *file_name, int pos_atual)
{
	system("cls");
	int cont, i;
	FILE * arq = fopen(file_name, "r");
	char line[100];
	
	if(pos_atual == -1)
	{
		fgets(line, 100, arq);
		while(!feof(arq))
		{
			for(i=0 ; line[i] != '\n' && line[i] != '\0' ; i++)
				printf("%c", line[i]);
			printf("\n");	
			fgets(line, 100, arq);
		}
	}
	else if(pos_atual > 0)
	{
		cont=0;
		if(!feof(arq))
		{	
			
			fgets(line, 100, arq);
			while(cont < pos_atual)
			{
				for(i=0 ; line[i] != '\n' && line[i] != '\0' ; i++)
					printf("%c", line[i]);
				printf("\n");	
				fgets(line, 100, arq);
				cont++;
			}
			
			if(cont == pos_atual)
			{
				textbackground(4);
				
				for(i=0 ; line[i] != '\n' && line[i] != '\0' ; i++)
					printf("%c", line[i]);
				printf("\n");
					
				textbackground(0);
				
				fgets(line, 100, arq);
				while(!feof(arq))
				{
					for(i=0 ; line[i] != '\n' && line[i] != '\0' ; i++)
						printf("%c", line[i]);
					printf("\n");
					fgets(line, 100, arq);
				}
			}
			
			
		}
	}
	fclose(arq);
}


int achar_posicao_main(char *nome_program)
{
	int pos=0;
	char line[100];
	FILE * arq = fopen(nome_program, "r");
	
	fgets(line, 100, arq);
	while(!feof(arq) && !eh_main(line))
	{
		pos++;
		fgets(line, 100, arq);
	}
	
	//linha de baixo do main
	pos++;
	fgets(line, 100, arq);
	
	//abre chave?
	while(strstr(line, "{") != NULL || strlen(line) == 0)
	{
		pos++;
		fgets(line, 100, arq);
	}
		
	fclose(arq);
	return pos;
}

void posicionar_linha_implementacao_main(FILE * arq, int pos_main)
{
	char linha[100];
	fgets(linha, 100, arq);
	while(pos_main > 1)
	{
		pos_main--;
		fgets(linha, 100, arq);
	}
}

void ler_linha_arquivo_main(FILE * arq, char * linha)
{
	fgets(linha, 100, arq);
}

int line_tok(char * string, const char split[100], char saida[100][100])
{
	
	char *token = strtok(string, split);
	
	int tl=0, i;
	while( token != NULL ) {
		//printf( " %s\n", token );
		strcpy(saida[tl], token);
		token = strtok(NULL, split);
	}
	return tl;
}

char is_number(const char *str) 
{
    while(*str != '\0')
    {
        if(*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

void split_variaveis_atribuicoes(char *linha, char saida[100][100], int *tl)
{
	const char split[22] = " 	,=;";
	
	char *token = strtok(linha, split);
	int i, i_linha, j;
	while( token != NULL ) {
		//printf( "%s\n", token );
		if(! eh_algum_tipo_variavel_declaracao(token) && strcmp(token, "\n") != 0 && strcmp(token, "\0"))
			strcpy(saida[(*tl)++], token);
		token = strtok(NULL, split);
	}
}

void inserir_variaveis_declaracao_dentro_funcao(pListaVar ** pListaVars, char string[100][100], int tl)
{
	//ADD VARIAVEIS
	StrDin * nome;
	StrDin * valor;
	int endereco;
	char ponteiro;
	int i, i_linha;
	
	init_str(&nome);
	init_str(&valor);
	ponteiro=0;
	
	
	//exibir_listas_vars(*pListaVars);
	
	
	i=0;
	while(i < tl)
	{
		i_linha=0;
		valor = vetchar_to_strDin("lixo\0");
		
		//printf("%s", string[i]);
		if(strstr(string[i], "*") != NULL)
		{
			ponteiro=1;
			i_linha++;
		}
		while(i_linha < strlen(string[i])) //PEGA NOME DA VAR
		{
			//printf("%c", string[i][i_linha]);
			inserir_char(&nome, string[i][i_linha++]);
		}
		
		i++;
		
		if(i < tl && is_number(string[i])) //PEGAR VALOR SE EXISTIR
		{
			reinit_str(&valor);
			i_linha=0;
			while(i_linha < strlen(string[i]))
			{
				//printf("%c", string[i][i_linha]);
				inserir_char(&valor, string[i][i_linha++]);
			}
				
			i++;
		}
		
		//exibir_str(nome);
		//PROCURAR SE A VAR JA TA NA LISTA
		//INSERIR NA PILHA DE VARS
		pListaVar * search_nome = search_lista_vars_nome_strdin(*pListaVars, nome); 
		if(search_nome == NULL)
			inserir_listas_vars_inicio(&*pListaVars, nome, valor, 0, ponteiro); 
		else
		{
			//exibir_str(search_nome->nome);
			reinit_str(&(search_nome)->valor);
			//exibir_str(valor);
			//exibir_str(search_nome->valor);
			search_nome->valor = valor;
			//exibir_str(search_nome->valor);
		}
		
		init_str(&nome); //DESREFERENCIA POS JA ADD NA LISTA
		init_str(&valor); //DESREFERENCIA POS JA ADD NA LISTA
	}
	
	//exibir_listas_vars(*pListaVars);
}

void split_chamada_funcao(char *linha, char saida[100][100], int *tl)
{
	const char split[9] = "	 ,();&*";
	
	char *token = strtok(linha, split);
	//int i, i_linha, j;
	while( token != NULL ) {
		//printf( "%s\n", token );
		if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
			strcpy(saida[(*tl)++], token);
		token = strtok(NULL, split);
	}
}

pListaFunc * empilha_chamada_funcao(char func_chamada[100][100], pListaFunc *pListaFuncoes, 
	pListaFunc ** pListaFuncChamadas /*pilha de funcoes*/)
{
	pListaFunc * search_func;
	pListaFunc * copia_funcao_search;
	init_lista_func(&search_func);
	init_lista_func(&copia_funcao_search);
	
	
	//busca funcao com o nome da chamada
	search_func = buscar_lista_funcao_nome_chars(pListaFuncoes, func_chamada[0]/*0=nome*/);
	
	
	//copia funcao
	copia_funcao_search = copy_funcao(search_func);
	
	//insere funcao na lista de func chamadas
	inserir_lista_func_inicio(
		&*pListaFuncChamadas, 
		copia_funcao_search->linha,
		copia_funcao_search->cont_linhas, 
		copia_funcao_search->tipo, 
		copia_funcao_search->nome, 
		copia_funcao_search->pListaVars_prototipo,
		copia_funcao_search->pListaLinhas_func,
		copia_funcao_search->pListaVarsInterna
	);
	
	return copia_funcao_search;	
}

void inserir_variaveis_prototipo_funcao(char func_chamada[100][100],
	pListaVar ** pListaVars, /*PILHA DE VARS*/ 
	pListaFunc * pFuncao_chamada /* FUNCAO QUE BUSQUEI NA LISTA DE FUNCOES LIDAS NO COMECO DO PROGRAMA*/)
{
	/*AQUI ADICIONO AS VARIAVEIS DE FUNC_CHAMADA COM AS VARIAVEIS DA FUNCAO_CHAMADA
	OLHO SE EH PONTEIRO PARA MUDAR O VALOR DEPOIS OU NAO....*/
	
	//ADD VARIAVEIS
	StrDin * nome;
	StrDin * valor;
	int endereco;
	int valor_endereco;
	pListaVar * var_pilha;
	char ponteiro;
	int pos_var;
	pVars_prototipo * variaveis_funcao;
	
	endereco = (*pListaVars)->endereco; //PEGA ENDERECO DO TOPO DA LISTA DE VARIAVEIS
	variaveis_funcao = pFuncao_chamada->pListaVars_prototipo; //VARIAVEIS DE PROTOTIPO
	pos_var=1; //1, pois 0 eh o nome da funcao
	while(variaveis_funcao != NULL)
	{
		init_str(&nome);
		init_str(&valor);
		ponteiro=0;
		
//		printf("\n%s", func_chamada[pos_var]);
		//ENDERECO DA VARIAVEL NO QUAL ELE APONTA
		var_pilha = 
			search_lista_vars_nome_char(*pListaVars, func_chamada[pos_var] /*pos_var=nome da var na pilha de var de execucao*/);  
		
		copy_str_rec(&nome, variaveis_funcao->nome);
		
		if(variaveis_funcao->pont) //VARIAVEL EH PONTEIRO
		{
			while(var_pilha->ponteiro)
				var_pilha = search_lista_vars_endereco(*pListaVars, var_pilha->valor_endereco);
				
			valor_endereco = var_pilha->endereco; //PEGO VALOR
//			exibir_str(var_pilha->valor);
			copy_str_rec(&valor, var_pilha->valor);
			ponteiro=1;
		}
		else
		{
			ponteiro=0;
			copy_str_rec(&valor, var_pilha->valor);
			valor_endereco = 0;
		}	
		
		//COLOCA ENDERECO NA VARIAVEL DE PROTOTIPO COM O MESMO ENDERECO DA PILHA DE ENDERECO
		endereco += 4; //+4 assim como no inser_lista_vars
		variaveis_funcao->endereco = endereco; 
		
		
		//INSERIR VARIAVEL NA PILHA DE EXECUCAO
		inserir_listas_vars_inicio(&*pListaVars, nome, valor, valor_endereco, ponteiro);
		
		pos_var++;
		variaveis_funcao = variaveis_funcao->prox;
	}
}

char eh_operador_str(char * str)
{
	if(strstr(str, "+") != NULL||
	strstr(str, "-") != NULL ||
	strstr(str, "/") != NULL ||
	strstr(str, "*") != NULL ||
	strstr(str, "%") != NULL
	)
		return 1;
	
	return 0;	
}

char eh_operador_char(char str)
{
	if(str== '+' ||
		str== '-' ||
		str== '/' ||
		str== '*' ||
		str== '%'
	)
		return 1;
	
	return 0;	
}


void split_calculo_linha(char * linha_char, char calculo[100][50], int *tl)
{		
	if(strstr(linha_char, "+"))
	{
		const char split[7] = " 	*+;=";
	
		char *token = strtok(linha_char, split);
		
		
		if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
			strcpy(calculo[(*tl)++], token);
		token = strtok(NULL, split);
		
		if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
			strcpy(calculo[(*tl)++], token);
		token = strtok(NULL, split);
			
		strcpy(calculo[(*tl)++], "+\0");

		if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
			strcpy(calculo[(*tl)++], token);
		token = strtok(NULL, split);
			
		while( token != NULL ) {
			token = strtok(NULL, split);
		}
	}
	else if(strstr(linha_char, "-"))
	{
		const char split[7] = " 	*-=";
	
		char *token = strtok(linha_char, split);
					
			if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
				strcpy(calculo[(*tl)++], token);
			token = strtok(NULL, split);
			if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
				strcpy(calculo[(*tl)++], token);
			token = strtok(NULL, split);
				
			strcpy(calculo[(*tl)++], "-\0");
			if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
				strcpy(calculo[(*tl)++], token);
			token = strtok(NULL, split);
		while( token != NULL ) {
			token = strtok(NULL, split);
		}
	}
	
	else if(strstr(linha_char, "/"))
	{
			const char split[7] = " 	*/;=";
	
		char *token = strtok(linha_char, split);
		
			if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
				strcpy(calculo[(*tl)++], token);
			token = strtok(NULL, split);
			
			if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
				strcpy(calculo[(*tl)++], token);
			token = strtok(NULL, split);
				
			strcpy(calculo[(*tl)++], "/\0");
			
			if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
				strcpy(calculo[(*tl)++], token);
			token = strtok(NULL, split); 
		while( token != NULL ) {
			token = strtok(NULL, split);
		}
	}	
	else
	{
		const char split[6] = " 	*;=";
	
		char *token = strtok(linha_char, split);
		
			if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
				strcpy(calculo[(*tl)++], token);
			token = strtok(NULL, split);

			if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
				strcpy(calculo[(*tl)++], token);
			token = strtok(NULL, split);
				
			strcpy(calculo[(*tl)++], "*\0");
			
			if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
				strcpy(calculo[(*tl)++], token);
			token = strtok(NULL, split);
			
		while( token != NULL ) {
			token = strtok(NULL, split);
		}
	}
		
}


int retorna_calculo(char linha_splitada[100][50], pListaVar * pListaVars, int tl)
{
	int tl_valor;
	char valor[50];
	char calculo[100][50];
	
	pListaVar * search_var; 
	init_listas_vars_main(&search_var);
	
	
	int tl_calc=0, calc;
	int i=1; //0 eh o nome da val
	while(i < tl)
	{
		if( !eh_operador_str(linha_splitada[i]) && !is_number(linha_splitada[i])) //eh variavel
		{
			search_var = search_lista_vars_nome_char(pListaVars, linha_splitada[i]);
			
			if(search_var->ponteiro)	
				search_var = search_lista_vars_endereco(pListaVars, search_var->valor_endereco);
			
			tl_valor=0;
			strdin_to_chars(search_var->valor, valor, &tl_valor);
			strcpy(calculo[tl_calc++],valor);
		}
		else/* +-/%**/
		{
			strcpy(calculo[tl_calc++], linha_splitada[i]);
		}
		i++;
		init_listas_vars_main(&search_var);
	}
	
	tl_calc--; //coloca tl na pos -1 
//	char unidade[100];
//	strcpy(unidade, calculo[tl_calc-1]);
	calc = atoi(calculo[tl_calc]);
	tl_calc--; 
//	printf("%d", atoi(unidade));
	
	//a+b somente uma operacao...
	while(tl_calc >= 0) //melhor isso mais tarde, colocar mais operacoes
	{
		if(strcmp(calculo[tl_calc], "\0") != 0 && strcmp(calculo[tl_calc], "\n") != 0)
			if(strstr(calculo[tl_calc], "+") != NULL)
			{
				tl_calc--;
				calc += atoi(calculo[tl_calc]);
			}
				
				
			else if(strstr(calculo[tl_calc], "-") != NULL)
			{
				tl_calc--;
				calc -= atoi(calculo[tl_calc]);
			}
				
			
			else if(strstr(calculo[tl_calc], "/") != NULL)
			{
				tl_calc--;
				calc /= atoi(calculo[tl_calc]);
			}
				
			
			else if(strstr(calculo[tl_calc], "%") != NULL)
			{
				tl_calc--;
				calc %= atoi(calculo[tl_calc]);
			}
				
			
			else if(strstr(calculo[tl_calc], "*") != NULL) //*
			{
				tl_calc--;
				calc *= atoi(calculo[tl_calc]);		
			}
		else			
			tl_calc--;	
	}
	
	return calc;
}


void executa_calculo(char * linha_char, pListaVar **pListaVars)
{
	pListaVar * var_recebe_calc;
	int i, tl=0, calc;
	char linha_splitada[100][50];
	int result_calc;
	
	split_calculo_linha(linha_char, linha_splitada, &tl);
	init_listas_vars_main(&var_recebe_calc);
	
	//nome da variavel que recebe todo o calculo;
//	printf("%s", linha_splitada[0]);
	var_recebe_calc = search_lista_vars_nome_char(*pListaVars, linha_splitada[0]);
	
	result_calc = retorna_calculo(linha_splitada, *pListaVars, tl);
	change_valor_valor_lista_listas_vars(var_recebe_calc, result_calc); 
	
	//caso a var que recebe todo calculo eh um poteiro, eh necessario buscar a var real,passando por todas referencias.
	var_recebe_calc = search_lista_vars_endereco(*pListaVars, var_recebe_calc->valor_endereco);
	change_valor_valor_lista_listas_vars(var_recebe_calc, result_calc);
	while(var_recebe_calc != NULL && var_recebe_calc->ponteiro)	
	{
		change_valor_valor_lista_listas_vars(var_recebe_calc, result_calc); 
		var_recebe_calc = search_lista_vars_endereco(*pListaVars, var_recebe_calc->valor_endereco);
	}
		
}

void empilha_funcao(char * linha, pListaVar ** pListaVars, pListaFunc * pListaFuncoes, 
	pListaFunc ** pListaFuncChamadas);
	
char executa_linhas_funcao_chamadas(pListaFunc **pListaFuncChamadas, 
	pListaVar ** pListaVars, pListaFunc *pListaFuncoes, char * nome_programa_fonte)
{
	StrDin * linha;
	char linha_char[100];
	char chamou_func=0;
	int tipo, tl;
	
	pLinhas_func * linhas = (*pListaFuncChamadas)->pListaLinhas_func; // CABECA DA LISTA DAS LINHAS DA FUNCAO
	exibir_str(linhas->linha);
	
	if( !isEmpty_lista_linhas_interna_func(linhas))
	{
		strdin_to_chars(linhas->linha, linha_char, &tl);
		//0 calculo - 1 chamada de funcao;
		if(linhas->tipo == 0) // calculo
		{
			executa_calculo(linha_char, &*pListaVars);
			
		}
		else if(linhas->tipo == 1) //chamada de funcao
		{
			//split_variaveis_atribuicoes(linha_char, saida, &tl); //splita linha lida do arquivo
//			inserir_variaveis_declaracao_dentro_funcao(&*pListaVars, saida, tl);//inserir variaveis na lista de variaveis
			
			(*pListaFuncChamadas)->linha++; //INCREMENTA LINHA ANTES DE INSERIR NOVA FUNCAO NA PILHA
			//printar_arquivo_tela_pos_atual(nome_programa_fonte, (*pListaFuncChamadas)->linha);
			
			empilha_funcao(linha_char, &*pListaVars, pListaFuncoes, &*pListaFuncChamadas);
			remover_inicio_linhas_interna_func_no_return(&(*pListaFuncChamadas)->pListaLinhas_func);	
			//system("cls");
//			exibir_listas_vars(*pListaVars);
//			getch();
			if(!isEmpty_lista_funcoes(*pListaFuncChamadas))
				chamou_func=1;
		} 
	}
	
	return chamou_func;
}

//TRATO AS VARIAVEIS DE ARGUMENTO/PROTOTIPO, COPIO A FUNCAO COM AS VARIAVEIS E ENDERECO CORRETO
//EMPILHA FUNCAO NA LISTA DE FUNCOES PARA EXECUCAO
void empilha_funcao(char * linha, pListaVar ** pListaVars, pListaFunc * pListaFuncoes, 
	pListaFunc ** pListaFuncChamadas)
{
	char saida[100][100];
	int tl=0;
	pListaFunc * copia_da_funcao_achada;
	
	split_chamada_funcao(linha, saida, &tl); //splita prototipo da funcao
	copia_da_funcao_achada = empilha_chamada_funcao(saida, pListaFuncoes, &*pListaFuncChamadas); //copia a funcao para lista de funcoes de chamada
	
	inserir_variaveis_prototipo_funcao(saida, &*pListaVars, copia_da_funcao_achada);//inserir funcao na lista de funcoes
	
//////	//PRINTAR A LISTA DE VARIAVEIS DO TOPO DA LISTA DE FUNCOES DE CHAMADA
//////			
//////	pVars_prototipo * aux_varChamadas = (*pListaFuncChamadas)->pListaVars_prototipo;
//////	printf("\n\nENDERECO\tTIPO\tPONT\tNOME\tVALOR\n");
//////	while(aux_varChamadas != NULL)
//////	{
//////		//int tipo; // 0 void - 1 int - 2 float - 3 char - 4 double
////////				StrDin * nome;
////////				char pont;
////////				StrDin * valor;
////////				int endereco;

//////		printf("%d", aux_varChamadas->endereco);
//////		printf("%d", aux_varChamadas->tipo);
//////		printf("%s", (aux_varChamadas->pont) ? "* ": " ");
//////		exibir_str(aux_varChamadas->nome);
//////		exibir_str(aux_varChamadas->valor);
//////		printf("\n");
//////		
//////		aux_varChamadas = aux_varChamadas->prox;
//////	}
	
}

void split_printf(char *linha, char saida[100][50], int * tl)
{
	int i=0, j;
	while(linha[i] != '(')
		i++;
	i++; // (
	
	while(linha[i] == ' ' || linha[i] != 34 ) //34 == "
		i++;
	i++; // "
		
	j=0;	
	while(linha[i] != 34) // 34 = "
	{
		saida[*tl][j] = linha[i];
		j++;
		i++;
	}
		
	i++; // "
	(*tl)++; //peguei primeiro argumento printf
	
//	printf("%s", saida[0]);
	
	while(linha[i] != ')')
	{
		while(linha[i] == 44 /* 44 eh virgula (,) */ || linha[i] == ' ')
			i++;
		j=0;	
		while(linha[i] != ',' && linha[i] != ')')
		{
			if(linha[i] != ' ')
			{
				saida[*tl][j] = linha[i];
				i++;
				j++;
			}
		}
			
//		printf("%s", saida[*tl]);	
		(*tl)++;
		
		while(linha[i] == ' ' && linha[i] != ')' )
			i++;
	}		
}

char eh_number_char(char ch)
{
	return ch >= '0' && ch <= '9';
}

char eh_character_char(char ch)
{
	return (ch >= 'A' && ch <= 'Z') || ch >= 'a' && ch <= 'z';
}

void split_calc_printf(char calc[100][50], int * tl, char * string, pListaVar * pListVars)
{
	//SPLITA LINHA DE CALCULO DENTRO DE UM ARGUMENTO DE PRINTF
	int i, i_aux, pont;
	StrDin * var_argument;
	pListaVar * search_var;
	char flag_operador, valor_in_chars[20];
	
	flag_operador=0;
	init_str(&var_argument);
	i=0;
	while(string[i] != '\0')
	{
		while(string[i] == ' ') i++; // PERCORRER ESPACOS VAZIOS
		
		if(eh_number_char(string[i])) //numero
		{
			i_aux=0;
			while(eh_number_char(string[i]))
			{
				calc[*tl][i_aux] = string[i];
				i++;
				i_aux++;
			}
			
			flag_operador=1;
			(*tl)++;
		}
		else if(eh_character_char(string[i])) //variavel
		{
			//PRIMEIRA ENTRADA NAO PODE SER NUMERO, POS ISSO NO IF VERIFICO SOMENTE LETRA
			i_aux=i; //pega posicao por seguranca para percorrer;
			
			do 
			{
				inserir_char(&var_argument, string[i_aux]);
				i_aux++;
			}while(eh_character_char(string[i_aux]) || eh_number_char(string[i_aux]) || string[i_aux] == '_');
			
			search_var = search_lista_vars_nome_strdin(pListVars, var_argument);
			if(search_var != NULL) //achei na pilha de vars
			{
				i=i_aux-1; //devolve posicao;
				strdin_to_chars_no_tl(search_var->valor, valor_in_chars); //str to chars
				strcpy(calc[*tl], valor_in_chars);//coloco na pos calc[tl]
				(*tl)++;
				reinit_str(&var_argument);
				i++;
			}
			flag_operador=1;
		}
		
		while(string[i] == ' ') i++; // PERCORRER ESPACOS VAZIOS
		
		if(string[i] != '\0')
			if(eh_operador_char(string[i]) && flag_operador)
			{
				calc[*tl][0] = string[i];
				calc[*tl][1] = '\0';
				(*tl)++;
				flag_operador=0;
				i++;
			}
			else
				i++;			
			
	}
}

int executa_calc_printf(char * string, pListaVar * pListaVars)
{
	int tl, result;
	char calc[100][50];
	
	tl=0;
	split_calc_printf(calc, &tl, string, pListaVars);
	
	tl--; //coloca tl na pos -1 
	result = atoi(calc[tl]);
	tl--; 
//	printf("%d", atoi(unidade));
	while(tl > 0)
	{
		if(strcmp(calc[tl], "\0") != 0 && strcmp(calc[tl], "\n") != 0)
			if(strstr(calc[tl], "+") != NULL)
			{
				tl--;
				result += atoi(calc[tl]);
			}
				
				
			else if(strstr(calc[tl], "-") != NULL)
			{
				tl--;
				result -= atoi(calc[tl]);
			}
				
			
			else if(strstr(calc[tl], "/") != NULL)
			{
				tl--;
				result /= atoi(calc[tl]);
			}
				
			
			else if(strstr(calc[tl], "%") != NULL)
			{
				tl--;
				result %= atoi(calc[tl]);
			}
				
			
			else if(strstr(calc[tl], "*") != NULL) //*
			{
				tl--;
				result *= atoi(calc[tl]);		
			}
		else			
			tl--;	
	}	
	
	return result;
}

StrDin * tratar_argumentos_printf(char saida[100][50], int argumentos, pListaVar * pListaVars)
{
	/*
		TRATA TODOS ARGUMENTOS DO PRINTF
	*/
	int argumento, pos, pos_aux, result_calculo_argument, tl_string_1_argument_printf;
	char ch, valor_calc_chars[20];
	pListaVar * busca_var;
	StrDin * printf_line; //USANDO EM CADA LINHA DA LISTA
	StrDin * var_aux; //USADO PARA PEGAR PESQUISAR O VALOR DA VARIAVEL
	
	init_str(&var_aux);
	init_str(&printf_line);
	

	pos=0;
	argumento=1; //linha 0 eh posicao da string do printf("blablabla"); linha 1 em diante é as chamadas de variavel
	while(argumento < argumentos)
	{
		//VE SE EH OPERADOR DO PRINTF INTERNO INTEIRO, FLOAT, STRING...etc
		do
		{
			if(saida[0][pos] != '%' && ( saida[0][pos+1] != 'd'  || saida[0][pos+1] != 'f'  ||
																    saida[0][pos+1]  != 's' ||
															    	saida[0][pos+1]  != 'c' )
			)
			{
				inserir_char(&printf_line, saida[0][pos]);
				pos++;
			}
			
		}while(saida[0][pos] != '\0' && saida[0][pos] != '%' && ( saida[0][pos+1] != 'd'  || 
																  saida[0][pos+1] != 'f'  ||
																  saida[0][pos+1]  != 's' ||
																  saida[0][pos+1]  != 'c' ));
		
		if(/*pos < tl_string_1_argument_printf && */argumento < argumentos)
		{
			pos = pos+2; //pula %d ou %s ou %f	
			
			if(saida[argumento][0] == '"') //STRING
			{
				pos_aux = 1;
				while(saida[argumento][pos_aux] != '"' && saida[argumento][pos_aux] != '\0')
				{
					inserir_char(&printf_line, saida[argumento][pos_aux]);
					pos_aux++;
				}
			}
			else if(saida[argumento][0] == 39) // ' -> unico char ' = aspas
			{
				pos_aux = 1;
				inserir_char(&printf_line, saida[argumento][pos_aux]);
					
			}
			
			else if(is_number(saida[argumento])) //NUMERO SEM OPERADOR
			{
				pos_aux = 0;
				while(saida[argumento][pos_aux] != '\0')
				{
					inserir_char(&printf_line, saida[argumento][pos_aux]);
					pos_aux++;
				}
			}
			
			else if(eh_variavel_printf(saida[argumento]))// VARIAVEL
			{
				pos_aux=0;
				while(saida[argumento][pos_aux] == '*' || saida[argumento][pos_aux] == '&')
					pos_aux++;
				
				while(saida[argumento][pos_aux] != ' ' && saida[argumento][pos_aux] != '\0')
				{
					inserir_char(&var_aux, saida[argumento][pos_aux]);
					pos_aux++;	
				}	
				
				busca_var = search_lista_vars_nome_strdin(pListaVars, var_aux);	
				reinit_str(&var_aux);
				
				var_aux = busca_var->valor;
				while(var_aux != NULL)
				{
					inserir_char(&printf_line, var_aux->ch);
					var_aux = var_aux->prox;
				}	
			}
			
			else //CALCULO
			{
				pos_aux=0;
				
				result_calculo_argument = executa_calc_printf(saida[argumento], pListaVars);
				int_to_chars(valor_calc_chars, result_calculo_argument);
				
				while(valor_calc_chars[pos_aux] != '\0')
				{
					inserir_char(&printf_line, valor_calc_chars[pos_aux]);
					pos_aux++;
				}	
			}
			
			argumento++;
		}
	}
	
	while(saida[0][pos] != '\0') //CASO SO TENHA PRINTF OU OS ARGUMENTOS ACABARAM
	{
		inserir_char(&printf_line, saida[0][pos]);
		pos++;
	}
	
	return printf_line;
}

void guardar_printf(char * string, pListaString ** pListaPrintfs, pListaVar * pListaVars)
{
	StrDin * printf_add;
	char saida[100][50];
	int linhas_saida;	
	
	linhas_saida=0;
	split_printf(string, saida, &linhas_saida);
	printf_add = tratar_argumentos_printf(saida, linhas_saida, pListaVars);
	
//	exibir_str(printf_add);
	inserir_lista_string_strdin(&*pListaPrintfs, printf_add);
}

void remover_variaveis_pilha_variaveis(pListaVar ** pListaVars, pListaFunc * pListaFuncChamadas)
{
	pVars_prototipo * variaveis_prototipo;
	pListaVar * vars_interna;
	
	variaveis_prototipo = pListaFuncChamadas->pListaVars_prototipo;
	while(variaveis_prototipo != NULL)
	{
		remover_listas_vars_endereco_no_return(&*pListaVars, variaveis_prototipo->endereco);
		variaveis_prototipo = variaveis_prototipo->prox;
	}
	
	vars_interna = pListaFuncChamadas->pListaVarsInterna;
	while(vars_interna != NULL)
	{
		remover_listas_vars_endereco_no_return(&*pListaVars, variaveis_prototipo->endereco);
		vars_interna = vars_interna->prox;
	}
}

void inserir_variaveis_interna_pilha_vars(char linha[100], pListaVar ** pListaVars)
{
	char saida[100][100];
	int tl;
	
	tl=0;
	split_variaveis_atribuicoes(linha, saida, &tl); //splita linha lida do arquivo
	inserir_variaveis_declaracao_dentro_funcao(&*pListaVars, saida, tl);//inserir variaveis na lista de variaveis
}

void incrementa_linha_funcao(pListaFunc ** pListaFuncChamadas)
{
	if((*pListaFuncChamadas)->cont_execucao == 0)
		(*pListaFuncChamadas)->cont_execucao++;
	else
	{
		(*pListaFuncChamadas)->linha++;
		(*pListaFuncChamadas)->cont_linhas++;
	}	
}

void executa_pilha_chamadas_funcoes(pListaFunc * pListaFuncoes, pListaFunc ** pListaFuncChamadas, 
	pListaVar ** pListaVars, pListaString ** pListaPrintfs, char *nome_programa_fonte)
{
	StrDin * linha;
	char linha_char[100];
	char chamou_func=0;
	int tipo, tl;
	
	pLinhas_func * linhas = (*pListaFuncChamadas)->pListaLinhas_func; // CABECA DA LISTA DAS LINHAS DA FUNCAO
//	exibir_str(linhas->linha);
	
	if( !isEmpty_lista_linhas_interna_func(linhas))
	{
		strdin_to_chars(linhas->linha, linha_char, &tl); //get linha in chars
		//0 calculo - 1 chamada de funcao;
		
		if(linhas->tipo == 0) // calculo
		{
			executa_calculo(linha_char, &*pListaVars);
			
			incrementa_linha_funcao(&*pListaFuncChamadas); //++ LINHA
			
			printar_arquivo_tela_pos_atual(nome_programa_fonte, (*pListaFuncChamadas)->linha);
			remover_inicio_linhas_interna_func_no_return(&(*pListaFuncChamadas)->pListaLinhas_func);
		}
		else if(linhas->tipo == 1) //chamada de funcao
		{
			incrementa_linha_funcao(&*pListaFuncChamadas); //++ LINHA
			printar_arquivo_tela_pos_atual(nome_programa_fonte, (*pListaFuncChamadas)->linha);
			remover_inicio_linhas_interna_func_no_return(&(*pListaFuncChamadas)->pListaLinhas_func);
			
			empilha_funcao(linha_char, &*pListaVars, pListaFuncoes, &*pListaFuncChamadas);
			
			
		} 
		else if(linhas->tipo == 2) //printf
		{
			incrementa_linha_funcao(&*pListaFuncChamadas); //++ LINHA
			printar_arquivo_tela_pos_atual(nome_programa_fonte, (*pListaFuncChamadas)->linha);
			remover_inicio_linhas_interna_func_no_return(&(*pListaFuncChamadas)->pListaLinhas_func);
			
			guardar_printf(linha_char, &*pListaPrintfs, *pListaVars);
		}
		else if(linhas->tipo == 3) //declaracao de variaveis
		{
			printar_arquivo_tela_pos_atual(nome_programa_fonte, (*pListaFuncChamadas)->linha);
			remover_inicio_linhas_interna_func_no_return(&(*pListaFuncChamadas)->pListaLinhas_func);
			incrementa_linha_funcao(&*pListaFuncChamadas); //++ LINHA
			
			inserir_variaveis_interna_pilha_vars(linha_char, &*pListaVars);
		}
		
		//REMOVER A FUNCAO DA LISTA DE FUNCOES DE CHAMADAS E VARIAVEIS DA LISTA DE VARIAVEIS
		//SE FUNCAO LISTA DE LINHAS VAZIA
		if(isEmpty_lista_linhas_interna_func((*pListaFuncChamadas)->pListaLinhas_func)) 
		{
			do
			{
				//REMOVE AS VARIAVEIS DE ARGUMENTO DA FUNCAO DA PILHA DE VARIAVEIS GLOBAIS;
				remover_variaveis_pilha_variaveis(&*pListaVars, *pListaFuncChamadas);
				
				//REMOVE TOPO DA PILHA DE FUNCOES DE CHAMADA;
				remover_inicio_func_no_return(&*pListaFuncChamadas);
			}while( !isEmpty_lista_funcoes(*pListaFuncChamadas) && isEmpty_lista_linhas_interna_func((*pListaFuncChamadas)->pListaLinhas_func));
				
		}
	}
}

int main()
{
	FILE * arquivo_execucao;
	int pos_main_exibir;
	char nome_programa_fonte[30];
	
	pListaFunc * pListaFuncoes;
	pListaFunc * pListaFuncChamadas; //pilha de chamada de funcoes!
	pListaVar * pListaVars;
	pListaString * pListaPrintfs;
	
	char linha[100];
	
	init_lista_string(&pListaPrintfs);
	init_lista_func(&pListaFuncChamadas);
	init_lista_func(&pListaFuncoes);
	init_listas_vars_main(&pListaVars);
	strcpy(nome_programa_fonte, "programa_ler.c");
	
	//LER TODAS FUNCOES E JOGA NA MEMORIA.
	ler_todas_funcoes(nome_programa_fonte, &pListaFuncoes);
	
	//EXIBIR O MARCADOR JA SELECIONADO A PRIMEIRA IMPLEMENTACAO DENTRO DO MAIN
	pos_main_exibir = achar_posicao_main(nome_programa_fonte);
	printar_arquivo_tela_pos_atual(nome_programa_fonte, -1);
	
	//posicionar no arquivo na primeira implementacao do main.
	arquivo_execucao = fopen(nome_programa_fonte, "r");
	posicionar_linha_implementacao_main(arquivo_execucao, pos_main_exibir);
	
	char saida[100][100];
	int tl;
	char chamou_func; //flag para ver se chamou nova funcao, assim nao tira a linha da nova funcao no topo da lista;
	char key; //OPERACAO DE MENU PRINCIPAL;
	
	key = getch();
	while(!feof(arquivo_execucao) && key != 'q')
	{	
		switch(key)
		{
			case 'm': //F9 - VER MEMORIA
				system("cls");
				exibir_listas_vars(pListaVars);	
				//printf("\n\n[ ENTER ]");
//				getch();
				break;
			
			case 't': //F10 - TELA
			
				if(!isEmpty_lista_funcoes(pListaFuncChamadas))
					printar_arquivo_tela_pos_atual(nome_programa_fonte, pListaFuncChamadas->linha); //printar na tela posicao atual do main
				else
					printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir);
				break;
			
			case 'p': //F? - PRINTFs
				system("cls");
				exibir_lista_string(pListaPrintfs);
				break;
				
			case 13: //ENTER - executa linha
					
				if(strstr(linha, "}") != NULL)
					key = 'q';				
				
				else if( !isEmpty_lista_funcoes(pListaFuncChamadas))
				{
					pos_main_exibir++;
					executa_pilha_chamadas_funcoes(pListaFuncoes, &pListaFuncChamadas, &pListaVars, &pListaPrintfs, nome_programa_fonte);	
				}
				else
				{
					ler_linha_arquivo_main(arquivo_execucao, linha);
					
					//DECLARACAO NO MAIN
					if(eh_declaracao_variavel_atribuicao(linha) && isEmpty_lista_funcoes(pListaFuncChamadas) && !eh_printf(linha))
					{
						tl=0;
						split_variaveis_atribuicoes(linha, saida, &tl); //splita linha lida do arquivo
						inserir_variaveis_declaracao_dentro_funcao(&pListaVars, saida, tl);//inserir variaveis na lista de variaveis
												
						printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir); //printar na tela posicao atual do main
						pos_main_exibir++;
					}
					
					//ENTRA NA FUNCAO E EXECUTA AS LINHAS
					else if(eh_chamada_de_funcao(linha) && isEmpty_lista_funcoes(pListaFuncChamadas) && !eh_printf(linha))
					{
						empilha_funcao(linha, &pListaVars, pListaFuncoes, &pListaFuncChamadas);
						
						printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir); //printar na tela posicao atual do main

					}
					
					else if(eh_printf(linha))
					{
						guardar_printf(linha, &pListaPrintfs, pListaVars);
						printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir); //printar na tela posicao atual do main
						pos_main_exibir++;
					}
				}
				break;
		}
		
		//system("cls");
//		exibir_listas_vars(pListaVars);
		
			key=getch();	
	}
	
	fclose(arquivo_execucao);

    return 0;

}


