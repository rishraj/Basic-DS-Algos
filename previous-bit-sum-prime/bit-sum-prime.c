#include <stdio.h>
#include <math.h>

int check_bsp(long long int n);
int check_prime(int n);

int main()
{
	long long int n;
	scanf("%lld" , &n);
	for(long long int i=1 ; i<=n ; i++)
	{
		int m=check_bsp(i);
		if(m == 1)
				printf("%lld\n", i);
		else
			continue;
	}
	
	return 0;
}

int check_bsp(long long int n)
{
	long long int k =0;
	int s=0 , sum=0 , c;
	while(n != 0)
	{
		c = n%2;
		k = ((pow(10,s)*c) + k);
		n = n/2;
		s++;
		sum = sum + c;
	}
	int m=check_prime(sum);
	if(m == 1)
		return 1;
	else
		return 0;
}

int check_prime(int n)
{
	int c=0 , s=0;
	for(int i=1 ; i<=n ; i++)
	{
		if(n%i == 0)
			c++;
	}
	if(c == 2)
		return 1;
	else
		return 0;
}














