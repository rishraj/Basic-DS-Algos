#include <stdio.h>


int main()
{
	int n,min,temp,c;
	scanf("%d",&n);
	int a[n];
	for(int i=0 ; i<n ; i++)
		scanf("%d",&a[i]);
	for(int j=0 ; j<n-1 ; j++)
	{
		min = a[j];
		c = j;
		for(int i=j+1 ; i<n ; i++)
		{
			if(a[i]<min)
			{
				min = a[i];
				c = i;
			}
		}
		temp = a[c];
		a[c] = a[j];
		a[j] = temp;
	}
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}