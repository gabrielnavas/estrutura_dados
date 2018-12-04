///*
//	ALUNO: GABRIEL MIGUEL NAVAS
//	RA:    261741888
//*/

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

void exibirTabuleiro(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y]);
void iniciarTabuleiro(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y]);
void voltarUltimaAvenida(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y], PilhaM2 &pm, int &cont);
int insertCav(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y], PilhaM2 &pm, int &cont);

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

void exibirTabuleiro(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y])
{
	system("cls");
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

void getNextPosicao(Posicao &novaPosicao, int i)
{	
	int x[] = {-1, -2, -2, -1, +1, +2, +2, +1};
	int y[] = {+2, +1, -1, -2, -2, -1, +1, +2};
	
	novaPosicao.x += x[i];
	novaPosicao.y += y[i];
}

int daPraIr(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y], Posicao posTentar)
{
	if(posTentar.x < 8 && posTentar.y < 8 && posTentar.x >= 0 && posTentar.y >= 0 &&
		tabuleiro[posTentar.x][posTentar.y].visitada == 0)
			return 1;
			
	return 0;		
}

void verificarMaisUmaAvenida(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y], PilhaM2 &pm, Posicao posVerif)
{
	int cont=0;
	for(int i=0 ; i < 8 && cont != 2 ; i++)
	{
		if(daPraIr(tabuleiro, posVerif))
			cont++;
		else
			getNextPosicao(posVerif, i);
	}
	
	if(cont == 2)
		inserir(pm, 1, posVerif);
}

void addPosicao(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y], PilhaM2 &pm, Posicao posTentar, int &cont)
{
	posTentar.cont=cont++;
	posTentar.visitada=1;
	tabuleiro[posTentar.x][posTentar.y] = posTentar;
	
	inserir(pm, 0, posTentar);
}

void voltarUltimaAvenida(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y], PilhaM2 &pm, int &cont)
{
	int achou=0;
	Posicao ultimaAv = remover(pm, 1);

	Posicao posTirar = elemTopo(pm, 0);
	
	char flag=0;
	while(flag == 0)
	{
		if(posTirar.x == ultimaAv.x && posTirar.y == ultimaAv.y)
			flag=1;
		else
		{
			posTirar = remover(pm, 0);
			posTirar.visitada=0;
			posTirar.cont = cont--;
			tabuleiro[posTirar.x][posTirar.y] = posTirar;
		}
	}
}

void retornarNaOrdem(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y], PilhaM2 &pm)
{
	Posicao posTirar;
	
	posTirar = remover(pm, 0);
	posTirar.visitada=0;
	posTirar.cont;
	tabuleiro[posTirar.x][posTirar.y] = posTirar;
	
	while(!vazia(pm, 0))
	{
		exibirTabuleiro(tabuleiro);
		textcolor(LIGHTGREEN);
		
		posTirar = remover(pm, 0);
		posTirar.visitada=0;
		posTirar.cont;
		tabuleiro[posTirar.x][posTirar.y] = posTirar;
		
		printf("\n\tPOSICAO %d RETIRADA. ", posTirar.cont+1);
		printf("\n\n\t[ - ENTER PARA O PROXIMO - ]");
		getch();
		
	}
	
	posTirar.visitada=0;
	posTirar.cont=0;
	tabuleiro[0][0] = posTirar;
	exibirTabuleiro(tabuleiro);
	
	printf("\n\tPOSICAO %d RETIRADA. ", posTirar.cont);
	printf("\n\n\t[ - ENTER PARA O PROXIMO - ]");
	getch();

	textcolor(LIGHTRED);
	printf("\n\n\t[ * ] -  ACABOU. :)");
	
	textcolor(YELLOW);
	printf("\n\n\tALUNO: GABRIEL MIGUEL NAVAS");
	printf("\n\tRA: 261741888");
}

