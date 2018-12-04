/*
NOME: GABRIEL MIGUEL NAVAS
RA: 261741888
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio2.h>

#include "PilhaM2.h"

#define MAXTAB_X 8
#define MINTAB_X 0
#define MAXTAB_Y 8
#define MINTAB_Y 0

void iniciarTabuleiro(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y])
{
	Posicao posInit;
	posInit.x=-1;
	posInit.y=-1;
	posInit.visitada=0;
	
	for(int i=0 ; i < 8 ; i++)
		for(int j=0 ; j < 8 ; j++)
			tabuleiro[i][j] = posInit;
}	

void copiarElementos(PilhaM2 pm1, int np1, PilhaM2 pm2, int np2)
{
	while(!vazia(pm1, np1))
		inserir(pm2, np2, remover(pm1, np1));
}

void exibirTabuleiro(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y], PilhaM2 pm)
{
	int cont=1;
	for(int i=0 ; i < 8 ; i++)
	{
		for(int j=0 ; j < 8 ; j++)
		{
			Posicao elem = tabuleiro[i][j];
			if(elem.visitada == 1)
			{
				textcolor(LIGHTRED);
				printf("%3d", elem.cont);
			}
			else if(elem.visitada == 0)
			{
				textcolor(WHITE);
				printf("%3d", 0);
			}
		}
		printf("\n");
	}		
}


void pegarPosicaoXY(Posicao &pos)
{
	
	do
	{
		system("cls || clear");		
		
		printf("DIGITE A POSICAO INICIAL X: ");
		scanf("%d", &pos.x);
		
		if(pos.x < MINTAB_X)
		{
			printf("POSICAO X TEM QUE SER MAIOR OU IGUAL A 0.");
			getch();
		}
		else if(pos.x  >= MAXTAB_X)
		{
			printf("POSICAO X TEM QUE SER MENOR QUE 8");
			getch();
		}	
	}while(pos.x  < MINTAB_X && pos.x  >= MAXTAB_X);
	
	
	do
	{
		system("cls || clear");		
		
		printf("DIGITE A POSICAO INICIAL Y: ");
		scanf("%d", &pos.y);
		
		if(pos.y  < MINTAB_X)
		{
			printf("POSICAO Y TEM QUE SER MAIOR OU IGUAL A 0.");
			getch();				
		}
			
		else if(pos.y >= MAXTAB_X)
		{
			printf("POSICAO Y TEM QUE SER MENOR QUE 8");
			getch();				
		}
			
	}while(pos.y < MINTAB_X && pos.y >= MAXTAB_X);
}

void gerarDirecoes(int posicoes[8])
{
	for(int i=0 ; i < 8 ; i--)
		posicoes[i] = i;
}

void getNextPosicao(Posicao &novaPosicao, int i)
{
	if(i == 7)
	{
		novaPosicao.x -= 1;
		novaPosicao.y += 2;
	}
	else if(i == 6)
	{
		novaPosicao.x -= 2;
		novaPosicao.y += 1;
	}
	else if(i == 4)
	{
		novaPosicao.x -= 2;
		novaPosicao.y -= 1;
	}
	else if(i== 5)
	{
		novaPosicao.x -= 1;
		novaPosicao.y -= 2;
	}
	else if(i == 2)
	{
		novaPosicao.x += 1;
		novaPosicao.y -= 2;
	}
	else if(i == 3)
	{
		novaPosicao.x += 2;
		novaPosicao.y -= 1;
	}
	else if(i == 0)
	{
		novaPosicao.x += 2;
		novaPosicao.y += 1;
	}
	else if(i == 1)
	{
		novaPosicao.x += 1;
		novaPosicao.y += 2;
	}
}

int buscarPilha(PilhaM2 pm, Posicao posicao)
{
	int flag=0;
	while(!vazia(pm, 1))
		inserir(pm, 2, remover(pm, 1));
	while(!vazia(pm, 2) && flag == 0)
	{
		Posicao elemSelec = remover(pm, 2);
		
		if(elemSelec.x == posicao.x && elemSelec.y == posicao.y)
			flag=1;	
			
		inserir(pm, 1, elemSelec);	
	}
	while(!vazia(pm, 2))
		inserir(pm, 1, remover(pm, 2));
	return flag;
}

void retirarPosicao(PilhaM2 pm, Posicao posicao)
{
	int flag=0;
	
	while(!vazia(pm, 1))
		inserir(pm, 2, remover(pm, 1));
	while(!vazia(pm, 2) && flag == 0)
	{
		Posicao elemSelec = remover(pm, 2);
		inserir(pm, 1, remover(pm, 1));
		
		if(elemSelec.x == posicao.x && elemSelec.y == posicao.y)
			flag=1;	
	}
	
	if(flag == 1)
		remover(pm, 2);
	
	while(!vazia(pm, 2))
		inserir(pm, 1, remover(pm, 2));
}

int buscarPosicaoTabuleiro(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y], Posicao posicao)
{
	if(posicao.x < MAXTAB_X && posicao.x >= MINTAB_X &&  
			posicao.y < MAXTAB_Y && posicao.y >= MINTAB_Y)
	{
		Posicao posConsult = tabuleiro[posicao.x][posicao.y];
		int visitada = posConsult.visitada;
		return  visitada;
	}
	
	return 1; 
}

int main()
{
	PilhaM2 pm;
	iniciar(pm, 3);
	
	Posicao tabuleiro[MAXTAB_X][MAXTAB_Y];
	iniciarTabuleiro(tabuleiro);
	
	int cont=0;
	
	Posicao posInit;
	pegarPosicaoXY(posInit);
	
	posInit.cont=cont++;
	posInit.visitada=1;
	
	inserir(pm, 0, posInit);
	tabuleiro[posInit.x][posInit.y] = elemTopo(pm, 0);

	int iInicio=0;
	Posicao novaPosicao = posInit;
	int vezesTestada=0;
	int i=iInicio;
	while(!vazia(pm, 0) && cont < 64)
	{
		getNextPosicao(novaPosicao, i);
		
		int posicaoVisitadaTab = buscarPosicaoTabuleiro(tabuleiro , novaPosicao);
		int posicaoJaIda = buscarPilha(pm, novaPosicao);
		
		if(novaPosicao.x < MAXTAB_X && novaPosicao.x >= MINTAB_X &&  
			novaPosicao.y < MAXTAB_Y && novaPosicao.y >= MINTAB_Y || vezesTestada==8)
		{	
			if( posicaoVisitadaTab == 1 && vezesTestada==8 &&
				posicaoJaIda == 1) 
			{
				while(!vazia(pm, 1))
					remover(pm, 1);
					
				while(!vazia(pm, 0))
					remover(pm, 0);	
					
				i=iInicio++;
			}
			if( (posicaoVisitadaTab == 1 && vezesTestada==8) ||
				(posicaoJaIda == 1 && vezesTestada==8) )
			{
				Posicao posRemovida = remover(pm, 0);
				
				posRemovida.visitada=0;
				posRemovida.cont = cont--;
				tabuleiro[posRemovida.x][posRemovida.y] = posRemovida;		
				
				inserir(pm, 1, posRemovida);
					
					
				printf("\nREMOVEU %d \n", cont);
				exibirTabuleiro(tabuleiro, pm);
				
				vezesTestada=0;	
				
			}
			else if(posicaoJaIda == 0 && posicaoVisitadaTab == 0 && vezesTestada != 8)
			{
				inserir(pm, 0,  novaPosicao); 	
			
				novaPosicao.visitada=1;
				novaPosicao.cont = cont++;
				tabuleiro[novaPosicao.x][novaPosicao.y] = novaPosicao;	
				
				vezesTestada=0;
				
				printf("\nINSERIU %d \n", novaPosicao.cont);
				exibirTabuleiro(tabuleiro, pm);
				
				retirarPosicao(pm, novaPosicao);
						
			}
			else
			{
				//INCREMENTA VEZES TESTADA ++
				vezesTestada++;		
				i++;
			} 
		}
		else
		{
			vezesTestada++;
			i++;
		}		
	
		if(i == 8)
			i=0;
		
		novaPosicao = elemTopo(pm, 0);
	}
}


