#include<stdio.h>

long fat(int n)
{
	if(n==0) return 1;
	
	return n*fat(n-1);
}

int main(void)
{
	printf("%d",fat(5));
}
