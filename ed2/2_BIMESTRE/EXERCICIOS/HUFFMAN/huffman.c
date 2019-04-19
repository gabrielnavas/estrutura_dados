#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct tree
{
    int freq;
    char info;
    struct tree * esq, * dir;
};
typedef struct tree Tree;

void init(Tree **t)
{
    *t = NULL;
}

void inserir_freq(int freq[], char * str)
{
    int i;

    for(i=0 ; i < 256 ; i++)
		freq[i] = 0;

    for(i=0 ; str[i] != '\0' ; i++)
		freq[str[i]]++;
}

Tree * criarNo(Tree * esq, Tree * dir, int freq, char info)
{
    Tree * novo;

    novo = (Tree *) malloc(sizeof(Tree));
    novo->esq = esq;
    novo->dir = dir;
    novo->freq = freq;
    novo->info = info;
    
	return novo;
}

void inserirF(Tree * floresta[], int * tl_flor, Tree * arvore)
{
    int i;
    
    i = *tl_flor;
    while(i > 0 && arvore->freq > floresta[i-1]->freq)
    {
		floresta[i] = floresta[i-1];
		i--;
    }
	
//	printf("%c\n", arvore->info);
    floresta[i] = arvore;
    (*tl_flor)++;
}

void removerF(Tree * floresta[], int *tl_flor, Tree ** arvore)
{
    if(*tl_flor > 0)
		*arvore = floresta[ --(*tl_flor) ];
    else
		*arvore=  NULL;
}

void inserir_floresta(Tree *floresta[], int *tl_flor, int freq[])
{
    int i;

    for(i=0 ; i < 256 ; i++)
		if(freq[i] > 0)
		    inserirF(floresta, &*tl_flor, criarNo(NULL, NULL, freq[i], i));
}

Tree * huffman(char *str)
{
    Tree * floresta[256],
	 * esq,
	 * dir;

    int tl_flor;
    int freq[256];

    tl_flor=0;
    
    inserir_freq(freq, str);

    inserir_floresta(floresta, &tl_flor, freq);

    while(tl_flor > 1)
    {
		removerF(floresta, &tl_flor, &dir);
		removerF(floresta, &tl_flor, &esq);
		inserirF(floresta, &tl_flor, criarNo(esq, dir, (esq->freq + dir->freq), '-')); 
    }

    return floresta[0];
}

void exibir_arvore(Tree * arvore, int * n)
{
    int i;

    if(arvore != NULL)
    {
		(*n)++;
		exibir_arvore(arvore->dir, &*n);
		
		for(i=0 ; i < 5 * (*n); i++)
		    printf(" ");
	
		printf("(%c,%d)\n", arvore->info, arvore->freq);
	
		exibir_arvore(arvore->esq, &*n);
		(*n)--;
    }
}

void codigo(Tree * no, char cod[], int *tl_cod)
{
    if(no != NULL)
    {
		int i;
		
	    if(no != NULL)
	    {
			if(no->esq == NULL && no->dir == NULL)
			    printf("%c: %s\n", no->info, cod);
			else
			{
			    (*tl_cod)++;
			    
			    cod[*tl_cod] = '0';
			    codigo(no->esq,  cod, &*tl_cod);
			    
			    cod[*tl_cod] = '1';
			    codigo(no->dir, cod, &*tl_cod);
		
			    (*tl_cod)--;
			}
	    }
    }
}

void tabela(Tree * no, char tab[][256], char codigo[], int *tl_cod)
{
	int i;
	
    if(no != NULL)
    {
		if(no->esq == NULL && no->dir == NULL)
		    strcpy(tab[ no->info ], codigo);
		else
		{
		    (*tl_cod)++;
		    codigo[*tl_cod] = '0';
		    tabela(no->esq, tab, codigo, &*tl_cod);
		    
		    codigo[*tl_cod] = '1';
		    tabela(no->dir, tab, codigo, &*tl_cod);
	
		    (*tl_cod)--;
		}
    }
}

void gerar_tabela(Tree * no, char tab[256][256])
{
	int tl_cod,
		i;
	
	char aux_codigo[256];
	
	tl_cod = -1;
	
	for(i=0 ; i < 256 ; i++)
		tab[i][0] = '\0';
		
	tabela(no, tab, aux_codigo, &tl_cod);	
}

void exibir_codigo(Tree * no)
{
	int tl_cod;	
	char aux_codigo[256];
	
	tl_cod = -1;
	
	codigo(no, aux_codigo, &tl_cod);	
}


void exibir_tabela(char tab[256][256])
{
	int i;
	
	for(i=0 ; i < 256 ; i++)
		if(strlen(tab[i]) > 0)
			printf("%s\n", tab[i]);	
}

int main()
{
    char tabela[256][256];
	int n;
    
	Tree * raiz;
	
	raiz = huffman("Abracadabra!\0");
      
//    exibir_codigo(raiz);

    gerar_tabela(raiz, tabela); 
	
	exibir_tabela (tabela);
}
