#include<stdio.h>
#include<string.h>
#include<conio2.h>

struct InfoArq
{
	int linhas;
	int espacos;
	int letras;
};

int vasculharArq(char fileName[100], struct InfoArq &ia)
{
	FILE *arq = fopen(fileName, "r");
	
	if(arq != NULL)
	{
		
		char line[1000];
		line[0] =  '\0';
		
		while(fgets(line, 1000, arq) != NULL)
		{
			if(strlen(line) > 0)
				ia.linhas++;
			
			for(int i=0 ; line[i] != '\0' ; i++)
				(line[i] == ' ') ? ia.espacos++ : ia.letras++;
		}
		
		fclose(arq);
		return 1;
	}
	
	return 0;
}

void iniciarStruct(struct InfoArq &ia)
{
	ia.espacos=0;
	ia.letras=0;
	ia.linhas=0;
}

int main(void)
{
	struct InfoArq ia;
	iniciarStruct(ia);
	
	int deuCerto = vasculharArq("arquivo.txt\0", ia);	
	if(deuCerto)
	{
		printf("\nARQUIVO TEM:\n");
		printf("\nLINHAS: %d", ia.linhas);
		printf("\nESPACOS: %d", ia.espacos);
		printf("\nLETRAS: %d", ia.letras);
	}
	else
		printf("ACONTECEU UM ERRO.");
		
	getch();	
}
