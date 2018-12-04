#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>
#include<ctype.h>

struct Aposta
{
	int numero;
	
	int dia;
	int mes;
	int ano;
	
	int apostas[7];	
};


int lenFileLines(char fileName[100])
{
	FILE *arq = fopen(fileName, "r");
	
	if(arq != NULL)
	{
		char lineStr[100];
		int len=0;
		while(fgets(lineStr, 100, arq) != NULL)
			len++;
			
		fclose(arq);
		
		return len;	
	}
	
	return -1;
}

int writeAposta(char fileName[100], struct Aposta aposta)
{
	int linhasArquivo = lenFileLines(fileName);
	if(linhasArquivo != -1)
	{
		FILE *arq = fopen(fileName, "a");
		
		aposta.numero=linhasArquivo+1;
		fprintf(arq, "%d ", aposta.numero);
		
		fprintf(arq, "%d ", aposta.dia);
		fprintf(arq, "%d ", aposta.mes);
		fprintf(arq, "%d ", aposta.ano);
		
		for(int i=0 ; i < 7 ; i++)
			fprintf(arq, "%d ", aposta.apostas[i]);
		fprintf(arq, "\n");
		
		fclose(arq);	
		
		return 1;
	}
	
	return -1;	
}


void scanfAposta(FILE *arq, struct Aposta &aposta)
{
	fscanf(arq, "%d", &aposta.numero);
	fscanf(arq, "%d", &aposta.dia); 
	fscanf(arq, "%d", &aposta.mes); 
	fscanf(arq, "%d", &aposta.ano);
}


void exibirApostas(char fileName[100])
{
	struct Aposta aposta;
	
	FILE *arq = fopen(fileName, "r");
	if(arq != NULL)
	{
		system("cls");
		printf("NUMERO\t\tDATA\t\tAPOSTAS");
		
		
		scanfAposta(arq, aposta);
		while(!feof(arq))
		{
			for(int i=0 ; i < 7 ; i++)
				fscanf(arq, "%d", &aposta.apostas[i]);
				
			printf("\n%d", aposta.numero);
			printf("\t\t%d/", aposta.dia);
			printf("%d/", aposta.mes);
			printf("%d\t\t", aposta.ano);
			
			for(int i=0 ; i < 7 ; i++)
				printf("%d ", aposta.apostas[i]);		
			
			scanfAposta(arq, aposta);
		}
		
		getch();
		
		fclose(arq);
	}
}

void fazerAposta(char fileName[100])
{
	struct Aposta aposta;
	
	system("cls");
	printf("DATA APOSTA. ");
	
	printf("\nDIA: ");
	scanf("%d", &aposta.dia);
	while(aposta.dia != 0)
	{
		printf("\nMES: ");
		scanf("%d", &aposta.mes);
		
		printf("\nANO: ");
		scanf("%d", &aposta.ano);
		
		for(int i=0 ; i < 7 ; i++)
		{
			printf("\nAPOSTA N %d", i+1);
			scanf("%d", &aposta.apostas[i]);
		}
		
		int gravou = writeAposta(fileName, aposta);
		if(gravou)
			printf("\n\nGRAVADO COM SUCESSO. [ENTER]");
		else
			printf("\n\nERRO AO GRAVAR. [ENTER]");
		
		getch();		
	
		system("cls");
		printf("DATA APOSTA. ");
		
		printf("\nDIA: ");
		scanf("%d", &aposta.dia);
	}
}

char menu()
{
	printf("ESCOLHA.");
	
	printf("\n\n[ 0 ] - SAIR.");
	printf("\n[ 1 ] - FAZER APOSTA.");
	printf("\n[ 2 ] - VER APOSTAS.");
	
	return toupper(getch());
}

void logicMenu()
{
	system("cls");
	char op = menu();
	while(op != '0')
	{
		if(op == '1') fazerAposta("apostas.txt\0");
		
		else if(op == '2') exibirApostas("apostas.txt\0");
		
		system("cls");
		op = menu();
	}	
}

int main(void)
{
	logicMenu();
}
