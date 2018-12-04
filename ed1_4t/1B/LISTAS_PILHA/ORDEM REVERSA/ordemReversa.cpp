#include<stdio.h>
#include<string.h>

#define MAXPILHA 1000

struct Pilha
{
	char pilha[MAXPILHA][100];
	int topo;
};

void iniciar(Pilha &p)
{
    p.topo=-1;
}

void inserir(Pilha &p, char elem[100])
{
	++p.topo;
    strcpy(p.pilha[p.topo], elem);
}

void remover(Pilha &p, char elem[100])
{
    strcpy(elem, p.pilha[p.topo]);
    p.topo--;
}

int cheia(int topo)
{
    return topo == MAXPILHA -1;
}

int vazia(int topo)
{
    return topo == -1;
}

int elemTopo(Pilha p, char elem[100])
{
    strcpy(elem, p.pilha[p.topo]);
}

void show(Pilha p)
{
    char elem[100];
    while(!vazia(p.topo))
    {
        remover(p, elem);
        puts(elem);
    }
}

int lenPilha(Pilha p)
{
	int qntd=0;
	char elem[100];
	while(!vazia(p.topo))
    {
        remover(p, elem);
        qntd++;
    }
    
    return qntd;
}
    
Pilha fraseRevePilha(char pala[100])
{
	int tl=strlen(pala);
	if(tl > 0)
	{
		Pilha p; iniciar(p);
		
		for(int i=0 ; i < tl ;  i++)
		{
			if(pala[i] != ' ')
			{
				int tlAux=0;
				char auxStr[100];
				while(pala[i] != ' ' && i < tl && pala[i] != '\n')
					auxStr[tlAux++] = pala[i++];
				auxStr[tlAux] = '\0';
						
				inserir(p , auxStr);		
			}
		}
		
		return p;
	}
}

void writeFraseInvertida(FILE *arq, Pilha p)
{
	int qntdElem = lenPilha(p);
	
	if(qntdElem > 0)
	{
		char palavra[100];
		
		if(qntdElem > 1)
		{
			while(!vazia(p.topo-1))
			{
				remover(p, palavra);
				fprintf(arq, "%s ", palavra);
			}
			
			remover(p, palavra);
			fprintf(arq, "%s\n", palavra);
		}
		else if(qntdElem == 1)
		{
			remover(p, palavra);
			fprintf(arq, "%s\n", palavra);
		}
	}
}
    
void exibirArquivo(char nome[100])
{
	FILE *arqE = fopen(nome, "r");
	char ch=fgetc(arqE);
	while(!feof(arqE))
	{
		printf("%c", ch);
		ch=fgetc(arqE);
	}
	
	fclose(arqE);
}    
    
int main(void)
{
    FILE *arqE = fopen("arqE.txt", "r");
    FILE *arqS = fopen("arqS.txt", "w");
    
    if(arqE != NULL && arqS != NULL)
    {
		char line[100];
		while(fgets(line, 100, arqE) != NULL)
			writeFraseInvertida(arqS, fraseRevePilha(line));
			
		fclose(arqE);
		fclose(arqS);	
		
		exibirArquivo("arqS.txt\0");
    }
}
