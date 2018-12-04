#include<stdio.h>

int fatorial(int n)
{
	long tot = 1;
	for(int i=2 ; i <=n ; i++)
		tot *= i;
		
	return tot;	
}

int main()
{
	printf("%d", fatorial(6));
}
