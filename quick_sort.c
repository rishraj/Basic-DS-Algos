#include <stdio.h>

void quick_sort(int *a , int p , int q);
int partition(int *a , int p , int q);

int main()
{
	int n;
	scanf("%d",&n);
	int a[n];
	for(int i=0 ; i<n ; i++)
		scanf("%d" , &a[i]);
	quick_sort(a , 0 , n-1);
	for(int i=0 ; i<n ; i++)
		printf("%d ", a[i]);
	printf("\n");
}

void quick_sort(int *a , int p , int q)
{
	if(p<q)
	{
		int r = partition(a , p , q);
		quick_sort(a , p , r-1);
		quick_sort(a , r+1 , q);
	}
}


int partition(int *a , int p , int q)
{
	int x = a[q];
	int i = p-1;
	for(int j=p ; j<=q-1 ; j++)	//range of j
	{
		if(a[j] <= x)
		{
			int temp = a[i+1];
			a[i+1] = a[j];
			a[j] = temp;
			i++;
		}
	}
	int temp = a[q];
	a[q] = a[i+1];
	a[i+1] = temp;
	return i+1;
}









