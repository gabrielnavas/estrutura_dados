#define MAXFILA 10000

struct Fila
{
	char fila[MAXFILA];
	int fim;
};

void iniciar(Fila &f)
{
	f.fim = -1;
}

void inserir(Fila &f, char elem)
{
	f.fila[++f.fim] = elem;
}

char retirar(Fila &f)
{
	char elemSair = f.fila[0];
	for(int i=0 ; i < f.fim ; i++)
		f.fila[i] = f.fila[i+1];
	f.fim--;
	return elemSair;	
}

char elemFim(Fila f)
{
	return f.fila[f.fim];
}

int cheia(int fim)
{
	return fim == MAXFILA-1;
}

int vazia(int fim)
{
	return fim == -1;
}

void exibir(Fila f)
{
	while(!vazia(f.fim))
		printf("[%c]", retirar(f));
}


