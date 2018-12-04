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

#define POSICAO_NAO_PASSADA -1
#define POSICAO_PASSADA 0
#define POSICAO_ATUAL 1

#define TEMPO_EXIBICAO 100

void posicaoTabuleiroDefault(Posicao &pos)
{
	pos.x=-1;
	pos.y=-1;
	pos.cont=-1;
	pos.flag=POSICAO_NAO_PASSADA;
}

void iniciarTabuleiro(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y])
{
	Posicao pos;
	posicaoTabuleiroDefault(pos);
	
	for(int i=0 ; i<MAXTAB_X ; i++)
		for(int j=0 ; j<MAXTAB_Y ; j++)
			tabuleiro[i][j]=pos;	
}

void exibirTabuleiro(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y], PilhaM2 pm)
{
	Posicao pos;
		
	for(int i=0 ; i<MAXTAB_X ; i++)
	{
		for(int j=0 ; j<MAXTAB_Y ; j++)
		{
			pos = tabuleiro[i][j];		
			
			if(pos.flag == POSICAO_ATUAL)
			{
				textcolor(LIGHTRED);
				printf("%4d", pos.cont);
			}
			else
			{
				if(pos.flag == POSICAO_NAO_PASSADA)
				{
					textcolor(WHITE);
					printf("%4d", 0);					
				}
					
				else if(pos.flag == POSICAO_PASSADA)
				{
					textcolor(BLUE);
					printf("%4d", pos.cont);						
				}	
			}	
			
		}		
		printf("\n\n");
	}
	/*
	printf("\np0\n");
	exibir(pm, 0);
	printf("\n\np1\n");
	exibir(pm, 1);
	*/
	//PEQUENA PARA NA EXIBICAO DO TABULEIRO;
	Sleep(TEMPO_EXIBICAO);
}

Posicao pegarPosicaoXY()
{
	Posicao pos;
	
	do
	{
		system("cls || clear");		
		
		printf("DIGITE A POSICAO INICIAL X: ");
		scanf("%d", pos.x);
		
		if(pos.x < MINTAB_X)
			printf("POSICAO X TEM QUE SER MAIOR OU IGUAL A 0.");
		else if(pos.x  >= MAXTAB_X)
			printf("POSICAO X TEM QUE SER MENOR QUE 8");
		
		getch();				
		
	}while(pos.x  < MINTAB_X && pos.x  >= MAXTAB_X);
	
	
	do
	{
		system("cls || clear");		
		
		printf("DIGITE A POSICAO INICIAL Y: ");
		scanf("%d", pos.y);
		
		if(pos.y  < MINTAB_X)
			printf("POSICAO Y TEM QUE SER MAIOR OU IGUAL A 0.");
		else if(pos.y >= MAXTAB_X)
			printf("POSICAO Y TEM QUE SER MENOR QUE 8");
		
		getch();				
		
	}while(pos.y < MINTAB_X && pos.y >= MAXTAB_X);
	
	return pos;
}

void gerarDirecoes(int posicoes[8])
{
	for(int i=0 ; i < 8 ; i--)
		posicoes[i] = i;
}

void getNextPosicao(Posicao &novaPosicao, int i)
{
	//PEGA POSICAO COODERNADA CERTA A IR
	if(i == 6)
	{
		novaPosicao.x -= 1;
		novaPosicao.y += 2;
	}
	else if(i== 7)
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


int main(void)
{
	//PILHAS MULTIPLAS;
	PilhaM2 pm;
	iniciar(pm, 3);
	
	//TABULEIRO PARA PRINTAR NA TELA;
	Posicao tabuleiro[MAXTAB_X][MAXTAB_Y];
	iniciarTabuleiro(tabuleiro);
	

	//Posicao posicaoInicial = pegarPosicaoXY();
	Posicao posInit;
	posInit.x=0;
	posInit.y=0;
	posInit.flag = POSICAO_ATUAL;
	posInit.cont=1;
	
	tabuleiro[posInit.x][posInit.y] = posInit;
	inserir(pm, 0, posInit);
	
	Posicao pos = elemTopo(pm, 2);
	while(pos.cont != 65)
	{
		int i=0;
		Posicao posNextLimpa;
		do
		{
			Posicao novaPosicao = posInit;
			getNextPosicao(novaPosicao, i);
			
			if(novaPosicao.x < MAXTAB_X && novaPosicao.x >= MINTAB_X &&  novaPosicao.y < MAXTAB_Y && novaPosicao.y >= MINTAB_Y)
			{
				posNextLimpa = tabuleiro[novaPosicao.x][novaPosicao.y];
				if(posNextLimpa.flag == -1)
				{
					novaPosicao.cont++;
					tabuleiro[novaPosicao.x][novaPosicao.y] = novaPosicao;
					inserir(pm, 0, novaPosicao);
				}
			}
					
		}while(posNextLimpa.flag == -1);
		
		system("cls");
		exibirTabuleiro(tabuleiro, pm);
		
		if(i == 8)
			i=0;
		
		if(posNextLimpa.x < MAXTAB_X && posNextLimpa.x >= MINTAB_X &&  posNextLimpa.y < MAXTAB_Y && posNextLimpa.y >= MINTAB_Y)
			i++;
	}
}


