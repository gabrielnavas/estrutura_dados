//#include "tad_partidos.h"

struct Candidato
{
	char nome[30];
	int numero;
	int votos;
};

struct ListaCandidatos
{
	Candidato candidato;
	ListaCandidatos *prox;
};



void deletarCandidatos(ListaCandidatos *listaCandidatos)
{
	if(listaCandidatos != NULL)
	{
		if(listaCandidatos->prox == NULL)
			delete(listaCandidatos->prox);
		else
		{
			ListaCandidatos *no = listaCandidatos;
			ListaCandidatos *apagar = listaCandidatos;
			while(no != NULL)
			{
				no = no->prox;
				delete(apagar);
				apagar = no;
			}		
		}
			
		listaCandidatos = NULL;	
	}
}

ListaCandidatos * iniciarListaCandidatos()
{
	return NULL;
}

ListaCandidatos * deletarCandidato_numero(ListaCandidatos *cabeca, int numeroKey)
{
	if(cabeca != NULL)
	{
		if(cabeca->candidato.numero == numeroKey)
		{
			ListaCandidatos *prox = cabeca->prox;
			delete(cabeca);
			cabeca = prox;
		}
			
		else
		{
			ListaCandidatos *no = cabeca;
			ListaCandidatos *ante = no;
			while(no != NULL && no->candidato.numero != numeroKey)
			{
				ante = no;
				no = no->prox;
			}
			
			if(no->prox == NULL)
			{
				delete(no);
				ante->prox = NULL;
			}
			else
			{				
				ante->prox = no->prox;
				delete(no);
			}
		}	
	}
	
	return cabeca;
}

void exibirCandidatosComPonteiros(ListaCandidatos *lista)
{
	int som=600;
	while(lista != NULL)
	{
		textcolor(LIGHTCYAN);
		printf("|%s|", lista->candidato.nome);
		
		Sleep(500);
		Beep(som, 500);
		som +=200;
		
		textcolor(GREEN);
		printf(" -> ");
		
		lista = lista->prox;
	}
	
	textcolor(RED);
	printf("NULL");
}
void exibirCandidatos(ListaCandidatos *lista)
{
	while(lista != NULL)
	{
		textcolor(LIGHTCYAN);
		printf("\n\tNOME CANDIDATO: "); 
		textcolor(LIGHTRED);
		for(int i=0 ; i < strlen(lista->candidato.nome) ; i++)
			printf("%c", lista->candidato.nome[i]);
		
		textcolor(LIGHTCYAN);		
		printf("\tNUMERO CANDIDATO: ");
		textcolor(LIGHTRED);
		printf("%d\n", lista->candidato.numero);
		
		textcolor(LIGHTCYAN);
		printf("\tVOTOS CANDIDATO: ");
		textcolor(LIGHTRED);
		printf("%d\n\n", lista->candidato.votos);
		
		lista = lista->prox;
	}
}

ListaCandidatos *criaCaixaCandidato(Candidato candidato)
{
	ListaCandidatos *novo = new ListaCandidatos;
	novo->prox = NULL;
	novo->candidato = candidato;
}

ListaCandidatos *procuraCandidato(ListaCandidatos *cabeca, Candidato candidato)
{
	while(cabeca != NULL)
	{
		if(strcmp(cabeca->candidato.nome, candidato.nome) == 0 || cabeca->candidato.numero == candidato.numero)
			return cabeca;
		cabeca = cabeca->prox;	
	}
	
	return NULL;
}

ListaCandidatos *procuraCandidato_nome(ListaCandidatos *cabeca, char nome[30])
{
	while(cabeca != NULL)
	{
		if(strcmp(cabeca->candidato.nome, nome) == 0)
			return cabeca;
		cabeca = cabeca->prox;	
	}
	
	return NULL;
}

ListaCandidatos *procuraCandidato_numero(ListaCandidatos *cabeca, int numero)
{
	while(cabeca != NULL)
	{
		if(cabeca->candidato.numero == numero)
			return cabeca;
		cabeca = cabeca->prox;	
	}
	
	return NULL;
}

ListaCandidatos *inserirCandidatosOrdenado_votos(ListaCandidatos *cabeca, Candidato candidato)
{
	ListaCandidatos *novo = criaCaixaCandidato(candidato);
	if(cabeca == NULL)
		cabeca = novo;
	else
	{
		ListaCandidatos *procura = procuraCandidato(cabeca, candidato);
		if(procura == NULL)
		{
			ListaCandidatos *no = cabeca;
			ListaCandidatos *ante = NULL;
			while(no != NULL && no->candidato.votos > novo->candidato.votos)
			{
				ante = no;
				no = no->prox;
			}
			
			if(ante == NULL)
			{
				novo->prox = no;
				cabeca = novo;
			}
			else
			{
				if(no != NULL)
				{
					novo->prox = no;
					ante->prox = novo;
				}
				else
				{
					ante->prox = novo;
				}
			}
		}
	}	
	
	return cabeca;
}


ListaCandidatos *inserirCandidatosOrdenado_numero(ListaCandidatos *cabeca, Candidato candidato)
{
	ListaCandidatos *novo = criaCaixaCandidato(candidato);
	if(cabeca == NULL)
		cabeca = novo;
	else
	{
		ListaCandidatos *procura = procuraCandidato(cabeca, candidato);
		if(procura == NULL)
		{
			ListaCandidatos *no = cabeca;
			ListaCandidatos *ante = NULL;
			while(no != NULL && no->candidato.numero > novo->candidato.numero)
			{
				ante = no;
				no = no->prox;
			}
			
			if(ante == NULL)
			{
				novo->prox = no;
				cabeca = novo;
			}
			else
			{
				if(no != NULL)
				{
					novo->prox = no;
					ante->prox = novo;
				}
				else
				{
					ante->prox = novo;
				}
			}
		}
		/*
		else
			printf("\nCANDIDATO JA CADASTRADO.");
			*/
	}	
	
	return cabeca;
}

ListaCandidatos *alteraDadosCandidato(ListaCandidatos *cabeca, ListaCandidatos *excluir, Candidato candidatoInserir)
{
	if(cabeca->candidato.numero == excluir->candidato.numero)
	{
		cabeca = cabeca->prox;
		delete(excluir);
	}
	else
	{
		ListaCandidatos *no = cabeca;
		ListaCandidatos *ante = cabeca;
		
		while(no->candidato.numero != excluir->candidato.numero && no != NULL)
		{
			ante = no;
			no = no->prox;
		}
		
		if(no->prox != NULL)
		{
			ante->prox = no->prox;
			delete(no);
		}
		else
		{
			delete(no);
			ante->prox = NULL;	
		}
	}
	
	inserirCandidatosOrdenado_numero(cabeca, candidatoInserir);	
}
