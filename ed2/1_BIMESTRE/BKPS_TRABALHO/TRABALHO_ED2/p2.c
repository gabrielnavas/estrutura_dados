#include<stdio.h>


int executa2(int p1, int *p2)
{
	int p;
	p=4;
	p=4*2+1;
	*p2=p;
	return *p2;
}

void executa(int *t1, int *t2, int *t3)
{
	int q=2, j=5;
	*t2=3;
	*t2 = executa2(q, t3);
	return;
}

int main()
{
	int a=2,b=10,c;
	a=executa2(a, &b);
	printf("%d\n", a);
	a=3;
	b=2;
	c=3;
}
