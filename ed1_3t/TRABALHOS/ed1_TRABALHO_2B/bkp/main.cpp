#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio2.h>

#include "tad_partidos.h"

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
		if( op == '1')		inserirPartidos(desc);
			
		else if(op == '2')	insercaoCandidatos(desc);
			
		else if(op == '3')	interface_deletarPartido(desc);
			
		else if(op == '4')	interface_deletarCandidato(desc);
			
		else if(op == '5')	alterarCandidato(desc);
			
		else if(op == '6')	exibirPartidosComCandidatos(desc);
			
		else if(op == '7')	showRank_candidatos(desc);
				
		else if(op == '8')	importarDados(desc, flag_importacao);
			
		else if(op == '9')	exportarDados(desc);				
						
	}while(op != '0');
}

char menuPrincipal()
{
	system("cls");
	printf("\n\t[ 0 ] - SAIR.");
	printf("\n\t[ 1 ] - INSERIR PARTIDO.");
	printf("\n\t[ 2 ] - INSERIR CANDIDATO.");
	printf("\n\t[ 3 ] - EXCLUIR PARTIDO. -- FAZER/TESTAR");
	printf("\n\t[ 4 ] - EXCLUIR CANDIDATO. -- FAZER/TESTAR");
	printf("\n\t[ 5 ] - ALTERAR CANDIDATO. -- FAZER VERIFICAÇOES");
	printf("\n\t[ 6 ] - EXIBIR TUDO. -- MOSTRAR EM MODO DE APONTAMENTO");
	printf("\n\t[ 7 ] - RANK DOS CANDIDATOS.  -- FAZER");
	printf("\n\t[ 8 ] - IMPORTAR DADOS.");
	printf("\n\t[ 9 ] - EXPORTAR DADOS. --COLOCAR NOME DO ARQUIVO ORIGINAL.");
	printf("\n\t[ 10 ] - Votar. - Fazer Carai.");
	
	return getch();	
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

void showRank_candidatos(Descritor desc)
{
	system("cls");
	
	ListaCandidatos *listaRank = getListaRank_candidatos(desc);
	if(listaRank != NULL)
	{
		textcolor(LIGHTGREEN);
		printf("\n\nINICIO DO RANK.\n\n");
		
		gotoxy(10, 8); textcolor(LIGHTRED);
		printf("POSICAO");
		
		gotoxy(20, 8); 
		printf("NOME");
		
		gotoxy(50, 8); 
		printf("NUMERO");
		
		gotoxy(60, 8); 
		printf("VOTOS");
		
		int cont=1;
		int posLinha=10;
		while(listaRank != NULL)
		{
			gotoxy(10, posLinha); textcolor(RED);
			printf("%d", cont++);
			
			gotoxy(20, posLinha); textcolor(LIGHTBLUE);	
			printf("%s", listaRank->candidato.nome);
			
			gotoxy(50, posLinha); textcolor(LIGHTCYAN);	
			printf("%d", listaRank->candidato.numero);
			
			gotoxy(60, posLinha++); textcolor(RED);	
			printf("%d\n",	listaRank->candidato.votos);			
							
			listaRank = listaRank->prox;
		}
		
		textcolor(LIGHTGREEN);
		printf("\n\n\tFINAL DO RANK. [PRESS ENTER]");
	}
	else
		printf("\n\n\tNAO HA CANDIDATOS INSERISO PARA MOSTRAR. [PRESS ENTER]");
	
	
	getch();
}

void interface_deletarPartido(Descritor &desc)
{
	system("cls");
	
	Partido partido;
	
	printf("NOME DO PARTIDO [ENTER PARA SAIR]: ");
	fflush(stdin);	gets(partido.nome);
	while(strcmp(partido.nome, "") != 0)
	{
		Partido auxPartido;
		ListaPartidos *procura = procuraPartido_nome(desc, partido.nome);
		if(procura == NULL)
		{
			printf("\n\nPARTIDO NAO CADASTRADO");
			getch();
		}
		else
		{
			auxPartido = procura->partido;
			printf("\n\n[ * ] - DELETANDO PARTIDO.");
			deletarPartido(desc, procura);
			printf("\n\n[ * ] - DELETADO.");
		}
		
		printf("NOME DO PARTIDO [ENTER PARA SAIR]: ");
		fflush(stdin);	gets(partido.nome);
	}
}

void interface_deletarCandidato(Descritor &desc)
{
	system("cls");
	
	Partido partido;
	
	printf("NOME DO PARTIDO [ENTER PARA SAIR]: ");
	fflush(stdin);	gets(partido.nome);
	while(strcmp(partido.nome, "") != 0)
	{
		Partido auxPartido;
		ListaPartidos *procura = procuraPartido_nome(desc, partido.nome);
		if(procura == NULL)
		{
			printf("\n\nPARTIDO NAO CADASTRADO");
			getch();
		}
		else
		{
			Candidato candidato;
			
			printf("\nNUMERO DO CANDIDATO [-1 = EXIT]: ");
			scanf("%d", &candidato.numero);
			while(candidato.numero != -1)
			{
				ListaCandidatos *procuraCandidatoNumero = procuraCandidato_numero(procura->partido.listaCandidatos, candidato.numero);
				
				if(procuraCandidatoNumero == NULL)
					printf("\nNUMERO DE CANDIDATO NAO EXISTENTE. [PRESS ENTER].");
				else
				{
					procura->partido.listaCandidatos = deletarCandidato_numero(procura->partido.listaCandidatos, candidato.numero);
					printf("\nCANDIDATO EXCLUIDO COM SUCESSO.");
					candidato.numero = -1;
				}
				
				getch();
				
				printf("\nNUMERO DO CANDIDATO [-1 = EXIT]: ");
				scanf("%d", &candidato.numero);
			}
		}
		
		printf("NOME DO PARTIDO [ENTER PARA SAIR]: ");
		fflush(stdin);	gets(partido.nome);
	}
}

void alterarCandidato(Descritor desc) 
{
	system("cls");
	
	Partido partido;
	
	
	printf("\n\n\tNOME DO PARTIDO [ENTER PARA SAIR]: ");
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
							
						printf("\n\tDADOS DO CANDIDATO (SITUACAO ANTIGA).");
						printf("\n\tNOME: %s\n\tNUMERO: %d\n\tVOTOS:%d", candidatoProcurado->candidato.nome, 
							candidatoProcurado->candidato.numero,
							candidatoProcurado->candidato.votos);
						
						printf("\n\n\tDADOS DO CANDIDATO (SITUACAO ATUAL): ");
						printf("\n\tNOME: %s\n\tNUMERO: %d\n\tVOTOS:%d", aux.nome,
																		 aux.numero,
						 												 aux.votos);
						 												 
						printf("\n\n\tDESEJA MUDAR QUAL DADO? [ESCOLHA]");
						
						printf("\n\t[ 0 ] - VOLTAR E CONCLUIR.");
						printf("\n\t[ 1 ] - NOME.");
						printf("\n\t[ 2 ] - NUMERO.");
						printf("\n\t[ 3 ] - VOTOS.");
						op = getch();
						
						if(op == '1')
						{
							char auxString[30];
							printf("\n\n\tNOVO NOME: ");
							fflush(stdin);	gets(auxString);
							ListaCandidatos *procura = procuraCandidatoALL_nome(desc, auxString);
							if(procura != NULL)
								printf("\n\tNOME JA ESTA SENDO ULTIZADO. [PRESS ENTER]");
							else
							{
								printf("\n\tNOME ALTERADO. [PRESS ENTER]");
								strcpy(aux.nome ,auxString);
							}
								
							getch();	
						}
						else if(op == '2')
						{
							int auxInt;
							printf("\n\n\tNOVO NUMERO: ");
							scanf("%d", &auxInt);
							ListaCandidatos *procura = procuraCandidatoALL_numero(desc, auxInt);
							if(procura != NULL)
								printf("\n\tNUMERO JA ESTA SENDO ULTIZADO. [PRESS ENTER]");
							else
							{
								aux.numero = auxInt;
								printf("\n\tNUMERO ALTERADO. [PRESS ENTER]");
							}
								
							getch();
						}
						else if(op == '3')
						{
							int auxInt;
							printf("\n\n\t(QUE FEIO EM, NAO RECOMENDADO).\n\tNOVA QUANTIDADE VOTOS: ");
							scanf("%d", &auxInt);
							if(auxInt < 0)
							{
								printf("\n\tVOTOS TEM QUE SER NO MINIMO 0. [PRESS ENTER]");
								
							}
							else
							{
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
					getch();
				}
				else
					printf("\n\n\tCANDIDATO NAO EXISTE [PRESS ENTER]");
				getch();
				
				system("cls");
				printf("\n\n\tNUMERO DO CANDIDATO [-1 = EXIT]: ");
				scanf("%d", &candidato.numero);
			}
		}
		else
			printf("\n\n\tPARTIDO NAO EXISTE. [PRESS ENTER]");
		
		system("cls");
		printf("\n\n\tNOME DO PARTIDO [ENTER PARA SAIR]: ");
		fflush(stdin);	gets(partido.nome);
	}
}

