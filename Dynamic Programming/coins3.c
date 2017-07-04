#include <stdio.h>
#include <stdlib.h>

int maxCoins(int row, int col);
int max(int a, int b);
void backtrack(int i, int j);

int **maxCoin;
int **coin;

int main()
{
	int row,col;
	printf("Enter the number of rows: ");
	scanf("%d", &row);
	printf("Enter the number of columns: ");
	scanf("%d", &col);
	coin = (int **)malloc(row*sizeof(int *));
	for(int i=0 ; i<row ; i++)
		coin[i] = (int *)malloc((col)*sizeof(int));
	printf("Enter the matrix:\n");
	for(int i=0 ; i<row; i++)
		for(int j=0 ; j<col ; j++)
			scanf("%d", &coin[i][j]);
	maxCoin = (int **)malloc((row+1)*sizeof(int *));
	for(int i=0 ; i<=row ; i++)
		maxCoin[i] = (int *)malloc((col+1)*sizeof(int));
	for(int i=0 ; i<=row ; i++)
		maxCoin[i][0] = 0;
	for(int i=0 ; i<=col ; i++)
		maxCoin[0][i] = 0;
	printf("Maximum no. of coins = %d\n", maxCoins(row, col));
	printf("Path taken : ");
	backtrack(row, col);
	printf("\n");
	
}

int maxCoins(int row, int col)
{
	for(int i=1 ; i<=row ; i++)
		for(int j=1 ; j<=col ; j++)
			maxCoin[i][j] = max(maxCoin[i-1][j], maxCoin[i][j-1]) + coin[i-1][j-1];
	return maxCoin[row][col];
}

int max(int a, int b)
{
	if(a>b)
		return a;
	else 
		return b;
}

void backtrack(int i, int j)
{
	int row = i;
	int col = j;
	char path[i+j];
	int c = 0;
	while(i>1 && j>1)
	{
		if(maxCoin[i][j] == maxCoin[i-1][j] + coin[i-1][j-1])
		{
			path[c] = 'D';
			c++;
			i--;
		}
		else if(maxCoin[i][j] == maxCoin[i][j-1] + coin[i-1][j-1])
		{
			path[c] = 'R';
			c++;
			j--;
		}
	}
	for(int i=row+col-1 ; i>0 ; i--)
	{
		printf("%c->", path[i]);
	}
}























