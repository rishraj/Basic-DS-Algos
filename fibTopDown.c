#include <stdio.h>

int fibTopDown(int n);

int main()
{
	int n;
	scanf("%d", &n);
	printf("%d\n", fibTopDown(n));
}

int fibTopDown(int n)
{
	if(n == 0)
		return 0;
	else if(n == 1)
		return 1;
	else
		return (fibTopDown(n-1) + fibTopDown(n-2));
}






