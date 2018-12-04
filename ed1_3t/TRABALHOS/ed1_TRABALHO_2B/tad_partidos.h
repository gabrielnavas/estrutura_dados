#include "tad_candidatos.h"

struct Partido
{
	ListaCandidatos *listaCandidatos;
	
	char nome[30];
	int numero;
};

struct ListaPartidos
{
	Partido partido;
	ListaPartidos *ante, *prox;
};

struct Descritor
{
	ListaPartidos *inicio, *fim;
	int cont;
};

void deletarPartido(Descritor &desc, ListaPartidos *no)
{	
	if(no->ante == NULL)
	{
		no->prox->ante = NULL;
		desc.inicio = no->prox;
	}
	else if(no->prox == NULL)
	{
		no->ante->prox = NULL;
		desc.fim = no->ante;
	}
	else
	{
		no->ante->prox = no->prox;
		no->prox->ante = no->ante;
	}
	desc.cont--;
	
	if(no->partido.listaCandidatos != NULL)
		deletarCandidatos(no->partido.listaCandidatos);
		
	delete(no);
}

void iniciarDescritor(Descritor &desc)
{
	desc.cont=0;
	desc.fim=NULL;
	desc.inicio=NULL;
}

void exibirPartidos(Descritor desc)
{
	if(desc.cont > 0)
	{
		ListaPartidos *no = desc.inicio;
		while(no != NULL)
		{
			printf("\nNOME PARTIDO: "); puts(no->partido.nome);
			printf("NUMERO PARTIDO: %d\n", no->partido.numero);
			
			no = no->prox;
		}
	}
}

void exibirPartidosComCandidatos(Descritor desc)
{
	system("cls");
	if(desc.cont > 0)
	{
		ListaPartidos *no = desc.inicio;
		while(no != NULL)
		{
			textcolor(LIGHTBLUE);
			printf("\n\tNOME PARTIDO: "); 
			
			textcolor(RED);
			for(int i=0 ; i < strlen(no->partido.nome) ; i++)
				printf("%c", no->partido.nome[i]);
				
			textcolor(RED);	
			printf("\tNUMERO PARTIDO: ");
			textcolor(LIGHTRED);
			printf("%d\n", no->partido.numero);
			
			exibirCandidatos(no->partido.listaCandidatos);
			
			textcolor(LIGHTGREEN);	
			printf("\n\n\t---------------------------");
			
			no = no->prox;
		}
		
		printf("\n\n\tFIM DE EXIBICAO. [PRESS ENTER]");
		getch();
	}
}


void exibirPartidosComCandidatosComPonteiros(Descritor desc)
{
	int som=600;
	system("cls");
	if(desc.cont > 0)
	{
		ListaPartidos *no = desc.inicio;
		while(no != NULL)
		{
			textcolor(RED);	
			printf("|%s|", no->partido.nome);
			
			Sleep(500);
			Beep(som, 500);
			som +=200;
			
			textcolor(GREEN);
			printf(" -> ");
			
			if(no->partido.listaCandidatos == NULL)
			{
				textcolor(RED);
				printf("NULL");
			}
			else
				exibirCandidatosComPonteiros(no->partido.listaCandidatos);
			
			
			printf("\n");
			textcolor(GREEN);
			printf(" ||");
			printf("\n");
			
			no = no->prox;
		}
		
		
		textcolor(GREEN);
		printf(" ||");
		printf("\n");
		
		textcolor(RED);
		printf("NULL");
		
		textcolor(LIGHTCYAN);
		printf("\n\n\tFIM DE EXIBICAO. [PRESS ENTER]");
		getch();
	}
}

ListaPartidos *criaCaixaPartido(Partido partido)
{
	ListaPartidos *novo = new ListaPartidos;
	
	novo->ante = NULL;
	novo->prox = NULL;
	novo->partido = partido;
	
	return novo;
}

ListaCandidatos *procuraCandidatosALL(Descritor desc, Partido partido)
{		
	if(desc.cont > 0)
	{	
		ListaPartidos *noPartidos = desc.inicio;
		while(noPartidos != NULL)
		{
			ListaCandidatos *noCandidatos = noPartidos->partido.listaCandidatos;
			while(noCandidatos != NULL)
			{
				if(stricmp(noCandidatos->candidato.nome, partido.nome) == 0 || noCandidatos->candidato.numero == partido.numero)
					return noCandidatos;
				
				noCandidatos = noCandidatos->prox;				
			}
			
			noPartidos = noPartidos->prox;
		}
			
	}
		
	return NULL;				
}

ListaCandidatos *procuraCandidatoALL_nome(Descritor desc, char nome[30])
{
	if(desc.cont > 0)
	{	
		ListaPartidos *noPartidos = desc.inicio;
		while(noPartidos != NULL)
		{
			ListaCandidatos *noCandidatos = noPartidos->partido.listaCandidatos;
			while(noCandidatos != NULL)
			{
				if(stricmp(noCandidatos->candidato.nome, nome) == 0)
					return noCandidatos;
				
				noCandidatos = noCandidatos->prox;				
			}
			
			noPartidos = noPartidos->prox;
		}
			
	}
		
	return NULL;				
}

ListaPartidos *retornaPonteiroDoCandidatoAchado(Descritor desc, int numero)
{
	if(desc.cont > 0)
	{
		ListaPartidos *noPartidos = desc.inicio;
		while(noPartidos != NULL)
		{
			ListaCandidatos *procuraPorNumero = procuraCandidato_numero(noPartidos->partido.listaCandidatos, numero);
			if(procuraPorNumero != NULL)
				return noPartidos;
			
			noPartidos = noPartidos->prox;	
		}
	}
	
}

ListaCandidatos *procuraCandidatoALL_numero(Descritor desc, int numero)
{
	if(desc.cont > 0)
	{	
		ListaPartidos *noPartidos = desc.inicio;
		while(noPartidos != NULL)
		{
			ListaCandidatos *noCandidatos = noPartidos->partido.listaCandidatos;
			while(noCandidatos != NULL)
			{
				if(noCandidatos->candidato.numero == numero)
					return noCandidatos;
				
				noCandidatos = noCandidatos->prox;				
			}
			
			noPartidos = noPartidos->prox;
		}
	}
		
	return NULL;				
}

ListaPartidos *procuraPartido_numero(Descritor desc, int numero)
{
	if(desc.cont > 0)
	{	
		ListaPartidos *no = desc.inicio;
		while(no != NULL)
		{
			if(no->partido.numero ==  numero)
				return no;
			
			no = no->prox;				
		}	
	}
		
	return NULL;				
}

ListaPartidos *procuraPartido_nome(Descritor desc, char nome[30])
{
	Partido auxProcurando;
	if(desc.cont > 0)
	{	
		ListaPartidos *no = desc.inicio;
		while(no != NULL)
		{
			auxProcurando = no->partido;
			if(strcmp(no->partido.nome, nome) == 0)
				return no;
			
			no = no->prox;				
		}	
	}
		
	return NULL;				
}

void inserirPartido_final(Descritor &desc, Partido partido)
{	
	ListaPartidos *novo = criaCaixaPartido(partido);

	if(desc.cont == 0)
	{
		desc.inicio = novo;
		desc.fim = novo;
		desc.cont++;
		
		//return 1;
	}
	else
	{
		ListaCandidatos *procura = procuraCandidatosALL(desc, partido);
		if(procura == NULL)
		{
			desc.fim->prox = novo;
			novo->ante = desc.fim;
			desc.fim = novo;
			desc.cont++;
			
			//return 1;
		}
		/*
		else
			printf("\nPARTIDO JA CADASTRADO.");
		*/
	}
}
