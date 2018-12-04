#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio2.h>
#include<time.h>
#include<windows.h>

#include "tad_partidos.h"

/*
	FEITO POR:
	GABRIEL NAVAS
	HUDSON
*/

void inserirPartidos(Descritor &desc);
void insercaoCandidatos(Descritor &desc);
int carregaDadosMemoria(Descritor &desc);
void gravarHardDisk(Descritor desc);
void alterarCandidato(Descritor desc);
char menuPrincipal();
void logica(Descritor &desc);
void exportarDados(Descritor &desc);
void importarDados(Descritor &desc, int &flag_importacao);
void insercaoCandidatosDireto(Descritor &desc, char nomePartido[30]);
void interface_deletarCandidato(Descritor &desc);
void interface_deletarPartido(Descritor &desc);
void showRank_candidatos(Descritor desc);
void interface_votar(Descritor &desc);
void informarDadosGravados(Descritor &desc, int flag_importacao);
void exibirPartidosComCandidatosComPonteiros(Descritor desc);
void showRank_candidatos_grafic(Descritor desc);

int main(void)
{
	Descritor desc;
	iniciarDescritor(desc);
	
	logica(desc);
}

void logica(Descritor &desc)
{
	int flag_importacao=0;
	system("cls");
	
	char op;
	do
	{		
		op = menuPrincipal();
		if(op == 'A')	interface_votar(desc);
		
		else if( op == 'B')	inserirPartidos(desc);
			
		else if(op == 'C')	insercaoCandidatos(desc);
			
		else if(op == 'D')	interface_deletarPartido(desc);
			
		else if(op == 'E')	interface_deletarCandidato(desc);
			
		else if(op == 'F')	alterarCandidato(desc);
			
		else if(op == 'G')	exibirPartidosComCandidatos(desc);
		
		else if(op == 'H')	exibirPartidosComCandidatosComPonteiros(desc);
			
		else if(op == 'I')	showRank_candidatos(desc);
		
		else if(op == 'J')	showRank_candidatos_grafic(desc);
				
		else if(op == 'K')	importarDados(desc, flag_importacao);
			
		else if(op == 'L')	exportarDados(desc);	
		
		else if(op == 'X')	informarDadosGravados(desc, flag_importacao);			
						
	}while(op != 'X');
}

char menuPrincipal()
{
	system("cls");
	
	textcolor(CYAN);
	printf("\n\n\t\tPROGRAMA ELEITORAL.");
	
	textcolor(GREEN); 
	printf("\n\n\t[ X ]"); 
	textcolor(LIGHTBLUE); 
	printf("- SAIR.");
	
	textcolor(GREEN); 
	printf("\n\t[ A ]"); 
	textcolor(LIGHTBLUE); 
	printf("- EXECUTAR PROCESSO ELEITORAL.");
	
	textcolor(GREEN); 
	printf("\n\t[ B ]"); 
	textcolor(LIGHTBLUE); 
	printf("- INSERIR PARTIDO.");
	
	textcolor(GREEN); 
	printf("\n\t[ C ]"); 
	textcolor(LIGHTBLUE); 
	printf("- INSERIR CANDIDATO.");
	
	textcolor(GREEN); 
	printf("\n\t[ D ]"); 
	textcolor(LIGHTBLUE); 
	printf("- EXCLUIR PARTIDO.");
	
	textcolor(GREEN); 
	printf("\n\t[ E ]"); 
	textcolor(LIGHTBLUE); 
	printf("- EXCLUIR CANDIDATO.");
	
	textcolor(GREEN); 
	printf("\n\t[ F ]"); 
	textcolor(LIGHTBLUE); 
	printf("- ALTERAR CANDIDATO.");

	textcolor(GREEN); 
	printf("\n\t[ G ]"); 
	textcolor(LIGHTBLUE); 
	printf("- EXIBIR TUDO.");
	
	textcolor(GREEN); 
	printf("\n\t[ H ]"); 
	textcolor(LIGHTBLUE); 
	printf("- EXIBIR TUDO COM PONTEIRO.");
	
	textcolor(GREEN); 
	printf("\n\t[ I ]"); 
	textcolor(LIGHTBLUE); 
	printf("- RANK DOS CANDIDATOS.");
	
	textcolor(GREEN); 
	printf("\n\t[ J ]"); 
	textcolor(LIGHTBLUE); 
	printf("- RANK DOS CANDIDATOS GRAFICO.");
	
	textcolor(GREEN); 
	printf("\n\t[ K ]"); 
	textcolor(LIGHTBLUE); 
	printf("- IMPORTAR DADOS.");
	
	textcolor(GREEN); 
	printf("\n\t[ L ]"); 
	textcolor(LIGHTBLUE); 
	printf("- EXPORTAR DADOS.");
	
	return toupper(getch());	
}

