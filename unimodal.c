#include <stdio.h>

int unimodal(int *a , int p , int q);

int main()
{
	int n;
	scanf("%d" , &n);
	int a[n];
	for(int i=0 ; i<n ; i++)
		scanf("%d" , &a[i]);
	printf("%d\n" , unimodal(a , 0 , n-1));
}

int unimodal(int *a , int p , int q)
{
	if(p == q)
	{
		return a[p];
	}
	int r = (p+q)/2;
	if(a[r] < a[r-1])
		return unimodal(a , p , r-1);
	else if(a[r] < a[r+1])
		return unimodal(a , r+1 , q);
	else 
		return a[r];
}






