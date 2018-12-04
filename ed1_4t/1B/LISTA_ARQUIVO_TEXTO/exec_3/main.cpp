#include<stdio.h>
#include<string.h>
#include<conio2.h>

int verificarIgualdadeArquivos(char fileName1[100], char fileName2[100])
{
	int igual=1;
	
	FILE *arq1 = fopen(fileName1, "r");
	FILE *arq2 = fopen(fileName2, "r");
	
	if(arq1 != NULL && arq2 != NULL)
	{
		char chArq1 = fgetc(arq1);
		char chArq2 = fgetc(arq2);
		while(!feof(arq1) && !feof(arq2) && igual == 1)
		{
			if(chArq1 != chArq2)
				igual=0;
				
			chArq1 = fgetc(arq1);
			chArq2 = fgetc(arq2);
		}
		
		fclose(arq1);
		fclose(arq2);
		
		return igual;
	}
	
	return -1;
}

int main(void)
{
	int igual = verificarIgualdadeArquivos("arquivo1.txt\0", "arquivo2.txt\0");
	if(igual == -1)
		printf("UM DOS ARQUIVOS NAO EXISTE");
	else if(igual)
		printf("OS ARQUIVOS SAO IGUALS");
	else
		printf("OS ARQUIVOS SAO DIFERENTES");
		
	getch();			
}
