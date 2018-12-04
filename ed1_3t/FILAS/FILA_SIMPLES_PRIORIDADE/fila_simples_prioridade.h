#define MAXFILA 5

struct Elem
{
	char info;
	int priori;
};

struct Fila
{
	Elem fila[MAXFILA];
	int fim, cont;
};

void iniciar(Fila &f)
{
	f.fim = -1;
	f.cont=0;
}

void inserir(Fila &f, Elem e)
{
	f.fila[++f.fim] = e;
	f.cont++;
	
	for(int i= f.fim ; i > 0 && f.fila[i].priori< f.fila[i-1].priori ; i--)
	{
		Elem aux = f.fila[i];
		f.fila[i] = f.fila[i-1];
		f.fila[i-1] = aux;
	}
}

Elem retirar(Fila &f)
{
	Elem aux = f.fila[0];
	for(int i=0 ; i < f.fim ; i++)
		f.fila[i] = f.fila[i+1];
	f.cont--;
	f.fim--;
	return aux;	
}

Elem elemInicio(Fila f)
{
	return f.fila[0];
}

Elem elemFim(Fila f)
{
	return f.fila[f.fim];
}

int cheia(int cont)
{
	return cont == MAXFILA;
}

int vazia(int cont)
{
	return cont == 0;
}

void exibir(Fila f)
{
	Elem e;
	while(!vazia(f.cont))
	{
		e = retirar(f);
		printf("| %d - %c |", e.priori, e.info);
	}
}
