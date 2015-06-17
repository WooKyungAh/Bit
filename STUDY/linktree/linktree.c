#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RB_RED		0
#define RB_BLACK	1

// list NODE
typedef struct _node
{
	struct _node *next;
	struct _node *prev;
}NODE;
// rbtree node
struct rb_node
{
	unsigned long rb_parent_color;
	struct rb_node *rb_right;
	struct rb_node * rb_left;
};
struct rb_root
{
	struct rb_node *rb_node;
};
// rbtree display에 필요한 구조체
typedef struct 
{
	int stno;
	char name[20];
	int color;
}INFO;
// STU 구조체!!
typedef struct
{
	int stno;
	char name[20];
	NODE list;
	struct rb_node tree;
}STU;

// doublelinked list #define
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE*)0)->MEMBER)
#define list_entry(ptr, type, member) \
	((type*) ((char*)ptr - (unsigned long)&((type*)0)->member))
#define container_of(ptr, type, member)		({		\
		const typeof( ((type*)0)->member) * __mptr = (ptr);		\
		(type*)( (char *)__mptr - offsetof(type, member) ); })
// rbtree #define
#define rb_entry(ptr, type, member) container_of(ptr, type, member)
#define rb_parent(r)	((struct rb_node*)((r)->rb_parent_color & ~3))
#define rb_color(r)		((r)->rb_parent_color & 1)
#define rb_is_red(r)	(!rb_color(r))
#define rb_is_black(r)	rb_color(r)
#define rb_set_red(r)	do { (r)->rb_parent_color &= ~1; } while (0)
#define rb_set_black(r) do { (r)->rb_parent_color |= 1;  } while (0)

// rbtree 관련함수
void rb_set_parent(struct rb_node *rb, struct rb_node *p)
{
	rb->rb_parent_color = (rb->rb_parent_color & 3) | (unsigned long)p;
}
void rb_set_color(struct rb_node *rb, int color)
{
	rb->rb_parent_color = (rb->rb_parent_color & ~1) | color;
}
void rb_link_node(struct rb_node *node, struct rb_node *parent, struct rb_node **rb_link)
{
	node->rb_parent_color = (unsigned long) parent;
	node->rb_left = node->rb_right = NULL;
	*rb_link = node;
}

