#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TEMPOSLEEP 1

#ifdef __unix__         
#include<unistd.h>
#define sleep1000(); sleep(TEMPOSLEEP);

#elif defined(_WIN32) || defined(WIN32) 
#include<windows.h>
#include<conio2.h>
#define sleep1000(); Sleep(TEMPOSLEEP);

#endif

#define MAXPILHA 1000

//PILHA
struct Pilha
{
	int topo;
	int pilha[MAXPILHA];
};

void iniciar(Pilha &p)
{
	p.topo=0;
}

void inserir(Pilha &p, int num)
{
	p.pilha[++p.topo]=num;
}

int remover(Pilha &p)
{
	return p.pilha[p.topo--];
}

int cheia(int topo)
{
	return topo == MAXPILHA-1;
}

int vazia(int topo)
{
	return topo == -1;
}

int elemTopo(Pilha p)
{
	return p.pilha[p.topo];
}

void exibir(Pilha p)
{
	while(!vazia(p.topo))
		printf("%d\n", remover(p));
}


int allPilhasCheia(Pilha p[1000], int tl)
{
	int contCheia=0;
	for(int i=0 ; i < tl ; i++)
		if(cheia(p[i].topo))
			contCheia++;
		
	return contCheia == tl;
}

void iniciarAllPilhas(Pilha p[1000], int tl)
{
	for(int i=0 ; i<tl ; i++)
		iniciar(p[i]);
}

int randomAccessP(int tl)
{
	return rand()%tl;
}

int randomEvento()
{
	return rand() % 2; //0 ou 1
}

int main(void)
{
	
	int tlP=0;
		
	printf("Qtd pilhas: ", tlP);
	scanf("%d", &tlP);
	if(tlP > 0)
	{
		srand(time(NULL));
		int tempo=0;
		int adds=0;
		int removes=0;
		
		Pilha p[tlP];
		iniciarAllPilhas(p, tlP);
		
		while(!allPilhasCheia(p, tlP))
		{
			int randomP = randomAccessP(tlP);
			int randomEvent = randomEvento();
			
			if(randomEvent)
			{
				int num = (rand()%1000)+1;
				inserir(p[randomP], num);
				printf("\nINSERIDO NA PILHA %d NUMERO %d", randomP, num);
				adds++;
			}
			else
			{
				int num = remover(p[randomP]);
				printf("\nREMOVIDO NA PILHA %d NUMERO %d", randomP, num);
				removes--;
			}
			
			tempo++;
			sleep1000();
		}
		
		printf("\n\nTEMPO TOTAL: %d", tempo);
		printf("\n\nADDS TOTAL: %d", adds);
		printf("\n\nREMOVES TOTAL: %d", removes);
	}
}