#include<stdio.h>
#include<stdlib.h>

struct tree
{
	int freq;
	char info;
	
	struct tree * esq, *dir;
};
typedef struct tree Tree;

Tree * criaNo(Tree * esq, Tree * dir, int freq, char info)
{
	Tree * novo;
	
	novo = (Tree*) malloc(sizeof(Tree));
	novo->esq = esq;
	novo->dir = dir;
	novo->freq = freq;
	novo->info = info;
	
	return novo;
}

void insereF(Tree * arv, Tree * floresta[], int * tl_f)
{
	int i;
	
	i=*tl_f;
	while(i > 0 && floresta[i-1]->freq < arv->freq)
	{
		floresta[i] = floresta[i-1];
		i--;
	}
	
	floresta[i] = arv;
	(*tl_f)++;
}

void removeF(Tree *floresta[], int * tl_f, Tree ** arv)
{
	if(*tl_f > -1)
		*arv = floresta[ --(*tl_f) ];
	else
		*arv = NULL;	
		
		
//	if(*arv != NULL) printf("%c %d", (*arv)->info ,(*arv)->freq);
}

void removeF_inicio(Tree *floresta[], int * tl_f, Tree ** arv)
{
	int i;
	
	if(*tl_f > -1)
	{
		*arv = floresta[ 0 ];
//		printf("%c %d", (*arv)->info ,(*arv)->freq);
		i=0;
		while(i < (*tl_f)-1)
		{
			floresta[i] = floresta[i+1];
			i++;
		}
			
			
		(*tl_f)--;	
	}
	else
		*arv = NULL;
}

void cria_freq(int freq[], char * str)
{
	int i;
	
	for(i=0 ; i < 256 ; i++)
		freq[i] = 0;
	
	for(i=0 ; str[i] != '\0' ; i++)
		freq[str[i]]++;	
}

Tree * huffman(char * str)
{
	int freq[256],
		 i,
		 tl_f;
	
	Tree * floresta[256],
		 * esq,
		 * dir;	 
		 
	tl_f = 0;	 
	
	cria_freq(freq, str);
	
	for(i=0 ; i < 256 ; i++)
		if(freq[i] > 0)
			insereF(criaNo(NULL, NULL, freq[i], i), floresta, &tl_f);
			
	while(tl_f > 1)
	{
		removeF(floresta, &tl_f, &esq);
		removeF(floresta, &tl_f, &dir);
		
		insereF(criaNo(esq, dir, esq->freq + dir->freq, '-'), floresta, &tl_f);
	}
	
	return floresta[0];			 
}

void exibe(Tree * raiz, int *n)
{
	int i;
	
	if(raiz != NULL)
	{
		(*n)++;
		
		exibe(raiz->dir, &*n);
		
		for(i=0 ; i < 5 * (*n) ; i++) 
			printf(" ");
		
		printf("(%c, %d)\n", raiz->info, raiz->freq);
		
		exibe(raiz->esq, &*n);
		(*n)--;
	}
}

int main(void)
{
	int n = -1;
	
	exibe(huffman("Abracadabra!\0"), &n);
}
