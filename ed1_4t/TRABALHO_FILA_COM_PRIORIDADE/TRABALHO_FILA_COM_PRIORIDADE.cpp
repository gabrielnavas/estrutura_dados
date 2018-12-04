#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio2.h>

#include "tad_lista_prioridade.h"

void mostrarArquivo(char fileName[1000])
{
	FILE *arq = fopen(fileName, "r");
	char line[1000];
	while(fgets(line, 100, arq) != NULL)
		for(int i=0 ; i < strlen(line) ; i++) 
			printf("%c", line[i]);
	
	fclose(arq);
}


int main()
{
	//LISTA UTILIZADA PARA O PROCESSO
	Descritor fila;
	iniciar(fila);
	
	//UNIDADE DE TEMPO
	int ut=0;
	
	//ID DO MAIOR CARA QUE FICOU NA FILA
	int idGanhador;
	int idGanhadorTempo=-1;
	
	//FLAG ATENDENDO OU NAO ATENDENDO
	char atendendo=0;
	Elem elemAtend;

	//VETORES, FILTRO DE PRIORIDADES
	// A=0 B=1 C=2
	int totTempo[3];
	int totQnt[3];
	for(int i=0 ; i < 3 ; i++) 	totTempo[i] = totQnt[i] = 0;
	
	//ARQUIVOS PARA LEITURA E GRAVACAO DOS DADOS
	FILE *arqE = fopen("dadosE.txt", "r");
	FILE *arqS = fopen("dadosS.txt", "w");
	
	do
	{
		/* VERIFICA SE ALGUEM ESTA ATENDENDO */
		if(atendendo)
		{
			elemAtend.tempoAtendimento--;
			
			if(elemAtend.tempoAtendimento == 0)
			{
				if(elemAtend.priori == 'A')
				{
					totTempo[0] += (ut - elemAtend.tempoUt);
					totQnt[0]++;
				}
				else if(elemAtend.priori == 'B')
				{
					totTempo[1] += (ut - elemAtend.tempoUt);
					totQnt[1]++;
				}
				else if(elemAtend.priori == 'C')
				{
					totTempo[2] += (ut - elemAtend.tempoUt);
					totQnt[2]++;
				}
				
				/* VERIFICA SE O TEMPO DO ID ATUAL EH O MAIOR  */
				if(idGanhadorTempo < elemAtend.tempoUt)
					idGanhador = elemAtend.id;
					
				atendendo = 0;
			}	
		}	
		
		/* NO TEMPO CERTO ADD ALGUEM NA FILA */
		if(ut % 3 == 0 && !feof(arqE))
		{
			Elem elemAdd;
			fscanf(arqE, "%d %d %c", &elemAdd.id, &elemAdd.tempoAtendimento, &elemAdd.priori);
			if(elemAdd.tempoAtendimento > 0 && elemAdd.tempoAtendimento < 8)
			{
				elemAdd.tempoUt = ut;
				inserir(fila, elemAdd);
				fila.totAtend++;
			}
		}
		
		/* GRAVAR NO FILA INTEIRA NO ARQUIVO*/
		if(!vazia(fila)) 
		{
			gravarFilaArquivo(arqS, fila); 
			//exibir(fila);
		}
		else
			fprintf(arqS, "FILA VAZIA.\n");
			
		/* CASO NAO TIVER ATENDENDO, ATENDE ALGUEM DA FILA */
		if( !atendendo && !vazia(fila))
		{
			elemAtend = remover(fila);
		
			/* FLAG PARA ATENDIMENTO */
			atendendo = 1;	
			
			fila.totAtend++;	
		}
		
		ut++;
		
	}while(!kbhit() && (!feof(arqE) || !vazia(fila)));
	
	/* GRAVA NO ARQUIVO: TEMPO MEDIO DE CADA PRIORIDADE */
	int totTempoPriori=0; char prioris[3] = {'A', 'B', 'C'};
	for(int i=0  ; i < 3 ; i++)
	{
		float calc = (float) totTempo[i]/totQnt[i];
		fprintf(arqS, "\nTEMPO MEDIO DA PRIORIDADE '%c': %.2f\n",  prioris[i], calc);
		totTempoPriori += totTempo[i]/totQnt[i];
	}
	
	/* GRAVA NO ARQUIVO: CONJUNTO TODO, TEMPO MEDIO */
	fprintf(arqS, "\nTEMPO MEDIO DO ATENDIMENTO: %.2f\n", (float)  totTempoPriori/3);
	
	/* GRAVA NO ARQUIVO: GRAVA O ID COM MAIS TEMPO */
	fprintf(arqS, "\nID COM MAIS TEMPO NA FILA: %d", idGanhador);
	
	fclose(arqE);
	fclose(arqS);
	
	mostrarArquivo("dadosS.txt\0");
}

//
//int mainTEst()
//{
//	Descritor fila;
//	iniciar(fila);
//	
//	Elem e;
//	
//	
//	
//	
//	
//	e.tempoUt=0;
//	e.tempoAtendimento=0;
//	e.id=3;
//	e.priori=3;
//	inserir(fila, e);
//	
//	e.tempoUt=0;
//	e.tempoAtendimento=0;
//	e.id=2;
//	e.priori=2;
//	inserir(fila, e);
//	
//	e.tempoUt=0;
//	e.tempoAtendimento=0;
//	e.id=1;
//	e.priori=1;
//	inserir(fila, e);
//	
//	
//	e.tempoUt=0;
//	e.tempoAtendimento=0;
//	e.id=2;
//	e.priori=2;
//	inserir(fila, e);
//	
//	while(!vazia(fila))
//	{
//		Elem elem = remover(fila);
//		printf("%d %d %c\n", elem.id, elem.tempoAtendimento, elem.priori);
//	}
//	
//	exibir(fila);
//}