void inserirPartidos(Descritor &desc)
{
	system("cls");
	Partido partido;
	partido.listaCandidatos = iniciarListaCandidatos();
	
	printf("\nNOME DO PARTIDO [ENTER PARA SAIR]: ");
	fflush(stdin);	gets(partido.nome);
	while(strcmp(partido.nome, "") != 0)
	{
		ListaPartidos *procuraPartido = procuraPartido_nome(desc, partido.nome);
		if(procuraPartido == NULL)
		{
			printf("\nNUMERO DO PARTIDO [-1 = EXIT]: ");
			scanf("%d", &partido.numero);
			while(partido.numero != -1)
			{	
				ListaPartidos *procuraPartido = procuraPartido_numero(desc, partido.numero);
				if(procuraPartido == NULL)
				{
					inserirPartido_final(desc, partido);
					printf("\nPARTIDO INSERIDO. [PRESS ENTER]");
					getch();
					partido.numero = -1;
					
					printf("\n\nDESEJA INSERIR CANDIDATOS? [S/N].");
					char op = toupper(getch());
					if(op == 'S')
						insercaoCandidatosDireto(desc, partido.nome);		
				}
				else
				{
					printf("\nNUMERO DO PARTIDO EXISTENTE. [PRESS ENTER]");
					getch();
					
					printf("\nNUMERO DO PARTIDO [-1 = EXIT]: ");
					scanf("%d", &partido.numero);
				}
			}
		}
		else
		{
			printf("\nNOME DO PARTIDO EXISTENTE.");
			getch();
		}
		
		system("cls");
		printf("\nNOME DO PARTIDO [ENTER PARA SAIR]: ");
		fflush(stdin);	gets(partido.nome);			
	}
}

