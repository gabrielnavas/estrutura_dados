#include<stdio.h>
#include "fila_estatica_char.h"



int main(void)
{
	Fila f;
	iniciar(f);
	
	inserir(f, 'a');
	
	printf("%c", elemFim(f));
	
	printf("%c", retirar(f));
	
	exibir(f);
}
