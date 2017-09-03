#include <stdio.h>
#include <stdlib.h>

void findSink(int n, int adjMat[][n]);
void checkSink(int n, int adjMat[][n], int x);

int main()
{
	int n;

	printf("Enter the no. of Vertices : ");
	scanf("%d", &n);

	int adjMat[n][n];
	printf("Enter the V X V matrix :\n");
	for(int i=0 ; i<n ; i++)
		for(int j=0 ; j<n ; j++)
			scanf("%d", &adjMat[i][j]);

	findSink(n, adjMat);
}

void findSink(int n, int adjMat[][n])
{
	int isSink[n];
	for(int i=0 ; i<n ; i++)
		isSink[i] = 1;

	int i = 0;
	int j = 0;

	while(i<n && j<n)
	{
		if(i == j)
			i++;
		else
		{
			if(adjMat[i][j] == 0)
			{
				isSink[j] = 0;
				j++;
			}
			else
			{
				isSink[i] = 0;
				i++;
			}
		}
	}

	for(int i=0 ; i<n ; i++)
	{
		if(isSink[i] == 1)
			checkSink(n, adjMat, i);
	}
}

void checkSink(int n, int adjMat[][n], int x)
{
	int rowSum = 0;
	int colSum = 0;

	for(int i=0 ; i<n ; i++)
	{
		rowSum = rowSum + adjMat[x][i];
		colSum = colSum + adjMat[i][x];
	}

	if(rowSum == 0 && colSum == n-1)
		printf("Sink : Vertex %d\n", x+1);
	else
		printf("No sink present\n");	
}

