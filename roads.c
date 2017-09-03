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

struct road{
	int x;
	int y;
	int weight;
	struct road *next;
};

void initialize_graph(struct graph *g, bool directed);
void read_graph(struct graph *g, bool directed);
void insert_edge(struct graph *g, int x, int y, int weight, bool directed);
void print_graph(struct graph *g);
void removeEdge(struct graph *g, int x1, int y1);
int isConnected(struct graph *g, int v, int type);
void DFSfor1(struct graph *g, int *visited, int v);
void DFSfor2(struct graph *g, int *visited, int v);
void printRoad(struct road *temp);

int main()
{
	int t;
	scanf("%d", &t);

	int result[t];

	struct graph *g;
	g = (struct graph *)malloc(sizeof(struct graph));

	for(int k=0 ; k<t ; k++)
	{
		int m, n, x, y, weight;

		scanf("%d%d", &n, &m);

		struct road *roads1 = NULL;
		struct road *roads2 = NULL;
		struct road *roads3 = NULL;

		initialize_graph(g, false);
		g->nvertices = n;
		g->nedges = m;

		for(int i=0 ; i<m ; i++)
		{
			scanf("%d%d%d", &x, &y, &weight);
			insert_edge(g, x, y, weight, g->directed);

			struct road *temp;
			temp = (struct road *)malloc(sizeof(struct road));
			temp->x = x;
			temp->y = y;
			temp->weight = weight;

			if(temp->weight == 1)
			{
				temp->next = roads1;
				roads1 = temp;
			}
			else if(temp->weight == 2)
			{
				temp->next = roads2;
				roads2 = temp;
			}
			else
			{
				temp->next = roads3;
				roads3 = temp;
			}
		}

//		print_graph(g);
//		printRoad(roads1);
//		printRoad(roads2);
//		printRoad(roads3);

		int c1=0;
		struct road *temp = roads1;
		while(temp != NULL)
		{
			int x1 = temp->x;
			int y1 = temp->y;
			int weight = temp->weight;

			removeEdge(g, x1, y1);

//			print_graph(g);

			if(isConnected(g, x1, 1) == 0)
				insert_edge(g, x1, y1, weight, g->directed);
			else
				c1++;

			temp = temp->next;
		}

	//	printRoad(roads1);
	//	printf("c1 = %d\n", c1);

		int c2=0;
		temp = roads2;
		while(temp != NULL)
		{
			int x1 = temp->x;
			int y1 = temp->y;
			int weight = temp->weight;

			removeEdge(g, x1, y1);

//			print_graph(g);

			if(isConnected(g, x1, 2) == 0)
				insert_edge(g, x1, y1, weight, g->directed);
			else
				c2++;

			temp = temp->next;
		}

		int c3=0;
		temp = roads3;
		while(temp != NULL)
		{
			int x1 = temp->x;
			int y1 = temp->y;
			int weight = temp->weight;

			removeEdge(g, x1, y1);

//			print_graph(g);

			if(isConnected(g, x1, 1) == 0 || isConnected(g, x1, 2) == 0)
				insert_edge(g, x1, y1, weight, g->directed);
			else
				c3++;

			temp = temp->next;
		}

//		printf("%d\n", c1+c2+c3);

		result[k] = c1+c2+c3;
	}
	for(int k=0 ; k<t ; k++)
		printf("%d\n", result[k]);
}

int isConnected(struct graph *g, int v, int type)
{
	int n = g->nvertices;
	int visited[n+1];
	for(int i=1 ; i<=n ; i++)
		visited[i] = 0;

	if(type == 1)
		DFSfor1(g, visited, v);
	else if(type == 2)
		DFSfor2(g, visited, v);

	for(int i=1 ; i<=n ; i++)
		if(visited[i] == 0)
			return 0;
	return 1;
}

void DFSfor1(struct graph *g, int *visited, int v)
{
//	printf("DFS1-vertex-%d\n", v);
	visited[v] = 1;

	struct edgenode *temp;
	temp = g->edges[v];

	while(temp != NULL)
	{
		if(temp->weight != 2)
		{
			v = temp->y;
			if(visited[v] == 0)
				DFSfor1(g, visited, v);
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
}

void DFSfor2(struct graph *g, int *visited, int v)
{
//	printf("DFS2-vertex-%d\n", v);
	visited[v] = 1;

	struct edgenode *temp;
	temp = g->edges[v];

	while(temp != NULL)
	{
		if(temp->weight != 1)
		{
			v = temp->y;
			if(visited[v] == 0)
				DFSfor2(g, visited, v);
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
}

void removeEdge(struct graph *g, int x1, int y1)
{
	struct edgenode *temp1 = g->edges[x1];
	if(temp1->y == y1)
		g->edges[x1] = temp1->next;
	else
	{
		struct edgenode *temp2 = temp1;
		while(temp1->y != y1)
		{
			temp2 = temp1;
			temp1 = temp1->next;
		}
		if(temp2->next->next == NULL)
			temp2->next = NULL;
		else
			temp2->next = temp2->next->next;
	}
	struct edgenode *temp3 = g->edges[y1];
	if(temp3->y == x1)
		g->edges[y1] = temp3->next;
	else
	{
		struct edgenode *temp4 = temp3;
		while(temp3->y != x1)
		{
			temp4 = temp3;
			temp3 = temp3->next;
		}
		if(temp4->next->next == NULL)
			temp4->next = NULL;
		else
			temp4->next = temp4->next->next;
	}
}


void initialize_graph(struct graph *g, bool directed)
{
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;

	for(int i=1 ; i<=MAXV ; i++)
	{
		g->degree[i] = 0;
		g->edges[i] = NULL;
	}
}

/*void read_graph(struct graph *g, bool directed)
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
}*/

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

void printRoad(struct road *temp)
{
	while(temp != NULL)
	{
		printf("%d %d type-%d\n", temp->x, temp->y, temp->weight);
		temp = temp->next;
	}
}












