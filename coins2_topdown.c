#include <stdio.h>
#include <stdlib.h>

int n,x;
int *t;
int *mem;

int coinsTopDown(int x);
int min(int a, int b);

int main()
{
	printf("Enter the no. of Denominations: ");
	scanf("%d", &n);
	t = (int *)malloc(n*sizeof(int));
	for(int i=0 ; i<n ; i++)
	{
		printf("Denomination #%d = ", i+1);
		scanf("%d", &t[i]);
	}
	printf("Enter the value: ");
	scanf("%d", &x);
	mem = (int *)malloc((x+1)*sizeof(int));
	for(int i=0 ; i<=x ; i++)
		mem[i] = -1;
	mem[0] = 0;
	for(int i=0 ; i<n ; i++)
		mem[t[i]] = 1;
	printf("Minimum no. of coins required = %d\n", coinsTopDown(x));
}

int coinsTopDown(int x)
{
	if(mem[x] > -1)
		return mem[x];
	int temp;
	int i=0;
	int cmin = x+1;
	while(i<n && x>=t[i])
	{
		temp = coinsTopDown(x-t[i]) + 1;
		cmin = min(cmin, temp);
		i++;
	}
	mem[x] = cmin;
	return mem[x];
}

int min(int a, int b)
{
	if(a<b)
		return a;
	else
		return b;
}