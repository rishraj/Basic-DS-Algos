#include <stdio.h>


int main()
{
	int n,carry=0;
	scanf("%d",&n);
	int a[n] , b[n];
	for(int i=0 ; i<n ; i++)
		scanf("%d" , &a[i]);
	for(int i=0 ; i<n ; i++)
		scanf("%d" , &b[i]);
	int s[n+1];
	for(int i=n-1 ; i>=0 ; i--)
	{
		if(a[i] == 1 && b[i] == 1 && carry == 1)
		{
			s[i+1] = 1;
			carry = 1;
		}
		else if((a[i]==1 || b[i]==1) && carry == 1)
		{
			s[i+1] = 0;
			carry = 1;
		}
		else if(carry == 1)
		{
			s[i+1] = 1;
			carry = 0;
		}
		else if((a[i]==1 && b[i]==1) && carry == 0)
		{
			s[i+1] = 0;
			carry = 1;
		}
		else if((a[i]==1 || b[i]==1) && carry == 0)
		{
			s[i+1] = 1;
			carry = 0;
		}
		else
		{
			s[i+1] = 0;
			carry = 0;
		}
	}
	s[0] = carry;
	for (int i = 0; i < n+1; ++i)
	{
		printf("%d", s[i]);
	}
	printf("\n");


}