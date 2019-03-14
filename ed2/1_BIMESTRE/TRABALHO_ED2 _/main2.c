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

char eh_chamada_de_funcao(char *string)
{
	if( strstr(string, "void") == NULL &&
		strstr(string, "char") == NULL &&
		strstr(string, "int") == NULL  &&
		strstr(string, "float") == NULL &&
		strstr(string, "double") == NULL &&
		strstr(string, "(") != NULL &&
		strstr(string, ")") != NULL &&
		strstr(string, ";") != NULL &&
		strstr(string, "=") == NULL)
		return 1;
	return 0;	
}

char eh_variavel_com_chamada_de_funcao(char *string)
{
	if( strstr(string, "void") == NULL &&
		strstr(string, "char") == NULL &&
		strstr(string, "int") == NULL  &&
		strstr(string, "float") == NULL &&
		strstr(string, "double") == NULL &&
		strstr(string, "(") != NULL &&
		strstr(string, ")") != NULL &&
		strstr(string, "=") != NULL &&
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
		strstr(string, "double") == NULL ||
		
		(strstr(string, "+") != NULL ||
		strstr(string, "-") != NULL ||
		strstr(string, "*") != NULL ||
		strstr(string, "/") != NULL)
		
		)
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
		strstr(string, "double") != NULL))
		return 1;
	return 0;	
}

char eh_algum_tipo_variavel_declaracao(char * string)
{
	if(	(strstr(string, "char") != NULL ||
		strstr(string, "int") != NULL  ||
		strstr(string, "float") != NULL ||
		strstr(string, "double") != NULL) &&
		strstr(string, ";") != NULL &&
		strstr(string, ")") == NULL &&
		strstr(string, "(") == NULL
	)
		return 1;
	return 0;
}

char eh_atribuicao_valor_variavel(char *str)
{
	if( (strstr(str, "int") == NULL ||
		strstr(str, "char") == NULL ||
		strstr(str, "float") == NULL ||
		strstr(str, "double") == NULL) && 
		strstr(str, "=") != NULL &&  
		strstr(str, "(") == NULL && 
		strstr(str, ")") == NULL && 
		strstr(str, ";") != NULL
	)
		return 1;
	return 0;
		
}

