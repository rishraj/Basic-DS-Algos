#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max(int a, int b) { return (a > b ? a : b); }

struct item{
	int cap;
	int val;
};

int compare(const void *a, const void *b);
int knapsack(struct item *arr, int i, int max_cap);
void backtrack(struct item *arr, int i, int max_cap);

int **max_val;
int *print_arr;
//int c=0;


int main()
{
	int n;
	scanf("%d", &n);
	if(n<=0)
		return 0;
	print_arr = malloc(n*sizeof(int));
	struct item arr[n];
	
	for(int i=1 ; i<=n ; i++)
		scanf("%d%d", &arr[i].cap, &arr[i].val);
	qsort (arr, n, sizeof(struct item), compare);
	int C;
	scanf("%d", &C);
	max_val = (int **)malloc((n+1)*sizeof(int *));
	//initializing max_val array
	for(int i=0 ; i<=n ; i++)
		max_val[i] = (int *) malloc((C+1)*sizeof(int));
	//setting base cases
	for(int i=0 ; i<= n ;i++)
		max_val[i][0] = 0;
	for(int i=0 ; i<=C ; i++)
		max_val[0][i] = 0;
	for(int i=1 ; i<=n ; i++)
		for(int j=1 ; j<=C ; j++)
			max_val[i][j] = -1;
	int max_value = knapsack(arr, n, C);
	backtrack(arr, n, C);
	printf("\n");
}


int knapsack(struct item *arr, int i, int max_cap)
{
	if(max_val[i][max_cap] > -1)
		return max_val[i][max_cap];
	if(max_cap < arr[i].cap)
	{
		max_val[i][max_cap] = knapsack(arr, i-1, max_cap);
		return max_val[i][max_cap];
	}
	else
	{
		max_val[i][max_cap] = max(knapsack(arr, i-1, max_cap), knapsack(arr, i-1, max_cap-arr[i].cap)+arr[i].val);
		return max_val[i][max_cap];
	}
}

void backtrack(struct item *arr, int i, int max_cap)
{
	if(i == 0 || max_cap == 0)
		return;
	if(max_val[i][max_cap] == max_val[i-1][max_cap-arr[i].cap] + arr[i].val && arr[i].cap <= max_cap)
	{
		printf("%d ", arr[i].cap);
		backtrack(arr, i-1, max_cap-arr[i].cap);
		
	//	print_arr[c] = arr[i].cap;
	//	c++;
	}
	else
		backtrack(arr, i-1, max_cap);
}



int compare(const void *a, const void *b)
{
	struct item *i1 = (struct item *)a;
	struct item *i2 = (struct item *)b;
	return i2->cap - i1->cap;
}








