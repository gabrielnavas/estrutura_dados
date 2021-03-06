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
    else
    	printf("NULL");
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

void ordenar_nivel(ListaGen * l, int nivel, int cont)
{
	ListaGen * ante, *aux;
	char info[8];
	
	if(!nulo(l) && !atomo(l))
	{
		if(cont == nivel)
		{
			ante = l;
			while(!nulo(ante))
			{
				aux = tail(ante);
				while(!nulo(aux))
				{
					if( !nulo(head(ante)) && atomo(head(ante)) && !nulo(head(aux)) && atomo(head(aux)))
						if(strcmp(ante->no.lista.cabeca->no.info, aux->no.lista.cabeca->no.info) > 0)
						{
							strcpy(info, ante->no.lista.cabeca->no.info);
							strcpy(ante->no.lista.cabeca->no.info, aux->no.lista.cabeca->no.info);
							strcpy(aux->no.lista.cabeca->no.info, info);
						}
						
					aux = tail(aux);	
				}
				
				//if(!nulo(ante) && !nulo(tail(ante)))
				ante = tail(ante);
			}
		}
		else
		{
			ordenar_nivel(head(l), nivel, cont+1);
			ordenar_nivel(tail(l), nivel, cont);
		}
	}
}

void excluir(ListaGen ** l, int nivel)
{
	ListaGen *aux, *ante, * aux2;
	int cont;
	Pilha * p;
	
	init(&p);
	
	if(nivel == 1)
	{
		while(!nulo(head(*l)) && atomo(head(*l)))
		{
			aux = *l;
			*l = tail(*l);
			free(aux->no.lista.cabeca);
			free(aux);
		}
		
		if(!nulo(*l))
		{
			ante = *l;
			aux = tail(ante);
		}
		else
			aux = NULL;
		while(!nulo(aux))
		{
			if(!nulo(head(aux)) && atomo(head(aux)))
			{
				ante->no.lista.cauda = aux->no.lista.cauda;
				free(aux->no.lista.cabeca);
				free(aux);
				aux = ante->no.lista.cauda;
			}
			else
			{
				ante = aux;
				aux = tail(aux);
			}
		}	
	}
	else
	{
		cont = 1;
		aux = *l;
		push(&p, aux);
		while(!isEmpty(p))
		{
			if(!nulo(aux))
			{
				pop(&p, &aux);
				while(!nulo(aux) && !atomo(aux) && cont < nivel)
				{
					push(&p, aux);
					aux = head(aux);
					cont++;
				}
				
				if(!nulo(aux) && !atomo(aux) && cont == nivel)
				{
					pop(&p , &aux2);
					while(!nulo(aux) && !nulo(head(aux)) && atomo(head(aux)))
					{
						aux2->no.lista.cabeca = tail(aux);
						free(aux->no.lista.cabeca);
						free(aux);
						aux = head(aux2);
					}
					if(!nulo(head(aux2)))
					{
						ante = head(aux2);
						aux = tail(ante);
					}
					else
						aux = NULL;
					push(&p, aux2);
					while(!nulo(aux))
					{
						if(!nulo(head(aux)) && atomo(head(aux)))
						{
							ante->no.lista.cauda = tail(aux);
							free(aux->no.lista.cabeca);
							free(aux);
							aux = tail(ante);
						}
						else
						{
							ante = aux;
							aux = tail(aux);
						}
					}	
				}
			}
			cont--;
			pop(&p, &aux);
			aux = tail(aux);
			if(!nulo(aux))
				push(&p, aux);
			
		}
	}
	
}

int main()
{
    ListaGen * l;
    l = cons(cons(cons(criat("A"), cons(criat("B"), NULL)),NULL), cons(cons(cons(criat("C"), NULL), NULL),NULL));
    excluir(&l, 3);
	exibir(l);
}