char eh_return(char *str)
{
	if(strstr(str, "return") != NULL)
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

char eh_number_char(char ch)
{
	return ch >= '0' && ch <= '9';
}

char eh_character_char(char ch)
{
	return (ch >= 'A' && ch <= 'Z') || ch >= 'a' && ch <= 'z';
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
				
		if(string[*pos] == ',' || string[*pos] == ')')
		{
			inserir_lista_vars_argumento_func(&*vars_cab, 0, 0,tipo, pont, nome, valor);
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



void ler_funcao(pListaFunc ** pLista_Funcoes, char * line_read, int * linha_atual, FILE * arq)
{	
	//VARS FUNCAO;
	int pos_line;
	int linha_inicio_funcao_implementacoes;
	int pTipo_func;
	StrDin * aux_tipoFunc;
	StrDin * pNome_func;
	int total_linhas;
	pVars_prototipo * pVars_argumentos;
	pLinhas_func * pLinhas_interna;
	
	init_lista_linhas_interna_func(&pLinhas_interna);
	init_lista_vars_argumento_func(&pVars_argumentos);
	init_str(&pNome_func);
	init_str(&aux_tipoFunc);
	pos_line=0;
	total_linhas=0;
	
	//----------------------------------PEGA TIPO
	while(line_read[pos_line] != ' ')
	{
		inserir_char(&aux_tipoFunc, line_read[pos_line]);
		pos_line++;
	}
	
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
	
	// POS ( DOS ARGUMENTOS
	pos_line++;
	
	//---------------------------------PEGA VARIAVEIS DO ARGUMENTO ////
	get_todas_variaveis_argumento(line_read, &pVars_argumentos, &pos_line);
	
	
	
	// ----------------------------- PEGA IMPLEMENTACAO DA FUNCAO ----- ///
	
	//CHEGAR NO FINAL DA LINHA
	while(pos_line < strlen(line_read) && line_read[pos_line] != ')' &&
	line_read[pos_line] != '{')
		pos_line++;
	
		
	fgets(line_read, 100, arq);
	(*linha_atual)++;
	pos_line=0;
	
	//pega linha abre chave
	if(strstr(line_read, "{") != NULL)
	{
		fgets(line_read, 100, arq);
		(*linha_atual)++;
		pos_line=0;
		
	}
	
	linha_inicio_funcao_implementacoes = (*linha_atual);

	//le ate nao chegar o final da funcao
	//0 calculo - 1 chamda de funcao - 2 printf
	while(strstr(line_read, "}") == NULL)
	{
		if(eh_chamada_de_funcao(line_read))
			inserir_lista_linhas_interna_func(&pLinhas_interna, 1, vetchar_to_strDin(line_read));
			
		else if(eh_printf(line_read))
			inserir_lista_linhas_interna_func(&pLinhas_interna, 2, vetchar_to_strDin(line_read));
//			
//		else if((eh_declaracao_variavel_atribuicao(line_read) || eh_atribuicao_valor_variavel(line_read) 
//					|| eh_atribuicao_valor_variavel(line_read))
//					&& !eh_printf(line_read))	
//			if(eh_calculo_in_funcao(line_read))
//				inserir_lista_linhas_interna_func(&pLinhas_interna, 0, vetchar_to_strDin(line_read));	
//			else //else => declaracao
//				
				
		else if(eh_declaracao_variavel_atribuicao(line_read) && !eh_return(line_read))		
			inserir_lista_linhas_interna_func(&pLinhas_interna, 3, vetchar_to_strDin(line_read));
			
		else if(eh_calculo_in_funcao(line_read) && !eh_return(line_read) && strstr(line_read, "(") == NULL)
			inserir_lista_linhas_interna_func(&pLinhas_interna, 0, vetchar_to_strDin(line_read));
			
			
		else if(eh_chamada_de_funcao && !eh_return(line_read) && strstr(line_read, "=") != NULL)	
			inserir_lista_linhas_interna_func(&pLinhas_interna, 5, vetchar_to_strDin(line_read));
		
		
		else if(eh_return(line_read))
			inserir_lista_linhas_interna_func(&pLinhas_interna, 4, vetchar_to_strDin(line_read));
		
		fgets(line_read, 100, arq);
		(*linha_atual)++;
		total_linhas++;
	}
	
	//acaba funcao ja na linha seguinte desta funcao
	if(strstr(line_read, "}") != NULL)
	{
		fgets(line_read, 1000, arq);
		(*linha_atual)++;
		pos_line=0;
	}
	
//	//COMO TAMANHO COMECA
//	if(total_linhas > -1)
//		total_linhas++;
	
	//insere na lista de funcoes;
	inserir_lista_func_fim(&*pLista_Funcoes, linha_inicio_funcao_implementacoes, total_linhas, pTipo_func, pNome_func, pVars_argumentos, pLinhas_interna, NULL);
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

void printar_arquivo_tela_pos_atual2(char *file_name, int pos_atual)
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

void printar_arquivo_tela_pos_atual(char *file_name, int pos_atual)
{
	system("cls");
	
	int COR_NOME_PROGRAMA = 7;
	int COR_NUMERACAO = 8;
	int COR_MOLDURA = 4;
	int KEY=14;
	int COR_DESCRICAO = 7;
	
	int num_line=1;
	int i, j, i_file_name, cont_line_col;	
	char line[100];
	
	if(pos_atual != -1)
		pos_atual += 1;
	
	FILE * arq = fopen(file_name, "r");
	
	
	textcolor(COR_MOLDURA);
	printf("%c", 218);
	for(i=0 ; i < 6 ; i++)
		printf("%c", 196);
	i += 3;
	printf("%c ", 180);
	textcolor(15);
	
	
	textcolor(COR_NOME_PROGRAMA);
	for(i_file_name=0 ; file_name[i_file_name] != '\0' ; i_file_name++, i++)
		printf("%c", file_name[i_file_name]);
	textcolor(15);	
	
	textcolor(COR_MOLDURA);
	printf("  %c", 195);	
	i += 2;
	for( ; i < 78 ; i++)
		printf("%c", 196);
	printf("%c\n", 191);
	textcolor(15);	
	
	fgets(line, 100, arq);
	while(!feof(arq))
	{
		textcolor(COR_MOLDURA); //MOLDURA
		printf("%c ", 179);
		textcolor(15);
		
		textcolor(COR_NUMERACAO); // NUMERACAO
		printf("%d  ",num_line);
		textcolor(15);
		
		if(num_line == pos_atual)
		{
			textbackground(4);
			cont_line_col=4;
		}
		
		for(i=0 ;  line[i] != '\n' && line[i+1] != '\0' ; i++)
		{
			cont_line_col++;
			printf("%c", line[i]);	
		}
			
		if(num_line == pos_atual)	
			while(cont_line_col < 76)
			{
				printf(" ");
				cont_line_col++;
			}
			
		printf("\n");
		num_line++;	
		
		textcolor(COR_MOLDURA);
		textbackground(0);
		gotoxy(80, num_line);
		printf("%c", 179);
		textcolor(15);
		printf("\n");
		
		fgets(line, 100, arq);
	}
	
	textcolor(COR_MOLDURA);
	printf("%c", 192);
	for(i=0 ; i < 78 ; i++)
		printf("%c", 196);
	printf("%c", 217);	
	textcolor(15);
	
	fclose(arq);
	
	printf("\n\n");
	
	char *opcoes[][10] = {
		{"\t F7\0", " Abrir\0"},
		{"\t F8\0", " Executar\0"},
		{"\t F9\0", " Memoria\0"},
		{"\t F10\0", " Tela\0"},
	};
	
	for(i=0 ; i < 4 ; i++)
	{
		textcolor(KEY);
		for(j=0 ; opcoes[i][0][j] != '\0' ; j++)
			printf("%c", opcoes[i][0][j]);
		
		textcolor(COR_DESCRICAO);
		for(j=0 ; opcoes[i][1][j] != '\0' ; j++)
			printf("%c", opcoes[i][1][j]);
	}
	
	textcolor(15);
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
		if( strstr(token, "int") == NULL && 
			strstr(token, "char") == NULL && 
			strstr(token, "double") == NULL && 
			strstr(token, "float") == NULL &&
			strcmp(token, "\n") != 0 && 
			strcmp(token, "\0"))
			strcpy(saida[(*tl)++], token);
		token = strtok(NULL, split);
	}
}

//char procura_variavel(char nome_variavel[100], pListaVar *pListaVars, pListaFunc * pListaFuncChamadas)
//{
//	if( !isEmpty_lista_funcoes(pListaFuncChamadas))
//	{
//		//procura nas variaveis internas
//		if(search_lista_vars_nome_char(pListaFuncChamadas->pListaVarsInterna, nome_variavel))
//			return 1;
//		
//		//variaveis de prototipo
//		else if(search_lista_vars_argumento_func_chars(pListaFuncChamadas->pListaVars_prototipo, nome_variavel))
//			return 1;
//			
//		//variaveis globais	
//		else if(search_lista_vars_nome_char(pListaVars, nome_variavel))
//			return 1;	
//	}
//	
//	//variaveis globais
//	else if(search_lista_vars_nome_char(pListaVars, nome_variavel))
//			return 1;
//			
//	return 0;		
//}

//void muda_valores_variaveis_atribuicao( char nome_variavel[100], char valor_chars[100],
//										pListaVar **pListaVars, pListaFunc * pListaFuncChamadas)
//{
//	pListaVar * aux_var_global;
//	
//	if( !isEmpty_lista_funcoes(pListaFuncChamadas))
//	{
//		pVars_prototipo * var_prototipo = search_lista_vars_argumento_func_chars(pListaFuncChamadas->pListaVars_prototipo, nome_variavel);
//		
//		if(var_prototipo != NULL)
//		{
//			reinit_str((&(var_prototipo)->valor));
//			//muda valor do parametro, lista da funcao
//			copy_str(&(var_prototipo)->valor, valor_chars);
//			
//			if(var_prototipo->pont)
//			{
//				//muda valor para todas que ela aponta
//				aux_var_global = *pListaVars;
//				while(aux_var_global != NULL)
//				{
////					printf("\nvalor_pont = %d", aux_var_global->valor_endereco);
////					
////					printf("\nvalor_endereco = %d\n" ,aux_var_global->endereco);
//					
//					
//					if(aux_var_global->ponteiro && aux_var_global->valor_endereco == var_prototipo->valor_endereco)
//					{
//						reinit_str((&(aux_var_global)->valor));
//						copy_str(&(aux_var_global)->valor,	valor_chars);
//					}
//					else if( !aux_var_global->ponteiro && aux_var_global->endereco == var_prototipo->valor_endereco)
//					{
//						reinit_str((&(aux_var_global)->valor));
//						copy_str(&(aux_var_global)->valor,	valor_chars);
//					}
//						
//					
//					aux_var_global = aux_var_global->prox;
//				}	
//			}//
////			else
////			{
//////					printf("\nvalor_pont = %d", aux_var_global->valor_endereco);
//////					
//////					printf("\nvalor_endereco = %d\n" ,aux_var_global->endereco);
////					
////				pListaVar * var_interna = search_lista_vars_nome_char(pListaFuncChamadas->pListaVarsInterna, nome_variavel);
////				
////				//muda valor da variavel da lista de vars interna
////				reinit_str((&(var_interna)->valor));
////				copy_str(&(var_interna)->valor,	valor_chars);	
////					
////				//muda o valor somente da variavel na memoria global
////				aux_var_global = *pListaVars;
////				while(aux_var_global != NULL && aux_var_global->endereco != var_prototipo->endereco)
////					aux_var_global = aux_var_global->prox;
////				
////				reinit_str((&(aux_var_global)->valor));
////				copy_str(&(aux_var_global)->valor,	valor_chars);				
////			}
//		}
//		
//		else
//		{
//			pListaVar * var_interna = search_lista_vars_nome_char(pListaFuncChamadas->pListaVarsInterna, nome_variavel);
//			
//			//muda valor da variavel da lista de vars interna
//			reinit_str((&(var_interna)->valor));
//			copy_str(&(var_interna)->valor,	valor_chars);
//			
//			//muda o valor somente da variavel na memoria global
//			aux_var_global = *pListaVars;
//			while(aux_var_global != NULL && aux_var_global->endereco != var_interna->endereco)
//				aux_var_global = aux_var_global->prox;
//			
//			reinit_str((&(aux_var_global)->valor));
//			copy_str(&(aux_var_global)->valor,	valor_chars);
//		}	
//	}
//	else
//	{
//		pListaVar * search_var = search_lista_vars_nome_char(*pListaVars, nome_variavel);
//		//muda valor da variavel main;
//		change_valor_valor_lista_listas_vars(search_var, atoi(valor_chars)); 
//	}
//}


void muda_valores_variaveis_calculo(pListaVar * search_var, char nome_variavel[100], 
	char valor_calc_chars[100], int result_calc, pListaVar **pListaVars, pListaFunc * pListaFuncChamadas)
{
	pListaVar * aux_var_global;
	
	if( !isEmpty_lista_funcoes(pListaFuncChamadas))
	{
		pVars_prototipo * var_prototipo = search_lista_vars_argumento_func_chars(pListaFuncChamadas->pListaVars_prototipo, nome_variavel);
		
		if(var_prototipo != NULL)
		{
			reinit_str((&(var_prototipo)->valor));
			//muda valor do parametro, lista da funcao
			copy_str(&(var_prototipo)->valor, valor_calc_chars);
			
			//muda o valor somente da variavel na memoria global
			aux_var_global = *pListaVars;
			while(aux_var_global != NULL && aux_var_global->endereco != var_prototipo->endereco)
				aux_var_global = aux_var_global->prox;
			
			reinit_str((&(aux_var_global)->valor));
			copy_str(&(aux_var_global)->valor,	valor_calc_chars);
			
			
			if(var_prototipo->pont)
			{
				//muda valor para todas que ela aponta
				aux_var_global = *pListaVars;
				while(aux_var_global != NULL)
				{
//					printf("\nvalor_pont = %d", aux_var_global->valor_endereco);
//					
//					printf("\nvalor_endereco = %d\n" ,aux_var_global->endereco);
					
					
					if(aux_var_global->ponteiro && aux_var_global->valor_endereco == var_prototipo->valor_endereco)
					{
						reinit_str((&(aux_var_global)->valor));
						copy_str(&(aux_var_global)->valor,	valor_calc_chars);
					}
					else if( !aux_var_global->ponteiro && aux_var_global->endereco == var_prototipo->valor_endereco)
					{
						reinit_str((&(aux_var_global)->valor));
						copy_str(&(aux_var_global)->valor,	valor_calc_chars);
					}
						
					
					aux_var_global = aux_var_global->prox;
				}	
			}//
//			else
//			{
////					printf("\nvalor_pont = %d", aux_var_global->valor_endereco);
////					
////					printf("\nvalor_endereco = %d\n" ,aux_var_global->endereco);
//					
//				pListaVar * var_interna = search_lista_vars_nome_char(pListaFuncChamadas->pListaVarsInterna, nome_variavel);
//				
//				//muda valor da variavel da lista de vars interna
//				reinit_str((&(var_interna)->valor));
//				copy_str(&(var_interna)->valor,	valor_calc_chars);	
//					
//				//muda o valor somente da variavel na memoria global
//				aux_var_global = *pListaVars;
//				while(aux_var_global != NULL && aux_var_global->endereco != var_prototipo->endereco)
//					aux_var_global = aux_var_global->prox;
//				
//				reinit_str((&(aux_var_global)->valor));
//				copy_str(&(aux_var_global)->valor,	valor_calc_chars);				
//			}
		}
		
		else
		{
			pListaVar * var_interna = search_lista_vars_nome_char(pListaFuncChamadas->pListaVarsInterna, nome_variavel);
			
			reinit_str((&(var_interna)->valor));
			//muda valor da variavel da lista de vars interna
			copy_str(&(var_interna)->valor,	valor_calc_chars);
			
			//muda o valor somente da variavel na memoria global
			aux_var_global = *pListaVars;
			while(aux_var_global != NULL && aux_var_global->endereco != var_interna->endereco)
				aux_var_global = aux_var_global->prox;
			
			reinit_str((&(var_interna)->valor));
			copy_str(&(var_interna)->valor,	valor_calc_chars);
		}	
	}
	else
	{
		//muda valor da variavel main;
		change_valor_valor_lista_listas_vars(search_var, result_calc); 
	}
}



void inserir_variaveis_declaracao_dentro_funcao(pListaVar ** pListaVars, 
    											pListaFunc * pListaFuncChamadas,
												char string[100][100], int tl)
{
//	&*pListaFuncChamadas
	//ADD VARIAVEIS
	StrDin * nome;
	StrDin * valor;
	
	pListaVar * aux_copia;
	int endereco;
	char ponteiro;
	int i, i_linha;
	char aux_nome[100];
	char aux_valor[100];
	
	init_str(&nome);
	init_str(&valor);
	ponteiro=0;
	
	
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
				if(string[i][i_linha] == '*')
					i++;
				else	
					inserir_char(&valor, string[i][i_linha++]);
			}
				
			i++;
		}
		
		//PROCURAR SE A VAR JA TA NA LISTA
		//INSERIR NA PILHA DE VARS
		

		pListaVar * search_nome = search_lista_vars_nome_strdin(*pListaVars, nome); 
//		if( !procura_variavel(aux_nome, *pListaVars, pListaFuncChamadas))
		if(search_nome == NULL)
		{
			//INSERE NA PILHA DE VARIAVEIS GLOBAIS
			inserir_listas_vars_inicio(&*pListaVars, nome, valor, 0, ponteiro); 
//			printf("%d", (*pListaVars)->endereco);
			
			//INSERIR NA FUNCAO DE CHAMADA TAMBEM TAMBEM
			if(pListaFuncChamadas != NULL)
			{
				//COPIA VAR QUE ACABOU DE INSERIR NA PILhA (INICIO) DE VARS GLOBAL
				aux_copia = copy_listas_var(*pListaVars);
				
				//INSERE NA PILHA DE VARIAVEIS DA FUNCAO QUE ESTA EM EXECUCAO
				
				inserir_listas_vars_inicio(&(pListaFuncChamadas)->pListaVarsInterna, 
					    aux_copia->nome, aux_copia->valor, aux_copia->valor_endereco, aux_copia->ponteiro);
				
				//INSERIR O MESMO ENDERECO EM MEMORIA;	    
				pListaFuncChamadas->pListaVarsInterna->endereco =  (*pListaVars)->endereco;		 
				
				//DESREFERENCIA A VAR AUX_COPIA    
				aux_copia->nome = aux_copia->valor = NULL;    
				aux_copia = NULL;
			}
		}
		else
		{
			reinit_str(&(search_nome)->valor);
			search_nome->valor = valor;
	
//	//
//			strdin_to_chars_no_tl(nome, aux_nome);
//			strdin_to_chars_no_tl(valor, aux_valor);
////			muda_valores_variaveis_calculo(search_nome, aux_nome, aux_valor, atoi(aux_valor), &*pListaVars, pListaFuncChamadas);
////	
//			muda_valores_variaveis_atribuicao(aux_nome, aux_valor, &*pListaVars, pListaFuncChamadas);
		}
		
		init_str(&nome); //DESREFERENCIA POS JA ADD NA LISTA
		init_str(&valor); //DESREFERENCIA POS JA ADD NA LISTA
	}
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
		copia_funcao_search->total_linhas, 
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
	int valor_endereco_vars_global;
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
		
		//ENDERECO DA VARIAVEL NO QUAL ELE APONTA
		var_pilha = 
			search_lista_vars_nome_char(*pListaVars, func_chamada[pos_var] /*pos_var=nome da var na pilha de var de execucao*/);  
		
		copy_str_rec(&nome, variaveis_funcao->nome);
		
		if(variaveis_funcao->pont) //VARIAVEL EH PONTEIRO
		{
			while(var_pilha->ponteiro)
				var_pilha = search_lista_vars_endereco(*pListaVars, var_pilha->valor_endereco);
				
			valor_endereco_vars_global = var_pilha->endereco; //PEGO VALOR
			copy_str_rec(&valor, var_pilha->valor);
			ponteiro=1;
		}
		else
		{
			ponteiro=0;
			copy_str_rec(&valor, var_pilha->valor);
			valor_endereco_vars_global = 0;
		}	
		
		//COLOCA ENDERECO NA VARIAVEL DE PROTOTIPO COM O MESMO ENDERECO DA PILHA DE ENDERECO
		endereco += 4; //+4 assim como no inser_lista_vars
		variaveis_funcao->endereco = endereco; 
		variaveis_funcao->valor_endereco = var_pilha->endereco;
		
		
		//INSERIR VARIAVEL NA PILHA DE EXECUCAO
		inserir_listas_vars_inicio(&*pListaVars, nome, valor, valor_endereco_vars_global, ponteiro);
		
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

int executa_calc_priori(char * string, pListaVar * pListaVars)
{
	int tl, aux, n1, n2;
	pListaVar * search_var;
	char valor_aux[100];
	char aritmet[100][50];
	
	tl=0;
	//PEGA SOMENTE OS NUMEROS E OPERADORES
	split_calc_printf(aritmet, &tl, string, pListaVars);
	
	tl--; //coloca tl na pos -1 
	
	while(tl > 1)
	{
		aux = tl;
		while(aux > 0 && strcmp(aritmet[aux], "*") != 0 && strcmp(aritmet[aux], "/") != 0)
			aux--;
//				
//		int i;
//		for(i=0 ; i < tl ; i++)
//			printf("\n%s", aritmet[i]);
		
		if(strcmp(aritmet[aux], "*") == 0 || strcmp(aritmet[aux], "/") == 0)
		{

			n1 = atoi(aritmet[aux-1]);
			n2 = atoi(aritmet[aux+1]);
		
			if(strcmp(aritmet[aux], "*") == 0)
				int_to_chars(valor_aux, n1*n2);
			else // /
				int_to_chars(valor_aux, n1/n2);	
		}
		else
		{
			aux=tl;
			while(aux > 0 && strcmp(aritmet[aux], "+") != 0 && strcmp(aritmet[aux], "-") != 0)
				aux--;
				
			n1 = atoi(aritmet[aux-1]);
			n2 = atoi(aritmet[aux+1]);
		
			if(strcmp(aritmet[aux], "+") == 0)
				int_to_chars(valor_aux, n1+n2);
			else // -
				int_to_chars(valor_aux, n1-n2);
		}
		
		strcpy(aritmet[aux-1], valor_aux);
			
		while(aux <= tl-2)
		{
			strcpy(aritmet[aux], aritmet[aux+2]);
			aux++;				
		}
		
		tl = tl - 2;
		
//		for(i=0 ; i < tl ; i++)
//			printf("\n%s", aritmet[i]);
	}
	
	return atoi(aritmet[0]);
}


void pega_nome_variavel_linha_calc(char * nome_variavel, char * linha_char)
{
	int i, j;
	
	for(i=0 ; linha_char[i] == ' ';  i++);
	
	for(j=0 ; linha_char[i] != ' ' &&  linha_char[i] != '='; i++)
		if(linha_char[i] != '	' && linha_char[i] != ' ' && linha_char[i] != '*' && linha_char[i] != '&')
			nome_variavel[j++] = linha_char[i];
	nome_variavel[j] = '\0';	
}

void retira_nome_variavel_linha(char * linha_char)
{
	int i, j;
	for(i=0 ; linha_char[i] != '=' ; i++);
	
	if(linha_char[i] == '=')
		i++;
		
	for(j=0 ; linha_char[i] != '\0' ; i++, j++)
			linha_char[j] = linha_char[i];	
	linha_char[j]= '\0';						
}
//
//void muda_valores_variaveis_calculo(pListaVar * search_var, char nome_variavel[100], 
//	char valor_calc_chars[100], int result_calc, pListaVar **pListaVars, pListaFunc * pListaFuncChamadas)
//{
//	pListaVar * aux_var_global;
//	
//	if( !isEmpty_lista_funcoes(pListaFuncChamadas))
//	{
//		pVars_prototipo * var_prototipo = search_lista_vars_argumento_func_chars(pListaFuncChamadas->pListaVars_prototipo, nome_variavel);
//		
//		if(var_prototipo != NULL)
//		{
//			//muda valor do parametro, lista da funcao
//			copy_str(&(var_prototipo)->valor, valor_calc_chars);
//			
//			if(var_prototipo->pont)
//			{
//				//muda valor para todas que ela aponta
//				aux_var_global = *pListaVars;
//				while(aux_var_global != NULL)
//				{
////					printf("\nvalor_pont = %d", aux_var_global->valor_endereco);
////					
////					printf("\nvalor_endereco = %d\n" ,aux_var_global->endereco);
//					
//					
//					if(aux_var_global->ponteiro && aux_var_global->valor_endereco == var_prototipo->valor_endereco)
//					{
//						reinit_str((&(aux_var_global)->valor));
//						copy_str(&(aux_var_global)->valor,	valor_calc_chars);
//					}
//					else if( !aux_var_global->ponteiro && aux_var_global->endereco == var_prototipo->valor_endereco)
//					{
//						reinit_str((&(aux_var_global)->valor));
//						copy_str(&(aux_var_global)->valor,	valor_calc_chars);
//					}
//						
//					
//					aux_var_global = aux_var_global->prox;
//				}	
//			}
//			else
//			{
////					printf("\nvalor_pont = %d", aux_var_global->valor_endereco);
////					
////					printf("\nvalor_endereco = %d\n" ,aux_var_global->endereco);
//					
//				pListaVar * var_interna = search_lista_vars_nome_char(pListaFuncChamadas->pListaVarsInterna, nome_variavel);
//				
//				//muda valor da variavel da lista de vars interna
//				copy_str(&(var_interna)->valor,	valor_calc_chars);	
//					
//				//muda o valor somente da variavel na memoria global
//				aux_var_global = *pListaVars;
//				while(aux_var_global != NULL && aux_var_global->endereco != var_prototipo->endereco)
//					aux_var_global = aux_var_global->prox;
//				
//				reinit_str((&(aux_var_global)->valor));
//				copy_str(&(aux_var_global)->valor,	valor_calc_chars);				
//			}
//		}
//		
//		else
//		{
//			pListaVar * var_interna = search_lista_vars_nome_char(pListaFuncChamadas->pListaVarsInterna, nome_variavel);
//			
//			//muda valor da variavel da lista de vars interna
//			copy_str(&(var_interna)->valor,	valor_calc_chars);
//			
//			//muda o valor somente da variavel na memoria global
//			aux_var_global = *pListaVars;
//			while(aux_var_global != NULL && aux_var_global->endereco != var_interna->endereco)
//				aux_var_global = aux_var_global->prox;
//			
//			reinit_str((&(var_interna)->valor));
//			copy_str(&(var_interna)->valor,	valor_calc_chars);
//		}	
//	}
//	else
//	{
//		//muda valor da variavel main;
//		change_valor_valor_lista_listas_vars(search_var, result_calc); 
//	}
//}



void executa_calculo(char * linha_char, pListaVar **pListaVars, pListaFunc * pListaFuncChamadas)
{
	//nome da variavel que recebe valor
	char nome_variavel[100];
	
	//aux para int to chars
	char valor_calc_chars[100];
	int result_calc;
	
	//pesquisar variavel pelo nome e depois por endereco
	pListaVar * search_var, * aux_var_global;
	
	pega_nome_variavel_linha_calc(nome_variavel, linha_char);
	
	//pesquisar variavel pelo nome e depois por endereco
	search_var = search_lista_vars_nome_char(*pListaVars, nome_variavel);
	
	retira_nome_variavel_linha(linha_char);
	
//	result_calc = executa_calc_printf(linha_char, *pListaVars);
	result_calc = executa_calc_priori(linha_char, *pListaVars);
	int_to_chars(valor_calc_chars, result_calc);
	
	muda_valores_variaveis_calculo(search_var, nome_variavel, valor_calc_chars, result_calc, &*pListaVars, pListaFuncChamadas);
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
//	exibir_str(linhas->linha);
	
	if( !isEmpty_lista_linhas_interna_func(linhas))
	{
		strdin_to_chars(linhas->linha, linha_char, &tl);
		//0 calculo - 1 chamada de funcao;
		if(linhas->tipo == 0) // calculo
		{
			executa_calculo(linha_char, &*pListaVars, *pListaFuncChamadas);
			
		}
		else if(linhas->tipo == 1) //chamada de funcao
		{
			(*pListaFuncChamadas)->linha++; //INCREMENTA LINHA ANTES DE INSERIR NOVA FUNCAO NA PILHA
			//printar_arquivo_tela_pos_atual(nome_programa_fonte, (*pListaFuncChamadas)->linha);
			
			empilha_funcao(linha_char, &*pListaVars, pListaFuncoes, &*pListaFuncChamadas);
			remover_inicio_linhas_interna_func_no_return(&(*pListaFuncChamadas)->pListaLinhas_func);	
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
				
				result_calculo_argument = executa_calc_priori(saida[argumento], pListaVars);
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

void remover_variaveis_pilha_variaveis(pListaVar ** pListaVars, pListaFunc ** pListaFuncChamadas)
{
	pVars_prototipo * variaveis_prototipo, *aux_prototipo;
	pListaVar * vars_interna, *aux_interna;
	
	//TRATAMENTO DAS VARIAVEIS DE PROTOTIPO
	variaveis_prototipo = (*pListaFuncChamadas)->pListaVars_prototipo;
	while(variaveis_prototipo != NULL)
	{
		//REMOVE DA PILHA GLOBAL DA LISTA DE VARIAVEIS
		remover_listas_vars_endereco_no_return(&*pListaVars, variaveis_prototipo->endereco);
		aux_prototipo = variaveis_prototipo;
		variaveis_prototipo = variaveis_prototipo->prox;
	}
	//REMOVE REINICIA LISTA DE PROTOTIPO INTERNA
	reinit_lista_vars_argumento_func_rec(&(*pListaFuncChamadas)->pListaVars_prototipo);
	
	
	//TRATAMENTO VARIAVEIS INTERNAS DA FUNCAO
	vars_interna = (*pListaFuncChamadas)->pListaVarsInterna;
	while(vars_interna != NULL)
	{
		//REMOVE DA PILHA GLOBAL DA LISTA DE VARIAVEIS
		remover_listas_vars_endereco_no_return(&*pListaVars, vars_interna->endereco);
		vars_interna = vars_interna->prox;
	}
	//REMOVE REINICIA LISTA DE VARIAVEIS INTERNA
	reinit_listas_vars(&(*pListaFuncChamadas)->pListaVarsInterna);
}


void inserir_variaveis_interna_pilha_vars(char linha[100], pListaVar ** pListaVars, 
    pListaFunc ** pListaFuncChamadas)
{
	char saida[100][100];
	int tl;
	
	tl=0;
	//splita linha lida do arquivo
	split_variaveis_atribuicoes(linha, saida, &tl); 

	
	//inserir variaveis na pilha de variaveis global
	inserir_variaveis_declaracao_dentro_funcao(&*pListaVars, *pListaFuncChamadas, saida, tl);
}

void incrementa_linha_funcao(pListaFunc ** pListaFuncChamadas)
{
	if((*pListaFuncChamadas)->cont_execucao == 0)
		(*pListaFuncChamadas)->cont_execucao++;
	else
	{
		(*pListaFuncChamadas)->linha++;
//		(*pListaFuncChamadas)->total_linhas++;
		(*pListaFuncChamadas)->cont_execucao++;
	}	
}

void remover_funcao_linhas_vazias(pListaVar **pListaVars,  pListaFunc ** pListaFuncChamadas)
{
	/*
	REMOVER A FUNCAO DA LISTA DE FUNCOES DE CHAMADAS E VARIAVEIS DA LISTA DE VARIAVEIS
	SE NAO VAZIA A LISTA DE FUNCOES
	SE VAZIA LISTA DE LINHAS DA FUNCAO
	SE O CONTADOR DE EXECUCAO FOR MAIOR QUE A QUANTIDADE DE LINHAS DA FUNCAO, POIS
	QUANDO ENTRA EM OUTRA TELA NA ULTIMA LINHA, PRECISA RETORNAR NA ULTIMA LINHA NOVAMENTE, 
	PARA DAI ENTAO RETIRAR A FUNCAO DA LISTA DE FUNCOES
	*/
	
	

		do
		{
			//REMOVE AS VARIAVEIS DE ARGUMENTO DA FUNCAO DA PILHA DE VARIAVEIS GLOBAIS;
			remover_variaveis_pilha_variaveis(&*pListaVars, &*pListaFuncChamadas);
			
			//REMOVE TOPO DA PILHA DE FUNCOES DE CHAMADA;
			remover_inicio_func_no_return(&*pListaFuncChamadas);
		
		}while( !isEmpty_lista_funcoes(*pListaFuncChamadas) && 
				isEmpty_lista_linhas_interna_func((*pListaFuncChamadas)->pListaLinhas_func) &&
				(*pListaFuncChamadas)->cont_execucao > (*pListaFuncChamadas)->total_linhas );

}

void split_linha_return(char *line, char saida[100][50], int * tl)
{
	int i;
	const char s[11] = " 	;";
	char *token;
	
	for(i=0 ; line[i] != 59 /* 59= ';' */ && line[i] != '\0' ; i++);
	
	line[++i] = '\0';	
//	puts(line);
	token = strtok(line, s);

	while( token != NULL ) {
		if(strlen(token) > 0 && strcmp(token, "\0") != 0 && strcmp(token, "\n") != 0)
			strcpy(saida[*tl], token);		
		token = strtok(NULL, s);
		(*tl)++;
	}
		
}

void change_valor_variavel_return_funcao(int novo_valor, pListaVar ** variavel_atualizar)
{
	char parse_int_to_chars[100];
	
	int_to_chars(parse_int_to_chars, novo_valor); //valor inteiro para vetor de char
	reinit_str(&(*variavel_atualizar)->valor); //removo valor ja existente liberando memoria
	(*variavel_atualizar)->valor = vetchar_to_strDin(parse_int_to_chars); //novo valor na variavel
}

void tratar_return(char * linha, pListaVar **pListaVars, pListaFunc ** pListaFunChamadas)
{
	int tl, tl_for_calc, valor_return;
	char saida[100][50], for_calculo[100][50], aux_parse_types[100];
	pListaVar * search_var;
	
	
	tl=0;
	split_linha_return(linha, saida, &tl);
	
	//se tiver variaveis ou sei la o que mais retornando;
	if(tl > 1)
	{
		if(eh_variavel(saida[1]))
		{
			search_var = search_lista_vars_nome_char(*pListaVars, saida[1]);
			strdin_to_chars_no_tl(search_var->valor, aux_parse_types); 
			valor_return = atoi(aux_parse_types);
		}
		else if(is_number(saida[1]))
		{
			//chars para inteiro//??
			valor_return = atoi(saida[1]);
		}
		else //eh calculo
		{
			tl_for_calc=0;
			split_calc_printf(for_calculo, &tl_for_calc, saida[1], *pListaVars);
			valor_return = executa_calc_priori(saida[1], *pListaVars);
		}
		
		//se igual a null e pq nenhuma variavel vai receber o retorno da funcao
		if((*pListaFunChamadas)->variavel_return != NULL)
			//ATUALIZA VALOR DA VARIAVEL QUE CHAMOU A FUNCAO
			change_valor_variavel_return_funcao(valor_return, &(*pListaFunChamadas)->variavel_return);
	}	
}

void split_nome_variavel_funcao_chamada(char * linha)
{
	//asdasd = 
	int tl;
	char pega_nome_split[100][50];
	const char s[23] = " 	=";
	char *token;
	
	token = strtok(linha, s);
	tl=0;
	
	while( token != NULL ) {
		strcpy(pega_nome_split[tl], token);		
		token = strtok(NULL, s);
		tl++;
	}
	
	strcpy(linha, pega_nome_split[0]);
}

void retira_nome_variavel(char * linha)
{
	//preciso tirar o nome da variavel que vai receber o valor da funcao
	int i, j;
	
	i=0;
	while(linha[i] != '=')
		i++; 
	if(linha[i] == '=')
	{
		i++;
		while(linha[i] == ' ')
			i++;
		
		if(linha[i] != ' ')
		{
			j=0;
			while(linha[i] != '\0')
			{
				linha[j] = linha[i];
				j++;
				i++;
			}
				
			linha[j] = '\0';
				
		}		
	}
}

void empilha_funcao_com_variavel_return(char * linha, pListaVar ** pListaVars, pListaFunc * pListaFuncoes, 
	pListaFunc ** pListaFuncChamadas)
{
	char nome_var_split[100];
	pListaVar *  search_var;
	
	strcpy(nome_var_split, linha);
	split_nome_variavel_funcao_chamada(nome_var_split); //splita para pegar nome da variavel que recebe o valor da funcao
	
	
	search_var = search_lista_vars_nome_char(*pListaVars, nome_var_split); //procura o ponteiro da variavel que esta na pilha de variaveis
	
	//preciso tirar o nome da variavel que vai receber o valor da funcao
	retira_nome_variavel(linha);
	
	empilha_funcao(linha, pListaVars, pListaFuncoes, pListaFuncChamadas);//empilha funcao
	
	//atribui no topo da funcao a variavel que recebe o retorna, pois ali no empilha, variavel_return = NULL
	(*pListaFuncChamadas)->variavel_return = search_var; //variavel de returno de funcao aponta para variavel correta da pilha de variaveis globais
}

void executa_pilha_chamadas_funcoes(pListaFunc * pListaFuncoes, pListaFunc ** pListaFuncChamadas, 
	pListaVar ** pListaVars, pListaString ** pListaPrintfs, int pos_main_exibir, char *nome_programa_fonte)
{
	StrDin * linha;
	char linha_char[100];
	char chamou_func=0;
	int tipo, tl;
	
	pLinhas_func * linhas = (*pListaFuncChamadas)->pListaLinhas_func; // CABECA DA LISTA DAS LINHAS DA FUNCAO

	//ENTROU NA FUNCAO, PRINTA NA PRIMEIRA LINHA
	if((*pListaFuncChamadas)->cont_execucao == -1)
	{
		printar_arquivo_tela_pos_atual(nome_programa_fonte, (*pListaFuncChamadas)->linha);
		(*pListaFuncChamadas)->cont_execucao = 0; //++
	}
	else
	{
		//EXECUTEI, SAI DA FUNCAO, EXECUCAO ULTRAPASSOU QUANDTIDADE DO TOTAL DE LINHAS
		if(	(*pListaFuncChamadas)->cont_execucao == (*pListaFuncChamadas)->total_linhas )
			(*pListaFuncChamadas)->cont_execucao++;
		
		
		if( !isEmpty_lista_linhas_interna_func(linhas) && 
			(*pListaFuncChamadas)->cont_execucao < (*pListaFuncChamadas)->total_linhas)
		{
			strdin_to_chars(linhas->linha, linha_char, &tl); //get linha in chars
			//0 calculo - 1 chamada de funcao;
			
			if(linhas->tipo == 0) // calculo
			{
				executa_calculo(linha_char, &*pListaVars, *pListaFuncChamadas);
				incrementa_linha_funcao(&*pListaFuncChamadas); //++ LINHA
				
				if((*pListaFuncChamadas)->cont_execucao >= -1)
					printar_arquivo_tela_pos_atual(nome_programa_fonte, (*pListaFuncChamadas)->linha+1);
				else
					printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir-1);
					
				remover_inicio_linhas_interna_func_no_return(&(*pListaFuncChamadas)->pListaLinhas_func);
			}
			else if(linhas->tipo == 1) //chamada de funcao
			{
				incrementa_linha_funcao(&*pListaFuncChamadas); //++ LINHA

				remover_inicio_linhas_interna_func_no_return(&(*pListaFuncChamadas)->pListaLinhas_func);
				
				empilha_funcao(linha_char, &*pListaVars, pListaFuncoes, &*pListaFuncChamadas);
//				
				executa_pilha_chamadas_funcoes(pListaFuncoes, 
													&*pListaFuncChamadas, 
													&*pListaVars, 
													&*pListaPrintfs, 
													pos_main_exibir,
													nome_programa_fonte);
			} 
			else if(linhas->tipo == 2) //printf
			{
				incrementa_linha_funcao(&*pListaFuncChamadas); //++ LINHA
				
				if((*pListaFuncChamadas)->cont_execucao >= -1)
					printar_arquivo_tela_pos_atual(nome_programa_fonte, (*pListaFuncChamadas)->linha+1);
				else
					printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir-1);
				
				remover_inicio_linhas_interna_func_no_return(&(*pListaFuncChamadas)->pListaLinhas_func);
				
				guardar_printf(linha_char, &*pListaPrintfs, *pListaVars);
			}
			else if(linhas->tipo == 3) //declaracao de variaveis
			{
				incrementa_linha_funcao(&*pListaFuncChamadas); //++ LINHA
				
				if((*pListaFuncChamadas)->cont_execucao >= -1)
					printar_arquivo_tela_pos_atual(nome_programa_fonte, (*pListaFuncChamadas)->linha+1);
				else
					printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir-1);
				
				remover_inicio_linhas_interna_func_no_return(&(*pListaFuncChamadas)->pListaLinhas_func);
				
				
				inserir_variaveis_interna_pilha_vars(linha_char, &*pListaVars, &*pListaFuncChamadas);
			}
			else if(linhas->tipo == 4) //return
			{
				incrementa_linha_funcao(&*pListaFuncChamadas); //++ LINHA
				//
//				(*pListaFuncChamadas)->linha += (*pListaFuncChamadas)->total_linhas-1;
//				(*pListaFuncChamadas)->cont_execucao == (*pListaFuncChamadas)->total_linhas;
				
				if((*pListaFuncChamadas)->cont_execucao >= -1)
					printar_arquivo_tela_pos_atual(nome_programa_fonte, (*pListaFuncChamadas)->linha+1);
				else
					printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir-1);
				
				tratar_return(linha_char, &*pListaVars, &*pListaFuncChamadas);
				
				//REMOVE TODAS AS LINHAS DESTA FUNCAO.
				remover_todas_linhas_interna_func_rec(&(*pListaFuncChamadas)->pListaLinhas_func);
			}
			else if(linhas->tipo == 5) //chamada funcao com return para variavel
			{
				incrementa_linha_funcao(&*pListaFuncChamadas); //++ LINHA
				
				remover_inicio_linhas_interna_func_no_return(&(*pListaFuncChamadas)->pListaLinhas_func);
				
				empilha_funcao_com_variavel_return(linha_char, &*pListaVars, pListaFuncoes, &*pListaFuncChamadas);
				
				executa_pilha_chamadas_funcoes(pListaFuncoes, 
													&*pListaFuncChamadas, 
													&*pListaVars, 
													&*pListaPrintfs, 
													pos_main_exibir,
													nome_programa_fonte);
			}
		}
	}	
		//REMOVER A FUNCAO DA LISTA DE FUNCOES DE CHAMADAS E VARIAVEIS DA LISTA DE VARIAVEIS
		//SE FUNCAO NAO TIVER MAIS LINHAS PARA EXECUTAR
	if( !isEmpty_lista_funcoes(*pListaFuncChamadas) && 
		isEmpty_lista_linhas_interna_func((*pListaFuncChamadas)->pListaLinhas_func) && 
		(*pListaFuncChamadas)->cont_execucao > (*pListaFuncChamadas)->total_linhas ) 
	{	
		remover_funcao_linhas_vazias(&*pListaVars, &*pListaFuncChamadas);
		if(!isEmpty_lista_funcoes(*pListaFuncChamadas))
			printar_arquivo_tela_pos_atual(nome_programa_fonte, (*pListaFuncChamadas)->linha+1);	
	}
	
}

