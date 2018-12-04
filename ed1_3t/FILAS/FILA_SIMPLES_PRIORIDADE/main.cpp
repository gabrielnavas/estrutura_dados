#include<stdio.h>

#include "fila_simples_prioridade.h"

int main(void)
{
	Fila f;
	iniciar(f);
	
	Elem e;
	
	e.info='3';
	e.priori=2;
	inserir(f, e);

	e.info='2';
	e.priori=1;
	inserir(f, e);
	
	e.info='1';
	e.priori=0;
	inserir(f, e);
		
	exibir(f);
}
