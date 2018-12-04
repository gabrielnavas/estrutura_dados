#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>



int verificaChaveParen(char fileName[100])
{
	int chave=0;
	int paren=0;
	int i=0;
	char verif[100];
	char ch;
	int erro = 0;
	FILE *arq = fopen(fileName, "r");
	if(arq != NULL)
	{
		ch = fgetc(arq);
		while(!feof(arq) && erro == 0)
		{
			if(ch == '{')
			{
				verif[i] = '{';
				i++;
				chave++;
			}
			
			else if(ch == '(')
			{
				verif[i] = '(';
				i++;
				paren++;
			}	
					
			else if(ch == '}' && verif[i-1] == '{')
			{
				chave--;
				i--;
			}
			
			else if(ch == ')' && verif[i-1] == '(')
			{
				paren--;
				i--;
			}
			else if(ch != '\0' && ch != '\n')
			erro = 1;
							
				
			ch = fgetc(arq);	
		}
		
		fclose(arq);
		if(erro == 0 && chave == 0 && paren == 0)
		return 0;
		else
		 return 1;
	}
	
	return -1;	
}

int main(void)
{
	char fileName[100];
	
	system("cls");
	printf("\n\n\tNOME DO ARQUIVO A VERIFICAR: ");
	fflush(stdin);	gets(fileName);
	while(strcmp(fileName, "") != 0)
	{
		int deuCerto = verificaChaveParen(fileName);
		if(deuCerto == 0)
			printf("\n\n\tO ARQUIVO ESTA CONSISTENTE.");
		else if(deuCerto == 1)
			printf("\n\n\tO ARQUIVO ESTA SEM CONSISTENCIA");
		else if( deuCerto == -1)
			printf("\n\n\tO ARQUIVO NAO EXISTE");	
			
		getch();	
			
		system("cls");
		printf("\n\n\tNOME DO ARQUIVO A VERIFICAR: ");
		fflush(stdin);	gets(fileName);		
	}
		
}
