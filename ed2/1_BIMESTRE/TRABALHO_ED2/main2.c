#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "meuconio.h"
#include "string_dinamica.h"
#include "variaveis_prototipo_funcao.h"
#include "chamadas_calculos_funcao.h"

#include "lista_funcoes.h"
#include "lista_pilha_variaveis.h"



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
	if(strstr(string, "=") != NULL && strstr(string, ";") != NULL)
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
			inserir_lista_vars_argumento_func(&*vars_cab, tipo, pont, nome, valor);
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
				
		
		fgets(line_read, 100, arq);
		(*linha_atual)++;
	}
	
	//acaba funcao ja na linha seguinte desta funcao
	if(strstr(line_read, "}") != NULL)
	{
		fgets(line_read, 1000, arq);
		(*linha_atual)++;
		pos_line=0;
	}
	
	//insere na lista de funcoes;
	inserir_lista_func(&*pLista_Funcoes, linha_inicio_funcao_implementacoes, pTipo_func, pNome_func, pVars_argumentos, pLinhas_interna);
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
	int i, i_linha;
	char ponteiro;
	
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
			inserir_listas_vars(&*pListaVars, nome, valor, 0, ponteiro); 
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
	int i, i_linha, j;
	while( token != NULL ) {
		printf( "%s\n", token );
		if(strcmp(token, "\n") != 0 && strcmp(token, "\0"))
			strcpy(saida[(*tl)++], token);
		token = strtok(NULL, split);
	}
}

pListaFunc * empilha_chamada_funcao(char func_chamada[100][100], pListaFunc *pListaFuncoes, 
	pListaFunc ** pListaFuncChamadas /*pilha de funcoes*/)
{
	//busca funcao com o nome da chamada
	pListaFunc * search_func = buscar_lista_funcao_nome(pListaFuncoes, vetchar_to_strDin(func_chamada[0]/*0=nome*/));
	
	//copia funcao
	pListaFunc * copia_funcao_search = copy_funcao(search_func);
	
	//insere funcao na lista de func chamadas
	inserir_lista_func(
		&*pListaFuncChamadas, 
		copia_funcao_search->linha, 
		copia_funcao_search->tipo, 
		copia_funcao_search->nome, 
		copia_funcao_search->pListaVars_prototipo,
		copia_funcao_search->pListaLinhas_func
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
	int valor_endereco;
	pListaVar * var_pilha;
	char ponteiro;
	int pos_var, endereco;
	
	pVars_prototipo * variaveis_funcao = pFuncao_chamada->pListaVars_prototipo; //VARIAVEIS DE PROTOTIPO
	pos_var=1; //1, pois 0 eh o nome da funcao
	while(variaveis_funcao != NULL)
	{
		init_str(&nome);
		init_str(&valor);
		ponteiro=0;
		
		printf("\n%s", func_chamada[pos_var]);
		//ENDERECO DA VARIAVEL NO QUAL ELE APONTA
		var_pilha = 
			search_lista_vars_nome_char(*pListaVars, func_chamada[pos_var] /*pos_var=nome da var na pilha de var de execucao*/);  
		
		if(variaveis_funcao->pont) //VARIAVEL EH PONTEIRO
		{
			valor_endereco = var_pilha->endereco; //PEGO VALOR
			copy_str_rec(&valor, var_pilha->valor);
		}
		else
		{
			copy_str_rec(&valor, var_pilha->valor);
			valor_endereco = 0;
		}	
			
		
		inserir_listas_vars(&*pListaVars, nome, valor, endereco, ponteiro);
		pos_var++;
		variaveis_funcao = variaveis_funcao->prox;
	}
}

int main()
{
	FILE * arquivo_execucao;
	int pos_atual;
	char nome_programa_fonte[30];
	pListaFunc * pListaFuncoes;
	pListaFunc * pListaFuncChamadas; //pilha de chamada de funcoes!
	pListaVar * pListaVars;
	char linha[100];
	
	init_lista_func(&pListaFuncChamadas);
	init_lista_func(&pListaFuncoes);
	init_listas_vars_main(&pListaVars);
	strcpy(nome_programa_fonte, "programa_ler.c");
	
	//LER TODAS FUNCOES E JOGA NA MEMORIA.
	ler_todas_funcoes(nome_programa_fonte, &pListaFuncoes);
	
	//EXIBIR O MARCADOR JA SELECIONADO A PRIMEIRA IMPLEMENTACAO DENTRO DO MAIN
	pos_atual = achar_posicao_main(nome_programa_fonte);
	printar_arquivo_tela_pos_atual(nome_programa_fonte, -1);
	
	//posicionar no arquivo na primeira implementacao do main.
	arquivo_execucao = fopen(nome_programa_fonte, "r");
	posicionar_linha_implementacao_main(arquivo_execucao, pos_atual);
	
	char saida[100][100];
	int tl;
	char key = getch();
	while(!feof(arquivo_execucao) && key != 'q')
	{	
		switch(key)
		{
			case 13: 
				ler_linha_arquivo_main(arquivo_execucao, linha);
						
				if(strstr(linha, "}") != NULL)
					key = 'q';				
				
				//DECLARACAO NO MAIN
				else if(eh_declaracao_variavel_atribuicao(linha) && isEmpty_lista_funcoes(pListaFuncChamadas))
				{
					tl=0;
					split_variaveis_atribuicoes(linha, saida, &tl); //splita linha lida do arquivo
					inserir_variaveis_declaracao_dentro_funcao(&pListaVars, saida, tl);//inserir variaveis na lista de variaveis
							
											
					printar_arquivo_tela_pos_atual(nome_programa_fonte, pos_atual); //printar na tela posicao atual do main
					pos_atual++;
				}
				
				
				else if(eh_chamada_de_funcao(linha))
				{
					tl=0;
					split_chamada_funcao(linha, saida, &tl);
					pListaFunc * funcao_prototipo_achada = 
						empilha_chamada_funcao(saida, pListaFuncoes, &pListaFuncChamadas);
					
					inserir_variaveis_prototipo_funcao(saida, &pListaVars, funcao_prototipo_achada);
					
				}
				//INICIAR A LEITURA DAS LINHAS
				break;
		}
		
				

		key=getch();	
	}
	
	fclose(arquivo_execucao);

//	mostrar_lista_funcao(pListaFuncoes);
    return 0;

//	StrDin * str1;
//	StrDin * str2;
//	init_str(&str1);
//	init_str(&str2);
//	
//	inserir_char(&str1, 'A');
//	inserir_char(&str2, 'A');
//	
//		inserir_char(&str1, 'B');
//	inserir_char(&str2, 'B');
//	
//		inserir_char(&str1, 'C');
//	inserir_char(&str2, 'C');
//	
//	printf("%d", strdin_igual(str1, str2));
}


