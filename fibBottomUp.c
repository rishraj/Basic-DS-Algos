#include <stdio.h>

int fibBottomUp(int n);
int fibBottomUp1(int n, int a, int b);

int main()
{
	int n;
	scanf("%d", &n);
	printf("%d\n", fibBottomUp(n));
	printf("%d\n", fibBottomUp1(n, 0, 1));
}

int fibBottomUp(int n)
{
	int a[n];
	a[0] = 0;
	a[1] = 1;
	for(int i=2 ; i<=n ; i++)
		a[i] = a[i-1] + a[i-2];
	return a[n];
}

//-------- alternate method ------------------------------------------
int fibBottomUp1(int n, int a, int b)
{
	if(n == 1)
		return b;
	else
		return fibBottomUp1(n-1, b, a+b);
}


