#include<stdio.h>
#include<string.h>
#include<conio2.h>
#include<ctype.h>

int novoArquivoComFirstLetrasPalavras(char fileName1[100], char fileName2[100])
{
	char line[100];
	
	FILE *arq1 = fopen(fileName1, "r");
	FILE *arq2 = fopen(fileName2, "w");
	
	if(arq1 != NULL && arq2 != NULL)
	{
		char line[100];
		while(fgets(line, 100, arq1) != NULL)
		{	
			fputc(toupper(line[0]), arq2);
			for(int i=1 ; line[i] != '\0' ; i++)
				if(line[i] == ' ')
				{
					i++;
					while(line[i] == ' ')
						i++;
							
					if(line[i] != '\0')	
						fputc(toupper(line[i]), arq2);	
				}
		}
		
		fclose(arq1);
		fclose(arq2);
		
		return 1;
	}
	
	return -1;
}

void exibirArquivo(char fileName[100])
{
	FILE *arq = fopen(fileName, "r");
	if(arq != NULL)
	{
		char line[100];
		while(fgets(line, 100, arq) != NULL)
		{
			for(int i=0 ; line[i] != '\0' ; i++)
				printf("%c", line[i]);
			printf("\n");
		}
		
		fclose(arq);	
	}
}

int main(void)
{
	int deuCerto = novoArquivoComFirstLetrasPalavras("arquivo1.txt\0", "arquivo2.txt\0");
	if(deuCerto == -1)
		printf("UM DOS ARQUIVOS NAO EXISTE");
	else if(deuCerto)
	{
		printf("\nARQUIVO 1: \n\n");
		exibirArquivo("arquivo1.txt\0");
			
		printf("\nARQUIVO 1: \n\n");
		exibirArquivo("arquivo2.txt\0");
	}
	
	getch();			
}
