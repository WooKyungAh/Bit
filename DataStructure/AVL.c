#if 0 
//AVL rotate_RR
#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
	int data;
	struct _node *left;
	struct _node *right;
}NODE;

NODE *root;
typedef enum{LEFT,RIGHT}TYPE;
NODE * search(NODE *node, int key)
{
	if(node == NULL) return NULL;
	printf("%d->", node->data);
	if(key == node->data)
		return node;
	else if(key < node->data)
		search(node->left, key);
	else
		search(node->right, key);
	return 0;
}
void insert_data(int data)
{
	NODE *temp, **p = &root;
	temp = (NODE*)malloc(sizeof(NODE));
	temp->data = data;
	temp->right = 0;
	temp->left = 0;
	if(root == 0)
	{
		root = temp;
		return;
	}
	while(*p)
	{
		if((*p)->data < data)
			p = &(*p)->right;
		else if((*p)->data > data)
			p = &(*p)->left;
		else
			return;
	}
	*p = temp;
}
void _display(NODE * temp, int (*a)[10], int *row, int *col)
{
	if(temp == 0)
		return;

	(*row)++;
	_display(temp->left, a, row, col);
	a[*row][(*col)++] = temp->data;
	_display(temp->right, a, row, col);
	(*row)--;
}
void display(NODE *temp)
{
	int i,j;
	int a[10][10] = {{0,},};
	int row = -1;
	int col = 0;

	system("clear");
	printf("-----------------------------------\n");
	_display(temp, a, &row, &col);
	for(i=0;i<5;i++)
	{
		for(j=0;j<10;j++)
		{
			if(a[i][j] == 0)
				printf("%4c", ' ');
			else
				printf("%4d", a[i][j]);
		}
		printf("\n\n");
	}
	getchar();
}
NODE * rotate_RR(NODE *parent)
{
	NODE *child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}
int main()
{
	NODE *node = 0;
	int i;
	int a[] = {6,3,1,5,7,11};
	display(root);
	for(i=0;i<6;i++)
	{
		insert_data(a[i]);
		display(root);
	}
	insert_data(12);
	display(root);

	node = search(root, 6);
	node->right = rotate_RR(node->right);
	display(root);

	return 0;
}
#endif
#if 0 
//AVL rotate_LL
#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
	int data;
	struct _node *left;
	struct _node *right;
}NODE;

NODE *root;
typedef enum{LEFT,RIGHT}TYPE;
void insert_data(int data)
{
	NODE *temp, **p = &root;
	temp = (NODE*)malloc(sizeof(NODE));
	temp->data = data;
	temp->right = 0;
	temp->left = 0;
	if(root == 0)
	{
		root = temp;
		return;
	}
	while(*p)
	{
		if((*p)->data < data)
			p = &(*p)->right;
		else if((*p)->data > data)
			p = &(*p)->left;
		else
			return;
	}
	*p = temp;
}
void _display(NODE * temp, int (*a)[10], int *row, int *col)
{
	if(temp == 0)
		return;

	(*row)++;
	_display(temp->left, a, row, col);
	a[*row][(*col)++] = temp->data;
	_display(temp->right, a, row, col);
	(*row)--;
}
void display(NODE *temp)
{
	int i,j;
	int a[10][10] = {0,};
	int row = -1;
	int col = 0;

	system("clear");
	printf("-----------------------------------\n");
	_display(temp, a, &row, &col);
	for(i=0;i<5;i++)
	{
		for(j=0;j<10;j++)
		{
			if(a[i][j] == 0)
				printf("%4c", ' ');
			else
				printf("%4d", a[i][j]);
		}
		printf("\n\n");
	}
	getchar();
}
NODE * serch(NODE *node, int key)
{
	if(node == NULL) return NULL;
	printf("%d->", node->data);
	if(key == node->data)
		return node;
	else if(key < node->data)
		serch(node->left, key);
	else
		serch(node->right, key);
}
NODE * rotate_RR(NODE *parent)
{
	NODE *child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}
NODE * rotate_LL(NODE * parent)
{
	NODE *child = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}
int main()
{
	NODE *node = 0;
	int i;
	int a[] = {7,6,3,11};
	display(root);
	for(i=0;i<4;i++)
	{
		insert_data(a[i]);
		display(root);
	}
	insert_data(1);
	display(root);
	node = serch(root, 7);
	node->left = rotate_LL(node->left);
	display(root);

}
#endif
#if 0 
//AVL rotate_LR
#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
	int data;
	struct _node *left;
	struct _node *right;
}NODE;

