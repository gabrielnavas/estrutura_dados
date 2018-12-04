#include<stdio.h>
#include "fila_dinamica_int.h"

//IMPLEMENTACAO COM ARQUIVO, LENDO E GRAVANDO EM ARQUIVO.

int main(void)
{
	FILE *arqE = fopen("entrada.txt","r");
	FILE *arqS = fopen("saida.txt","w");
	
	Fila f; 
	iniciar(f);
	
	int n;
	fscanf(arqE, "%d", &n);
	while(n != 0)
	{
		//INSERIR FILA ORDENADA COM OS NUMEROS DE 1 ate N;
		for(int i=1 ; i <= n ; i++)
			inserir(f, i);
		
		fprintf(arqS, "DISCARDED CARDS: %d, ", retirar(f));
		while(!vazia(f.cont-1))
		{
			inserir(f, retirar(f));
			fprintf(arqS, "%d, ", retirar(f));
		}
		fprintf(arqS, "\nREMAING CARD %d\n", retirar(f));
		
		fscanf(arqE, "%d", &n);
	}
	
	fclose(arqE);
	fclose(arqS);
}


