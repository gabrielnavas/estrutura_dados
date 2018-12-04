#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio2.h>


int transfereMasc_fputc(char file1[100], char file2[100])
{
	FILE *arq1 = fopen(file1, "r");
	FILE *arq2 = fopen(file2, "w");
	
	if(arq1 != NULL && arq2 != NULL)
	{
		char chr = toupper(fgetc(arq1));
		while(!feof(arq1))
		{
			fputc(chr, arq2);
			chr = toupper(fgetc(arq1));
		}
		
		fclose(arq1);
		fclose(arq2);
		
		return 1;
	}	
	
	return 0;
}

int transfereMasc_fputs(char file1[100], char file2[100])
{
	FILE *arq1 = fopen(file1, "r");
	FILE *arq2 = fopen(file2, "w");
	
	if(arq1 != NULL && arq2 != NULL)
	{
		char str[100];
		while(fgets(str, 100, arq1) != NULL)
		{
			int i;
			for(i=0 ; str[i] != '\0' ; i++)
				str[i] = toupper(str[i]);
			str[i] = '\0';
			
			fputs(str, arq2);
		}
		
		fclose(arq1);
		fclose(arq2);
		
		return 1;
	}	
	
	return 0;
}

int exibe_fputs(char file[100])
{
	FILE *arq = fopen(file, "r");
	
	if(arq != NULL)
	{
		char str[100];
		
		while(fgets(str, 100, arq) != NULL)
			puts(str);
		
		fclose(arq);
		
		return 1;
	}	
	
	return 0;
}

int exibe_fputc(char file[100])
{
	FILE *arq = fopen(file, "r");
	
	if(arq != NULL)
	{
		char chr = fgetc(arq);
		while(!feof(arq))
		{
			printf("%c", chr);
			chr = fgetc(arq);
		}
		
		fclose(arq);
		
		return 1;
	}	
	
	return 0;
}

void exemplo_fputs()
{
	int deuCerto = transfereMasc_fputc("arquivo1.txt\0", "arquivo2.txt\0");
	if(deuCerto)
	{
		printf("Deu Certo.\n");
		exibe_fputc("arquivo2.txt\0");
	}
	else
		printf("DEU ERRADO!");
		
	getch();
}


void exemplo_fgets()
{
	int deuCerto = transfereMasc_fputs("arquivo1.txt\0", "arquivo2.txt\0");
	if(deuCerto)
	{
		printf("Deu Certo.\n");
		exibe_fputs("arquivo2.txt\0");
	}
	else
		printf("DEU ERRADO!");
		
	getch();
}

int main(void)
{
	//exemplo_fputs();
	exemplo_fgets();
}

