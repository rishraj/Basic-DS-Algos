#include <stdio.h>
#include <stdlib.h>

int min(int a, int b){ return (a < b ? a : b); }

int **mat;
int **res;

struct point{
	int x;
	int y;
};


void maxZeroSq(int row, int col);
void findMaxVal(int row, int col);
//void printMat(int row, int col);

int main()
{
	int m, n, x;
	scanf("%d %d %d", &m, &n, &x);
	struct point arr[x];

	mat = (int **)malloc(m*sizeof(int *));
	for(int i=0 ; i<m ; i++)
		mat[i] = (int *)malloc(n*sizeof(int));

	for(int i=0 ; i<x ; i++)
		scanf("%d%d", &arr[i].x, &arr[i].y);

	for(int i=0 ; i<m ; i++)
		for(int j=0 ; j<n ; j++)
			mat[i][j] = 1;

	for(int i=0 ; i<x ; i++)
		mat[arr[i].x][arr[i].y] = 0;

//	printMat(m, n);
//	printf("\n");
	maxZeroSq(m, n);

}
void maxZeroSq(int row, int col)
{
	res = (int **)malloc(row*sizeof(int *));
	for(int i=0 ; i<row ; i++)
		res[i] = (int *)malloc(col*sizeof(int));

	for(int i=0 ; i<row ; i++)
		res[i][0] = mat[i][0];
	for(int i=0 ; i<col ; i++)
		res[0][i] = mat[0][i];

	for(int i=1 ; i<row ; i++)
	{
		for(int j=1 ; j<col ; j++)
		{
			if(mat[i][j] == 1)
				res[i][j] = min(res[i-1][j], min(res[i][j-1], res[i-1][j-1])) + 1;
			else
				res[i][j] = 0;
		}
	}
	

/*	for(int i=0 ; i<row ; i++)
	{
		for(int j=0 ; j<col ; j++)
			printf("%d ", res[i][j]);
		printf("\n");
	}*/


	findMaxVal(row, col);
}

void findMaxVal(int row, int col)
{
	int maxVal = res[0][0];

	struct point index;
	index.x = 0;
	index.y = 0;

	for(int i=0 ; i<row ; i++)
	{
		for(int j=0 ; j<col ; j++)
		{
			if(res[i][j] > maxVal)
			{
				maxVal = res[i][j];
				index.x = i;
				index.y = j;
			}
		}
	}
	if(maxVal == 0)
		printf("0\n");
	else
		printf("%d %d %d %d\n", index.x-maxVal+1, index.y-maxVal+1, index.x, index.y);
}








/*void printMat(int row, int col)
{
	for(int i=0 ; i<row ; i++)
	{
		for(int j=0 ; j<col ; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}*/

