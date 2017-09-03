#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXV 1000

struct edge
{
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

struct final{
	int x;
	int y;
};

int n;
int m;
struct edge *edges;

int compare(const void *a, const void *b);
void initialize_graph(struct graph *g, bool directed);
void read_graph(struct graph *g, bool directed);
void insert_edge(struct graph *g, int x, int y, int weight, bool directed);
//void print_graph(struct graph *g);
void removeEdge(struct graph *g, int x1, int y1);
void MST(struct graph *g);
int isConnected(struct graph *g, int v);
void DFS(struct graph *g, int *visited, int v);
int compareStable(const void *a, const void *b);


int main(void)
{
	scanf("%d", &n);
	
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

	edges = malloc((m)*sizeof(struct edge));

	for(int i=0 ; i<m ; i++)
	{
		edges[i].x = x[i];
		edges[i].y = y[i];
		edges[i].weight = weight[i];
	}

	qsort(edges, m, sizeof(struct edge), compare);
	
	struct graph *g;
	g = (struct graph *)malloc(sizeof(struct graph));
	int directed = 0;
	read_graph(g, false);

//	print_graph(g);
	
	MST(g);
	return 0;
}

void MST(struct graph *g)
{
	struct final arr[n-1];
	int j=0;
	for(int i=m-1 ; i>=0 ; i--)
	{
		int weight  = edges[i].weight;
		removeEdge(g, edges[i].x, edges[i].y);
		if(isConnected(g, 1) == 0)
		{
			insert_edge(g, edges[i].x, edges[i].y, weight, false);
			arr[j].x = edges[i].x;
			arr[j].y = edges[i].y;
			j++;
		}
	}
	for(int i=0 ; i<n-1 ; i++)
	{
		if(arr[i].x > arr[i].y)
		{
			int temp = arr[i].x;
			arr[i].x = arr[i].y;
			arr[i].y = temp;
		}
	}
	qsort(arr, n-1, sizeof(struct final), compareStable);
	for(int i=0 ; i<n-1 ; i++)
	{
		printf("%d %d\n", arr[i].x, arr[i].y);
	}
}

int compareStable(const void *a, const void *b)
{
	struct final *item1 = (struct final *)a;
	struct final *item2 = (struct final *)b;
	if(item1->x == item2->x)
		return item1->y - item2->y;
	else
		return item1->x - item2->x;
}

int isConnected(struct graph *g, int v)
{
	int visited[n];
	for(int i=1 ; i<=n ; i++)
		visited[i] = 0;
	DFS(g, visited, v);
	for(int i=1 ; i<=n ; i++)
		if(visited[i] == 0)
			return 0;
	return 1;
}

void DFS(struct graph *g, int *visited, int v)
{
	struct edgenode *temp;
	temp = g->edges[v];
	visited[v] = 1;
	while(temp != NULL)
	{
		v = temp->y;
		if(visited[v] == 0)
			DFS(g, visited, v);
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
		g->degree[i] = 0;
	for(int i=1 ; i<=MAXV ; i++)
		g->edges[i] = NULL;
}

void read_graph(struct graph *g, bool directed)
{
	int e;
	int x, y;

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
*/
int compare(const void *a, const void *b)
{
	struct edge *edge1 = (struct edge *)a;
	struct edge *edge2 = (struct edge *)b;

	return ( edge1->weight - edge2->weight);
}



