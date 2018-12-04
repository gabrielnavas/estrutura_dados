#include<stdio.h>
#include<stdlib.h>

#define MAXPILHA 1000

struct Pilha
{
	int topo;
	float pilha[MAXPILHA];
};


void iniciar(Pilha &p)
{
	p.topo = -1;
}

void inserir(Pilha &p, float elem)
{
	p.pilha[++p.topo] = elem;
}

float retirar(Pilha &p)
{
	return p.pilha[p.topo--];
}

int cheia(int topo)
{
	return topo == MAXPILHA -1;
}

int vazia(int topo)
{
	return topo == -1;
}

float elemTopo(Pilha p)
{
	return p.pilha[p.topo];
}

void exibir(Pilha p)
{
	while(!vazia(p.topo))
		printf("%.2f", retirar(p));
}

int main(void)
{
	FILE *arqE = fopen("entrada.txt", "r");
	FILE *arqS = fopen("saida.txt", "w");
	
	Pilha p;
	iniciar(p);
	
	char elem = fgetc(arqE);
	while(!feof(arqE))
	{
		if(elem != ' ')
			if(elem == '+')
				inserir(p, retirar(p) + retirar(p));
			else if(elem == '-')
			{
				float valor2 = retirar(p);
				float valor1 = retirar(p);
				inserir(p, valor1 - valor2);
			}	
			else if(elem == '*')
				inserir(p, retirar(p)*retirar(p));
			else if(elem == '/')
			{
				float valor2 = retirar(p);
				float valor1 = retirar(p);
				inserir(p, valor1 - valor2);
			}
			else
				inserir(p, ((float) elem - 48));
				
			elem = fgetc(arqE);	
	}	
	
	fprintf(arqS, "%.2f", retirar(p));
	printf("%.2f", retirar(p));
	
	fclose(arqE);
	fclose(arqS);
}