void informarDadosGravados(Descritor &desc, int flag_importacao)
{
	if(flag_importacao)
	{
		system("cls");
	
		exportarDados(desc);
		
		textcolor(LIGHTMAGENTA);
		printf("\n\n\tSAINDO, BYE");

		textcolor(RED);
		printf("\n\n\t :)");
		textcolor(WHITE);
	}
}

ListaCandidatos * getListaRank_candidatos(Descritor desc)
{
	ListaCandidatos *listaRank = NULL; //LISTA PRINCIPAL CABECA;
	if(desc.cont > 0)
	{		
		ListaPartidos *noPartidos = desc.inicio;
		while(noPartidos != NULL)
		{
			ListaCandidatos * noCandidatos = noPartidos->partido.listaCandidatos;
			while(noCandidatos != NULL)
			{
				Candidato candidato = noCandidatos->candidato;
				
				listaRank = inserirCandidatosOrdenado_votos(listaRank, candidato);
				noCandidatos = noCandidatos->prox;
			} 
			
			noPartidos = noPartidos->prox;
		}
	}
	
	return listaRank;
}

void interface_votar(Descritor &desc)
{
	Candidato candidato;
	system("cls");
	textcolor(LIGHTGREEN);
	printf("\n\n\tNUMERO DO CANDIDATO A VOTAR. [-1 = EXIT] \n\n\t --> ");
	textcolor(GREEN);
	scanf("%d", &candidato.numero);
	while(candidato.numero != -1)
	{
		ListaCandidatos *procuraCandidato = procuraCandidatoALL_numero(desc, candidato.numero);
		if(procuraCandidato != NULL)
		{
			ListaPartidos *partidoCandidatoVotar = retornaPonteiroDoCandidatoAchado(desc, procuraCandidato->candidato.numero);
			
			textcolor(CYAN);
			printf("\n\n\tNOME PARTIDO: %s NUMERO PARTIDO: %d", partidoCandidatoVotar->partido.nome,
													partidoCandidatoVotar->partido.numero);
			textcolor(LIGHTCYAN);										
			printf("\n\n\tNOME CANDIDATO: %s", procuraCandidato->candidato.nome);
			
			printf("\n\n\tNUMERO CANDIDATO: %d", procuraCandidato->candidato.numero);
			
			textcolor(YELLOW);
			printf("\n\n\tCONFIRMAR VOTO? [Y/N]");
			fflush(stdin);
			char op = toupper(getch());
			if(op == 'Y')
			{
				procuraCandidato->candidato.votos++;
				textcolor(LIGHTGREEN);
				printf("\n\n\tVOTADO COM SUCESSO!");
					
				Beep(800, 280);
					for(int i=0 ; i< 7 ; i++)
					Beep(900, 40);
			}		
			else
			{
				textcolor(LIGHTGREEN);
				printf("\n\n\tUMA PENA.");
			}
			
			getch();
		}
		else
		{
			textcolor(RED);
			printf("\n\n\tPARTIDO NAO EXISTE, [PRESS ENTER] ");
			getch();
			textcolor(WHITE);
			
		}
		
		system("cls");
		textcolor(LIGHTGREEN);
		printf("\n\n\tNUMERO DO CANDIDATO A VOTAR. [-1 = EXIT] \n\n\t --> ");
		textcolor(GREEN);
		scanf("%d", &candidato.numero);	
	}
}

