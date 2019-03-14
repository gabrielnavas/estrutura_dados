#include<stdio.h>

void calcula3(int *I3)
{
	*I3 =  2+1+5*2;
	printf("Eu sou um prinf sem saida de variavel :)\n");
	return;
}

int calcula1(int *I2, int *J2, int K2) {	
	int W=1, W2=2;
	W = W+W2;
	*I2 = *I2+3+1;
	calcula3(I2);
	*J2=*I2+K2;
	K2=K2+1;
	return *J2;
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
	printf("%d\n", 2*(4+15/(10+5))-4+(2*2 + (2+1) )*4);
	printf("%d - %d %s\n", 2*4+(2*2 + (2+1) )*4, 'O', "Gabriel\0");
	calcula2(VAAR, B, &C);
	int Y,O;
	O=calcula1(&VAAR, &B, C);
	Y=4;
	O=2;
	printf("valor de C eh %d e %d deu certo %s\n",VAAR, 1+2+3,"gabriel");
	printf("VAAR valor modificado = %d\n",VAAR);
	printf("B valor modificado = %d\n",B);
	printf("C valor modificado = %d\n",C);
	printf("O valor modificado = %d\n", O);
}
