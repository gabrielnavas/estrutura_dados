struct pilha_int
{
	int info;
	struct pilha_int * prox;	
};

typedef struct pilha_int PilhaInt;

void init_int(PilhaInt ** p)
{
	*p = NULL;
}

void push_int(PilhaInt **p, int info)
{
	PilhaInt * novo = (PilhaInt*) malloc(sizeof(PilhaInt));
	novo->info = info;
	novo->prox = *p;
	*p = novo;
}

void pop_int(PilhaInt **p, int *info)
{
	PilhaInt * aux = *p;
	*p = (*p)->prox;
	*info = aux->info;
	free(aux);
}

int top_int(PilhaInt *p)
{
	return p->info;
}

char isEmpty_int(PilhaInt *p)
{
	return p == NULL;
}
