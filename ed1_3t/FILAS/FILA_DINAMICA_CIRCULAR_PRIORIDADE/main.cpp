#include<stdio.h>

#include "fila_dinamica_circular_prioridade.h"

int main(void)
{
	Fila fila;
	iniciar(fila);
	
	Elem e;
	
	e.priori = 3;
	e.info = '3';
	inserir(fila, e);
	
	
	
	e.priori = 2;
	e.info = '2';
	inserir(fila, e);
	
	
	
	e.priori = 1;
	e.info = '1';
	inserir(fila, e);
	
	exibir(fila);
}
