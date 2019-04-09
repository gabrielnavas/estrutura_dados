#include<stdio.h>
#include<stdlib.h>
#include<string.h>



struct reg_lista
{
    struct listagen * cabeca;
    struct listagen * cauda;
};

struct info_lista
{
    char info[8];
    struct reg_lista  lista;
};

struct listagen
{
    char terminal;
    struct info_lista no;
};

typedef struct listagen ListaGen;

#include "pilha_lista_gen.h"

#include "pilha_int.h"

char nulo(ListaGen * l)
{
    return l == NULL;
}


char atomo(ListaGen * l)
{
    return !nulo(l) && l->terminal;
}

ListaGen * criat(char *info)
{
    ListaGen * novo;
    novo = (ListaGen*) malloc(sizeof(ListaGen));
    novo->terminal = 1;
    strcpy(novo->no.info, info);
    return novo;
}

ListaGen * cons(ListaGen * h, ListaGen * t)
{
    ListaGen * novo;
    if(atomo(t))
    {
		printf("cauda nao pode ser atomo");
		return NULL;
    }
    else
    {
		novo = (ListaGen*) malloc(sizeof(ListaGen));
		novo->terminal = 0;
		novo->no.lista.cabeca = h;
		novo->no.lista.cauda = t;
		return novo;
    }
}

ListaGen * head(ListaGen *l)
{
    if(nulo(l) || atomo(l))
    {
		printf("lista nao pode ser nula nem atomo para retornar a cabeca");
		return NULL;
    }
    else
		return l->no.lista.cabeca;
}

ListaGen * tail(ListaGen * l)
{
    if(nulo(l) || atomo(l))
    {
		printf("lista nao pode ser nula nem atomo para retornar a cabeca");
		return NULL;
    }
    else 
		return l->no.lista.cauda;
}

void exibir(ListaGen * l)
{
    if(!nulo(l))
    {
		if(atomo(l))
		    printf("%s", l->no.info);
		else
		{
		    printf("[");
		    while(!nulo(l))
		    {
				exibir(head(l));
				l = tail(l);
				if(!nulo(l))
					printf(", ");
				else
					printf(", NULL");	
		    }
		    printf("]");
		}
    }
}

void exibir_atomos(ListaGen * l)
{
	Pilha *p;
	ListaGen * laux;
	init(&p);
	
	laux = head(l);
	while(!nulo(l))
	{
		while(!nulo(laux) && !atomo(laux))
		{
			push(&p, laux);
			laux = head(laux);
		}
		
		if(!nulo(laux) && atomo(laux))
		{
			printf("%s", laux->no.info);
			pop(&p, &laux);
		}
			
			
		pop(&p, &laux);
		while(!isEmpty(p) && nulo(tail(laux)))
			pop(&p, &laux);
			
		if(!nulo(tail(laux)))
		{
			laux = tail(laux);
//			laux = head(laux);
		}	
		else if(!nulo(tail(l)))
		{
			l = tail(l);
			laux = head(l);
		}
	}
}

void kill_ite(ListaGen ** l)
{
	Pilha *p;
	ListaGen * aux;
	
	init(&p);
	
	push(&p, *l);
	while(!isEmpty(p))
	{
		if(!nulo(*l))
		{
			pop(&p, &*l);
			while(!nulo(*l) && !atomo(*l))
			{
				push(&p, *l);
				*l = head(*l);
			}
			
			if(atomo(*l))
				free(*l);
		}
		
		pop(&p, &*l);
		aux = *l;
		*l=tail(*l);
		free(aux);
		if(!nulo(*l))
			push(&p, *l);
	}
	*l = NULL;
}

void append(ListaGen ** l1, ListaGen * l2)
{
	ListaGen * aux;
	
	if(nulo(*l1))
		*l1 = l2;
	else
	{
		aux = *l1;
		while(!nulo(tail(aux)))
			aux = tail(aux);
		aux->no.lista.cauda = l2;	
	}	
}

void planificar(ListaGen * l, ListaGen ** l2)
{
	if(!nulo(l))
	{
		if(atomo(l))
			append(&*l2, cons(criat(l->no.info), NULL));
		else
		{
			planificar(head(l), &*l2);
			planificar(tail(l), &*l2);
		}	
	}
}

ListaGen * top_level(ListaGen * l)
{
	ListaGen *ln = NULL;
	ListaGen * aux;
	
	while(!nulo(l))
	{
		if(atomo(head(l)))
			append(&ln, cons(criat(l->no.lista.cabeca->no.info), NULL));
		else
		{
			aux = head(l);
			while(!nulo(aux))
			{
				append(&ln, cons(NULL, NULL));
				aux = tail(aux);
			}
		}	
		
		l = tail(l);
	}
	
	return ln;
}

ListaGen * nth(ListaGen * l)
{
	ListaGen *ln = NULL;
	ListaGen * aux;
	int cont=0;
	
	while(!nulo(l))
	{
		if(atomo(head(l)))
			append(&ln, cons(criat(l->no.lista.cabeca->no.info), NULL));
		else
		{
			aux = head(l);
			while(!nulo(aux))
			{
				append(&ln, cons(NULL, NULL));
				aux = tail(aux);
			}
		}	
		
		l = tail(l);
	}
	
	return ln;
}

