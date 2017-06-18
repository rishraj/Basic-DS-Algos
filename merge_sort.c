#include <stdio.h>
#include <math.h>

void merge_sort(int *a , int p , int r);
void merge(int *a , int p , int s , int q);

int main()
{
	int n;
	scanf("%d" , &n);			//size of the array
	int a[n];
	for(int i=0 ; i<n ; i++)
		scanf("%d" , &a[i]);
	merge_sort(a ,0, n-1);			//calling the merge_sort function
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void merge_sort(int *a , int p , int q)
{
	if(p == q)						//base case of recursion
		return;
	int r = floor((p+q)/2);			//finding approx midpoint of array
	merge_sort(a , p , r);			//sorting left half
	merge_sort(a , r+1 , q);		//sorting right half
	merge(a , p , r , q);			//merging the two
}


void merge(int *a , int p , int s , int q)
{
	int l1,r1;
	int m=s-p+1;
	int n=q-s;
	int l[m+1];							//1 extra size taken to accomodate sentinels
	int r[n+1];
	for(int i=0 ; i<m ; i++)
		l[i] = a[p+i];
	l[m] = 10000;			//sentinel
	for(int i=0 ; i<n ; i++)
		r[i] = a[s+1+i];
	r[n] = 10000;
	l1 = 0;
	r1 = 0;
	for(int i=p ; i<=q ; i++)        //be cautious while doing this step(it won't be from (0 to size of a))
	{
		if(l[l1]<=r[r1])			//sliding the minimum of two arrays in the original array one by one
		{
			a[i] = l[l1];
			l1++;
		}
		else
		{
			a[i] = r[r1];
			r1++;
		}
	}
}

