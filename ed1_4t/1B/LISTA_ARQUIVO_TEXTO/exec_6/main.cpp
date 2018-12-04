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


int lenFileLines(FILE *arq)
{
	char lineStr[100];
	int len=0;
	while(fgets(lineStr, 100, arq) != NULL)
		len++;
			
	return len;	
}


void scanfAposta(FILE *arq, struct Aposta &aposta)
{
	fscanf(arq, "%d", &aposta.numero);
	fscanf(arq, "%d", &aposta.dia); 
	fscanf(arq, "%d", &aposta.mes); 
	fscanf(arq, "%d", &aposta.ano);
	for(int i=0 ; i < 7 ; i++)
		fscanf(arq, "%d", &aposta.apostas[i]);
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
			printf("\n%d", aposta.numero);
			printf("\t\t%d/", aposta.dia);
			printf("%d/", aposta.mes);
			printf("%d\t\t", aposta.ano);
			
			for(int i=0 ; i < 7 ; i++)
				printf("%d ", aposta.apostas[i]);		
			
			scanfAposta(arq, aposta);
		}
		
		fclose(arq);
	}
	else
		printf("ARQUIVO DE APOSTA NA EXISTE.");
	
	getch();	
}

int writeAposta(char fileName[100], struct Aposta aposta)
{
	FILE *arq = fopen(fileName, "a+");
	if(arq != NULL)
	{
		int linhasArquivo = lenFileLines(arq);
		
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
	
	return 0;	
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
			printf("\nAPOSTA N %d: ", i+1);
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

int ganhadorQuina(char fileName[100], int quina[5], struct Aposta &aposta)
{
	int ganhador=-1;
	
	FILE *arq = fopen(fileName, "r");
	if(arq != NULL)
	{
		scanfAposta(arq, aposta);
		while(!feof(arq) && ganhador == -1)
		{
			int acertos=0;
			for(int i=0 ;i<5 ;i++)
				for(int j=0 ;j<7 ;j++)
					if(quina[i] == aposta.apostas[j])
						acertos++;
						
			if(acertos >= 5)
				ganhador=aposta.numero;	
			else	
				scanfAposta(arq, aposta);			
		}
		
		if(feof(arq))
		{
			fclose(arq);
			return 0;
		}
			
	}
	
	return ganhador;
}

void verGanhador(char fileName[100])
{
	system("cls");
	
	int quina[5];
	for(int i=0 ; i < 5 ; i++)
	{
		printf("NUMERO %d: ", i+1);
		scanf("%d", &quina[i]);
	}
	
	Aposta aposta;
	int deuCerto = ganhadorQuina(fileName, quina,aposta);
	if(deuCerto == -1)
		printf("\nProblemas com o arquivo.");
	else if(deuCerto == 0)
		printf("\nNao achou ganhador.");
	else
	{
		printf("\nGANHADOR EH: ");		
		printf("\nNUMERO: %d", aposta.numero);
		
	}
	
	printf("\n\nPRESS ENTER");
	getch();	
}

char menu()
{
	printf("ESCOLHA.");
	
	printf("\n\n[ 0 ] - SAIR.");
	printf("\n[ 1 ] - FAZER APOSTA.");
	printf("\n[ 2 ] - VER APOSTAS (FORMATADO).");
	printf("\n[ 3 ] - VER GANHADOR. QUINA.");
	
	return toupper(getch());
}

void logicMenu()
{
	
	char op;
	do
	{
		system("cls");
		op = menu();
		
		if(op == '1') fazerAposta("apostas.txt\0");
		
		else if(op == '2') exibirApostas("apostas.txt\0");
		
		else if(op == '3') verGanhador("apostas.txt\0");
		
	}while(op != '0');	
}

int main(void)
{
	logicMenu();
}
