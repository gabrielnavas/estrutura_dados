#include<stdio.h>


int executa2(int p1, int *p2)
{
	int p;
	p=4;
	p=4*2+1;
	*p2=p;
	
	return p1;
}

int executa(int *t1, int *t2, int *t3)
{
	int q=2, j=5;
	*t1 = q+2;
	*t2 = *t3+4;
	*t3 = executa2(q, &*t3);
	
	return j;
}

int main()
{
	int a=2,b=10,c;
	c = executa(&a, &b, &c);
	printf("RESULTADO RETURN: %d\n", c);
	a=3;
	b=2;
	c=3;
	printf("RESULTADO A %d\n", a);
	printf("RESULTADO B %d\n", b);
	printf("RESULTADO C %d\n", c);
}