void showRank_candidatos_grafic(Descritor desc)
{
	system("cls");
	ListaCandidatos *listaRank = getListaRank_candidatos(desc);
	if(listaRank != NULL)
	{
		
		textcolor(LIGHTGREEN);
		printf("\n\n\tINICIO DO RANK GRAFICO");
		
		int cont=1;
		int posLinha=6;
		while(listaRank != NULL)
		{					
			ListaPartidos *nomeBuscadoPartido = retornaPonteiroDoCandidatoAchado(desc, listaRank->candidato.numero);	
			
			gotoxy(1, posLinha); textcolor(LIGHTGREEN);	
			printf("%d", cont);
			
			gotoxy(5, posLinha); textcolor(LIGHTCYAN);	
			printf("PARTIDO: %s", nomeBuscadoPartido->partido.nome);			
			
			gotoxy(36, posLinha); textcolor(LIGHTGREEN);	
			printf("CANDIDATO: %s", listaRank->candidato.nome);	
			
			gotoxy(66, posLinha); textcolor(LIGHTMAGENTA);	
			printf("NUMERO: %d", listaRank->candidato.numero);
			
			gotoxy(80, posLinha); textcolor(LIGHTBLUE);	
			printf("VOTOS: ", listaRank->candidato.votos);
			gotoxy(86, posLinha++); textcolor(RED);
			printf("%d", listaRank->candidato.votos);	
			
			gotoxy(5, posLinha); 
			if(listaRank->candidato.votos == 0)
			{
				printf("NENHUM VOTO.");
			}
			else
			{
				srand(time(NULL));
				for(int i=0 ; i < listaRank->candidato.votos ; i++)
				{
					textcolor((rand() % 15) +1);
					printf("*");
				}
					
			}		
			
			cont++;
			posLinha +=2;
							
			listaRank = listaRank->prox;
		}
		
		textcolor(LIGHTGREEN);
		printf("\n\n\tFINAL DO RANK GRAFICO");
		
		textcolor(LIGHTCYAN);
		printf("\n\n\t[PRESS ENTER]");
	}
	else
	{
		gotoxy(10, 3); textcolor(LIGHTGREEN);
		printf("NAO HA CANDIDATOS PARA MOSTRAR.");
		
		gotoxy(10, 5); textcolor(YELLOW);
		printf("[PRESS ENTER]");
	}
			
	getch();
}

void showRank_candidatos(Descritor desc)
{
	system("cls");
	int flag_ganhador=0;
	ListaCandidatos *listaRank = getListaRank_candidatos(desc);
	if(listaRank != NULL)
	{
		gotoxy(10, 3); textcolor(LIGHTGREEN);
		printf("INICIO DO RANK.\n\n");
		
		gotoxy(10, 5); textcolor(LIGHTRED);
		printf("POSICAO");

		gotoxy(20, 5); 
		printf("NOME PARTIDO");

		gotoxy(50, 5); 
		printf("NOME CANDIDATO");
		
		gotoxy(80, 5); 
		printf("NUMERO");
		
		gotoxy(90, 5); 
		printf("VOTOS");
		
		int cont=1;
		int posLinha=6;
		while(listaRank != NULL)
		{	
			if(flag_ganhador == 0)
			{
				gotoxy(0, posLinha+1); textcolor(LIGHTGREEN);
				printf("\n   WIN->");
			}		
			gotoxy(10, posLinha); textcolor(RED);
			printf("%d", cont++);
			
			ListaPartidos *nomeBuscadoPartido = retornaPonteiroDoCandidatoAchado(desc, listaRank->candidato.numero);
			gotoxy(20, posLinha); textcolor(LIGHTGREEN);
			printf("%s", nomeBuscadoPartido->partido.nome);
			
			gotoxy(50, posLinha); textcolor(LIGHTBLUE);	
			printf("%s", listaRank->candidato.nome);
			
			gotoxy(80, posLinha); textcolor(LIGHTCYAN);	
			printf("%d", listaRank->candidato.numero);
			
			gotoxy(90, posLinha++); textcolor(RED);	
			printf("%d\n",	listaRank->candidato.votos);			
			
			flag_ganhador=1;
							
			listaRank = listaRank->prox;
		}
		
		textcolor(LIGHTGREEN);
		printf("\n\n\tFINAL DO RANK");
		
		textcolor(LIGHTCYAN);
		printf("\n\n\t[PRESS ENTER]");
	}
	else
	{
		gotoxy(10, 3); textcolor(LIGHTGREEN);
		printf("NAO HA CANDIDATOS PARA MOSTRAR.");
		
		gotoxy(10, 5); textcolor(YELLOW);
		printf("[PRESS ENTER]");
	}
			
	getch();
}

