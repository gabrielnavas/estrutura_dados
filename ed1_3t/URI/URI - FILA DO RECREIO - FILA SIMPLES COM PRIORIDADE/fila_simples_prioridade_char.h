#define MAXFILA 20

struct Elem
{
	char info;
	int priori;
	int flag;
};

struct Fila
{
	int fim, cont;
	Elem fila[MAXFILA];
};

void iniciar(Fila &f)
{
	f.fim=-1;
	f.cont=0;
}

void inserir(Fila &f, Elem e)
{
	f.fila[++f.fim] = e;
	f.cont++;
	
	for(int i=f.fim ; i > 0 && f.fila[i].priori > f.fila[i-1].priori ; i--)
	{
		f.fila[i].flag=1;
		f.fila[i-1].flag=1;
		
		Elem aux = f.fila[i];
		f.fila[i] = f.fila[i-1];
		f.fila[i-1] = aux;
	}
}

Elem retirar(Fila &f)
{
	Elem e = f.fila[0];
	f.cont--;
	
	for(int i=0 ; i < f.fim ; i++)
			f.fila[i] = f.fila[i+1];
	
	return e;	
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
		printf("%c %d %d\n", e.info, e.priori, e.flag);				 
	}
 		
}
