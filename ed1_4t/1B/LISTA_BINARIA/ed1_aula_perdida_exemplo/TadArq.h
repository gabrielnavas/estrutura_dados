struct TpProduto{
	char nome[40];
	int qtde,codigo;
	float preco;
};

//void CadPrdo(char NomeArq[100]); OK
//int BuscaProd(FILE *PtrArq,int CodProd); OK
//void RelatProd(char NomeArq[100]); OK
//void Juncao(char NomeArq1[100],Juncao(char NomeArq1[100]); FALTA

void CadPrdo(char NomeArq[100]){
	TpProduto Prod;
	int x;
	printf("Digite o codigo,0 para sair: \n");
	scanf("%d",&Prod.codigo);
	while(Prod.codigo!=0)
	{
	printf("Digite o nome do produto: \n");
	fflush(stdin);
	gets(Prod.nome);
	printf("Digite a quantidade: \n");
	scanf("%d",&Prod.qtde);
	printf("Digite o preco: \n");
	scanf("%f",&Prod.preco);	
	x=validacao(Prod);
	if(x==0)
	printf("Cadastro Feito com Sucesso\n");
	else
	printf("Cadastro nao completado");
	printf("Digite o codigo,0 para sair: \n");
	scanf("%d",&Prod.codigo);	
	}
	
	
}
int validacao(TpProduto Prodkey){
	FILE *PtrArq;
	Ponteiro=fopen("Produtos1.txt","r+");
	rewind(Ponteiro);
	TpProduto Prod;
	int x=0;
	fread(&Prod,sizeof(Prod),1,PtrArq);
	while(!feof(PtrArq) && x!=1)
	{
		if(Prod.codigo==Prodkey.codigo)
		x=1;
		else
		fread(&Prod,sizeof(Prod),1,PtrArq);
	}
	if(x==0)
	{
	fwrite(&Prodkey,sizeof(Prodkey),1,PtrArq);
	fclose(PtrArq);
	return 0;
	}
	else
	{
	return 1;
	fclose(PtrArq);
	}
}

void RelatProd()
{
	FILE *PtrArq;
	Ponteiro=fopen("Produtos1.txt","r+");
	rewind(Ponteiro);
	TpProduto Prod;
	fread(&Prod,sizeof(Prod),1,PtrArq);
	while(!feof(PtrArq))
	{
		printf("Codigo: %d \n",Prod.codigo);
		printf("Nome: %s \n",Prod.nome);
		printf("Quantidade: %d \n",Prod.qtde);
		printf("Preco: %.2f \n",Prod.preco);
		fread(&Prod,sizeof(Prod),1,PtrArq);
	}
	fclose(PtrArq);
}

void BuscaProduto()
{
	FILE *PtrArq
	TpProduto Prod;
	char aux[40];
	int x=0;
	Ponteiro=fopen("Produtos1.txt","r+");
	rewind(Ponteiro);
	printf("Digite o nome do produto que voce busca,exit para sair: \n");
	fflush(stdin);
	gets(aux);
	while(strcmp(aux,"exit")==0)
	{
		fread(&Prod,sizeof(Prod),1,PtrArq);
		while(!feof(PtrArq))
		{
			if(strcmp(Prod.nome,aux)==0)	
			{
			x=1;
			}
			else
			{	
			fread(&Prod,sizeof(Prod),1,PtrArq);	
			}
		}
		if(x==1)
		printf("Produto encontrado com sucesso\n");
		else
		printf("Produto não encontrado");
		x=0;
		rewind(Ponteiro);
		printf("Digite o nome do produto que voce busca,exit para sair: \n");
		fflush(stdin);
		gets(aux);	
	}

	fclose(PtrArq);
}


