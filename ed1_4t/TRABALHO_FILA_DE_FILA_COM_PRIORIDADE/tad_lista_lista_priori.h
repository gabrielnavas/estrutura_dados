
/////// MUDE AQUI A VELOCIDADE DE EXECUCAO
#define VELOCIDADE_EXIBICAO 850
#define VELOCIDADE_MSGS 750
//////////////////////////////////////////

struct Elem
{
	int id;
	int tempoAtendimento;
	char priori; /* A-Z*/
	int tempoUt;
};

struct TpPont
{
	Elem elem;
	
	TpPont * ante;
	TpPont * baixo;
	TpPont * prox;
};

struct Descritor
{
	int cont;
	int totAtendidos;
	
	TpPont * inicio, * fim;
};


void iniciar(Descritor &d);
TpPont * criaCaixa(Elem elem);
void inserir(Descritor &d, Elem elem);
Elem remover(Descritor &d);
Elem elemInicio(Descritor d);
Elem elemFim(Descritor d);
int vazia(Descritor d);
void exibir(Descritor d);

void gravarFilaArquivo(FILE *arq, Descritor d);
void exibirGraficamente(Descritor d, int acao);


void iniciar(Descritor &d)
{
	d.cont = d.totAtendidos = 0;
	d.inicio = d.fim = NULL;
}

TpPont * criaCaixa(Elem elem)
{
	TpPont * novo = new TpPont;
	novo->elem = elem;
	novo->ante = novo->baixo = novo->prox = NULL;
	return novo;
}

void inserir(Descritor &d, Elem elem)
{
	TpPont * novo = criaCaixa(elem);
	
	if(d.cont == 0)
		d.inicio = d.fim = novo;
	else
	{
		//elemento no final
		novo->ante = d.fim;
		d.fim->prox = novo;
		d.fim = novo;
		
		exibirGraficamente(d, 1);
		
		//trocar os valores se o novo elemento for menor que o anterior
		TpPont * ante = d.fim->ante;
		while(ante != NULL && novo->elem.priori < ante->elem.priori)
		{
			//trocar a fila também, troco apenas a cabeca
			if(ante->baixo == NULL)
			{
				Elem eAux = novo->elem;
				novo->elem = ante->elem;
				ante->elem = eAux;
			}
			else
			{
				Elem eAux = novo->elem;
				novo->elem = ante->elem;
				ante->elem = eAux;
				
				novo->baixo = ante->baixo;
				ante->baixo = NULL;
			}
			
			//ando para tras
			novo = ante;
			ante = ante->ante;
			
			exibirGraficamente(d, 3); //colocr no final
			
		}
		
		//verifico se nesse andar eu parei dentro da fila e se o elemento anterior eh igual o novo
		if(ante != NULL && ante->elem.priori == novo->elem.priori)
		{
			//verifico se a lista do anterior tem alguem
			if(ante->baixo == NULL)
			{
				if(novo->prox == NULL)
					d.fim = ante;
						
				ante->baixo = novo;
				if(novo->prox != NULL)
				{
					novo->prox->ante = novo->ante;
				}
				novo->ante->prox = novo->prox;
				novo->ante = ante;
				novo->prox = NULL;	
			}
			else //caso exista
			{
				if(novo->prox == NULL)
					d.fim = ante;
				
				if(novo->prox != NULL)
					novo->prox->ante = novo->ante;
				novo->ante->prox = novo->prox;
				
				TpPont * aux = ante->baixo;
				while(aux->prox != NULL)
					aux = aux->prox;
					
				novo->prox = NULL;
				novo->ante = aux;
				aux->prox = novo;	
			}
		}
	}	
	
	exibirGraficamente(d, -1);
	d.cont++;
}

Elem remover(Descritor &d)
{
	Elem elem = d.inicio->elem; /* elemento a retornar */
	TpPont * del = d.inicio; /* ponteiro para deletar */
	
	//somente um elemento na lista
	if(d.cont == 1)
	{	
		d.inicio = d.fim = NULL;
		delete(del);
	}
	
	//mais de um elemento
	else
	{		
		//nenhum elemento no primeiro elemento, inicio aponta pro proximo
		if(d.inicio->baixo == NULL)
		{
			d.inicio = d.inicio->prox;
			if(d.inicio != NULL)
			{
				d.inicio->ante = NULL;
				if(d.inicio->prox == NULL)
					d.fim = d.inicio;
			}
		}
		//lista baixo tem elemento
		else
		{	
			//nao existe mais elementos na lista principal
			if(d.inicio->prox == NULL)
			{
				d.inicio = d.fim =  d.inicio->baixo;				
				d.inicio->baixo = d.inicio->prox;
				d.inicio->ante = NULL;
				d.inicio->prox = NULL;
			}
			
			//existe mais elementos na lista principal
			else
			{
				del->baixo->baixo = del->baixo->prox;
				del->baixo->prox = d.inicio->prox;
				d.inicio->prox->ante = del->baixo;
				del->baixo->ante = NULL;
				d.inicio = del->baixo;
			}	
		}
		delete(del);
	}
	
	d.cont--;	
	
	exibirGraficamente(d, 0);
	return elem;
}

