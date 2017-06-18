#include <stdio.h>

int left(int i);
int right(int i);
void heapify(int *a , int i , int n);
void buildheap(int *a , int n);
void heapsort(int *a , int n);

int main()
{
	int n;
	scanf("%d" , &n);
	int a[n];
	for(int i=1 ; i<=n ; i++)
		scanf("%d" , &a[i]);
	heapsort(a , n);
	for(int i=1 ; i<=n ; i++)
		printf("%d ", a[i]);
	printf("\n");
}

void heapsort(int *a , int n)
{
	buildheap(a , n);
	for(int i = n ; i>=2 ; i--)
	{
		int temp = a[i];
		a[i] = a[1];
		a[1] = temp;
		heapify(a , 1 , i-1);
	}
}

int left(int i)
{
	return (2*i);
}

int right(int i)
{
	return (2*i)+1;
}

void heapify(int *a , int i , int n)
{
	if(i>(n/2))
		return;
	int l = left(i);
	int r =  right(i);
	int largest = i;
	if(l<=n && a[l]>a[largest])
		largest = l;
	if(r<=n && a[r]>a[largest])
		largest = r;
	if(a[largest] != a[i])
	{
		int temp = a[largest];
		a[largest] = a[i];
		a[i] = temp;
		heapify(a , largest , n);
	}
}

void buildheap(int *a , int n)
{
	for(int i=(n/2) ; i>=1 ; i--)
	{
		heapify(a , i , n);
	}
}