void pega_nome_arquivo(char * nome)
{
	FILE * arq = NULL;
	
	do
	{
		system("cls");
		
		printf("NOME: ");
		fflush(stdin);	gets(nome);	
		
		arq = fopen(nome, "r");
		
		if(strlen(nome) <= 0 || arq == NULL)
		{
			printf("NOME INCORRETO.\nENTER PARA CONTINUAR");
			getch();
		}
		
	}while(strlen(nome) <= 0 || arq == NULL);
	
	fclose(arq);
	
}

void carregar_inicio_programa_fonte(pListaFunc ** pListaFuncoes, pListaFunc ** pListaFuncChamadas,
	pListaVar ** pListaVars, pListaString ** pListaPrintfs, int * pos_main_exibir, 
	char *nome_programa_fonte, FILE ** arq)
{
	if(*arq != NULL)
	{
		//JA FOI ABERTO UM ARQUIVO
		fclose(*arq);
		
		//INICIAR OU REINICIAR LISTAS;
		reinit_lista_string_strdin(&*pListaPrintfs);
		reinit_lista_func(&*pListaFuncChamadas);
		reinit_lista_func(&*pListaFuncoes);
		reinit_listas_vars(&*pListaVars);
	}
	else
	{
		init_lista_string(&*pListaPrintfs);
		init_lista_func(&*pListaFuncChamadas);
		init_lista_func(&*pListaFuncoes);
		init_listas_vars_main(&*pListaVars);
	}

	//TELA PEGAR NOME
	pega_nome_arquivo(nome_programa_fonte);
	

	//LER TODAS FUNCOES E SUBIR NA MEMORIA.
	ler_todas_funcoes(nome_programa_fonte, &*pListaFuncoes);
	
	//POSICIONAR INICIO DO MAIN;
	*pos_main_exibir = achar_posicao_main(nome_programa_fonte);
	
	//PRINTAR NA TELA INICIO DO PROGRAMA
	printar_arquivo_tela_pos_atual(nome_programa_fonte, *pos_main_exibir);
	
	//posicionar no arquivo na primeira implementacao do main.
	*arq = fopen(nome_programa_fonte, "r");
	posicionar_linha_implementacao_main(*arq, *pos_main_exibir);

}

