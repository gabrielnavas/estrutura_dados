#define MAXFILA 10000

struct Fila
{
	char fila[MAXFILA];
	int inicio, fim, cont;
};

void iniciar(Fila &f)
{
	f.inicio=0;
	f.fim = -1;
	f.cont=0;
}

void inserir(Fila &f, char elem)
{
	if(f.fim == MAXFILA -1)
		f.fim = -1;
	f.fila[++f.fim] = elem;
	f.cont++;	
}

char retirar(Fila &f)
{
	char elemSair = f.fila[f.inicio];
	if(f.inicio == MAXFILA -1)
		f.inicio = -1;
	f.inicio++;
	f.cont--;
	return elemSair;	
}

int cheio(int cont)
{
	return cont == MAXFILA;
}

int vazia(int cont)
{
	return cont == 0;
}

char elemInicio(Fila f)
{
	return f.fila[f.inicio];
}

char elemFim(Fila f)
{
	return f.fila[f.inicio];
}

void exibir(Fila f)
{
	while(!vazia(f.cont))
		printf("[%c]", retirar(f));
}