void insercaoCandidatosDireto(Descritor &desc, char nomePartido[30])
{
	system("cls");
	ListaCandidatos *candidatos = iniciarListaCandidatos();
	Candidato candidato;
	
	ListaPartidos *procuraPartidoNome = procuraPartido_nome(desc, nomePartido);
	
	printf("\nNOME DO CANDIDATO [ENTER PARA SAIR]: ");
	fflush(stdin);	gets(candidato.nome);
	while(strcmp(candidato.nome, "") != 0)
	{
		ListaCandidatos *procuraCandidatoNome = procuraCandidatoALL_nome(desc, candidato.nome);
		if(procuraCandidatoNome == NULL)
		{
			printf("\nNUMERO DO CANDIDATO [-1 = EXIT]: ");
			scanf("%d", &candidato.numero);
			while(candidato.numero != -1)
			{
				ListaCandidatos *procuraCandidatoNumero = procuraCandidatoALL_numero(desc, candidato.numero);
				if(procuraCandidatoNumero == NULL)
				{
					candidato.votos=0;
					
										
					procuraPartidoNome->partido.listaCandidatos = inserirCandidatosOrdenado_numero(procuraPartidoNome->partido.listaCandidatos, candidato);
					//partidoAchado ->  partido.listaCandidatos = candidatos;
					
					printf("\nINSERIDO COM SUCESSO.");
					candidato.numero = -1;
					getch();
				}
				else
				{
					printf("\nNUMERO DO CANDIDATO JA EXISTENTE. [PRESS ENTER].");
					getch();
					
					printf("\nNUMERO DO CANDIDATO [-1 = EXIT]: ");
					scanf("%d", &candidato.numero);
				}
			}
		}
		else
		{
			printf("\nNOME DO CANDIDATO JA EXISTENTE. [PRESS ENTER]");
			getch();
		}
		
		system("cls");
		printf("\nNOME DO CANDIDATO [ENTER PARA SAIR]: ");
		fflush(stdin);	gets(candidato.nome);
	}
}

