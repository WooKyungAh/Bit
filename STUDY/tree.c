#if 0 
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
void insert_data(int data, NODE *s, TYPE type)
{
	NODE *temp;
	temp = (NODE *)malloc(sizeof(NODE));
	temp->data = data;
	temp->left = 0;
	temp->right = 0;
	if(root == 0)
	{
		root = temp;
		return;
	}
	if(type == LEFT)
		s->left = temp;
	else if(type == RIGHT)
		s->right = temp;

}
void in_order(NODE * temp)
{
	if(temp == 0)
		return;
	in_order(temp->left);
	printf("%d\n", temp->data);
	in_order(temp->right);
}
void display(NODE * temp)
{
	int i;
	static int indent = -1;
	if(temp == 0)
		return;
	indent++;
	display(temp->right);
	for(i=0;i<indent;i++)
		printf("%4c",' ');
	printf("%d\n", temp->data);
	display(temp->left);
	indent--;
}
int (* __display(NODE * temp))[10]
{
	static int a[10][10] = {{0,},};
	static int col = 0;
	static int row = -1;
	if(temp == 0)
		return 0;

	row++;
	__display(temp->left);
	a[row][col++] = temp->data;
	__display(temp->right);
	row--;
	return a;
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
void print(int (*a)[10])
{
	int i,j;
	printf("-----------------------------------\n");
	for(i=0;i<3;i++)
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
}
int main()
{
	int (*arr)[10];
	int arry[10][10] = {{0,},};
	int r = -1, c = 0;
	insert_data(1, 0, LEFT);
	insert_data(2, root, LEFT);
	insert_data(3, root, RIGHT);
	insert_data(4, root->left, LEFT);
	insert_data(5, root->left, RIGHT);
	insert_data(6, root->right, LEFT);
	insert_data(7, root->right, RIGHT);
	in_order(root);
	display(root);
	arr = __display(root);
	print(arr);
	_display(root, arry, &r, &c);
	print(arry);
	return 0;
}
#endif

#if 0 
// 이진탐색 tree
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
//	if(prev->data < data)
//		prev->right = temp;
//	else
//		prev->left = temp;
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
void print(int (*a)[10])
{
	int i,j;
	printf("-----------------------------------\n");
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
}
int main()
{
	int arry[10][10] = {{0,},};
	int r = -1, c = 0;
	int a[7] = {5,3,4,7,6,1,2};
	int i;
	for(i=0;i<7;i++)
		insert_data(a[i]);
	_display(root, arry, &r, &c);
	print(arry);
	return 0;
}
#endif
#if 1 
//이진탐색의 일반화
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
void __fill(NODE * temp, int *a, int *n)
{
	if(temp == 0)
		return ;
	__fill(temp->left, a, n);
	a[(*n)++] = temp->data;
	__fill(temp->right, a, n);
}
NODE * __bal(int *a, int n)
{
	int mid = n/2;
	NODE *temp;

	if(n<1)
		return 0;
	temp = (NODE*)malloc(sizeof(NODE));

	temp->data = a[mid];
	temp->left = __bal(a,mid);
	temp->right = __bal(a+mid+1,n-mid-1);
	return temp;
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
void print(int (*a)[10])
{
	int i,j;
	printf("-----------------------------------\n");
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
}
int main()
{
	int arry[10][10] = {{0,},};
	int r = -1, c = 0;
	int a[7] = {5,3,4,7,6,1,2};
	int i,j;
	int k = 0;
	for(i=0;i<7;i++)
		insert_data(a[i]);
	_display(root, arry, &r, &c);
	print(arry);
	__fill(root, a, &k);
	for(i=0;i<7;i++)
		printf("[%d] ", a[i]);
	printf("\n");
	root = __bal(a, 7);
	r=-1;
	c=0;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
			arry[i][j] = 0;
	}
	_display(root, arry, &r, &c);
	print(arry);
	return 0;
}
#endif
