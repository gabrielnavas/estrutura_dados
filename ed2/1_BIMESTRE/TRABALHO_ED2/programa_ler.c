#include<stdio.h>

int calcula1(int *I, int *J, int K)
{
	*I=*I+3;
	*J=*I+K;
	K=K+1;
}

void calcula2(int I, int J, int *K)
{
	I=I+2;
	J=J+*K;
	*K=*K+1;
}

void executa(int *p1, int *p2, int *p3)
{
	int q=2, j=5;
	printf("q*j=%d\n",q*j);
	printf("%d\n",*p1**p2);
	printf("Eu sou um prinf sem saida de variavel :)\n");
	*p1=*p2+*p3;
	*p2=*p2**p3;
	printf("%d%d\n", *p1, *p2);
	calcula1(&*p3, &*p1,*p2);
	calcula2(*p2, *p2, &*p2);
}

int main()
{
	int VAAR=3,B=5,C=7;
	VAAR=2;
	B=3;
	C=2;
	int Y,O;
	executa(&VAAR,&B,&C);
	printf("valor de C eh %d e %d deu certo %s\n",VAAR, 1+2+3,"gabriel");
	printf("Primeiro valor modificado = %d\n",VAAR);
	printf("Segundo valor modificado = %d\n",B);
	printf("Terceiro valor modificado = %d\n",C);
}