void insercaoCandidatos(Descritor &desc)
{
	system("cls");
	Partido partido;
	
	printf("\nNOME DO PARTIDO A INSERIR O CANDIDATO. [ENTER PARA SAIR]: ");
	fflush(stdin);	gets(partido.nome);
	while(strcmp(partido.nome, "") != 0)
	{
		ListaPartidos *procuraPartidoNome = procuraPartido_nome(desc, partido.nome);
		if(procuraPartidoNome != NULL)
		{	
			Candidato candidato;
			printf("\nNOME DO CANDIDATO. [ENTER PARA SAIR]: ");
			fflush(stdin);	gets(candidato.nome);
			while(strcmp(candidato.nome, "") != 0)
			{
				ListaCandidatos *procuraCandidatoNome = procuraCandidatoALL_nome(desc, candidato.nome);
				if(procuraCandidatoNome == NULL)
				{
					printf("\nNUMERO DO CANDIDATO [-1 = EXIT]: ");
					scanf("%d", &candidato.numero);
					while(candidato.numero != -1)
					{					
						ListaCandidatos *procuraCandidatoNumero = procuraCandidatoALL_numero(desc, candidato.numero);
						if(procuraCandidatoNumero == NULL)
						{
							candidato.votos=0;
							procuraPartidoNome->partido.listaCandidatos = inserirCandidatosOrdenado_numero(procuraPartidoNome->partido.listaCandidatos, candidato);
							printf("\nINSERIDO COM SUCESSO.");
							candidato.numero = -1;
							getch();
						}
						else
						{
							printf("\nNUMERO DO CANDIDATO EXISTENTE. [PRESS ENTER]");							
							getch();
							
							printf("\nNUMERO DO CANDIDATO [-1 = EXIT]: ");
							scanf("%d", &candidato.numero);
						}
						
					}
				}
				else
				{
					printf("\nNOME DO CANDIDATO EXISTENTE. [PRESS ENTER]");							
					getch();
				}
				
				system("cls");
				printf("\nNOME DO CANDIDATO. [ENTER PARA SAIR]: ");
				fflush(stdin);	gets(candidato.nome);
			}
		
		}
		else
		{
			printf("\nNOME DO PARTIDO NAO EXISTE. [PRESS ENTER].");
			getch();
		}
		
		system("cls");
		printf("\nNOME DO PARTIDO A INSERIR O CANDIDATO. [ENTER PARA SAIR]: ");
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
			printf("\n\t[ * ] - DADOS CARREGADOS COM SUCESSO.");
		else
		{
			printf("\n\t[ * ] - DADOS CARREGADOS. - EXISTEM DADOS REPITIDOS, NAO FORAM CARREGADOS");
		}
			
		flag_importacao=1;	
	}
	else
		printf("\n\t[ * ] - VOCE JA CARREGOU OS DADOS.");
		
			
	printf("\n\n\t[ PRESS ENTER ]");
	getch();
	
}

void exportarDados(Descritor &desc)
{
	printf("\n[ * ] - GRAVANDO DADOS.");
	
	gravarHardDisk(desc);
	printf("\n[ * ] - DADOS GRAVADOS.");
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
	
	//remove("dados.txt");
	//rename("dados_aux.txt", "dados.txt");
}

