struct pilhaGen
{
	ListaGen * info;
	struct pilhaGen * prox;	
};

typedef struct pilhaGen Pilha;

void init(Pilha ** p)
{
	*p=NULL;
}

void push(Pilha **p, ListaGen * info)
{
	Pilha * novo = (Pilha*) malloc(sizeof(Pilha));
	novo->info = info;
	novo->prox = *p;
	*p = novo;
}

void pop(Pilha **p, ListaGen ** info)
{
	Pilha * aux = *p;
	*p = (*p)->prox;
	*info = aux->info;
	free(aux);
}

ListaGen * top(Pilha *p)
{
	return p->info;
}

char isEmpty(Pilha *p)
{
	return p == NULL;
}
