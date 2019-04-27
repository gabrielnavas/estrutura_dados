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

void inserir_freq(int freq[], char * str)
{
    int i;

	//ZERAR TODO VETOR
    for(i=0 ; i < 256 ; i++)
		freq[i] = 0;

	//INSERIR NA POSICAO CORRETA A SUA FREQUENCIA
    for(i=0 ; str[i] != '\0' ; i++)
		freq[str[i]]++;
}


void inserirF(Tree * floresta[], int * tl_flor, Tree * arvore)
{
	//INSERE ORDENADO
	
    int i;
    
    i = *tl_flor;
    while(i > 0 && arvore->freq > floresta[i-1]->freq)
    {
    	//VAI RETIRANDO ATE ENCONTRAR A POSICAO CERTA
		floresta[i] = floresta[i-1];
		i--;
    }
	
    floresta[i] = arvore;
    (*tl_flor)++;
}

void removerF(Tree * floresta[], int *tl_flor, Tree ** arvore)
{
	//RETIRA DA ULTIMA POSICAO
	
    if(*tl_flor > 0)
		*arvore = floresta[ --(*tl_flor) ];
    else
		*arvore=  NULL;
}

Tree * huffman(char *str)
{
    Tree * floresta[256],
	 	 * esq,
	 	 * dir;

    int tl_flor,
		freq[256],
		i;
	
    tl_flor=0;
    
    //INSERIR NO VETOR DE FREQUENCIA AS OCORRENCIAS DE CARACTERES
    inserir_freq(freq, str);

	//INSERIR NA FLORESTA USANDO O VETOR DE FREQUENCIA
    for(i=0 ; i < 256 ; i++)
		if(freq[i] > 0)
		    inserirF(floresta, &tl_flor, criarNo(NULL, NULL, freq[i], i));
    
	//RETIRAR DO VETOR ESQ E DIR QUE JA ESTA ORDENADO E INSERIR NA ARVORE
	while(tl_flor > 1)
    {
    	//REMOVE tl-1 = dir
		removerF(floresta, &tl_flor, &dir);
		
    	//REMOVE tl-1 = esq
		removerF(floresta, &tl_flor, &esq);
		
		//INSERE ORDENADO O NO COM ESQ E DIREITA E A SOMATORIA DA FREQ
		inserirF(floresta, &tl_flor, criarNo(esq, dir, (esq->freq + dir->freq), '-')); 
    }
	
	//RETORNA A ARVORE FORMADA
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

void tabela(Tree * no, char tab[][256], char codigo[], int *tl_cod)
{
	int i;
	
    if(no != NULL)
    {
		if(no->esq == NULL && no->dir == NULL)
		{
			codigo[(*tl_cod) + 1] = '\0';
			strcpy(tab[ no->info ], codigo);
		}
		    
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

void comprimir(char * str, Tree* no, char *saida)
{
	char tab[256][256],
		 codigo[256];
	
	int tl_cod, //TL PARA AUX_CODIGO
		i; 		//CODIGO PARA GERAR CODIGO DE CADA CARACTER

	tl_cod = -1;
	codigo[0]='\0';	
	
	//GERA TABELA
	tabela(no, tab, codigo, &tl_cod);	
	
	saida[0] = '\0'; //init var
	//GERAR CODIGO
	for(i=0 ; str[i] != '\0' ; i++)
		strcat(saida, tab[str[i]]);
		
}

void descomprimir(char * codigo, Tree* raiz, char *saida)
{
	int i,
		j;
	Tree * n;
	
	n=raiz;
	for(i=0, j=0 ; codigo[i] !='\0' ; i++)
	{
		n = (codigo[i] == '0') ? n->esq : n->dir;
		
		if(n != NULL && n->dir == NULL && n->esq == NULL)
		{
			saida[j] = n->info;
			n = raiz;
			j++;
		}
	}
	
	//FINALIZA SAIDA
	saida[j]='\0';
}

int main()
{
 	char str_saida[1000],
	 	 str[1000] = "Abracadabra!\0",
		 codigo[1000];
    
    int n;
    
    //ARVORE USADA PARA CRIACAO DO HUFFMAN
	Tree * raiz;
	
	//GERA ARVORE DE HUFFMAN
	raiz=huffman(str);
	
	//EXIBIR ARVORE
	n=-1;
	exibir_arvore(raiz, &n);
	

	//GERA CODIGO A PARTIR DA STRING
	comprimir(str, raiz, codigo);
	printf("STRING: %s GEROU CODIGO %s\n", str, codigo);
		
	
	//GERA STRING A PARTIR DO CODIGO
	descomprimir(codigo, raiz, str_saida);
	printf("CODIGO %s GEROU STRING: %s\n", codigo, str_saida);
}
