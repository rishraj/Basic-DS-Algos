#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXV 1000

struct edgenode{
	int y;
	int weight;
	struct edgenode *next;
};

struct graph{
	struct edgenode *edges[MAXV+1];
	int degree[MAXV+1];
	int nvertices;
	int nedges;
	bool directed;
};

void initialize_graph(struct graph *g, bool directed);
void read_graph(struct graph *g, bool directed);
void insert_edge(struct graph *g, int x, int y, bool directed);
void print_graph(struct graph *g);


int main()
{
	struct graph *g;
	g = (struct graph *)malloc(sizeof(struct graph));

	int directed;
	printf("Input 1 for directed and 0 for undirected : ");
	scanf("%d", &directed);
	if(directed == 1)
		read_graph(g, true);
	else
		read_graph(g, false);

	print_graph(g);
}

void initialize_graph(struct graph *g, bool directed)
{
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;

	for(int i=1 ; i<=MAXV ; i++)
		g->degree[i] = 0;
	for(int i=1 ; i<=MAXV ; i++)
		g->edges[i] = NULL;
}

void read_graph(struct graph *g, bool directed)
{
	int e;
	int x, y;

	initialize_graph(g, directed);

	scanf("%d%d", &(g->nvertices), &e);

	for(int i=1 ; i<=e ; i++)
	{
		scanf("%d%d", &x, &y);
		insert_edge(g, x, y, directed);
	}
}

void insert_edge(struct graph *g, int x, int y, bool directed)
{
	struct edgenode *temp;
	temp = (struct edgenode *)malloc(sizeof(struct edgenode));
	temp->y = y;
	temp->weight = 1;
	temp->next = g->edges[x];
	g->edges[x] = temp;
	g->degree[x]++;

	if(directed == false)
		insert_edge(g, y, x, true);
	else
		g->nedges++;
}

void print_graph(struct graph *g)
{
	struct edgenode *temp;

	for(int i=1 ; i<=g->nvertices ; i++)
	{
		printf("degree = %d, %d:",g->degree[i], i);
		temp = g->edges[i];
		while(temp != NULL)
		{
			printf(" %d", temp->y);
			temp = temp->next;
		}
		printf("\n");
	}
}
