int main()
{
	FILE * arquivo_codigo;
	int pos_main_exibir;
	char nome_programa_fonte[30];
	
	pListaFunc * pListaFuncoes;
	pListaFunc * pListaFuncChamadas; //pilha de chamada de funcoes!
	pListaVar * pListaVars;
	pListaString * pListaPrintfs;
	
	char linha[100];
	char saida[100][100];
	int tl;
	char key1, key2; //OPERACAO DE MENU PRINCIPAL;
	arquivo_codigo = NULL; 
	
	carregar_inicio_programa_fonte( &pListaFuncoes,
									&pListaFuncChamadas,
									&pListaVars,
									&pListaPrintfs,
									&pos_main_exibir,
									nome_programa_fonte,
									&arquivo_codigo );
	
	
	key1 = getch();
	while(key1 != 'q')
	{	
		while(key1 == 13 && key1 != 'q') //ENTER - executa linha
		{	
			if(isEmpty_lista_funcoes(pListaFuncChamadas))
			{
				//LER MAIN
				ler_linha_arquivo_main(arquivo_codigo, linha);
				
				//ENTRA NA FUNCAO E EXECUTA AS LINHAS
				if( eh_chamada_de_funcao(linha) ||  
					eh_variavel_com_chamada_de_funcao(linha) && 
					!eh_printf(linha))/* && 
						!eh_calculo_in_funcao(linha)))*/
				{
					if(eh_chamada_de_funcao(linha) && strstr(linha, "=") == NULL)
						empilha_funcao(linha, &pListaVars, pListaFuncoes, &pListaFuncChamadas);
					else if(eh_variavel_com_chamada_de_funcao(linha) && !eh_printf(linha))
						empilha_funcao_com_variavel_return(linha, &pListaVars, pListaFuncoes, &pListaFuncChamadas);
						
					executa_pilha_chamadas_funcoes(pListaFuncoes, 
													&pListaFuncChamadas, 
													&pListaVars, 
													&pListaPrintfs, 
													pos_main_exibir,
													nome_programa_fonte);	
				}
				else
				{
					if(strstr(linha, "}") != NULL || feof(arquivo_codigo))
					{
						printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir);
						printf("\n\n\t\t[ * ] - Programa chegou ao fim. :)");
					}
					else
					{
						//RETURN DENTRO DO MAIN
						if(eh_return(linha)) 
							key1 = 'q';
						
						//printf de saida
						else if(eh_printf(linha))
						{
							guardar_printf(linha, &pListaPrintfs, pListaVars);
							
							pos_main_exibir++;
							printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir); //printar na tela posicao atual do main
							
						}
						
						//DECLARACAO DE VARIAVEL COM VALOR
						else if((eh_declaracao_variavel_atribuicao(linha) && !eh_printf(linha)))
						{
							tl=0;
							split_variaveis_atribuicoes(linha, saida, &tl); //splita linha lida do arquivo
							inserir_variaveis_declaracao_dentro_funcao(&pListaVars, NULL, saida, tl);//inserir variaveis na lista de variaveis
							
							pos_main_exibir++;						
							printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir); //printar na tela posicao atual do main
						
						}
						
						//CALCULO
						else if(eh_calculo_in_funcao(linha))
						{
							//calculo dentro do main
							executa_calculo(linha, &pListaVars, pListaFuncChamadas);
							
							pos_main_exibir++;
							printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir); //printar na tela posicao atual do main
						}
						
						
					}
				}
			}
			else //nao vazia lista de chamadas
			{
				executa_pilha_chamadas_funcoes(pListaFuncoes, 
													&pListaFuncChamadas, 
													&pListaVars, 
													&pListaPrintfs, 
													pos_main_exibir,
													nome_programa_fonte);

				//SE LIBEROU TODAS FUNCOES DA LISTA DE EXECUCAO DE FUNCOES PRINTA O MAIN								
				if(isEmpty_lista_funcoes(pListaFuncChamadas))
				{
					pos_main_exibir++;
					printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir); 
					
				}
			}
				
			if(key1 != 'q')
				key1 = getch();
		}
		
		if( key1 != 'q')
		{
				key2 = getch();
			if(key1 == 0 && key2 == 67) //ver memoria
			{
				system("cls");
				exibir_listas_vars(pListaVars);	
			}
			else if(key1 == 0 && key2 == 66) //ver tela de execucao
			{
				
				//printar na tela posicao atual do main
				if(!isEmpty_lista_funcoes(pListaFuncChamadas) && pListaFuncChamadas->cont_execucao == 0)
					printar_arquivo_tela_pos_atual(nome_programa_fonte, pListaFuncChamadas->linha);
				else if(!isEmpty_lista_funcoes(pListaFuncChamadas) && pListaFuncChamadas->cont_execucao > 0)
					printar_arquivo_tela_pos_atual(nome_programa_fonte, pListaFuncChamadas->linha+1);	
				else
					printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_main_exibir);
			}
			else if(key1 == 0 && key2 == 68) //ver printfs - saida
			{
				system("cls");
				exibir_lista_string(pListaPrintfs);
			}
			else if(key1 == 0 && key2 == 65) //inserir um arquivo
			{
				carregar_inicio_programa_fonte( &pListaFuncoes,
												&pListaFuncChamadas,
												&pListaVars,
												&pListaPrintfs,
												&pos_main_exibir,
												nome_programa_fonte,
												&arquivo_codigo );
			}
		}
		
		if(key1 != 'q')
			key1 = getch();	
		
	}
	
	fclose(arquivo_codigo);

    return 0;

}


