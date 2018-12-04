#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<conio2.h>

int isVogal(char chr)
{
	return toupper(chr) == 'A' || toupper(chr) == 'E' || 
		toupper(chr) == 'I' || toupper(chr) == 'O' || toupper(chr) == 'U';
}

int contaPalavraVogais(char fileName[100])
{
	int qndPala=0;

	FILE *arq = fopen(fileName, "r");

	if(arq != NULL)
	{
		char line[100];

		while(fgets(line, 100, arq) != NULL)
		{
			if(line[0] != ' ' && isVogal(line[0]))
				qndPala++;
			
			for(int i=0 ; line[i] != '\0' ; i++)
				if(line[i] == ' ' && isVogal(line[i+1]))
					qndPala++;
		}
			
		fclose(arq);

		return qndPala;
	}

	return -1;
}

int main(void)
{
	int qtd = contaPalavraVogais("arquivo.txt\0");
	if(qtd != -1)
		printf("QUANTIDADE: %d", qtd);
	else
		printf("ARQUIVO NAO EXISTE");

	getch();
}
