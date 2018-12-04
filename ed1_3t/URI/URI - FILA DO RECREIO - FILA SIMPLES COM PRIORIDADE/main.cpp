#include<stdio.h>

#include "fila_simples_prioridade_char.h"

int getFlags(Fila f)
{
	int cont=0;
	while(!vazia(f.cont))
	{
		Elem e = retirar(f);
		if(e.flag == 1)
			cont++;
	}
	
	return cont;
}

int main(void)
{
	FILE *arqE = fopen("entrada.txt","r");
	FILE *arqS = fopen("saida.txt","w");
	
	Fila f;
	int casos;
	
	fscanf(arqE, "%d", &casos);
	while(casos > 0)
	{
		iniciar(f);
		
		int alunos;
		fscanf(arqE, "%d", &alunos);
		int contaAlunos = alunos;
		while(contaAlunos > 0)
		{
			Elem e;
			e.flag=0;
			fscanf(arqE, "%d", &e.priori);
			inserir(f, e);
			
			contaAlunos--;
		}
		
		
		exibir(f);
		int alunosMudados = getFlags(f);
		alunos = alunos - alunosMudados;
		fprintf(arqS, "%d\n", alunos);
		
		casos--;
		
		fscanf(arqE, "%d", &casos);
	}
	
	fclose(arqE);
	fclose(arqS);
	
}
