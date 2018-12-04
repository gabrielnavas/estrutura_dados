#include<stdio.h>


struct Fila
{
	char dado;
	Fila * prox;
};

Fila * iniciar(Fila *f)
{
	f = NULL;
	return f;
}

Fila * inserir(Fila *f, char dado)
{
	Fila * novo = new Fila;
	novo->dado = dado;
	novo->prox = NULL;
	
	if(f == NULL)
		f = novo;
	else
	{
		Fila * aux = f;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;	
	}	
	
	return f;
}

Fila * remover(Fila *f, char &ch)
{
	ch = f->dado;
	Fila * del = f;
	f = f->prox;
	delete(del);
	return f;
}

char vazia(Fila *f)
{
	return f == NULL;
}

char elemInicio(Fila *f)
{
	return f->dado;
}

char elemFim(Fila *f)
{
	Fila *aux = f;
	while(aux->prox != NULL)
		aux = aux->prox;
	return aux->dado;	
}

void exibir(Fila *f)
{
	if(!vazia(f))
	{
		printf("%c", f->dado);
		exibir(f->prox);
	}
}

int main(void)
{
	Fila *f = iniciar(f);
	
	f=inserir(f, 'a');
	f=inserir(f, 'b');
	f=inserir(f, 'c');
	f=inserir(f, 'd');
	f=inserir(f, 'e');
	
//	exibir(f);		
	
	char ch;
	while(!vazia(f))
	{
	
	f=remover(f, ch);
	printf("%c", ch);
	}
}