void interface_deletarPartido(Descritor &desc)
{
	if(desc.cont > 0)
	{
		Partido partido;
	
		system("cls");
		textcolor(LIGHTGREEN);
		printf("\n\n\tNOME DO PARTIDO [ENTER PARA SAIR]: ");
		fflush(stdin);	gets(partido.nome);
		while(strcmp(partido.nome, "") != 0)
		{
			ListaPartidos *procura = procuraPartido_nome(desc, partido.nome);
			if(procura == NULL)
			{
				printf("\n\n\tPARTIDO NAO CADASTRADO");
				getch();
			}
			else
			{
				textcolor(LIGHTCYAN);
				printf("\n\n\tDADOS.");
				
				textcolor(LIGHTBLUE);
				printf("\n\n\tNOME PARTIDO: %s", procura->partido.nome);
				printf(" NUMERO PARTIDO: %d", procura->partido.numero);
				
				textcolor(YELLOW);
				printf("\n\n\tDESEJA APAGAR ESSE PARTIDO? [Y/N].");
				char op = toupper(getch());
				if(op == 'Y' || op == 'S')
				{
					textcolor(LIGHTGREEN);
					printf("\n\n\t[ * ] - DELETANDO PARTIDO.");
					deletarPartido(desc, procura);
					
					textcolor(LIGHTMAGENTA);
					printf("\n\n\tPARTIDO EXCLUIDO COM SUCESSO. [PRESS ENTER]");
				}
				else
				{
					textcolor(LIGHTMAGENTA);
					printf("\n\n\tPARTIDO NAO EXCLUIDO. [PRESS ENTER]");
				}
				
				getch();
			}
			
			system("cls");
			textcolor(LIGHTGREEN);
			printf("\n\n\tNOME DO PARTIDO [ENTER PARA SAIR]: ");
			fflush(stdin);	gets(partido.nome);
		}
	}
	else
	{
		system("cls");
		textcolor(RED);
		printf("\n\n\tNAO HA PARTIDO PARA DELETAR");
		
		textcolor(LIGHTGREEN);
		printf("\n\n\t[PRESS ENTER]");
		
		getch();
			
	}
}

void interface_deletarCandidato(Descritor &desc)
{
	system("cls");
	if(desc.cont > 0)
	{
			
		Candidato candidato;
		
		textcolor(LIGHTGREEN);
		printf("\n\n\tNUMERO DO CANDIDATO [-1 = EXIT]: ");
		scanf("%d", &candidato.numero);
		while(candidato.numero != -1)
		{
			ListaCandidatos *procuraCandidatoNumero = procuraCandidatoALL_numero(desc, candidato.numero);
			if(procuraCandidatoNumero == NULL)
				printf("\n\n\tNUMERO DE CANDIDATO NAO EXISTENTE. [PRESS ENTER].");
			else
			{
				ListaPartidos *cabecaCandidatoAchado = retornaPonteiroDoCandidatoAchado(desc, procuraCandidatoNumero->candidato.numero);
				
				printf("\n\n\tDADOS.");
				printf("\n\n\tNOME PARTIDO: %s", cabecaCandidatoAchado->partido.nome);
				printf("  NUMERO PARTIDO: %d", cabecaCandidatoAchado->partido.numero);
				
				printf("\n\n\tNOME CANDIDATO: %s", procuraCandidatoNumero->candidato.nome);
				printf("  NUMERO CANDIDATO: %d", procuraCandidatoNumero->candidato.numero);
				printf("\n\tVOTOS: %d", procuraCandidatoNumero->candidato.votos);
				
				printf("\n\n\tDESEJA APAGAR ESSE CANDIDATO? [Y/N].");
				char op = toupper(getch());
				if(op == 'Y' || op == 'S')
				{
					cabecaCandidatoAchado->partido.listaCandidatos = deletarCandidato_numero(cabecaCandidatoAchado->partido.listaCandidatos, 																	candidato.numero);
					printf("\nCANDIDATO EXCLUIDO COM SUCESSO. [PRESS ENTER]");
				}
				else
				{
					printf("\n\n\tCANDIDATO NAO EXCLUIDO. [PRESS ENTER]");
				}
				
				getch();
				candidato.numero = -1;
			}
			
			getch();
			
			system("cls");
			textcolor(LIGHTGREEN);
			printf("\n\n\tNUMERO DO CANDIDATO [-1 = EXIT]: ");
			scanf("%d", &candidato.numero);
		}	
	}
	else
	{
		textcolor(RED);
		printf("\n\n\tNAO HA CANDIDATO PARA EXCLUIR.");
		
		textcolor(LIGHTGREEN);
		printf("\n\n\t[PRESS ENTER]");
		getch();
	}
}


