#include <stdio.h>
#include <stdlib.h>

int **root;
float **minES;

void optimalBST(float *p, float *q, int n);
void printTree(int i, int j);

int main()
{
	int n;
	scanf("%d", &n);

	float p[n], q[n+1];

	for(int i=1 ; i<=n ; i++)
		scanf("%f", &p[i]);

	for(int i=0 ; i<=n ; i++)
		scanf("%f", &q[i]);

	minES = (float **)malloc((n+2)*sizeof(float *));
	for(int i=1 ; i<=n+1 ; i++)
		minES[i] = (float *)malloc((n+2)*sizeof(float));

	for(int i=1 ; i<=n+1 ; i++)
		for(int j=0 ; j<=n ; j++)
			minES[i][j] = 0;

	root = (int **)malloc((n+1)*sizeof(int *));
	for(int i=1 ; i<=n ; i++)
		root[i] = (int *)malloc((n+1)*sizeof(int));

	for(int i=1 ; i<=n ; i++)
		for(int j=1 ; j<=n ; j++)
			root[i][j] = 0;

	optimalBST(p, q, n);
}

void optimalBST(float *p, float *q, int n)
{
	float w[n+2][n+2];

	for(int i=1 ; i<=n+1 ; i++)
		for(int j=0 ; j<=n ; j++)
			w[i][j] = 0;

	for(int i=1 ; i<=n+1 ; i++)
	{
		minES[i][i-1] = q[i-1];
		w[i][i-1] = q[i-1];
	}

	for(int l=1 ; l<=n ; l++)
	{
		for(int i=1 ; i<=n-l+1 ; i++)
		{
			float temp;
			int j = i+l-1;
			minES[i][j] = 10000.0;
			w[i][j] = w[i][j-1] + p[j] + q[j];

			for(int r=i ; r<=j ; r++)
			{
				temp = minES[i][r-1] + minES[r+1][j] + w[i][j];
				if(temp < minES[i][j])
				{
					minES[i][j] = temp;
					root[i][j] = r;
				}
			}
		}
	}
	printf("%.2f\n", minES[1][n]);
	printTree(1, n);
	printf("\n");
}

void printTree(int i, int j)
{
	if(i == j)
	{
		printf("(%d)", root[i][j]);
		return;
	}
	if(root[i][j] == j)
	{
		printf("(%d", root[i][j]);
		printTree(i, root[i][j]-1);
		printf("())");
	}
	else if(root[i][j] == i)
	{
		printf("(%d()", root[i][j]);
		printTree(root[i][j]+1, j);
		printf(")");
	}
	else
	{
		printf("(%d", root[i][j]);
		printTree(i, root[i][j]-1);
		printTree(root[i][j]+1, j);
		printf(")");
	}
}































