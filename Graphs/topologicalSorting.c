#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXV 200

char stack[2000];
int stackCounter = 0;
char *DS = stack;

bool processed[MAXV+1];
bool discovered[MAXV+1];
char parent[MAXV+1];
int entry_time[MAXV+1];
int exit_time[MAXV+1];
int time = 0;
int impossible = 0;

struct edgenode{
	char y;
	int weight;
	struct edgenode *next;
};

struct graph{
	struct edgenode *edges[MAXV];
	int degree[MAXV+1];
	int invertex[MAXV+1];
	int nvertices;
	int nedges;
	bool directed;
};

struct word{
	char name[200];
	int length;
};

void push(char *stack, char c);
char pop(char *stack);
int empty(char *stack);
int full(char *stack);
void initializeGraph(struct graph *g, bool directed);
void readGraph(struct graph *g);
void insertEdge(struct graph *g, char x, char y, int weight, bool directed);
void printGraph(struct graph *g);
void dfs(struct graph *g, char v);
void process_vertex_early(char v);
void process_edge(char x, char y);
void process_vertex_late(char v);
int edge_classification(char x, char y);
void topologicalSort(struct graph *g);

void toSmall(char *name, int length)
{
	for(int i=0 ; i<length ; i++)
	{
		if(name[i]>='A' && name[i]<='Z')
			name[i] = name[i] + ('a'-'A');
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	struct word names[n];
	for(int i=0 ; i<n ; i++)
	{
		scanf("%s", names[i].name);
		names[i].length = strlen(names[i].name);
		toSmall(names[i].name, names[i].length);
	}

	struct graph *g;
	g = (struct graph *)malloc(sizeof(struct graph));

	initializeGraph(g, true);

	for(int i=0 ; i<=n-2 ; i++)
	{
		if(names[i].length <= names[i+1].length)
		{
			int j;
			for(j=0 ; j<names[i].length ; j++)
			{
				if(names[i].name[j] != names[i+1].name[j])
				{
					insertEdge(g, names[i].name[j], names[i+1].name[j], 1, true);
					break;
				}
			}
		}
		else
		{
			int j;
			for(j=0 ; j<names[i+1].length ; j++)
			{
				if(names[i].name[j] != names[i+1].name[j])
				{
					insertEdge(g, names[i].name[j], names[i+1].name[j], 1, true);
					break;
				}
			}
			if(j == names[i+1].length)
			{
				printf("IMPOSSIBLE\n");
				return 0;
			}
		}
	}

//	printGraph(g);

	topologicalSort(g);
	
	return 0;
}

void topologicalSort(struct graph *g)
{
	for(char i='a' ; i<='z' ; i++)
	{
		if(g->invertex[i] == 1)
		{
			if(discovered[i] != true)
				dfs(g, i);
		}
	}
	if(impossible == 0)
	{
	/*	while(empty(DS)!=1)
		{
			char y=pop(DS);
			printf("%c ", y);
		}
		printf("\n");*/

		char alpha[27];
		for(char i='a' ; i<='z' ; i++)
		{
			alpha[i] = 0;
		}

		while(empty(DS)!=1)
		{
			char y=pop(DS);
			for(char i='a' ; i<y ; i++)
			{
				if(alpha[i]!=1 && g->invertex[i]!=1)
				{
					alpha[i] = 1;
					printf("%c", i);
				}
			}
			printf("%c", y);
		}
		for(char i='a' ; i<='z' ; i++)
			if(alpha[i] != 1 && g->invertex[i] != 1)
				printf("%c", i);
		printf("\n");
	}
	else
		printf("IMPOSSIBLE\n");
}


void dfs(struct graph *g, char v)
{
	if(processed[v] == true)
		return;

	struct edgenode *temp;
	char y;

	discovered[v] = true;
	time = time+1;
	entry_time[v] = time;

	process_vertex_early(v);

	temp = g->edges[v];
	while(temp != NULL)
	{
		char y = temp->y;
		if(discovered[y] != true)
		{
			parent[y] = v;
			process_edge(v, y);
			dfs(g, y);
		}
		else if((!processed[y] && (parent[v] != y)) || (g->directed))
			process_edge(v, y);

		temp = temp->next;
	}
	process_vertex_late(v);

	time = time+1;
	exit_time[v] = time;

	processed[v] = true;
}

void process_vertex_early(char v)
{
	
}

void process_edge(char x, char y)
{
	int class;

	class = edge_classification(x, y);

	if(class == 2)
		impossible = 1;
}

void process_vertex_late(char v)
{
	push(DS, v);
}

int edge_classification(char x, char y)
{
	if(parent[y] == x) return 1; //TREE
	if(discovered[y] && !processed[y]) return 2; //BACK
	if(processed[y] && (entry_time[y] > entry_time[x])) return 3; //FORWARD
	if(processed[y] && (entry_time[y] < entry_time[x])) return 4; //CROSS
	return -1;
}

void initializeGraph(struct graph *g, bool directed)
{
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;

	for(char i='a' ; i<='z' ; i++)
	{
		g->degree[i] = 0;
		g->edges[i] = NULL;
		g->invertex[i] = 0;
		processed[i] = false;
		discovered[i] = false;
		parent[i] = (char)1;
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

	g->nedges++;
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

void push(char *stack, char c)
{
	stack[stackCounter] = c;
	stackCounter++;
}

char pop(char *stack)
{
	stackCounter--;
	return stack[stackCounter];
}

int empty(char *stack)
{
	if(stackCounter == 0)
		return 1;
	else 
		return 0;
}

int full(char *stack)
{
	if(stackCounter == 1000)
		return 1;
	else 
		return 0;
}