void alterarCandidato(Descritor desc) 
{
	system("cls");
	
	if(desc.cont > 0)
	{
		
		Partido partido;
		
		textcolor(LIGHTGREEN);
		printf("\n\n\tDIGITE NOME DO PARTIDO, REFERENTE AO CANDIDATO.  [ENTER PARA SAIR]: ");
		textcolor(LIGHTCYAN);
		fflush(stdin);	gets(partido.nome);
		while(strcmp(partido.nome, "") != 0)
		{
			ListaPartidos *partidoProcurado = procuraPartido_nome(desc, partido.nome);
			if(partidoProcurado != NULL)
			{
				Candidato candidato;
				printf("\n\tNUMERO DO CANDIDATO [-1 = EXIT]: ");
				scanf("%d", &candidato.numero);
				while(candidato.numero != -1)
				{
					ListaCandidatos *candidatoProcurado = procuraCandidato_numero(
					partidoProcurado->partido.listaCandidatos, candidato.numero);
					if(candidatoProcurado != NULL)
					{
						Candidato newCandidato = candidatoProcurado->candidato;
						Candidato aux = newCandidato;
						char op;
						do
						{
							system("cls");
							printf("\n\tPARTIDO: %s", partido.nome);	
							
							
							textcolor(LIGHTGREEN);	
							printf("\n\tDADOS DO CANDIDATO (SITUACAO ANTIGA).");
							
							
							textcolor(LIGHTBLUE);
							printf("\n\tNOME: %s\n\tNUMERO: %d\n\tVOTOS:%d", candidatoProcurado->candidato.nome, 
								candidatoProcurado->candidato.numero,
								candidatoProcurado->candidato.votos);
							
							
							
							textcolor(YELLOW);
							printf("\n\n\tDADOS DO CANDIDATO (SITUACAO ATUAL): ");
							textcolor(LIGHTCYAN);
							printf("\n\tNOME: %s\n\tNUMERO: %d\n\tVOTOS:%d", aux.nome,
																			 aux.numero,
							 												 aux.votos);
							 									
																 
							textcolor(YELLOW);			 
							printf("\n\n\tDESEJA MUDAR QUAL DADO? [ESCOLHA]");
							
							textcolor(LIGHTRED);
							printf("\n\t[ 0 ] - VOLTAR E CONCLUIR.");
							printf("\n\t[ 1 ] - NOME.");
							printf("\n\t[ 2 ] - NUMERO.");
							printf("\n\t[ 3 ] - VOTOS.");
							op = getch();
							
							if(op == '1')
							{
								char auxString[30];
								
								textcolor(LIGHTBLUE);
								printf("\n\n\tNOVO NOME: ");
								fflush(stdin);	gets(auxString);
								ListaCandidatos *procura = procuraCandidatoALL_nome(desc, auxString);
								if(procura != NULL)
								{
									textcolor(RED);
									printf("\n\tNOME JA ESTA SENDO ULTIZADO. [PRESS ENTER]");
								}
								else
								{
									textcolor(LIGHTGREEN);
									printf("\n\tNOME ALTERADO. [PRESS ENTER]");
									strcpy(aux.nome ,auxString);
								}
									
								getch();	
							}
							else if(op == '2')
							{
								int auxInt;
								textcolor(LIGHTBLUE);
								printf("\n\n\tNOVO NUMERO: ");
								scanf("%d", &auxInt);
								ListaCandidatos *procura = procuraCandidatoALL_numero(desc, auxInt);
								if(procura != NULL)
								{
									textcolor(RED);
									printf("\n\tNUMERO JA ESTA SENDO ULTIZADO. [PRESS ENTER]");
								}
								else
								{
									textcolor(LIGHTGREEN);
									aux.numero = auxInt;
									printf("\n\tNUMERO ALTERADO. [PRESS ENTER]");
								}
									
								getch();
							}
							else if(op == '3')
							{
								int auxInt;
								textcolor(LIGHTBLUE);
								printf("\n\n\t(QUE FEIO EM, NAO RECOMENDADO).\n\tNOVA QUANTIDADE DE VOTOS: ");
								scanf("%d", &auxInt);
								if(auxInt < 0)
								{
									textcolor(RED);
									printf("\n\tVOTOS TEM QUE SER NO MINIMO 0. [PRESS ENTER]");
								}
								else
								{
									textcolor(LIGHTGREEN);
									printf("\n\tQUANTIDADE DE VOTOS ALTERADO. [PRESS ENTER]");
									aux.votos = auxInt;	
								}
								
								getch();
							}
						}while(op != '0');
						
						newCandidato = aux;
						
						partidoProcurado->partido.listaCandidatos = alteraDadosCandidato(partidoProcurado->partido.listaCandidatos,
																	candidatoProcurado, newCandidato);
						printf("\n\n\tALTERACOES CONCLUIDAS!! [PRESS ENTER]");

					}
					else
						printf("\n\n\tCANDIDATO NAO EXISTE [PRESS ENTER]");
					getch();
					
					system("cls");
					printf("\n\n\tNUMERO DO CANDIDATO DESEJADO [-1 = EXIT]: ");
					scanf("%d", &candidato.numero);
				}
			}
			else
				printf("\n\n\tPARTIDO NAO EXISTE. [PRESS ENTER]");
			
			system("cls");
			textcolor(LIGHTGREEN);
			printf("\n\n\tDIGITE NOME DO PARTIDO, REFERENTE AO CANDIDATO[ENTER PARA SAIR]: ");
			textcolor(LIGHTCYAN);
			fflush(stdin);	gets(partido.nome);
		}
	}
	else
	{
		textcolor(LIGHTGREEN);
		printf("\n\n\tNAO HA DADOS PARA ALTERAR.");
		
		textcolor(RED);
		printf("\n\n\t[PRESS ENTER]");
		getch();
	}
}