int deph(ListaGen * l)
{
	Pilha *p;
	PilhaInt *p_cout;
	init(&p);
	init_int(&p_cout);

	int cont=0;
	int n=0;
	
	push(&p, l);
	push_int(&p_cout, cont);
	while(!isEmpty(p))
	{
		if(!nulo(l))
		{
			pop(&p, &l);
			pop_int(&p_cout, &cont);
			while(!nulo(l) && !atomo(l))
			{
				if(cont > n)
					n= cont;
				
				if(nulo(head(l)))
					cont++;
					
				push(&p, l);
				push_int(&p_cout, cont);
				
				l = head(l);
				if(!nulo(l) && !atomo(l))
					cont++;
			}
		}
	
		pop(&p, &l);
		pop_int(&p_cout, &cont);
		l = tail(l);
		if(!nulo(l))
		{
			push(&p, l);
			push_int(&p_cout, cont);
		}			
	}
	return n;
}

void inserir_nivel_especifico(ListaGen ** l, char *info, int nivel)
{
	int cont, n;
	Pilha *p;
	PilhaInt *p_cont;
	ListaGen * l_aux, *aux;
	
	init(&p); 
	init_int(&p_cont);
	
	if(nivel == 0)
	{
		if(nulo(*l))
			*l = cons(criat(info), NULL);
		else
		{
			l_aux = *l;
			while(!nulo(tail(l_aux)))
				l_aux = tail(l_aux);
			l_aux->no.lista.cauda = cons(criat(info), NULL);	
		}		
	}
	else
	{
		l_aux = *l;
		cont = 0;
		
		push(&p, l_aux);
		push_int(&p_cont, cont);
		while(!isEmpty(p))
		{
			if(!nulo(l_aux))
			{
				pop(&p, &l_aux);
				pop_int(&p_cont, &cont);
				while(!nulo(l_aux) && !atomo(l_aux) && cont < nivel)
				{
					push(&p, l_aux);
					push_int(&p_cont, cont);
					
					l_aux = head(l_aux);
					cont++;
				}
				
				if(!nulo(l_aux) && !atomo(l_aux) && cont == nivel)
				{
					aux = l_aux;
					while(!nulo(tail(aux)))
						aux = tail(aux);
					aux->no.lista.cauda = cons(criat(info), NULL);	
						
					pop(&p, &l_aux);
					pop_int(&p_cont, &cont);
					
					l_aux = tail(l_aux);
					
					push(&p, l_aux);
					push_int(&p_cont, cont);
				}	
			}
			
			if(nulo(l_aux) || atomo(l_aux))
			{
				pop(&p, &l_aux);
				pop_int(&p_cont, &cont);
			}
			
			while(!isEmpty(p) && nulo(l_aux))
			{
				pop(&p, &l_aux);
				pop_int(&p_cont, &cont);
			}
			
			if(!nulo(l_aux))
				l_aux = tail(l_aux);
			
			while(!nulo(l_aux) && nulo(head(l_aux)))
				l_aux = tail(l_aux);
			
			if(!nulo(l_aux))
			{
				push(&p, l_aux);
				push_int(&p_cont, cont);
			}
		}	
	}
}

void inserir_nivel_ite(ListaGen ** lista, int nivel, char info[])
{
	ListaGen * aux, *l;
	Pilha * p;
	int flag_insercao,
		cont;
	
	init(&p);
	flag_insercao=0;
	cont = 1;
	if(nulo(*lista))
		*lista = cons(criat(info), NULL);
	else
	{
		l = *lista;
		push(&p, l);
		while(!isEmpty(p))
		{
			if(!nulo(l))
			{
				pop(&p, &l);
				while(!nulo(l) && !atomo(l) && cont < nivel)
				{
					push(&p, l);
					l = head(l);
					cont++;
				}
				
				if(!nulo(l) && !atomo(l) && cont == nivel)
				{
					if(nulo(head(l)))
						l->no.lista.cabeca = cons(criat(info), NULL);
					else
					{
						aux = head(l);
						while(!nulo(tail(aux)))
							aux = tail(aux);
						aux->no.lista.cauda = cons(criat(info), NULL);
				 	}
					
					flag_insercao = 1;	
				}
			}
			
			cont--;
			pop(&p, &l);
			l = tail(l);
			if(!nulo(l))
				push(&p, l);
		}
		
	}	
	if(!flag_insercao)
	{
		l = *lista;
		while(!nulo(tail(l)))
			l = tail(l);
		cont=1;
		(l)->no.lista.cauda = 	cons(NULL, NULL);
		while(cont < nivel)
		{
			l = head(l);
			l->no.lista.cabeca = 	cons(NULL, NULL);
			cont++;
		}
		
		l->no.lista.cabeca = cons(criat(info), NULL);
	}
}

int main()
{
    ListaGen * l;
	l = cons(cons(criat("A"), NULL), cons(NULL, cons(cons(NULL, cons(cons(criat("A"), cons(NULL, NULL)), NULL)), NULL)));
	
	exibir(l);
	
	printf("\n\n");
	inserir_nivel_ite(&l, 2, "GUSTAVO");
	
	exibir(l);
}
