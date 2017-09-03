#include <stdio.h>
#include <stdlib.h>

int findMinCoins(int *t, int n, int x);
int tMax(int *t, int n, int x);
void backtrack(int *t, int n, int x);

int *c;

int main()
{
	int n, x;
	printf("Enter the no. of Denominations: ");
	scanf("%d", &n);
	int t[n];
	for(int i=0 ; i<n ; i++)
	{
		printf("Denomination #%d = ", i+1);
		scanf("%d", &t[i]);
	}
	printf("Enter the value: ");
	scanf("%d", &x);
	printf("Minimum no. of coins required = %d\n", findMinCoins(t, n, x));
	printf("Coins used : ");
	backtrack(t, n, x);
	printf("\n");
}

int findMinCoins(int *t, int n, int x)
{
	if(x<t[0])
		return -1;
	c = malloc(x*sizeof(int));
	c[0] = 0;
	for(int i=t[0] ; i<=x ; i++)
	{
		int tmax = tMax(t, n, i);
		c[i] = c[i-tmax] + 1;
	}
	return c[x];
}

int tMax(int *t, int n, int x)
{
	for(int i=0 ; i<n ; i++)
	{
		if(t[i] > x)
			return t[i-1];
	}
	return t[n-1];
}

void backtrack(int *t, int n, int x)
{
	int temp = c[x];
	while(temp>0){
		int i=0;
		while(i<n && t[i]<=x)
		{
			if(c[x] == c[x-t[i]]+1)
			{
				printf("%d ", t[i]);
				x = x-t[i];
				break;
			}
			i++;
		}
		temp--;
	}
}

