void inserirPartidos(Descritor &desc)
{
	system("cls");
	Partido partido;
	partido.listaCandidatos = iniciarListaCandidatos();
	
	textcolor(LIGHTGREEN);
	printf("\n\n\tNOME DO PARTIDO [ENTER PARA SAIR]: ");
	fflush(stdin);	textcolor(CYAN);gets(partido.nome);
	while(strcmp(partido.nome, "") != 0)
	{
		ListaPartidos *procuraPartido = procuraPartido_nome(desc, partido.nome);
		if(procuraPartido == NULL)
		{
			textcolor(LIGHTGREEN);
			printf("\n\n\tNUMERO DO PARTIDO [-1 = EXIT]: ");
			textcolor(CYAN);
			scanf("%d", &partido.numero);
			while(partido.numero != -1)
			{	
				ListaPartidos *procuraPartido = procuraPartido_numero(desc, partido.numero);
				if(procuraPartido == NULL)
				{
					inserirPartido_final(desc, partido);
					textcolor(LIGHTGREEN);
					printf("\n\n\tPARTIDO INSERIDO. [PRESS ENTER]");
					getch();
					partido.numero = -1;
					
					textcolor(LIGHTCYAN);
					printf("\n\n\tDESEJA INSERIR CANDIDATOS? [S/N].");
					char op = toupper(getch());
					if(op == 'S' || op == 'Y')
						insercaoCandidatosDireto(desc, partido.nome);		
				}
				else
				{
					textcolor(RED);
					printf("\n\n\tNUMERO DO PARTIDO EXISTENTE. [PRESS ENTER]");
					getch();
					
					textcolor(LIGHTGREEN);
					printf("\n\n\tNUMERO DO PARTIDO [-1 = EXIT]: ");
					textcolor(CYAN);
					scanf("%d", &partido.numero);
				}
			}
		}
		else
		{
			printf("\n\n\tNOME DO PARTIDO EXISTENTE.");
			getch();
		}
		
		system("cls");
		textcolor(LIGHTGREEN);
		printf("\n\n\tNOME DO PARTIDO [ENTER PARA SAIR]: ");
		fflush(stdin);	textcolor(CYAN);gets(partido.nome);			
	}
}

