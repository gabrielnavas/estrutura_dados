#define MAXELEMPILHA 3

struct Pilha
{
	int topo;
	int pilha[MAXELEMPILHA];
};

void iniciar(Pilha &p)
{
	p.topo = -1;
}

char cheia(int topo)
{
	return topo == MAXELEMPILHA -1;
}

char vazia(int topo)
{
	return topo == -1;
}

void inserir(Pilha &p, char elemento)
{
	p.pilha[++p.topo]=elemento;
}

int remover(Pilha &p)
{
	return p.pilha[p.topo--];
}

int elemTopo(Pilha p)
{
	return p.pilha[p.topo];
}

void exibir(Pilha p)
{
	while(!vazia(p.topo))
		printf("%d", remover(p));
}
