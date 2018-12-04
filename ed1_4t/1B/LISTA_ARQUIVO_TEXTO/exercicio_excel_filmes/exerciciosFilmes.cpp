#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio2.h>
#include<ctype.h>

#define MAX_FILMES 10000

struct Filme{
    char nome[60], classif[6];
    int ano, duracao;
    float gasto,renda,espec;
};


int readFilmes(Filme filmes[MAX_FILMES], int &tl)
{
    Filme reg;
    FILE *arq = fopen("arquivoFIlmes.csv","r");
    if(arq != NULL)
    {
        fscanf(arq,"%[^;];%d;%[^;];%f;%f;%d;%f\n",&reg.nome, &reg.ano, &reg.classif, &reg.gasto, &reg.renda, &reg.duracao, &reg.espec);
        while(!feof(arq))
        {   
            filmes[tl++] = reg;
            //printf("%s %d %s %.2f %.2f %d %.2f \n",reg.nome, reg.ano, reg.classif, reg.gasto, reg.renda, reg.duracao, reg.espec);

            fscanf(arq,"%[^;];%d;%[^;];%f;%f;%d;%f\n",&reg.nome, &reg.ano, &reg.classif, &reg.gasto, &reg.renda, &reg.duracao, &reg.espec);
        }
        fclose(arq);

        return 1;    
    } 
    
    return 0;
}

void showFilmes(Filme reg[MAX_FILMES], int &tl)
{
	for(int i=0 ; i < tl ; i++)
	    printf("%s %d %s %.2f %.2f %d %.2f \n", 
			reg[i].nome, 
			reg[i].ano, 
			reg[i].classif, 
			reg[i].gasto, 
			reg[i].renda, 
			reg[i].duracao, 
			reg[i].espec
		);

}

Filme filmeMaiorLucro(Filme filmes[MAX_FILMES], int tl)
{
    Filme filmeMaiorLucro = filmes[0];

    for(int i=1 ; i < tl ; i++)
        if(filmes[i].gasto > filmeMaiorLucro.gasto)
            filmeMaiorLucro = filmes[i];

    return filmeMaiorLucro;    
}

Filme filmeMaiorTaxaEspec(Filme filmes[MAX_FILMES], int tl)
{
    Filme filmeMaiorEspec = filmes[0];

    for(int i=1 ; i < tl ; i++)
        if(filmes[i].espec > filmeMaiorEspec.espec)
            filmeMaiorEspec = filmes[i];

    return filmeMaiorEspec;    
}

float filmesDuracaoMedia(Filme filmes[MAX_FILMES], int tl)
{
    int totalDuracao=0;
    
    for(int i=0 ; i < tl ; i++)
        totalDuracao += filmes[i].duracao;

    return totalDuracao/tl;
}



int filmesAnoMaiorFilmesProduzidos(Filme filmes[MAX_FILMES], int tl)
{
    if(tl > 0)
    {
    	int tlFA=0;
        Filme filmesAnos[MAX_FILMES];
		
		/* INSERIR ORDENADO */
		for(int j=0 ; j < tl ; j++)
		{
			filmesAnos[tlFA++] = filmes[j];
			for(int i=tlFA-1 ; i > 0 && filmesAnos[i].ano < filmesAnos[i-1].ano ; i--)
            {
            	Filme aux = filmesAnos[i];
				filmesAnos[i] = filmesAnos[i-1];
				filmesAnos[i-1] = aux;	
            }
		}
        
		/*
	    for(int i=0 ; i < tl-1 ; i++)
	        for(int j=i ; j < tl ; j++)
	            if(filmesAnos[i].ano > filmesAnos[j].ano)
	            {
	                Filme aux = filmesAnos[i];
	                filmesAnos[i] = filmesAnos[j];
	                filmesAnos[j] = aux;
	            }
		*/
		    
        int anoMaior;
        int qntd=0;
        for(int i=0 ; i < tl-1 ; i++)
        {
        	/* COMPARA O ATUAL COM O PROXIMO, SE FOR IGUAL ELE CONT++*/
        	int cont=1;
        	while(filmesAnos[i].ano == filmesAnos[i+1].ano)
        	{
        		cont++;
        		i++;
        	}
        	
        	/* VE SE CONT EH MAIOR QUE QNTDT JA ANOTADA DO FILME ANTERIOR*/
			if(cont > qntd)
			{
				anoMaior=filmesAnos[i].ano;
				qntd=cont;
			}	
        }
        
        return anoMaior;
    }

    return -1;
}

