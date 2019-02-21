#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>


#define CAMINHO_ARQUIVO_LIVRO_BIN "livro_bin.bin"


// ------------------------------- structs lista livro bin funcoes ----------------------- //
struct livroBin
{
	char autor[100];
	char titulo_livro[100];
	char editora[100];
	int ano;
	int pagina;
};
typedef struct livroBin LivroBin;

struct Pont_LivroBin
{
	LivroBin livroBin;
	struct Pont_LivroBin * prox;
};
typedef struct Pont_LivroBin pLivroBin;
// ---------------------------------------------------------------------------------------- //


// ----------------------------------- structs string dinamica ---------------------------- //
struct StringDin
{
	char ch;
	struct StringDin * prox;
};
typedef struct StringDin StrDin;
// ---------------------------------------------------------------------------------------- //


// ----------------------------- structs listas em memoria -------------------------------- //
struct Pont_Autor
{
	StrDin * sobrenome;
	StrDin * nome;
	struct Pont_autor * prox;
};
typedef struct Pont_autor pAutor;


struct Pont_Lista_Autor
{
	struct Pont_autor * pListaAutor;
	struct Pont_Lista_Autor * prox;
};
typedef struct Pont_Lista_Autor pListaAutor;

struct Pont_livro
{
	StrDin * titulo;
	int ano;
	int paginas;
	struct Pont_livro * prox;
	struct Pont_livro * ante;
};
typedef struct Pont_livro pLivros;

struct Pont_Editora
{
	StrDin * editora;
	struct Pont_Editora * prox;
};
typedef struct Pont_Editora pEditora;
// ----------------------------------------------------------------------------------------//


// ------------------------------------- funcoes string dinamica --------------------------//
void init_str_din(StrDin ** str)
{
	*str = NULL;
}

void inserir_str_char(StrDin ** str, char ch)
{
	StrDin * novo, *aux;
	
	novo = (StrDin*) malloc(sizeof(StrDin));
	novo->ch = ch;
	novo->prox = NULL;
	
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

int where_point_start_string(StrDin * str, char * sub_string)
{
	int point;
	StrDin * str_aux;
	
	init_str_din(&str_aux);
	
	
}


// -----------------------------------------------------------------------------------------


// ------------------------------- funcoes lista livro bin funcoes ----------------------- //

void init_bin_livros(pLivroBin ** lb)
{
	*lb = NULL;
}

void lista_bin_livros_insere_final(pLivroBin ** lb, LivroBin livro)
{
	pLivroBin * novo, *aux;
	
	if(*lb == NULL)
		   *lb = novo;
	else
	{
		aux = *lb;
		while(aux->prox != NULL)
		    aux = aux->prox;
		aux->prox = novo;    
	}	   
}

char lista_bin_livros_remove_inicio(pLivroBin **lb, LivroBin * livro)
{
	pLivroBin * aux;
	
	if(*lb != NULL)
	{
		aux = *lb;
		*livro = (*lb)->livroBin;
		(*lb) = (*lb)->prox;
		free(aux);
		
		return 1;
	}
	
	return 0;
}

void ler_livros_binario(pLivroBin ** lb)
{
	FILE * arq;
	LivroBin livro;
	
	arq = fopen(CAMINHO_ARQUIVO_LIVRO_BIN, "rb");
	
	fread(&livro, sizeof(LivroBin), 1, arq);
	while(!feof(arq))
	{
		lista_bin_livros_insere_final(&*lb, livro);
		fread(&livro, sizeof(LivroBin), 1, arq);
	}
	
	fclose(arq);
}


// -----------------------------------------------------------------------------


int main()
{
	
}
