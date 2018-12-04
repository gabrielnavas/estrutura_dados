#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>

#include "lista_char.h"

int main(void)
{
	Descritor desc;
	iniciar(desc);
	
	inserirOrdenado(desc);
	
	printf("\n\n%c\n", desc.inicio->info);
	printf("%c\n\n\n", desc.fim->info);
	
	
	exibir(desc);
	
	removerElem(desc);
	
	
	
}
