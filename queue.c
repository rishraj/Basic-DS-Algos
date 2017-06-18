#include <stdio.h>
#include <stdlib.h>

void enqueue(int d);
int dequeue();
int full();
int empty();

int n;
int *a;
int tail;
int head;


int main()
{
//	scanf("%d" , &n);
	n=4;
	a = malloc(n*sizeof(int));
}

void enqueue(int d)
{
	if(full()!=1)
	{
		a[tail] = d;
		tail = (tail+1)%n;
	}
	else
		printf("Array is Full!\n");
}

int dequeue()
{
	if(empty()!=1)
	{
		int x = a[head];
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
