void relatorioFilmesSeparadosClassificacao(Filme filmes[MAX_FILMES], int tl)
{
	system("cls");
	
	if(tl > 0)
	{
		Filme filmesClass[MAX_FILMES];
		int tlFC=0;
		
		for(int i=0 ; i < tl ; i++)
		{
			filmesClass[tlFC++] = filmes[i];
			for(int j= tlFC-1 ; j > 0 && strcmp( filmesClass[j-1].classif, filmesClass[j].classif ) > 0 ; j--)
			{
				Filme aux = filmesClass[j];
				filmesClass[j] = filmesClass[j-1];
				filmesClass[j-1] = aux;
			}
		}    
		
	
		
		for(int i=0 ; i < tlFC ; i++)
		{
			printf("\n\nNOME: "); puts(filmesClass[i].nome);
			printf("CLASSIFICACAO: "); puts(filmesClass[i].classif);
			printf("ANO: %d", filmesClass[i].ano);
			printf("\nCLASSIFICACAO: %d", filmesClass[i].duracao);
			printf("\nGASTO: %.2f", filmesClass[i].gasto);
			printf("\nRENDA: %.2f", filmesClass[i].renda);
			printf("\nESPEC: %.2f", filmesClass[i].espec);	
		}
		
		printf("FIM RELATORIO.");
	}
	else
		printf("NÃO EXISTE FILMES ADICIONADOS.");	
	
	printf("PRESS ENTER.");
	getch();
}


void verArquivoBinario(char fileName[100])
{
	Filme filme;
	FILE *arq = fopen(fileName, "rb");
	if(arq != NULL)
	{
		do
		{
			fread(&filme, sizeof(Filme),1,arq);
			
			printf("\n\nNOME: "); puts(filme.nome);
			printf("CLASSIFICACAO: "); puts(filme.classif);
			printf("ANO: %d", filme.ano);
			printf("\nCLASSIFICACAO: %d", filme.duracao);
			printf("\nGASTO: %.2f", filme.gasto);
			printf("\nRENDA: %.2f", filme.renda);
			printf("\nESPEC: %.2f", filme.espec);	
		
			
		}while(!feof(arq));
		
		fclose(arq);
		
		printf("\n\nFIM.");
	}
	else
		printf("ARQUIVO NAO EXISTE");
	
	getch();
}

void arquivoBinarioAnoProducaoWrite(char fileName[100], Filme filmes[MAX_FILMES], int tl)
{
    
	FILE *arq = fopen(fileName, "wb");
	if(arq != NULL)
	{
		Filme filmesOrdenadoAno[MAX_FILMES];
		int tlFOA=0;

		for(int i=0 ; i < tl ; i++)
		{
			filmesOrdenadoAno[tlFOA++] = filmes[i];
			for(int j= tlFOA-1 ; j > 0 && filmesOrdenadoAno[j].ano < filmesOrdenadoAno[j-1].ano ; j--)
			{
				Filme aux = filmesOrdenadoAno[j];
				filmesOrdenadoAno[j] = filmesOrdenadoAno[j-1];
				filmesOrdenadoAno[j-1] = aux;
			}
		}
			
		for(int i=0 ; i < tlFOA ; i++)
			fwrite(&filmesOrdenadoAno[i], sizeof(Filme),1,arq);

		fclose(arq);

		printf("\nGRAVADO COM SUCESSO. \nDESEJA VISUALIZAR O ARQUIVO BINARIO? (S/N)");
		char op= toupper(getch());
		if(op == 'S')
			verArquivoBinario(fileName);
	}	
	else
		printf("ARQUIVO NAO EXISTE");
}

void arquivoBinarioTaxaEspecProducaoWrite(char fileName[100], Filme filmes[MAX_FILMES], int tl)
{
	
    	/*
		char nome[60], classif[6];
	    int ano, duracao;
	    float gasto,renda,espec;
		*/
	
	FILE *arq = fopen(fileName, "wb");
	if(arq != NULL)
	{
		Filme filmesOrdTaxaEspec[MAX_FILMES];
		int tlFOTX=0;
		
		for(int i=0 ; i < tl ; i++)
		{
			filmesOrdTaxaEspec[tlFOTX++] = filmes[i];
			for(int j=tlFOTX-1 ; j > 0 && filmesOrdTaxaEspec[j].espec < filmesOrdTaxaEspec[j-1].espec ; j--)
			{
				Filme aux =  filmesOrdTaxaEspec[j];
				filmesOrdTaxaEspec[j] = filmesOrdTaxaEspec[j-1];
				filmesOrdTaxaEspec[j-1] = aux;
			}
		}
		
		for(int i=0 ; i < tlFOTX ; i++)
			fwrite(&filmesOrdTaxaEspec[i], sizeof(Filme), 1, arq);
		
		fclose(arq);
		
		printf("\n\nGRAVADO COM SUCESSO.\nDESEJA VER O ARQUIVO BINARIO? (S/N)");
		char op = toupper(getch());
		if(op == 'S')
			verArquivoBinario(fileName);
	}
}

void medianoAnoProducao(Filme filmes[MAX_FILMES], int tl)
{
	Filme filmesAnoProd[MAX_FILMES];
	int tlAP=0;
	
	for(int i=0 ; i < tl ; i++)
	{
		filmesAnoProd[tlAP++]=filmes[i];
		for(int j=tlAP-1 ; j > 0 && filmesAnoProd[j].ano < filmesAnoProd[j-1].ano ; j--)
		{
			Filme aux = filmesAnoProd[j];
			filmesAnoProd[j] = filmesAnoProd[j-1];
			filmesAnoProd[j] = aux;
		}
	}
	
	if(tlAP/2 == 0)
		printf("\nANO MEDIANO: %d", filmesAnoProd[tlAP/2]);
	else
	{
		int v1 = tlAP/2;
		int anoV1 = filmesAnoProd[v1].ano;
		
		int v2 = (tlAP/2) + 1;
		int anoV2 = filmesAnoProd[v2].ano;
		
		
		int calc = (anoV1 + anoV2)/2;
		printf("\nANO MEDIANO: %d", calc);
	}
		
	getch();	
	
}

