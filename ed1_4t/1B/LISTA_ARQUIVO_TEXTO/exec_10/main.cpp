#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<conio2.h>


int escreverContagemNome(char nome[100], char fileName[1000], int maxCont)
{
	FILE *arq = fopen(fileName, "w");
	
	if(arq != NULL)
	{
		for(int i=1 ; i <= maxCont ; i++)
			fprintf(arq ,"%d\n", i);
		
		fputs(nome, arq);
		f
		fclose(arq);	
	}
}

int exibir(char fileName[100])
{
	FILE *arq = fopen(fileName, "r");
	
	if(arq != NULL)
	{
		char line[100];
		while(!feof(arq))
		
		fclose(arq);	
	}
}

int main(void)
{
	
}
