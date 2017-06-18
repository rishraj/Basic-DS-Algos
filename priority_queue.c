#include <stdio.h>

int left(int i);
int right(int i);
void heapify(int *a , int i , int n);
void buildheap(int *a , int n);
int maximum(int *a);
int extract_maximum(int *a);
void increase_val(int *a , int i , int val);
void insert_val(int *a , int val);

int n;

int main()
{

	scanf("%d" , &n);
	int a[n];
	for(int i=1 ; i<=n ; i++)
		scanf("%d" , &a[i]);
	buildheap(a , n);
}

int left(int i)
{
	return (2*i);
}

int right(int i)
{
	return (2*i)+1;
}

int parent(int i)
{
	return (i/2);
}


void heapify(int *a , int i , int n)
{
	int l = left(i);
	int r = right(i);
	int largest = i;
	if(l<=n && a[l]>a[largest])
		largest = l;
	if(r<=n && a[r]>a[largest])
		largest = r;
	if(largest != i)
	{
		int temp = a[i];
		a[i] = a[largest];
		a[largest] = temp;
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

int maximum(int *a)
{
	return a[1];
}

int extract_maximum(int *a)
{
	int x = a[1];
	int temp = a[n];
	a[n] = a[1];
	a[1] = temp;
	n = n-1;
	heapify(a , 1 , n);
	return x;
}

void increase_val(int *a , int i , int val)
{
	if(a[i] >= val)
		printf("Error\n");
	else
	{
		a[i] = val;
		while(i>=2 && a[parent(i)] < a[i])
		{
			int temp = a[i];
			a[i] = a[parent(i)];
			a[parent(i)] = temp;
			i = parent(i);
		}
	}
}

void insert_val(int *a , int val)
{
	n = n+1;
	a[n] = val-1;
	increase_val(a , n , val);
}

















