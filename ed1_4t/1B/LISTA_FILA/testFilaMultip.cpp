#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>

#include "filaPriori.h"

int main(void)
{
	Fila f[4];
	for(int i=0 ; i < 4 ; i++)
		iniciar(f[i]);
	
	int cx;
	int saiu=0;
	Elem pessoa;
	int tempoTotal=0;
	int tempo=1;
	while(!kbhit())
	{
		cx = rand()%4;
		if(tempo % 3 == 0 && !cheia(f[cx].fim))
		{
			pessoa.dado=tempo;
			pessoa.priori=rand()%3;
			
			inserir(f[cx], pessoa);			
		}
		else
		{
			cx = rand()%4;
			if(cx == 0 && !vazia(f[0].fim))
			{
				pessoa = remover(f[cx]);
				tempoTotal += (tempo - pessoa.dado);	
				saiu++;
			}
			
			if(cx == 1 && !vazia(f[1].fim))
			{
				pessoa = remover(f[cx]);
				tempoTotal += (tempo - pessoa.dado);	
				saiu++;
			}
			
			if(cx == 2 && !vazia(f[2].fim))
			{
				pessoa = remover(f[cx]);
				tempoTotal += (tempo - pessoa.dado);	
				saiu++;
			}
			
			if(cx == 3 && !vazia(f[3].fim))
			{
				pessoa = remover(f[cx]);
				tempoTotal += (tempo - pessoa.dado);
				saiu++;	
			}
		}
		
		tempo++;
	}
	
	printf("SAIU %d, TEMPO TOTAL %d, MEDIA: %.2f", saiu, tempoTotal, ((double) tempoTotal/saiu*100));
	getch();
}
