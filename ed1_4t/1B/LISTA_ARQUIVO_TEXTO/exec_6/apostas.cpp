#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio2.h>
#include<ctype.h>

#define FILE_NAME_APOSTAS "apostas.txt"

struct Aposta
{
	int numero;
	
	int dia;
	int mes;
	int ano;
	
	int dezena[7];
};

int quantidadeAposta(FILE *arq)
{
	int qntdAposta=0;
	
	fseek(arq, 0 ,0);
	char line[100];
	while(!feof(arq))
	{
		fgets(line, 100, arq);
		qntdAposta++;
	}
		
	return qntdAposta;
}

int inserirAposta(char fileName[100], Aposta aposta)
{
	FILE *arq = fopen("apostas.txt", "a+");
	if(arq != NULL)
	{
		aposta.numero = quantidadeAposta(arq);
		
		fprintf(arq, "%d %d %d %d ", aposta.numero, aposta.dia, aposta.mes, aposta.ano);
		for(int i=0 ; i < 7 ;i++)
			fprintf(arq, "%d ", aposta.dezena[i]);
		fprintf(arq, "\n");
		
		fclose(arq);
		
		return 1;	
	}

	return 0;
}

int exibeSemFormatacao(char fileName[100])
{
	system("cls || clear");
	
	FILE *arq = fopen("apostas.txt", "r");
	if(arq != NULL)
	{
		char chr = fgetc(arq);
		while(!feof(arq))
		{
			printf("%c", chr);
			chr = fgetc(arq);
		}
			
		fclose(arq);
	}
	
	return 1;	
}

int exibeComFormatacao(char fileName[100])
{
	system("cls || clear");
	
	Aposta aposta;
	FILE *arq = fopen("apostas.txt", "r");
	if(arq != NULL)
	{
		while(!feof(arq))
		{
			fscanf(arq, "%d %d %d %d", aposta.numero, aposta.dia, aposta.mes, aposta.ano);
				
			printf("NUM: %d", aposta.numero);
			printf("DATA: %d/%d/%d\n", aposta.dia, aposta.mes, aposta.ano);
			for(int i=0 ; i < 7 ; i++)	
				printf("[%d]", aposta.dezena[i]);
			printf("\n\n");					
		}
		
		fclose(arq);
	}
	
	return 1;
}

void inserirApostaConhecerDados()
{
	system("cls || clear");
	
	Aposta aposta;
	
	system("cls || clear");
	printf("Dia: ");
	scanf("%d", &aposta.dia);
	while(aposta.dia != 0)
	{
		printf("Mes: ");
		scanf("%d", &aposta.dia);
		
		printf("Ano: ");
		scanf("%d", &aposta.dia);
		
		printf("DIGITE AS 7 DEZENAS: ");
		for(int i=0 ; i < 7 ; i++)
		{
			printf("DEZENA %d: ", i+1);
			scanf("%d", &aposta.dezena[i]);
		}
		
		int deuCerto = inserirAposta(FILE_NAME_APOSTAS, aposta);
		if(deuCerto)
			printf("GRAVADO COM SUCESSO.");
		else 
			printf("NAO DEU CERTO.");
		
		getch();
		
		system("cls || clear");
		printf("Dia: ");
		scanf("%d", &aposta.dia);		
	}
}

char menu()
{
	printf("OPCAO: ");
	
	printf("\n\n[ 0 ] - SAIR.");
	printf("\n[ 1 ] - INSERIR APOSTA.");
	printf("\n[ 2 ] - EXIBIR SEM FORMATACAO.");
	printf("\n[ 3 ] - EXIBIR COM FORMATACAO.");
	
	return toupper(getch());
}

int main(void)
{
	char op = menu();
	while(op != '0')
	{
		if(op == '1')
			inserirApostaConhecerDados();
		
		else if(op == '2')
			exibeSemFormatacao(FILE_NAME_APOSTAS);
			
		else if(op == '3')	
			exibeComFormatacao(FILE_NAME_APOSTAS);
	}
	
	
	
}