//--------------------------------------------------------------------------------
// doublelink 버블정렬
void setting_link(NODE *head, NODE *temp)
{
	STU * prev;
	STU * next;
	NODE * node;
	NODE * nd;

	for(nd = temp; nd->next != head; nd = nd)
	{
		prev = container_of(nd, STU, list);
		next = container_of(nd->next, STU, list);
		node = nd->next;
		if(prev->stno > next->stno)
		{
			node->prev = temp->prev;
			temp->prev->next = node;
			temp->next = node->next;
			node->next->prev = temp;
			node->next = temp;
			temp->prev = node;
		}
		else
			break;
	}
}
// rbtree rotate
static void __rb_rotate_left(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *right = node->rb_right;
	struct rb_node *parent = rb_parent(node);

	if((node->rb_right = right->rb_left))
		rb_set_parent(right->rb_left, node);
	right->rb_left = node;

	rb_set_parent(right, parent);

	if(parent)
	{
		if(node == parent->rb_left)
			parent->rb_left = right;
		else
			parent->rb_right = right;
	}
	else
		root->rb_node = right;
	rb_set_parent(node, right);
}
static void __rb_rotate_right(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *left = node->rb_left;
	struct rb_node *parent = rb_parent(node);

	if((node->rb_left = left->rb_right))
		rb_set_parent(left->rb_right, node);
	left->rb_right = node;

	rb_set_parent(left, parent);

	if(parent)
	{
		if(node == parent->rb_right)
			parent->rb_right = left;
		else
			parent->rb_left = left;
	}
	else
		root->rb_node = left;
	rb_set_parent(node, left);
}
// temp를 doublelink내로 삽입
void insert_data_link(NODE *head, NODE *temp)
{
	temp->next = head->next;
	head->next = temp;
	temp->prev = head;
	temp->next->prev = temp;
	setting_link(head, temp);
}
// rbtree에 color 삽입
void rb_insert_color(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *parent, *gparent;

	rb_set_black(root->rb_node);
	while((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);
		if(parent == gparent->rb_left)
		{
			{
				register struct rb_node *uncle = gparent->rb_right;
				if(uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}
			if(parent->rb_right == node)
			{
				register struct rb_node *tmp;
				__rb_rotate_left(parent, root);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			rb_set_black(parent);
			rb_set_red(gparent);
			__rb_rotate_right(gparent, root);
		}
		else
		{
			{
				register struct rb_node *uncle = gparent->rb_left;
				if(uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}
			if(parent->rb_left == node)
			{
				register struct rb_node *tmp;
				__rb_rotate_right(parent, root);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			rb_set_black(parent);
			rb_set_red(gparent);
			__rb_rotate_left(gparent, root);
		}
	}
	rb_set_black(root->rb_node);
}
void insert_data_tree(struct rb_root *root, int stno, struct rb_node *node)
{
	struct rb_node **p = &root->rb_node;
	struct rb_node *parent = NULL;
	STU *s;

	while(*p)
	{
		parent = *p;
		s = rb_entry(parent, STU, tree);

		if(stno < s->stno)
			p = &(*p)->rb_left;
		else if(stno > s->stno)
			p = &(*p)->rb_right;
		else
			return;
	}
	rb_link_node(node, parent, p);
	rb_insert_color(node, root);
	return;
}
// doublelink로 출력
void display_link(NODE * head)
{
	NODE *temp;
	STU * s;
	system("clear");
	printf("[head]");
	for(temp = head->next; temp != head; temp = temp->next)
	{
		s = container_of(temp, STU, list);
		printf("<->[%d: %s]",s->stno, s->name);
	}
	printf("<->[head]\n");
}
// rbtree로 출력
void __display(struct rb_node *temp, INFO(*a)[10], int *row, int *col)
{
	if(temp == 0)
		return ;
	(*row)++;
	__display(temp->rb_left, a, row,col);
	a[*row][*col].color = rb_color(temp);
	a[*row][*col].stno = rb_entry(temp, STU, tree)->stno;
	strcpy(a[*row][(*col)++].name, rb_entry(temp, STU, tree)->name);
	__display(temp->rb_right, a, row, col);
	(*row)--;
}
void display_tree(struct rb_root * root)
{
	int i, j;
	INFO a[10][10] = {0,};
	int row = -1;
	int col = 0;
	__display(root->rb_node, a, &row, &col);
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(a[i][j].stno == 0)
				printf("%6c", ' ');
			else
			{
				if(a[i][j].color == 1)
					printf("(%d: %s)", a[i][j].stno, a[i][j].name);
				else
					printf("<%d: %s>", a[i][j].stno, a[i][j].name);
			}
		}
		printf("\n\n");
	}
	getchar();
}
// 데이터 삽입 -> 학번, 이름
void input_data(NODE * head, struct rb_root* root)
{
	int no;
	char name[20];
	STU * s;

	printf("exit : 0\n");
	printf("STUDENT NO : ");
	scanf("%d", &no);	fflush(stdin);
	while(no)
	{
		s = (STU*)malloc(sizeof(STU));
		s->stno = no;
		printf("STUDENT NAME : ");
		scanf("%s", name);	fflush(stdin);
		strcpy(s->name, name);

		insert_data_link(head, &s->list);
		insert_data_tree(root, no, &s->tree);
		display_link(head);
		printf("\n\n");
		display_tree(root);
		
		printf("exit : 0\n");
		printf("STUDENT NO : ");
		scanf("%d", &no);	fflush(stdin);
	}
}
// list search
NODE * search_list(int no, NODE * head)
{
	NODE * node = head->next;
	STU * s;
	s = container_of(node, STU, list);
	while(s->stno != no)
	{
		node = node->next;
		s = container_of(node, STU, list);
	}
	return node;
}
// list erase
void link_erase(NODE * list, NODE * head)
{
	list->prev->next = list->next;
	list->next->prev = list->prev;
	//free(list);
}
// rbtree search
struct rb_node * search_tree(int no, struct rb_root * root)
{
	struct rb_node * node = root->rb_node;
	STU * s;
	s = container_of(node, STU, tree);
	while(s->stno != no)
	{
		if(s->stno > no)
		{
			node = node->rb_left;
			s = container_of(node, STU, tree);
		}
		else
		{
			node = node->rb_right;
			s = container_of(node, STU, tree);
		}
	}
	return node;
}
// rbtree erase
static void __rb_erase_color(struct rb_node *node, struct rb_node *parent,
		struct rb_root *root)
{
	struct rb_node *other;

	while((!node || rb_is_black(node)) && node != root->rb_node) 	// ??
	{
		if(parent->rb_left == node)		// parent의 left일때	
		{
			other = parent->rb_right;
			if(rb_is_red(other))	//형제가 red라면
			{
				rb_set_black(other);
				rb_set_red(parent);
				__rb_rotate_left(parent, root);
				other = parent->rb_right;
			}
			if((!other->rb_left || rb_is_black(other->rb_left)) &&
				(!other->rb_right || rb_is_black(other->rb_right)))	// ??
			{
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else		// 
			{
				if(!other->rb_right || rb_is_black(other->rb_right))
				{
					rb_set_black(other->rb_left);
					rb_set_red(other);
					__rb_rotate_left(parent, root);
					other = parent->rb_right;
				}
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->rb_right);
				__rb_rotate_left(parent, root);
				node = root->rb_node;
				break;
			}
		}
		else		// parent의 right일때
		{
			other = parent->rb_left;
			if(rb_is_red(other))	// 형제가 red일때
			{
				rb_set_black(other);
				rb_set_red(parent);
				__rb_rotate_right(parent, root); 	// right rotate
				other = parent->rb_left;	// other가 left로 갔으므로 other에 저장해준다
			}
			if((!other->rb_left || rb_is_black(other->rb_left)) &&
				(!other->rb_right || rb_is_black(other->rb_right)))
			{
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if(!other->rb_left || rb_is_black(other->rb_left))
				{
					rb_set_black(other->rb_right);
					rb_set_red(other);
					__rb_rotate_left(other, root);
					other = parent->rb_left;
				}
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->rb_left);
				__rb_rotate_right(parent, root);
				node = root->rb_node;
				break;
			}
		}
	}
	if(node)
		rb_set_black(node);
}
void rb_erase(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *child, *parent;
	int color;

	if(!node->rb_left)
		child = node->rb_right;
	else if(!node->rb_right)
		child = node->rb_left;
	else
	{
		struct rb_node *old = node, *left;

		node = node->rb_right;
		while((left = node->rb_left) != NULL)
			node = left;

		if(rb_parent(old))
		{
			if(rb_parent(old)->rb_left == old)
				rb_parent(old)->rb_left = node;
			else
				rb_parent(old)->rb_right = node;
		}
		else
			root->rb_node = node;

		child = node->rb_right;
		parent = rb_parent(node);
		color = rb_color(node);

		if(parent == old)
			parent = node;
		else
		{
			if(child)
				rb_set_parent(child, parent);
			parent->rb_left = child;

			node->rb_right = old->rb_right;
			rb_set_parent(old->rb_right, node);
		}

		node->rb_parent_color = old->rb_parent_color;
		node->rb_left = old->rb_left;
		rb_set_parent(old->rb_left, node);

		goto color;
	}

	parent = rb_parent(node);
	color = rb_color(node);

	if(child)
		rb_set_parent(child, parent);
	if(parent)
	{
		if(parent->rb_left == node)
			parent->rb_left = child;
		else
			parent->rb_right = child;
	}
	else
		root->rb_node = child;

  color:
	if(color == RB_BLACK)
		__rb_erase_color(child, parent, root);
}
// 삭제
void delete_data(NODE * head, struct rb_root * root)
{
	int no;
	NODE * list;
	struct rb_node * tree;
	printf("삭제할 학번 입력 : ");
	scanf("%d", &no);	fflush(stdin);
	
	while(no)
	{
		tree = search_tree(no, root);
		rb_erase(tree,root);
		printf("tree erase!!\n");
		list = search_list(no, head);
		printf("list search~\n");
		link_erase(list, head);
		printf("list erase!!\n");

		display_link(head);
		printf("\n\n");
		display_tree(root);
		printf("삭제할 학번 입력 : ");
		scanf("%d", &no);	fflush(stdin);
	}
}

int main()
{
//	int i;
	NODE head = {&head, &head};
	struct rb_root root = {0,};

	display_link(&head);
	input_data(&head, &root);
	delete_data(&head, &root);
	display_link(&head);
	display_tree(&root);
	return 0;
}
