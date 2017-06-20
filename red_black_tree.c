#include <stdio.h>
#include <stdlib.h>


//making the structure the nodes of the tree
struct node{
	int data;
	int colour;
	struct node *parent;
	struct node *leftChild;
	struct node *rightChild;
};

//--------- function declarations ---------------------------------
struct node *newNode(int data);
void insert(int data);
void balance(struct node *temp);
void leftRotate(struct node *x);
void rightRotate(struct node *x);
void pre_fix_tour(struct node *x);
void visit(struct node *x);
void inorder_tree_walk(struct node *x);
//----------------------------------------------------------------

//root declaration
struct node *root = NULL;

int main()
{
	int n;
	scanf("%d", &n);
	for(int i=0 ; i<n ; i++)
	{
		int data;
		scanf("%d", &data);
		insert(data);
	}
	pre_fix_tour(root);
//	inorder_tree_walk(root);

}

//function created to explore inorder traversal in the tree.
/*void inorder_tree_walk(struct node *x)
{
	if(x != NULL)
	{
		inorder_tree_walk(x->leftChild);
		printf("%d\n", x->data);
		inorder_tree_walk(x->rightChild);
	}
}*/

//----------pre_fix_tour routine---------------------------------
void pre_fix_tour(struct node *x)
{
	if(x == NULL)
		printf("Empty Tree\n");
	else
		visit(x);
}

//-------------visit routine-------------------------------------
void visit(struct node *x)
{
	if(x != NULL)
	{
		visit(x->leftChild);
		if(x->colour == 0 && x->parent != NULL)
			printf("%d,Black,%d\n", x->data, x->parent->data);
		else if(x->colour == 1 && x->parent != NULL)
			printf("%d,Red,%d\n", x->data, x->parent->data);
		else
			printf("%d,Black\n", x->data);
		visit(x->rightChild);
	}
}

//---------------function to make a new node-----------------------
struct node *newNode(int data)
{
	struct node *temp;
	temp = (struct node *)malloc(1*sizeof(struct node));
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	temp->parent = NULL;
	temp->data = data;
	temp->colour = 1;
	return temp;
}

//---------function for insering and node in the tree-------------
void insert(int data)
{
	struct node *temp = newNode(data);
	if(root == NULL)
		root = temp;
	else
	{
		struct node *x = root;
		struct node *y;
		while(x != NULL)
		{
			y = x;
			if(data >= x->data)
				x = x->rightChild;
			else
				x = x->leftChild;
		}
		if(data >= y->data)
		{
			y->rightChild = temp;
			temp->parent = y;
		}
		else
		{
			y->leftChild = temp;
			temp->parent = y;
		}
	}
	balance(temp);
}

//-------------------balancing the tree----------------------------
void balance(struct node *x)
{
	while(x->parent != NULL && x->parent->parent != NULL)
	{
		//if parent is also red
		if(x->parent->colour == 1)
		{
			//if parent is the left child of it's parent
			if(x->parent == x->parent->parent->leftChild)
			{
				//uncle is not null
				if(x->parent->parent->rightChild != NULL)
				{
					//uncle is red
					if(x->parent->parent->rightChild->colour == 1)
					{
						x->parent->colour = 0;
						x->parent->parent->rightChild->colour = 0;
						x->parent->parent->colour = 1;
						x = x->parent->parent;
					}
					//uncle is black
					else
					{
						//node is near the uncle
						if(x == x->parent->rightChild)
						{
							x = x->parent;
							leftRotate(x);
						}
						//node is far from the uncle
						if(x->parent != NULL)
							x->parent->colour = 0;
						if(x->parent->parent != NULL)
						{
							x->parent->parent->colour = 1;
							rightRotate(x->parent->parent);
						}
					}
				}
				//if uncle is null, consider it to be black
				else
				{
					if(x == x->parent->rightChild)
					{
						x = x->parent;
						leftRotate(x);
					}
					if(x->parent != NULL)
						x->parent->colour = 0;
					if(x->parent->parent != NULL)
					{
						x->parent->parent->colour = 1;
						rightRotate(x->parent->parent);
					}
				}
			}
			//almost similar computations if parent is the right child of it's parent
			else
			{
				if(x->parent->parent->leftChild != NULL)
				{
					if(x->parent->parent->leftChild->colour == 1)
					{
						x->parent->colour = 0;
						x->parent->parent->leftChild->colour = 0;
						x->parent->parent->colour = 1;
						x = x->parent->parent;
					}
					else
					{
						if(x == x->parent->leftChild)
						{
							x = x->parent;
							rightRotate(x);
						}
						if(x->parent != NULL)
							x->parent->colour = 0;
						if(x->parent->parent != NULL)
						{
							x->parent->parent->colour = 1;
							leftRotate(x->parent->parent);
						}
					}
				}
				else
				{
					if(x == x->parent->leftChild)
					{
						x = x->parent;
						rightRotate(x);
					}
					if(x->parent != NULL)
						x->parent->colour = 0;
					if(x->parent->parent != NULL)
					{
						x->parent->parent->colour = 1;
						leftRotate(x->parent->parent);
					}
				}
			}
		}
		//if the parent is black, just return
		else
		{
			root->colour = 0;
			return;
		}
	}
	root->colour = 0;
}

//---------leftRotating about a particular node-------------------
void leftRotate(struct node *x)
{
	struct node *y = x->rightChild;
	x->rightChild = y->leftChild;
	if(x->rightChild != NULL)
		x->rightChild->parent = x;
	y->parent = x->parent;
	if(x->parent == NULL)
		root = y;
	else if(x->parent->leftChild == x)
		x->parent->leftChild = y;
	else
		x->parent->rightChild = y;
	y->leftChild = x;
	x->parent = y;
}

//----------rightRotating about a particular node----------------
void rightRotate(struct node *x)
{
	struct node *y = x->leftChild;
	x->leftChild = y->rightChild;
	if(x->leftChild != NULL)
		x->leftChild->parent = x;
	y->parent = x->parent;
	if(x->parent == NULL)
		root = y;
	else if(x->parent->leftChild == x)
		x->parent->leftChild = y;
	else
		x->parent->rightChild = y;
	y->rightChild = x;
	x->parent = y;
}

//***************************END**********************************