void insercaoCandidatosDireto(Descritor &desc, char nomePartido[30])
{
	system("cls");
	ListaCandidatos *candidatos = iniciarListaCandidatos();
	Candidato candidato;
	
	ListaPartidos *procuraPartidoNome = procuraPartido_nome(desc, nomePartido);
	
	printf("\n\n\tNOME DO CANDIDATO [ENTER PARA SAIR]: ");
	fflush(stdin);	gets(candidato.nome);
	while(strcmp(candidato.nome, "") != 0)
	{
		ListaCandidatos *procuraCandidatoNome = procuraCandidatoALL_nome(desc, candidato.nome);
		if(procuraCandidatoNome == NULL)
		{
			printf("\n\n\tNUMERO DO CANDIDATO [-1 = EXIT]: ");
			scanf("%d", &candidato.numero);
			while(candidato.numero != -1)
			{
				ListaCandidatos *procuraCandidatoNumero = procuraCandidatoALL_numero(desc, candidato.numero);
				if(procuraCandidatoNumero == NULL)
				{
					candidato.votos=0;
					
										
					procuraPartidoNome->partido.listaCandidatos = inserirCandidatosOrdenado_numero(procuraPartidoNome->partido.listaCandidatos, candidato);
					//partidoAchado ->  partido.listaCandidatos = candidatos;
					
					printf("\n\n\tINSERIDO COM SUCESSO.");
					candidato.numero = -1;
					getch();
				}
				else
				{
					printf("\n\n\tNUMERO DO CANDIDATO JA EXISTENTE. [PRESS ENTER].");
					getch();
					
					printf("\n\n\tNUMERO DO CANDIDATO [-1 = EXIT]: ");
					scanf("%d", &candidato.numero);
				}
			}
		}
		else
		{
			printf("\n\n\tNOME DO CANDIDATO JA EXISTENTE. [PRESS ENTER]");
			getch();
		}
		
		system("cls");
		printf("\n\n\tNOME DO CANDIDATO [ENTER PARA SAIR]: ");
		fflush(stdin);	gets(candidato.nome);
	}
}

void insercaoCandidatos(Descritor &desc)
{
	system("cls");
	Partido partido;
	
	textcolor(LIGHTGREEN);
	printf("\n\n\tNOME DO PARTIDO A INSERIR O CANDIDATO. [ENTER PARA SAIR]: ");
	fflush(stdin);	gets(partido.nome);
	while(strcmp(partido.nome, "") != 0)
	{
		ListaPartidos *procuraPartidoNome = procuraPartido_nome(desc, partido.nome);
		if(procuraPartidoNome != NULL)
		{	
			Candidato candidato;
			textcolor(LIGHTBLUE);
			printf("\n\n\tNOME DO CANDIDATO. [ENTER PARA SAIR]: ");
			fflush(stdin);	gets(candidato.nome);
			while(strcmp(candidato.nome, "") != 0)
			{
				ListaCandidatos *procuraCandidatoNome = procuraCandidatoALL_nome(desc, candidato.nome);
				if(procuraCandidatoNome == NULL)
				{
					printf("\n\n\tNUMERO DO CANDIDATO [-1 = EXIT]: ");
					scanf("%d", &candidato.numero);
					while(candidato.numero != -1)
					{					
						ListaCandidatos *procuraCandidatoNumero = procuraCandidatoALL_numero(desc, candidato.numero);
						if(procuraCandidatoNumero == NULL)
						{
							candidato.votos=0;
							procuraPartidoNome->partido.listaCandidatos = inserirCandidatosOrdenado_numero(procuraPartidoNome->partido.listaCandidatos, candidato);
							printf("\n\n\tINSERIDO COM SUCESSO.");
							candidato.numero = -1;
							getch();
						}
						else
						{
							printf("\n\n\tNUMERO DO CANDIDATO EXISTENTE. [PRESS ENTER]");							
							getch();
							
							printf("\n\n\tNUMERO DO CANDIDATO [-1 = EXIT]: ");
							scanf("%d", &candidato.numero);
						}
						
					}
				}
				else
				{
					printf("\n\n\tNOME DO CANDIDATO EXISTENTE. [PRESS ENTER]");							
					getch();
				}
				
				system("cls");
				textcolor(LIGHTBLUE);
				printf("\n\n\tNOME DO CANDIDATO. [ENTER PARA SAIR]: ");
				fflush(stdin);	gets(candidato.nome);
			}
		
		}
		else
		{
			printf("\n\n\tNOME DO PARTIDO NAO EXISTE. [PRESS ENTER].");
			getch();
		}
		
		system("cls");
		textcolor(LIGHTGREEN);
		printf("\n\n\tNOME DO PARTIDO A INSERIR O CANDIDATO. [ENTER PARA SAIR]: ");
		fflush(stdin);	gets(partido.nome);
	}
}


