#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXV 26

struct edgenode{
	char y;
	int weight;
	struct edgenode *next;
};

struct graph{
	struct edgenode *edges[MAXV];
	int degree[MAXV];
	int invertex[MAXV];
	int nvertices;
	int nedges;
	bool directed;
};

void initializeGraph(struct graph *g);
void readGraph(struct graph *g);
void insertEdge(struct graph *g, char x, char y, int weight, bool directed);
void printGraph(struct graph *g);

int main()
{
	int directed;
	printf("Enter 1 for directed graph and 0 otherwise: ");
	scanf("%d", &directed);
	int m;
	printf("Enter the no. of edges: ");
	scanf("%d", &m);
	printf("Enter the m edges:\n");

	struct graph *g;
	g = (struct graph *)malloc(sizeof(struct graph));

	g->nedges = m;
	g->directed = directed;

	readGraph(g);

	printGraph(g);

}

void initializeGraph(struct graph *g)
{
	for(char i='a' ; i<='z' ; i++)
	{
		g->edges[i] = NULL;
		g->degree[i] = 0;
		g->invertex[i] = 0;
	}
}

void readGraph(struct graph *g)
{
	initializeGraph(g);

	char x, y;

	for(int i=1 ; i<=g->nedges ; i++)
	{
		scanf(" %c %c", &x, &y);		//space before %c is important here
		int weight = 1;
		insertEdge(g, x, y, weight, g->directed);
	}
}

void insertEdge(struct graph *g, char x, char y, int weight, bool directed)
{
	g->invertex[x] = 1;
	g->invertex[y] = 1;
	struct edgenode *temp;
	temp = (struct edgenode *)malloc(sizeof(struct edgenode));
	temp->y = y;
	temp->weight = weight;
	temp->next = g->edges[x];
	g->edges[x] = temp;
	g->degree[x]++;

	if(directed == false)
		insertEdge(g, y, x, weight, true);
}

void printGraph(struct graph *g)
{
	for(char i='a' ; i<='z' ; i++)
	{
		if(g->invertex[i] == 1)
		{
			struct edgenode *temp;
			temp = g->edges[i];
			printf("Degree = %d %c:", g->degree[i], i);
			while(temp != NULL)
			{
				printf(" %c", temp->y);
				temp = temp->next;
			}
			printf("\n");
		}
	}
}



