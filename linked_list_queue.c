#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *next;
};

struct node * new_node(int data);
void enqueue(struct node *newnode);
int dequeue();
void printQueue(struct node *head);

struct node *tail = NULL;
struct node *head = NULL;


int main()
{
	int n;
	scanf("%d", &n);
	for(int i=0 ; i<n ; i++)
	{
		int data;
		scanf("%d", &data);
		struct node *temp = new_node(data);
		enqueue(temp);
	}
}

struct node * new_node(int data)
{
	struct node *temp;
	temp = (struct node *)calloc(1, sizeof(struct node));
	temp->data = data;
	return temp;
}

void enqueue(struct node *newnode)
{
	if(tail == NULL)
	{
		tail = newnode;
		head = newnode;
	}
	else
	{
		tail->next = newnode;
		tail = newnode;
	}
}

int dequeue()
{
	if(head == NULL)
	{
		printf("Queue is empty\n");
		return 0;
	}
	else
	{
		struct node *temp = head;
		int x = head->data;
		head = head->next;
		free(temp);
		return x;
	}
}

void printQueue(struct node *head)
{
	if(head != NULL)
	{
		struct node *temp = head;
		while(temp != NULL)
		{
			printf("%d ", temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}