void graficofilmesAnoMaiorFilmesProduzidos(Filme filmes[MAX_FILMES], int tl)
{
    if(tl > 0)
    {
    	int tlFA=0;
        Filme filmesAnos[MAX_FILMES];
		
		/* INSERIR ORDENADO */
		for(int j=0 ; j < tl ; j++)
		{
			filmesAnos[tlFA++] = filmes[j];
			for(int i=tlFA-1 ; i > 0 && filmesAnos[i].ano < filmesAnos[i-1].ano ; i--)
            {
            	Filme aux = filmesAnos[i];
				filmesAnos[i] = filmesAnos[i-1];
				filmesAnos[i-1] = aux;	
            }
		}
        
		    
        
        for(int i=0 ; i < tl-1 ; i++)
        {
        	printf("%d => *", filmesAnos[i].ano);
        	while(filmesAnos[i].ano == filmesAnos[i+1].ano)
        	{
        		printf("*");
        		i++;
        	}
				
			
			printf("\n");
        	
        }
        
        printf("\n\nFIM");
    }
    else
		printf("NAO EXISTE FILMES PARA EXIBIR.");
    
}

char menu()
{
	printf("ESCOLHA: ");

	printf("\n\n[ X ] - SAIR.");
    
	
	printf("\n\n[ A ] - Filme com maior lucro; --- ");
    printf("\n\n[ B ] - Filme com maior taxa de espectadores; --- ");
    printf("\n\n[ C ] - duracao media dos filmes;---- ");
    printf("\n\n[ D ] - O ano em que houve o maior numero de filmes produzidos; ---");
    printf("\n\n[ E ] - Gerar um relatorio com os filmes separados pela classificacao; ----");
    printf("\n\n[ F ] - Gerar um arquivo binario com os filmes ordenados pelo ano de producao; ---");
    printf("\n\n[ G ] - Gerar um arquivo binario com os filmes ordenados pela taxa de espectadores -> da menor para a maior; ---");
    printf("\n\n[ H ] - Encontre o valor mediano para o ano de producao => colocar em ordem por ano de producao e descobrir o ano na posisao central. Quando a quantidade for impar, pegar o elemento central, caso contrario, pegar a media dos dois elementos mais centrais;");
    printf("\n\n[ I ] - GRAFICO Implementar um grafico de dispersao ou de linha -> eixos Ano X Quantidade de filmes produzidos.");

    return toupper(getch());
}

void logic()
{
    int tl=0;
    Filme filmes[MAX_FILMES];
    
    int allRight = readFilmes(filmes, tl);
    if( !allRight )
    {
        printf("ARQUIVO NAO ENCONTRADO");
        getch();
    }

    char op;
    do
    {
        op = menu();

        if(op == 'A')
        {
        	system("cls");
        	
        	Filme filmeMaiorLucr = filmeMaiorLucro(filmes, tl);
        	printf("FILME MAIOR LUCRO FOI: "); puts(filmeMaiorLucr.nome);
        	printf("LUCRO %.2f", filmeMaiorLucr.gasto);
        	
        	getch();
		}
		
        else if(op == 'B')
        {
        	system("cls");
        
		    Filme filmeMaiorEspec =  filmeMaiorTaxaEspec(filmes, tl);
        	printf("FILME MAIOR TAXA ESPECTADORES FOI: "); puts(filmeMaiorEspec.nome);
        	printf("ESPEC %.2f", filmeMaiorEspec.espec);
        	
        	getch();
		}
        else if(op == 'C')
        {   
        	system("cls");
        
        	printf("MEDIA DURACAO FILME: %.2f", filmesDuracaoMedia(filmes, tl));
        	
        	getch();
		}
		
        else if(op == 'D')
        {     
		
			system("cls");  
			int ano = filmesAnoMaiorFilmesProduzidos(filmes, tl);
            printf("O ano em que houve o maior numero de filmes produzidos %d", ano);
        	getch();        	
		}
		
        else if(op == 'E')
            relatorioFilmesSeparadosClassificacao(filmes, tl);

        else if(op == 'F')
            arquivoBinarioAnoProducaoWrite("BINARIO_FILMES_ORDENADO_ANO.bin\0", filmes, tl);

        else if(op == 'G')
            arquivoBinarioTaxaEspecProducaoWrite("BINARIO_FILMES_ORDENADO_ANO.bin\0", filmes, tl);

        else if(op == 'H')
            medianoAnoProducao(filmes, tl);

        else if(op == 'I')
            graficofilmesAnoMaiorFilmesProduzidos(filmes, tl);

    }while(op != 'X');
}

int main(void)
{
	logic();
	
	
} 
