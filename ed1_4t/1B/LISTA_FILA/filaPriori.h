#include <stdio.h>

#define MAXFILA 1000

struct Elem
{
	int dado;
	int priori;
};

struct Fila
{
	int fim;
	Elem fila[MAXFILA];
};

void iniciar(Fila &f)
{
	f.fim=-1;
}

void inserir(Fila &f, Elem e)
{
	f.fila[++f.fim] = e;
	for(int i=f.fim ; i > 0 && f.fila[i].priori < f.fila[i-1].priori ; i--)
	{
		Elem aux = f.fila[i];
		f.fila[i-1] = f.fila[i];
		f.fila[i] = aux;
	}
}

Elem remover(Fila &f)
{
	Elem e = f.fila[0];
	for(int i=0 ; i < f.fim ; i++)
		f.fila[i] = f.fila[i+1];
	f.fim--;
	return e;	
}

Elem elemTopo(Fila f)
{
	return f.fila[0];
}

Elem elemFim(Fila f)
{
	return f.fila[f.fim];
}

char cheia(int fim)
{
	return fim == MAXFILA-1;
}

char vazia(int fim)
{
	return fim == -1;
}

void exibir(Fila f)
{
	while(!vazia(f.fim))
		printf("%d", remover(f));
}