NODE *root;
typedef enum{LEFT,RIGHT}TYPE;
void insert_data(int data)
{
	NODE *temp, **p = &root;
	temp = (NODE*)malloc(sizeof(NODE));
	temp->data = data;
	temp->right = 0;
	temp->left = 0;
	if(root == 0)
	{
		root = temp;
		return;
	}
	while(*p)
	{
		if((*p)->data < data)
			p = &(*p)->right;
		else if((*p)->data > data)
			p = &(*p)->left;
		else
			return;
	}
	*p = temp;
}
void _display(NODE * temp, int (*a)[10], int *row, int *col)
{
	if(temp == 0)
		return;

	(*row)++;
	_display(temp->left, a, row, col);
	a[*row][(*col)++] = temp->data;
	_display(temp->right, a, row, col);
	(*row)--;
}
void display(NODE *temp)
{
	int i,j;
	int a[10][10] = {{0,},};
	int row = -1;
	int col = 0;

	system("clear");
	printf("-----------------------------------\n");
	_display(temp, a, &row, &col);
	for(i=0;i<5;i++)
	{
		for(j=0;j<10;j++)
		{
			if(a[i][j] == 0)
				printf("%4c", ' ');
			else
				printf("%4d", a[i][j]);
		}
		printf("\n\n");
	}
	getchar();
}
NODE * serch(NODE *node, int key)
{
	if(node == NULL) return NULL;
	printf("%d->", node->data);
	if(key == node->data)
		return node;
	else if(key < node->data)
		serch(node->left, key);
	else
		serch(node->right, key);
	return 0;
}
NODE * rotate_RR(NODE *parent)
{
	NODE *child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}
NODE * rotate_LL(NODE * parent)
{
	NODE *child = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}
NODE * rotate_LR(NODE * parent)
{
	NODE *child = parent->left;
	parent->left = rotate_RR(child);
	return rotate_LL(parent);
}
int main()
{
	NODE *node = 0;
	int i;
	int a[] = {7,6,3,11};
	display(root);
	for(i=0;i<4;i++)
	{
		insert_data(a[i]);
		display(root);
	}
	insert_data(4);
	display(root);
	node = serch(root, 7);
	node->left = rotate_LR(node->left);
	display(root);

	return 0;
}
#endif
#if 1 
//AVL rotate_RL
#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
	int data;
	struct _node *left;
	struct _node *right;
}NODE;

NODE *root;
typedef enum{LEFT,RIGHT}TYPE;
void insert_data(int data)
{
	NODE *temp, **p = &root;
	temp = (NODE*)malloc(sizeof(NODE));
	temp->data = data;
	temp->right = 0;
	temp->left = 0;
	if(root == 0)
	{
		root = temp;
		return;
	}
	while(*p)
	{
		if((*p)->data < data)
			p = &(*p)->right;
		else if((*p)->data > data)
			p = &(*p)->left;
		else
			return;
	}
	*p = temp;
}
void _display(NODE * temp, int (*a)[10], int *row, int *col)
{
	if(temp == 0)
		return;

	(*row)++;
	_display(temp->left, a, row, col);
	a[*row][(*col)++] = temp->data;
	_display(temp->right, a, row, col);
	(*row)--;
}
void display(NODE *temp)
{
	int i,j;
	int a[10][10] = {{0,},};
	int row = -1;
	int col = 0;

	system("clear");
	printf("-----------------------------------\n");
	_display(temp, a, &row, &col);
	for(i=0;i<5;i++)
	{
		for(j=0;j<10;j++)
		{
			if(a[i][j] == 0)
				printf("%4c", ' ');
			else
				printf("%4d", a[i][j]);
		}
		printf("\n\n");
	}
	getchar();
}
NODE * search(NODE *node, int key)
{
	if(node == NULL) return NULL;
	printf("%d->", node->data);
	if(key == node->data)
		return node;
	else if(key < node->data)
		search(node->left, key);
	else
		search(node->right, key);
	return 0;
}
NODE * rotate_RR(NODE *parent)
{
	NODE *child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}
NODE * rotate_LL(NODE * parent)
{
	NODE *child = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}
NODE * rotate_LR(NODE * parent)
{
	NODE *child = parent->left;
	parent->left = rotate_RR(child);
	return rotate_LL(parent);
}
NODE * rotate_RL(NODE * parent)
{
	NODE *child = parent->right;
	parent->right = rotate_LL(child);
	return rotate_RR(parent);
}
int main()
{
	NODE *node = 0;
	int i;
	int a[] = {6,3,7,11};
	display(root);
	for(i=0;i<4;i++)
	{
		insert_data(a[i]);
		display(root);
	}
	insert_data(9);
	display(root);
	node = search(root, 6);
	node->right= rotate_RL(node->right);
	display(root);

	return 0;
}
#endif
