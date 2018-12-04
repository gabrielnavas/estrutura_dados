#define MAXFILA 1000

struct Elem
{
	char info;
	char priori;
};

struct Fila
{
	int inicio, fim, cont;
	Elem fila[MAXFILA];
};

void iniciar(Fila &f)
{
	f.inicio = 0;
	f.fim = -1;
	f.cont=0;
}

void inserir(Fila &f, Elem e)
{
	if(f.fim == MAXFILA -1)
		f.fim = -1;
	f.fila[++f.fim] = e;
	f.cont++;
	
	int flag=0;
	for(int i=f.fim ; i != f.inicio && flag != 1 ; i--)
	{
		if(i != 0 && f.fila[i].priori < f.fila[i-1].priori)
		{
			Elem aux = f.fila[i];
			f.fila[i] = f.fila[i-1];
			f.fila[i-1] = aux;
		}
		else if(i == 0 && f.fila[0].priori < f.fila[MAXFILA-1].priori)
		{
			Elem aux = f.fila[0];
			f.fila[0] = f.fila[MAXFILA-1];
			f.fila[MAXFILA-1] = aux;
		}
		else
			flag=1;
	}	
}

Elem retirar(Fila &f)
{
	Elem aux  = f.fila[f.inicio];
	if(f.inicio == MAXFILA -1)
		f.inicio=-1;
	f.inicio++;
	f.cont--;
	return aux;	
}

int cheia(int cont)
{
	return cont == MAXFILA;
}

int vazia(int cont)
{
	return cont == 0;
}

Elem elemInicio(Fila f)
{
	return f.fila[f.inicio];
}

Elem elemFim(Fila f)
{
	return f.fila[f.fim];
}

void exibir(Fila f)
{
	Elem e;
	while(!vazia(f.cont))
	{
		e = retirar(f);
		printf("| %d %c |", e.priori, e.info);
	}
		
}
