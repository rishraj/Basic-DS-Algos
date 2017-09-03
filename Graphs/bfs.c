#include <stdio.h>
#include <stdlib.h>

void BFS(int n, int adjMat[][n], int s);
void enqueue(int d);
int dequeue();
int full();
int empty();

int n = 100;
int Q[100];
int tail = 0;
int head = 0;

int main()
{
	int V;
	scanf("%d", &V);

	int adjMat[V+1][V+1];

	for(int i=1 ; i<=V ; i++)
		for(int j=1 ; j<=V ; j++)
			scanf("%d", &adjMat[i][j]);

	int s;
	scanf("%d", &s);

	BFS(V, adjMat, s);
}


void BFS(int V, int adjMat[][V], int s)
{
	int dist[V+1];
	for(int i=1 ; i<=V ; i++)
		dist[i] = 10000;
	enqueue(s);
	dist[s] = 0;
	while(!empty())
	{
		int v = dequeue();
		for(int i=1 ; i<=V ; i++)
		{
			if(adjMat[v][i] == 1 || adjMat[i][v] == 1)
			{
				if(dist[i] == 10000)
				{
					dist[i] = dist[v] + 1;
					enqueue(i);
				}
			}
		}
	}

	for(int i=1 ; i<=V ; i++)
	{
		printf("Distance of %d from %d is %d\n", i, s, dist[i]);
	}
}


//******************** Queue *******************************
void enqueue(int d)
{
	if(full()!=1)
	{
		Q[tail] = d;
		tail = (tail+1)%n;
	}
	else
		printf("Array is Full!\n");
}

int dequeue()
{
	if(empty()!=1)
	{
		int x = Q[head];
		head = (head+1)%n;
		return x;
	}
	else
	{
		printf("Array is Empty!\n");
		return 0;
	}
}

int full()
{
	if((head - tail) == 1)
		return 1;
	else if(head == 0 && tail == n-1)
		return 1;
	else
		return 0;
}

int empty()
{
	if(tail == head)
		return 1;
	else
		return 0;
}


