void importarDados(Descritor &desc, int &flag_importacao)
{
	system("cls");
	if(flag_importacao == 0)
	{
		
		printf("\n\t[ * ] - CARREGANDO DADOS.");
		
		int sucess = carregaDadosMemoria(desc);
		
		if(sucess)
		{
			system("cls");
			textcolor(YELLOW);
			printf("\n\n\t[ * ] - DADOS CARREGADOS COM SUCESSO.");
		}
			
		else
		{
			textcolor(YELLOW);
			printf("\n\t[ * ] - DADOS CARREGADOS. - EXISTEM DADOS REPITIDOS, NAO FORAM CARREGADOS");
		}
			
		flag_importacao=1;	
	}
	else
		printf("\n\t[ * ] - VOCE JA CARREGOU OS DADOS UMA VEZ.");
		
	
	textcolor(LIGHTGREEN);		
	printf("\n\n\t[ PRESS ENTER ]");
	getch();
	
}

void exportarDados(Descritor &desc)
{
	system("cls");
	
	printf("\n\n\t[ * ] - GRAVANDO DADOS, ESPERE.");
	
	system("cls");
	gravarHardDisk(desc);
	
	textcolor(YELLOW);
	printf("\n\n\t[ * ] - DADOS GRAVADOS.");
	
	textcolor(LIGHTGREEN);
	printf("\n\n\t[PRESS ENTER]");
	getch();
}

int carregaDadosMemoria(Descritor &desc)
{
	int flag_dadosRepitidos=1;
	Partido partido;
	
	FILE *arq = fopen("dados.txt", "r");
	
	fscanf(arq, "%s", &partido.nome);
	while(!feof(arq) != 0)
	{
		ListaPartidos *procurarNomePartido = procuraPartido_nome(desc, partido.nome);
		if(procurarNomePartido == NULL)
		{
			fscanf(arq, "%d", &partido.numero);
			ListaPartidos *procurarNumeroCandidato = procuraPartido_numero(desc, partido.numero);
			if(procurarNumeroCandidato == NULL)
			{
				ListaCandidatos *listaCandidatos = NULL;
				Candidato candidato;
				
				fscanf(arq, "%s", &candidato.nome);	
				while(stricmp(candidato.nome, "--") != 0)
				{
					ListaCandidatos *procuraNomeCandidato = procuraCandidatoALL_nome(desc, candidato.nome);
					if(procuraNomeCandidato == NULL)
					{
						fscanf(arq ,"%d", &candidato.numero);
						ListaCandidatos *procuraNumeroCandidato = procuraCandidatoALL_numero(desc, candidato.numero);
						if(procuraNumeroCandidato == NULL)
						{
							fscanf(arq ,"%d", &candidato.votos);	
							listaCandidatos = inserirCandidatosOrdenado_numero(listaCandidatos, candidato);
						}
					}
					else
					{
						flag_dadosRepitidos=0;
						for(int i=0 ; i < 2 ; i++)
							fscanf(arq, "%s", &candidato.nome);
					}
					
					fscanf(arq, "%s", &candidato.nome);	
				}			
				
				partido.listaCandidatos = listaCandidatos;
				inserirPartido_final(desc, partido);
			}
			else
			{
				flag_dadosRepitidos=0;
				fscanf(arq, "%s", &partido.nome);
				while(strcmp(partido.nome, "--") != 0)
					fscanf(arq, "%s", &partido.nome);
			}
				
		}
		else
		{
			flag_dadosRepitidos=0;
			fscanf(arq, "%s", &partido.nome);
			while(strcmp(partido.nome, "--") != 0)
				fscanf(arq, "%s", &partido.nome);
		}
		
		fscanf(arq, "%s", &partido.nome);
	}
	
	fclose(arq);
	
	return flag_dadosRepitidos;
}

void gravarHardDisk(Descritor desc)
{
	FILE *arq = fopen("dados_aux.txt","w");
	
	ListaPartidos *descritorPartidos = desc.inicio;
	while(desc.cont > 0)
	{
		fprintf(arq, "%s %d\n", descritorPartidos->partido.nome,
							    descritorPartidos->partido.numero);
		
		ListaCandidatos *listaCandidatos = descritorPartidos->partido.listaCandidatos;
		while(listaCandidatos != NULL)
		{
			fprintf(arq, "%s %d %d\n",  listaCandidatos->candidato.nome,
										listaCandidatos->candidato.numero, 
										listaCandidatos->candidato.votos);
			
			listaCandidatos = listaCandidatos->prox;
		}
		fprintf(arq, "--\n");
		
		desc.cont--;
		descritorPartidos = descritorPartidos->prox;
	}
	
	fclose(arq);
	
	remove("dados.txt");
	rename("dados_aux.txt", "dados.txt");
}

