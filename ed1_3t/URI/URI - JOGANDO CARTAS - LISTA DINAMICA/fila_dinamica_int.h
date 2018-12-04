#define MAXFILA 100000

struct Fila
{
	int inicio, fim, cont;
	int fila[MAXFILA];
};


void iniciar(Fila &f)
{
	f.inicio =0;
	f.fim = -1;
	f.cont = 0;
}

void inserir(Fila &f, int elem)
{
	f.fila[++f.fim] = elem;
	f.cont++;
}

int retirar(Fila &f)
{
	int elem = f.fila[f.inicio++];
	f.cont--;
	return elem;
}

int cheia(int cont)
{
	return cont == MAXFILA;
}

int vazia(int cont)
{
	return cont == 0;
}

int elemInicio(Fila f)
{
	return f.fila[f.inicio];
}

int elemFim(Fila f)
{
	return f.fila[f.fim];
}

void exibir(Fila f)
{
	while(!vazia(f.cont))
		printf("[%d]", retirar(f));
}
