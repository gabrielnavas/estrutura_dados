#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>
#include<ctype.h>
#include<windows.h>

#include "lista_char.h"

int main(void)
{
	Descritiva desc;
	iniciarDesc(desc);
	
	inserirOrdenado(desc);
	exibir(desc);
}
