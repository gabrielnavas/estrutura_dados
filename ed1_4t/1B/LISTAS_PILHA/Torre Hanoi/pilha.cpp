#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio2.h>

#include"PilhaInt.h"

#define MAXPILHAS 3

void iniciarPilhas(Pilha p[MAXPILHAS], int tl)
{
	for(int i=0 ; i < tl ; i++)
		iniciar(p[i]);
		
	//JA INICIA PILHA	
	inserir(p[0], 3);
	inserir(p[0], 2);
	inserir(p[0], 1);	
}

void mostrarPilhas(Pilha p[MAXPILHAS], int tl)
{
	Pilha pAux[MAXPILHAS];
	
	//COPIA PILHA;
	for(int i=0 ; i < tl ; i++)
		pAux[i] = p[i];
	
	for(int i=0 ; i < tl ; i++)
	{
		printf("P%d ==> ", i);
		exibir(p[i]);
		printf("\n");
	}
		
}

void mudarNumerosPilhaLoop(Pilha p[MAXPILHAS], int tl)
{
	int pBase;
	int pAlvo;
	
	do
	{
		system("cls || clear");
		mostrarPilhas(p, tl);
		
		printf("\n\nPILHA BASE: ");
		scanf("%d", &pBase);
		
		if(pBase >= 0 && !vazia(p[pBase].topo))
		{
			printf("\n\nPILHA ALVO: ");
			scanf("%d", &pAlvo);
			
			if(pAlvo >= 0 && elemTopo(p[pBase]) < elemTopo(p[pAlvo]) || vazia(p[pAlvo].topo))
			{
				inserir(p[pAlvo], remover(p[pBase]));	
				
				system("cls || clear");
				mostrarPilhas(p, tl);
				
				printf("\nINSERIDO");
			}
			else
			{
				if(pAlvo < 0 && pAlvo > 2)
				{
					if(pAlvo < 0)
						printf("\nPILHA ALVO TEM QUE SER MAIOR OU IGUAL A 0");
					else if(pAlvo > 2)
						printf("\nPILHA ALVO TEM QUE SER MENOR QUE 2");
				}
				else if(elemTopo(p[pBase]) > elemTopo(p[pAlvo]))
					printf("\nTOPO BASE EH MAIOR QUE TOPO ALVO");
			}
		}
		else
		{
			if(pBase < 0)
				printf("\nPILHA BASE TEM QUE SER MAIOR QUE 0");
			else if(vazia(p[pBase].topo))
				printf("\nPILHA BASE ESTA VAZIA.");
		}
		
		getch();
		
	
	}while(pBase >= 0 && pAlvo >= 0);
}

int main(void)
{	
	Pilha p[3];
	int tlP=3;
	iniciarPilhas(p, tlP);
	
	mudarNumerosPilhaLoop(p, tlP);
}
