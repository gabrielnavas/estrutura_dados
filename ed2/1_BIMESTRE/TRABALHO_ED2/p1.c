#include<stdio.h>

void calcula3(int *I3)
{
	*I3 =  2+1+5*2;
	printf("Eu sou um prinf sem saida de variavel :)\n");
	return;
}

int calcula1(int *I2, int *J2, int K2)
{	
	int W=1, W2=2;
	W = W+W2;
	*I2 = *I2+3+1;
	calcula3(I2);
	*J2=*I2+K2;
	K2=K2+1;
}

void calcula2(int I, int J, int *K)
{
	I=I+2;
	J=J+*K;
	*K=*K+1;
}


int main()
{
	int VAAR=3,B=5,C=7;
	calcula1(&VAAR,&B,C);
	printf("%d", 3+2*4);
	printf("valor de VAAR=%d", VAAR);
	VAAR=2;
	B=3;
	C=2;
	VAAR = 2*4+B;
	B = VAAR * 4 + C;
	int Y,O;
	printf("valor de C eh %d e %d deu certo %s\n",VAAR, 1+2+3,"gabriel");
	printf("VAAR valor modificado = %d\n",VAAR);
	printf("B valor modificado = %d\n",B);
	printf("C valor modificado = %d\n",C);
}
