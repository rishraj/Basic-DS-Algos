#include <stdio.h>
#include <stdlib.h>

int maxCoins(int n);
int max(int a, int b);
void backtrack(int i);

int *val;
int *c;

int main()
{
	int n;
	scanf("%d", &n);
	c = malloc(n*sizeof(int));
	for(int i=0 ; i<n ; i++)
	{
		scanf("%d", &c[i]);
	}
	int res = maxCoins(n);
//	printf("Maximum value of coins = %d\n", res);
//	printf("Coins selected : ");
	backtrack(n);
	printf("\n");
}

int maxCoins(int n)
{
	val = (int *)malloc((n+1)*sizeof(int));
	val[0] = 0;
	val[1] = c[0];
	for(int i=2 ; i<=n ; i++)
		val[i] = max(val[i-1], val[i-2] + c[i-1]);
	return val[n];
}

int max(int a, int b)
{
	if(a < b)
		return b;
	else
		return a;
}

void backtrack(int i)
{
	if(i == 0)
		return;
	else if(i == 1)
		printf("%d ", c[0]);
	else
	{
		if(val[i] == val[i-1])
			backtrack(i-1);
		else if(val[i] == val[i-2] + c[i-1])
		{
			backtrack(i-2);
			printf("%d ", c[i-1]);
		}
	}
}












