#if 0 
//AVL high
#include <stdlib.h>
#include <stdio.h>
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
#define max(a,b)	(((a) > (b)) ? (a) : (b))
int get_height(NODE *node)
{
	int height = 0;
	if(node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}
int main()
{
	int a[] = {6,3,1,5,7,12};
//	NODE *node = 0;
	int i;
	int height;

	display(root);
	for(i=0;i<6;i++)
	{
		insert_data(a[i]);
		display(root);
	}
	insert_data(9);
	display(root);
	printf("Tree height test\n");
	getchar();

	height = get_height(root);
	printf("root height: %d\n", height);

	return 0;
}
#endif
#if 0 
//AVL balance 
#include <stdlib.h>
#include <stdio.h>
typedef struct _node
{
	int data;
	struct _node *left;
	struct _node *right;
}NODE;

NODE * balance_tree(NODE ** node);
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
	printf("%d->\n", node->data);
	if(key == node->data)
		return node;
	else if(key < node->data)
		search(node->left, key);
	else
		search(node->right, key);
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
#define max(a,b)	(((a) > (b)) ? (a) : (b))
int get_height(NODE *node)
{
	int height = 0;
	if(node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}
int get_balance(NODE * node)
{
	if(node ==NULL) return 0;
	return get_height(node->left) - get_height(node->right);
}
NODE *search_parent(NODE * node, int key)
{
	if(node->left->data == key)
		return node;
	if(node->right->data == key)
		return node;
	if(key < node->data)
		search_parent(node->left, key);
	else
		search_parent(node->right, key);
}
int main()
{
	int a[] = {6,3,1,5,7,12,9,4};
	NODE *node = 0;
	int i;
	int height;
	int num;

	display(root);
	for(i=0;i<8;i++)
	{
		insert_data(a[i]);
		display(root);
	}
	insert_data(10);
	display(root);
	printf("Tree height test\n");
	while(1)
	{
		fflush(stdin);
		printf("num : ");
		scanf("%d", &num);
		node = search(root, num);

//		height = get_height(node);
//		printf("root height: %d\n", height);
		height = get_balance(node);
		printf("%d의 밸런스값: %d\n", num, height);
		getchar();
		if(height < -1 || height > 1)
		{
			node = search_parent(root, num);
			if(node->data < num)
				node->right = balance_tree(&(node->right));
			else
				node->left = balance_tree(&(node->left));
		}
		gerchar();
		display(root);
	}
	node = search(root, 6);
	node->right = balance_tree(&(node->right));
	display(root);
	return 0;
}
#endif
#if 1 
//AVL balance 
#include <stdlib.h>
#include <stdio.h>
typedef struct _node
{
	int data;
	struct _node *left;
	struct _node *right;
}NODE;

NODE * balance_tree(NODE ** node);
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
NODE * insert(NODE ** root, int data)
{
	NODE **p = root;
	if(*p == NULL)
	{
		*p = (NODE*)malloc(sizeof(NODE));
		if(*p == NULL)
		{
			printf("메모리 할당 실패\n");
			exit(-1);
		}
		(*p)->data = data;
		(*p)->left = (*p)->right = NULL;
	}else if(data < (*p)->data)
	{
		(*p)->left = insert(&((*p)->left), data);
		*p = balance_tree(p);
	}
	else if(data > (*p)->data)
	{
		(*p)->right= insert(&((*p)->right), data);
		*p = balance_tree(p);
	}
	else
	{
		printf("중복데이터 입력\n");
		exit(-1);
	}
	return *p;
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
	printf("%d->\n", node->data);
	if(key == node->data)
		return node;
	else if(key < node->data)
		search(node->left, key);
	else
		search(node->right, key);
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
#define max(a,b)	(((a) > (b)) ? (a) : (b))
int get_height(NODE *node)
{
	int height = 0;
	if(node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}
int get_balance(NODE * node)
{
	if(node ==NULL) return 0;
	return get_height(node->left) - get_height(node->right);
}

NODE * balance_tree(NODE ** node)
{
	int height_diff;
	height_diff = get_balance(*node);
	printf("밸런스값: %d\n", height_diff);
	if(height_diff > 1)
	{
		if(get_balance((*node)->left) > 0)
		{
			*node = rotate_LL(*node);
		}
		else
		{
			*node = rotate_LR(*node);
		}
	}
	else if(height_diff < -1)
	{
		if(get_balance((*node)->left) > 0)
			*node = rotate_RL(*node);
		else
			*node = rotate_RR(*node);
	}
	return *node;
}
NODE *search_parent(NODE * node, int key)
{
	if(node->left->data == key)
		return node;
	if(node->right->data == key)
		return node;
	if(key < node->data)
		search_parent(node->left, key);
	else
		search_parent(node->right, key);
}
int main()
{
	int a[] = {6,3,1,5,7,12,4,2};
	int i;
	display(root);
	for(i=0;i<8;i++)
	{
		insert(&root, a[i]);
		display(root);
	}
	return 0;
}
#endif
