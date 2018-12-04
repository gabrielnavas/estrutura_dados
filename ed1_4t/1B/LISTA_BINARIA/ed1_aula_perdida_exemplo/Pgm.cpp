#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "F:\ED1\TAD\TadArq.h"

void Arquivo(FILE *Ponteiro)
{
 Ponteiro=fopen("TadArq.h","ab");
 fclose(Ponteiro);			
}


int main(){
	FILE *Ponteiro;
	Arquivo(Ponteiro);
	
	
	
	
}