Elem elemInicio(Descritor d)
{
	return d.inicio->elem;
}

Elem elemFim(Descritor d)
{
	if(d.fim->baixo == NULL)
		return d.fim->elem;
	
	TpPont * aux = d.fim->baixo;	
	while(aux->prox != NULL)	
		aux = aux->prox;
		
	return aux->elem;	
}

int vazia(Descritor d)
{
	return d.cont == 0;
}

void exibir(Descritor d)
{
	TpPont * aux = d.inicio;
	while(aux != NULL)
	{
		Elem e1 = aux->elem;
		printf("%d %d %c %d\n", e1.id, e1.tempoAtendimento, e1.priori, e1.tempoUt);
		TpPont * aux2 = aux->baixo;
		while(aux2 != NULL)
		{
			Elem e2 = aux2->elem;
			printf("%d %d %c %d\n", e2.id, e2.tempoAtendimento, e2.priori, e2.tempoUt);
			aux2 = aux2->prox;
		}
		aux = aux->prox;
	}
}

void gravarFilaArquivo(FILE *arq, Descritor d)
{
	TpPont * l1 = d.inicio;
	while(l1 != NULL)
	{
		fprintf(arq, "%d %d %c %d\n", 
			l1->elem.id, l1->elem.tempoAtendimento, l1->elem.priori, l1->elem.tempoUt);
		
		TpPont *l2 = l1->baixo;
		while(l2 != NULL)
		{
			fprintf(arq, "%d %d %c %d\n", 
				l2->elem.id, l2->elem.tempoAtendimento, l2->elem.priori, l2->elem.tempoUt);
			
			l2 = l2->prox;	
		}
		
		l1 = l1->prox;
	}
}

//ESTA FUNCAO QUE EXIBE AS INFO NA TELA
void exibirGraficamente(Descritor d, int acao)
{
	system("cls");
	
	if(d.cont == 0)
	{
		gotoxy(5, 1); textcolor(LIGHTCYAN);
		printf("FILA VAZIA.");
		Sleep(VELOCIDADE_EXIBICAO+VELOCIDADE_MSGS);
	}
	else
	{	
		Elem e1, e2;
		int x=2,y=1;
		TpPont * l1 = d.inicio, *l2;
		while(l1 != NULL)
		{
			textcolor(LIGHTRED); gotoxy(y,x);
			e1 = l1->elem;
			
			textcolor(LIGHTBLUE);
			printf("|");
			textcolor(GREEN);
			printf("%2d %c",e1.id , e1.priori);
			textcolor(LIGHTBLUE);
			printf("|");
			
			l2 = l1->baixo;
			while(l2 != NULL)
			{
				x += 2;
				textcolor(GREEN); gotoxy(y, x);
				e2 = l2->elem;
				
				textcolor(LIGHTBLUE);
				printf("|");
				textcolor(GREEN);
				printf("%2d %c",e2.id , e2.priori);
				textcolor(LIGHTBLUE);
				printf("|");
				
				l2 = l2->prox;
			}
			
			gotoxy(y, x+2);
			
			textcolor(LIGHTBLUE);
			printf("|");
			textcolor(YELLOW);
			printf("NULL ");
			textcolor(LIGHTBLUE);
			printf("|");
			
			x=2;
			y += 8;
			l1 = l1->prox;
		}
		
		gotoxy(y, x);
		textcolor(LIGHTBLUE);
		printf("|");
		textcolor(YELLOW);
		printf("NULL ");
		textcolor(LIGHTBLUE);
		printf("|");
	}
	
	if(acao != -1) 
		Sleep(VELOCIDADE_EXIBICAO+200);
		
	if(acao == 1)
	{
		textcolor(GREEN);
		gotoxy(5, 1);
		printf("INSERIU NO FINAL");
		Sleep(VELOCIDADE_EXIBICAO+VELOCIDADE_MSGS);
	}
	else if(acao == 0)
	{
		textcolor(LIGHTRED);
		gotoxy(5, 1);
		printf("REMOVEU NO INICIO");
		Sleep(VELOCIDADE_EXIBICAO+VELOCIDADE_MSGS);
	}
	else if(acao == 3)
	{
		textcolor(LIGHTBLUE);
		gotoxy(5, 1);
		printf("POSICIONANDO");
		Sleep(VELOCIDADE_EXIBICAO+VELOCIDADE_MSGS);
	}	
}