void pegaPosicaoXY_Inicial(int &x, int &y)
{
	
	
	printf("\n\n\tDIGITE.");
	do
	{
		system("cls");
		
		textcolor(LIGHTRED);
		printf("\n\n\tDICA, POSICAO X=0 E POSICAO Y=0 DEMORA MENOS.");
		
		textcolor(LIGHTGREEN);
		printf("\n\tPOSICAO INICIAL X: ");
		scanf("%d", &x);
		
		if(x < 0 || x >= 8)
		{
			gotoxy(10, 10); textcolor(YELLOW);
			printf("POSICAO X TEM QUE SER ENTRE 0 A 7. [ ENTER ]");
			
			getch();
			
			gotoxy(10,10);
			printf("POSICAO X TEM QUE SER ENTRE 0 A 7. [ ENTER ]");
		}
		
	}while(x < 0 || x >= 8);
	do
	{
		system("cls");
		printf("\n\n\tX=%d", x);
		textcolor(LIGHTRED);
		printf("\n\n\tDICA, POSICAO X=0 E POSICAO Y=0 DEMORA MENOS.");
		
		textcolor(LIGHTGREEN);
		printf("\n\n\tPOSICAO INICIAL Y: ");
		scanf("%d", &y);
		
		if(y < 0 || y >= 8)
		{
			gotoxy(10,10); textcolor(YELLOW);
			printf("POSICAO Y TEM QUE SER ENTRE 0 A 7. [ ENTER ]");
			
			getch();
			
			gotoxy(10,10);
			printf("                                            "); 
		}
		
	}while(y < 0 || y >= 8);
	

	system("cls");
	
	textcolor(LIGHTBLUE);
	printf("\n\n\tX=%d", x);
	printf("\n\n\tY=%d", y);
	
	textcolor(LIGHTCYAN);
	if(x == 0 && y == 0)
		printf("\n\n\t[ AGUARDE, DEMORA CERCA DE 15s ]");
	else
		printf("\n\n\t[ AGUARDE, ISSO PODE DEMORAR ]");
}

void exibe_final(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y], PilhaM2 pm)
{
	exibirTabuleiro(tabuleiro);
	
	textcolor(YELLOW);
	printf("\n\n\tOBRIGADO POR AGUARDAR.");
	
	textcolor(LIGHTCYAN);
	printf("\n\tDESEJA RETORNAR AS POSICOES NA ORDEM DO TABULEIRO? [S/N]");
	
	char op = toupper(getch());
	if(op == 'S')
		retornarNaOrdem(tabuleiro, pm);
}

int insertCavREC(Posicao tabuleiro[MAXTAB_X][MAXTAB_Y], PilhaM2 &pm, int &cont)
{
	if(cont == 64)
		return -1;
	
	else
	{
		Posicao posTentar = elemTopo(pm, 0);
		for(int i=0 ; i < 8 && cont != 64 ; i++)
		{
			posTentar = elemTopo(pm, 0);
			getNextPosicao(posTentar, i);
			
			if(daPraIr(tabuleiro, posTentar))
			{
				verificarMaisUmaAvenida(tabuleiro, pm, posTentar);
				addPosicao(tabuleiro, pm, posTentar,cont);
				exibirTabuleiro(tabuleiro);
				
				char remo = insertCavREC(tabuleiro, pm, cont);
				if(remo && cont != 64)
					voltarUltimaAvenida(tabuleiro, pm, cont);
			}
		}
	}
	return 1;
}

int main(void)
{
	//PILHAS MULTIPLAS
	PilhaM2 pm;
	iniciar(pm, 2);
	
	//TABULEIRO DO TIPO POSICAO INICIADO COM POSICOES NAO INICIADAS
	Posicao tabuleiro[MAXTAB_X][MAXTAB_Y];
	iniciarTabuleiro(tabuleiro);
	
	//CONTADOR INTERNO DA RECURSAO
	int cont=0;
	
	//POSICAO INICIAL NO TABULEIRO
	Posicao pos;
	pegaPosicaoXY_Inicial(pos.x, pos.y);
	pos.cont=cont++;
	pos.visitada=1;
	
	//POSICIONO A PRIMEIRA POSICAO NO TABULEIRO.
	tabuleiro[pos.x][pos.y] = pos;
	
	//INSIRO NA PILHA DE POSICOES
	inserir(pm, 0, pos);
	
	//COMECO DA RECURSAO
	insertCavREC(tabuleiro, pm, cont);
	
	//EXIBICAO PASSO A PASSO DO TABULEIRO.
	exibe_final(tabuleiro, pm);
}
