#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<conio2.h>

int getPalavra(char frase[1000])
{
	int palavras=0;
	
	for(int i=0 ; palavra[i] != '\0' ;i++)
	{
		if(palavra[i] == ' ' && palavra[i+1] != ' ' && palavra[i+2] != ' ')
		{
			palavras++;
			/*
			while(palavra[i] == ' ' && palavra[i+1] != ' ' && palavra[i+2] != ' ')
				i++;
				*/
		}
	}
	
	return palavras;	
}

int linhaQueTemPalavra(char fileName[100], char palavraKey[100])
{
	int linhaMaisPalavraKey=0;
	int qntMaior=0;
	
	FILE *arq = fopen(fileName, "r");
	if(arq != NULL)
	{
		int posLinha=1;
		char line[100];
		while(fgets(line, 100, arq) != NULL)
		{
			int qnt = contarPalavrasFrase(line);
			if(qnt > qntMaior)
			{
				qntMaior = qnt;
				linhaMaisPalavraKey = posLinha;
			}
		}
	}
}

int main(void)
{
	linhaQueTemPalavra("arquivo.txt\0", "galinha\0");
}
