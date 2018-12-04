#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
int ConheceNome(char NomeTxt[100])
{
	FILE *arq = fopen(NomeTxt,"r");
	if(arq == NULL)
	return 0;
	else
	{
		fclose(arq);
		return 1;
	}
}

void Transf(char NomeTxt[100], char NovoTxt[100])
{
	char palavra[100];
	int i;
	FILE *arq1 = fopen(NomeTxt,"r");
	FILE *arq2 = fopen(NovoTxt,"a");
	while(!feof(arq1))
	{
		fgets(palavra,100,arq1);
		for(i=0;i<strlen(palavra);i++)
			if(palavra[i] == ' ')
				palavra[i] = '\n';
		fputs(palavra,arq2);
	}
	fclose(arq1);
	fclose(arq2);
}

void Exibe(char Texto[100])
{
	char lido;
	FILE *Ptxt=fopen(Texto,"r");
	if(Ptxt == NULL)
		printf("\nErro!Arquivo não foi aberto!\n");
	else
	{
		lido = fgetc(Ptxt);
		while(!feof(Ptxt))
		{
			printf("%c",lido);
			lido = fgetc(Ptxt);
		}
		fclose(Ptxt);
	}
}

int main()
{
	char Atual[100],Novo[100];
	int cfr=0;
	printf("\nNome do arquivo:\n");
	scanf("%s",&Atual);
	cfr = ConheceNome(Atual);
	if(cfr == 1)
	{
		printf("\nNome do novo arquivo:\n");
		scanf("%s",&Novo);
		Transf(Atual,Novo);
		Exibe(Novo);
	}
	else
		printf("Arquivo nao existe");
}
//Usando fgec, implemente uma função que receba um arquivo CPP e retorne se as "{}" e os "()" estão consistentes
//Usando fgets, implemente uma função que receba um arquivo com um texto e retorne um outro arquivo com uma palavra em cada linha
