#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXV 1000


int n, m;
struct edge *edges;


struct edge{
	int x;
	int y;
	int weight;
};

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

void dijkstra(struct graph *g, int s, int d);
void initialize_graph(struct graph *g, bool directed);
void read_graph(struct graph *g, bool directed);
void insert_edge(struct graph *g, int x, int y, int weight, bool directed);
//void print_graph(struct graph *g);

int main()
{
	int s,d;
	scanf("%d%d%d", &n, &s, &d);
	int x[100];
	int y[100];
	int weight[100];

	int i=0;

	while(scanf("%d", &x[i]) != EOF)
	{
		scanf("%d%d", &y[i], &weight[i]);
		i++;
	}

	m = i;

	edges = malloc(m*sizeof(struct edge));

	for(int i=0 ; i<m ; i++)
	{
		edges[i].x = x[i];
		edges[i].y = y[i];
		edges[i].weight = weight[i];
	}


	struct graph *g;
	g = (struct graph *)malloc(sizeof(struct graph));
	int directed = 1;
	read_graph(g, true);

//	print_graph(g);

	dijkstra(g, s, d);
}

void dijkstra(struct graph *g, int s, int d)
{
	struct edgenode *temp;
	bool intree[MAXV+1];
	int distance[MAXV+1];
	int parent[MAXV+1];
	int v;
	int w;
	int weight;
	int dist;

	for(int i=0 ; i<g->nvertices ; i++)
	{
		intree[i] = false;
		distance[i] = 10000;
		parent[i] = -1;
	}

	distance[s] = 0;
	v = s;

	while(intree[v] == false)
	{
		intree[v] = true;
		temp = g->edges[v];

		while(temp != NULL)
		{
			w = temp->y;
			weight = temp->weight;
			if(distance[w] > distance[v] + weight)
			{
				distance[w] = distance[v] + weight;
				parent[w] = v;
			}
			temp = temp->next;
		}

		v=0;
		dist = 10000;
		for(int i=0 ; i<g->nvertices ; i++)
		{
			if(intree[i] == false && (dist > distance[i]))
			{
				dist = distance[i];
				v = i;
			}
		}

//		printf("Minimum distance for %d from %d is %d and it's parent is %d\n", v, s, dist, parent[v]);

		if(v == d)
		{
			int temp1[v+1];
			int c=0;
			printf("\n%d\n", dist);
			while(v != -1)
			{
				temp1[c] = v;
				c++;
				v = parent[v];
			}
			for(int i=c-1 ; i>=0 ; i--)
				printf("%d ", temp1[i]);
			printf("\n");
			break;
		}
	}



}







void initialize_graph(struct graph *g, bool directed)
{
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;

	for(int i=0 ; i<=MAXV ; i++)
		g->degree[i] = 0;
	for(int i=0 ; i<=MAXV ; i++)
		g->edges[i] = NULL;
}

void read_graph(struct graph *g, bool directed)
{
	initialize_graph(g, directed);

	g->nvertices = n;

	for(int i=0 ; i<m ; i++)
	{
		insert_edge(g, edges[i].x, edges[i].y, edges[i].weight, directed);
	}
}

void insert_edge(struct graph *g, int x, int y, int weight, bool directed)
{
	struct edgenode *temp;
	temp = (struct edgenode *)malloc(sizeof(struct edgenode));
	temp->y = y;
	temp->weight = weight;
	temp->next = g->edges[x];
	g->edges[x] = temp;
	g->degree[x]++;

	if(directed == false)
		insert_edge(g, y, x, weight, true);
	else
		g->nedges++;
}

/*void print_graph(struct graph *g)
{
	struct edgenode *temp;

	for(int i=0 ; i<g->nvertices ; i++)
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
*/












