#include<stdio.h>
#include<windows.h>
#include<conio2.h>

#include "tad_lista_lista_priori.h"

#define TEMPO_MOSTRAR_ID_ATUAL 1000

/***************************************

	ALUNO: GABRIEL NAVAS
	RA: 261741888

 ****************************************/

void infos();
void mostrarArquivo(char fileName[100]);
void filtroPrioris(int totTempo[26], int totQnt[26], char priori, int ut, int tempoUt);
void mostrarIdAtualTela(Elem elemAtend);
void avisarQueParouAtendimento(Elem elemAtend, int utAtual);

int main()
{
	infos();
	
	//LISTA UTILIZADA PARA O PROCESSO
	Descritor fila;
	iniciar(fila);
	
	//UNIDADE DE TEMPO
	int ut=0;
	
	//ID DO MAIOR CARA QUE FICOU NA FILA
	int idGanhador;
	int idGanhadorTempo = -9999;
	
	//FLAG ATENDENDO OU NAO ATENDENDO
	char atendendo=0;
	Elem elemAtend;

	//VETORES, FILTRO DE PRIORIDADES
	// A=0 B=1 C=2...
	int totTempo[26];
	int totQnt[26];
	for(int i=0 ; i < 26 ; i++) totTempo[i] = totQnt[i] = 0;
	
	int totTempoTodos=0;
	
	//ARQUIVOS PARA LEITURA E GRAVACAO DOS DADOS
	FILE *arqE = fopen("dadosE.txt", "r");
	FILE *arqS = fopen("dadosS.txt", "w");
	
	do
	{
		/* NO TEMPO CERTO ADD ALGUEM NA FILA */
		if(ut % 3 == 0 && !feof(arqE))
		{
			Elem elemAdd;
			fscanf(arqE, "%d %d %c", 
					&elemAdd.id,
				 	&elemAdd.tempoAtendimento, 
				 	&elemAdd.priori
			);
			
			if(elemAdd.tempoAtendimento > 0 && elemAdd.tempoAtendimento < 8)
			{
				elemAdd.tempoUt = ut;
				inserir(fila, elemAdd);
			}
		}
		
		/* GRAVAR NO FILA INTEIRA NO ARQUIVO*/
		if(!vazia(fila)) 
			gravarFilaArquivo(arqS, fila); 
		else
			fprintf(arqS, "FILA VAZIA.\n");
			
		/* CASO NAO TIVER ATENDENDO, ATENDE ALGUEM DA FILA */
		if( !atendendo && !vazia(fila))
		{
			elemAtend = remover(fila);
		
			/* FLAG PARA ATENDIMENTO */
			atendendo = 1;
		}
		
		/* VERIFICA SE ALGUEM ESTA ATENDENDO */
		if(atendendo)
		{
			elemAtend.tempoAtendimento--;
			mostrarIdAtualTela(elemAtend);
			
			if(elemAtend.tempoAtendimento == 0)
			{
				filtroPrioris(totTempo, totQnt, elemAtend.priori, 
					ut, elemAtend.tempoUt);
				
				fila.totAtendidos++;
				totTempoTodos += (ut - elemAtend.tempoUt);
				
				/* VERIFICA SE O TEMPO DO ID ATUAL EH O MAIOR  */
				int utReal = (ut - elemAtend.tempoUt);
				if(utReal > idGanhadorTempo) 
				{
					idGanhador = elemAtend.id;
					idGanhadorTempo = utReal;
				}
					
				atendendo = 0;
				
				avisarQueParouAtendimento(elemAtend, ut);
			}	
		}
		
		ut++;
	}while(!kbhit() && (!feof(arqE) || !vazia(fila) || atendendo == 1));
	
	/* GRAVA NO ARQUIVO: TEMPO MEDIO DE CADA PRIORIDADE */
	char prioris[26] = {'A', 'B', 'C', 'D', 'E', 'F', 
						'G', 'H', 'I', 'J' ,'K', 'L', 'M',
						'N', 'O', 'P', 'Q', 'R', 'S',
						'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
						
	for(int i=0  ; i < 26 ; i++)
	{
		if(totQnt[i] != 0)
		{
			float calc = (float) totTempo[i]/totQnt[i];
			fprintf(arqS, "\nTEMPO MEDIO DA PRIORIDADE '%c': %.2f\n",  prioris[i], calc);
		}
	}
	
	/* GRAVA NO ARQUIVO: CONJUNTO TODO, TEMPO MEDIO */
	fprintf(arqS, "\nTEMPO MEDIO DO ATENDIMENTO: %.2f\n", 
		(float)  totTempoTodos/fila.totAtendidos);
	
	/* GRAVA NO ARQUIVO: GRAVA O ID COM MAIS TEMPO */
	fprintf(arqS, "\nID COM MAIS TEMPO NA FILA: %d", idGanhador);
	
	fclose(arqE);
	fclose(arqS);
	
	mostrarArquivo("dadosS.txt\0");
}




void infos()
{
	textcolor(GREEN);
	printf("\n  * EH NECESSARIO MUDAR O LAYOUT DO CMD PARA FUNCIONAR BEM O GRAFICO");
	printf("\n\t\t-> LARGURA NO MINIMO 167");
	printf("\n\t\t-> ALTURA MAIOR QUE 30 PELO MENOS");
	
	textcolor(YELLOW);
	printf("\n\n\t\t\t** OBRIGADO. :) **");
	
	Sleep(3000);
	
	textcolor(LIGHTBLUE);
	printf("\n\n\n\t\t[ ENTER PARA CONTINUAR E INICIAR O PROCESSO ]");
	getch();
}

void mostrarArquivo(char fileName[100])
{
	textcolor(WHITE);
	system("cls");
	
	printf("\t\tRELATORIO DO ARQUIVO: %s\n\n", fileName);
	
	FILE *arq = fopen(fileName, "r");
	char line[1000];
	while(fgets(line, 100, arq) != NULL)
		for(int i=0 ; i < strlen(line) ; i++) 
			printf("%c", line[i]);
	
	fclose(arq);
}

void filtroPrioris(int totTempo[26], int totQnt[26], char priori, int ut, int tempoUt)
{
	int pos;
	switch(priori)
	{
		case 'A': pos=0; break; case 'B': pos=1; break;
		case 'C': pos=2; break; case 'D': pos=3; break;
		case 'E': pos=4; break; case 'F': pos=5; break;
		case 'G': pos=6; break; case 'H': pos=7; break;
		case 'I': pos=8; break; case 'J': pos=9; break;
		case 'K': pos=10; break; case 'L': pos=11; break;
		case 'M': pos=12; break; case 'N': pos=13; break;
		case 'O': pos=14; break; case 'P': pos=15; break;
		case 'Q': pos=16; break; case 'R': pos=17; break;
		case 'S': pos=18; break; case 'T': pos=19; break;
		case 'U': pos=20; break; case 'V': pos=21; break;
		case 'W': pos=22; break; case 'X': pos=23; break;
		case 'Y': pos=24; break; case 'Z': pos=25; break;
	}
	totTempo[pos] += (ut - tempoUt);
	totQnt[pos]++;
}
			
void mostrarIdAtualTela(Elem elemAtend)
{
	gotoxy(25, 1); textcolor(LIGHTCYAN);
	printf("| ID ATENDIMENTO ATUAL %d | TEMPO ATUAL %d | ENTROU EM UT %d", 
		elemAtend.id, elemAtend.tempoAtendimento, elemAtend.tempoUt);	
	Sleep(TEMPO_MOSTRAR_ID_ATUAL);
	
	
	gotoxy(25, 1); 
	printf("                                                              ");
}				

void avisarQueParouAtendimento(Elem elemAtend, int utAtual)
{
	gotoxy(25,1); textcolor(LIGHTMAGENTA);
	printf(" | TERMINOU O ATENDIMENTO DO ID %d | FICOU NA FILA %d UT", 
		elemAtend.id, (utAtual - elemAtend.tempoUt)) ;
	Sleep(TEMPO_MOSTRAR_ID_ATUAL);
	
	gotoxy(25,1); 
	printf("                                                           "); 
}

