#include<stdio.h>

#include "fila_dinamica_circular_char.h"

int main(void)
{
	Fila f;
	iniciar(f);
	
	inserir(f, 'a');
	inserir(f, 'b');
	inserir(f, 'c');
	
	retirar(f);
	exibir(f);
	
	printf("%c", retirar(f));
	
	exibir(f);
}
