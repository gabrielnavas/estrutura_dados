#define MAXPILHA 250

struct Posicao
{
	//X = LINHA;
	//Y = COLUNA;
	int x;
	int y;
	
	int visitada;
	int cont;
};

struct PilhaM2
{
	int topo[MAXPILHA];
	int base[MAXPILHA];
	Posicao pilha[MAXPILHA];
};

void iniciar(PilhaM2 &pm, int qntd)
{
	int qntPDiv = MAXPILHA/qntd;
	for(int i=0 ; i <= qntd ; i++)
	{
		pm.base[i] = qntPDiv*i;
		pm.topo[i] = qntPDiv*i-1;
	}
}

void inserir(PilhaM2 &pm, int np, Posicao pos)
{
	pm.pilha[++pm.topo[np]] = pos;
}

Posicao remover(PilhaM2 &pm, int np)
{
	return pm.pilha[pm.topo[np]--];
}

int cheia(PilhaM2 pm, int np)
{
	return pm.topo[np]+1 == pm.base[np+1];
}

int vazia(PilhaM2 pm, int np)
{
	return pm.topo[np] < pm.base[np];
}

Posicao elemTopo(PilhaM2 pm, int np)
{
	return pm.pilha[pm.topo[np]];
}

void exibir(PilhaM2 pm, int np)
{
	Posicao pos;
	while(!vazia(pm, np))
	{
		pos = remover(pm, np);
		printf("%d %d\n", pos.x, pos.y);
	}
}


