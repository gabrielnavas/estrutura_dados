#include<stdio.h>

void executa(int *p1, int *p2, int *p3)
{
	int q=2, j=5;
	return;
}

int executa2(int p1, int *p2)
{
	p1 = p1**p2;
	
	return p1**p2;
}

int executa3(int p2)
{
	return 1*p2;
}

int main()
{
	int Y=2,O=4;
	int P=1;
	executa(&Y, &O, &P);
	O = executa3(P);
	int VAAR=3,B=5,C=7;
	VAAR=2;
	B=3;
	C=2;
	executa(&VAAR,&B,&C);
	printf("%d", Y);
}
