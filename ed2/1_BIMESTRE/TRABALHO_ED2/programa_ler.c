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
	*p1=*p2+*p3;
	*p2=*p2**p3;
	calcula1(&*p3, &*p1,*p2);
	calcula2(*p2, *p2, &*p2);
}

int main()
{
	int A=3,B=5,C=7;
	A=2;
	B=3;
	C=2;
	int Y,O;
	executa(&A,&B,&C);
	printf("Primeiro valor modificado = %d\n",A);
	printf("Segundo valor modificado = %d\n",B);
	printf("Terceiro valor modificado = %d\n",C);
}
