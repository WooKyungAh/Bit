#if 0
//step 1
//single linked list의 설계
typedef struct _node
{
	int data;
	struct _node *next;
}NODE;
NODE *head = 0;
#endif

#if 0 
//step 2
//single linked list의 설계
typedef struct _node
{
	int data;
	struct _node *next;
}NODE;
NODE *head = 0;

void insert_data(int data)
{
	NODE *temp;
	temp = (NODE*)malloc(sizeof(NODE));
	temp->data = data;
	temp->next = head;
	head = temp;
}
int main()
{
	int i;
	for(i=0;i<7;i++)
	{
		insert_data(i+1);
	}
	return 0;
}

#endif

#if 0
//step 3
//중간에 삽입하기
#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
	int data;
	struct _node *next;
}NODE;
NODE *head = 0;
//void insert_data(int data)
void insert_data(NODE **head,int data)
{
	NODE *temp;
	temp = (NODE*)malloc(sizeof(NODE));
	temp->data = data;
	temp->next = *head;
	*head = temp;
}
void display_data(NODE * head)
{
	NODE * temp;
	system("clear");
	printf("[head]");
	for(temp = head; temp != 0; temp = temp->next)
		printf("->[%d]", temp->data);
	getchar();
}
int main()
{
	int i;
	NODE *rear = 0;
	for(i=0;i<7;i++)
	{
		insert_data(&head, i+1);
	}
	display_data(head);
	display_data(rear);
	for(i=7;i>0;i--)
	{
		insert_data(&rear,i);
		display_data(rear);
	}
	return 0;
}
#endif

#if 0 
//step 4
//삽입함수 하나로 통일
#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
	int data;
	struct _node *next;
}NODE;
//NODE *head = 0;
NODE head = {0,0};
//void insert_data(int data)
void insert_data(NODE *head,int data)
{
	NODE *temp;
	temp = (NODE*)malloc(sizeof(NODE));
	temp->data = data;
	temp->next = head->next;
	head->next = temp;
}
/*
void insert_next(NODE **s, int data)
{
	NODE *temp;
	temp = (NODE*)malloc(sizeof(NODE));
	temp->data = data;
	temp->next = (*s)->next;
	(*s)->next = temp;
}*/
void display_data(NODE * head)
{
	NODE * temp;
	system("clear");
	printf("[head]");
	for(temp = head; temp != 0; temp = temp->next)
		printf("->[%d]", temp->data);
	getchar();
}
int main()
{
	int i;
	NODE *s;
	for(i=0;i<7;i++)
	{
		insert_data(&head, i+1);
	}
	for(s=head.next;s->data != 6; s=s->next);
	insert_data(s, 10);
	display_data(head.next);
	return 0;
}
#endif


#if 0 
//step5 
//!=NULL 안쓰고 !=tail 이용하기
#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
	int data;
	struct _node *next;
}NODE;
//NODE *head = 0;
//NODE head = {0,0};
NODE head, tail;
void init(void)
{
	head.next = &tail;
	tail.next = NULL;
}
void insert_data(NODE *head,int data)
{
	NODE *temp;
	temp = (NODE*)malloc(sizeof(NODE));
	temp->data = data;
	temp->next = head->next;
	head->next = temp;
}
void display_data(NODE * head)
{
	NODE * temp;
	system("clear");
	printf("[head]");
	for(temp = head->next; temp != &tail; temp = temp->next)
		printf("->[%d]", temp->data);
	getchar();
}
int main()
{
	int i;
	NODE *s;
	init();
	display_data(&head);
	for(i=0;i<7;i++)
	{
		insert_data(&head, i+1);
		display_data(&head);
	}
	for(s=head.next;s->data != 6;s=s->next);
	insert_data(s,0);
	display_data(&head);
	return 0;
}
#endif

#if 1
//step 6 
//reverse함수 구현
#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
	int data;
	struct _node *next;
}NODE;
//NODE *head = 0;
//NODE head = {0,0};
NODE head={0,&head};
void insert_data(NODE *hd,NODE *temp)
{
//	NODE *temp;
//	temp = (NODE*)malloc(sizeof(NODE));
	temp->next = hd->next;
	hd->next = temp;
}
void display_data(NODE * hd)
{
	NODE * temp;
	system("clear");
	printf("[head]");
	for(temp = hd->next; temp != hd; temp = temp->next)
		printf("->[%d]", temp->data);
	getchar();
}
void reverse(NODE *temp)
{
	NODE *prev = temp, *curr, *next;
	curr = prev->next;
	while(curr != temp)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	temp->next = prev;
}
int main()
{
	int i;
	NODE *s,*m;
	display_data(&head);
	for(i=0;i<7;i++)
	{
		s = (NODE*)malloc(sizeof(NODE));
		s->data = i+1;
		insert_data(&head,s);
		display_data(&head);
	}
	for(s=head.next;s->data != 6;s=s->next);
	m = (NODE*)malloc(sizeof(NODE));
	m->data = 0;
	insert_data(s,m);
	display_data(&head);
	reverse(&head);
	display_data(&head);
	return 0;
}
#endif
