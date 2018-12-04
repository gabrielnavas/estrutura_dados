#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio2.h>

#include "PilhaM2.h"


void iniciarTabuleiro(Posicao tabuleiro[8][8])
{
	Posicao posInit;
	posInit.x=-1;
	posInit.y=-1;
	posInit.visitada=0;
	
	for(int i=0 ; i < 8 ; i++)
		for(int j=0 ; j < 8 ; j++)
			tabuleiro[i][j] = posInit;
}	

void exibirTabuleiro(Posicao tabuleiro[8][8])
{
	//printf("\n");
	
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
	//PEGA POSICAO COODERNADA CERTA A IR
	if(i == 0)
	{
		novaPosicao.x -= 1;
		novaPosicao.y += 2;
	}
	else if(i == 1)
	{
		novaPosicao.x -= 2;
		novaPosicao.y += 1;
	}
	else if(i == 2)
	{
		novaPosicao.x -= 2;
		novaPosicao.y -= 1;
	}
	else if(i== 3)
	{
		novaPosicao.x -= 1;
		novaPosicao.y -= 2;
	}
	else if(i == 4)
	{
		novaPosicao.x += 1;
		novaPosicao.y -= 2;
	}
	else if(i == 5)
	{
		novaPosicao.x += 2;
		novaPosicao.y -= 1;
	}
	else if(i == 6)
	{
		novaPosicao.x += 2;
		novaPosicao.y += 1;
	}
	else if(i == 7)
	{
		novaPosicao.x += 1;
		novaPosicao.y += 2;
	}
}

int tentar(Posicao t[8][8], int cont, PilhaM2 p)
{
	if(cont == 64) return 1;
		
	for(int i=0 ; i < 8 ; i++)
	{
		Posicao pos = elemTopo(p, 0);
		getNextPosicao(pos, i);
				
		if(pos.x < 8 && pos.x >= 0 &&  pos.y < 8 && pos.y >= 0)
		{	
//			Posicao posTentar = ;
			if(t[pos.x][pos.y].visitada == 0)
			{
				inserir(p, 0, pos);
				pos.cont = cont++;
				pos.visitada=1;
				t[pos.x][pos.y] = pos;
				exibirTabuleiro(t);//////////////
				
				int certo = tentar(t, cont, p);
				if(certo == 0)
				{
					Posicao posTirar = remover(p, 0);
					posTirar.visitada=0;
					posTirar.cont = cont--;
					t[pos.x][pos.y] = posTirar;
								
					exibirTabuleiro(t);//////////////
				}
			}
		}
				
	}	
	
	return 0;
}

int main(void)
{	
	PilhaM2 pm;
	iniciar(pm, 2);
	
	Posicao tabuleiro[8][8];
	iniciarTabuleiro(tabuleiro);
	
	int cont=0;
	Posicao posInit;
	posInit.x=0;
	posInit.y=0;
	posInit.cont=cont++;
	posInit.visitada=1;
	
	inserir(pm, 1, posInit);
	tabuleiro[posInit.x][posInit.y] = elemTopo(pm, 0);
	
	
	tentar(tabuleiro, cont, pm);			
}


