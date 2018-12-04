#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

int retiraItem(char verif[], int &tl, char chr)
{
	int i=tl-1;
	int achou=0;
	while(achou != 1 && i >= 0)
	{
		if(verif[i] == chr)
		{
			achou=1;
			for(int j=i ; j < tl-1 ; j++)
				verif[j] = verif[j+1];
		}
			
		i--;	
	}
	
	return achou;
}

int verificaChaveParen(char fileName[100])
{
	FILE *arq = fopen(fileName, "r");
	
	if(arq != NULL)
	{
		int tl=0;
		char verif[100];
		int erro = 0;
		
		char line[1000];
		fgets(line, 100, arq);
		while(!feof(arq) && erro == 0)
		{
			for(int ch=0; ch < strlen(line) ; ch++)
			{
				if(line[ch] == '{' && line[ch+1] != 39) //39='
					verif[tl++] = '{';
				
				else if(line[ch] == '(' && line[ch+1] != 39) //39='
					verif[tl++] = '(';
						
				else if(line[ch] == '}' && line[ch+1] != 39) //39='
				{
					int achou = retiraItem(verif, tl , '{');
					if(achou == 0)
						erro=1;
						
					tl--;
				}
				
				else if(line[ch] == ')' && line[ch+1] != 39) //39='
				{
					int achou = retiraItem(verif, tl , '(');
					if(achou == 0)
						erro=1;
						
					tl--;
				}								
			}
			fgets(line, 100, arq);	
		}
		
		fclose(arq);
		
		return tl == 0 && erro == 0;
	}
	
	return -1;	
}

int main(void)
{
	
	int deuCerto = verificaChaveParen("ler.cpp\0");
	if(deuCerto == 1)
		printf("\n\n\tO ARQUIVO ESTA CONSISTENTE.");
	else if(deuCerto == 0)
		printf("\n\n\tO ARQUIVO ESTA SEM CONSISTENCIA");
	else if( deuCerto == -1)
		printf("\n\n\tO ARQUIVO NAO EXISTE");		
}
	
