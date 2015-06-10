//double linked list
// => NODE에 데이터를 넣는것이 아니라 데이터에 NODE를 넣는다.
#if 0
//step 1
//double linked list
typedef struct _node
{
	int data;
	struct _node *next;
	struct _node *prev;
}NODE;
NODE head = {0, &head, &head};
#endif

#if 0 
#include <stdio.h>
#include <stdlib.h>
//step 2 
//double linked list
typedef struct _node
{
	int data;
	struct _node *next;
	struct _node *prev;
}NODE;
NODE head = {0, &head, &head};
/*
void insert_data(NODE *head, NODE *temp)
{
	temp->next = head->next;
	head->next = temp;
	temp->prev = head;
	temp->next->prev = temp;
}*/
void __insert_data(NODE *prev, NODE *next, NODE *temp)
{
	temp->next = next;
	prev->next = temp;
	temp->prev = prev;
	next->prev = temp;
}
void insert_front(NODE *head, NODE *temp)
{
	__insert_data(head, head->next, temp);
}
void insert_back(NODE *head, NODE *temp)
{
	__insert_data(head->prev, head, temp);
}
void display(NODE *head)
{
	NODE *temp;
	system("clear");
	printf("[head]");
	for(temp = head->next;temp != head; temp = temp->next)
		printf("<->[%d]",temp->data);
	printf("<->[head]");
	getchar();

}
int main()
{
	int i;
	NODE *temp, *s;
	display(&head);
	for(i=0;i<7;i++)
	{
		temp = (NODE*)malloc(sizeof(NODE));
		temp->data = i+1;
		insert_front(&head, temp);
		display(&head);
	}
	for(s=&head;s->data != 5; s = s->next);
	temp = (NODE*)malloc(sizeof(NODE));
//	insert_data(s, temp);
	insert_front(s, temp);
	display(&head);
	temp = (NODE*)malloc(sizeof(NODE));
	temp->data = 8;
	insert_front(&head,temp); 
	display(&head);
	temp = (NODE*)malloc(sizeof(NODE));
	temp->data = 9;
	insert_back(&head,temp); 
	display(&head);
	return 0;
}
#endif

#if 0 
#include <stdio.h>
#include <stdlib.h>
//step 3 
//double linked list
typedef struct _node
{
	void *data;
	struct _node *next;
	struct _node *prev;
}NODE;
NODE head = {0, &head, &head};
/*
void insert_data(NODE *head, NODE *temp)
{
	temp->next = head->next;
	head->next = temp;
	temp->prev = head;
	temp->next->prev = temp;
}*/
void __insert_data(NODE *prev, NODE *next, NODE *temp)
{
	temp->next = next;
	prev->next = temp;
	temp->prev = prev;
	next->prev = temp;
}
void insert_front(NODE *head, NODE *temp)
{
	__insert_data(head, head->next, temp);
}
void insert_back(NODE *head, NODE *temp)
{
	__insert_data(head->prev, head, temp);
}
typedef struct
{
	char name[20];
}SAWON;
void display(NODE *head)
{
	NODE *temp;
	SAWON *s;
	system("clear");
	printf("[head]");
	for(temp = head->next;temp != head; temp = temp->next)
	{
//		printf("<->[%s]",(char*)temp->data);
		s = (SAWON*)temp->data;
		printf("<->[%s]",s->name); 
	}
	printf("<->[head]");
	getchar();

}
int main()
{
	int i;
//	NODE temp[5];
	NODE *temp;
	SAWON s[5] = {"홍길동", "이순신", "유관순", "안중근", "박문수"};
	display(&head);
	for(i=0;i<5;i++)
	{
//		temp[i].data = s+i;
		temp = (NODE*)malloc(sizeof(NODE));
		temp->data = s+i;
		insert_back(&head, temp);
		display(&head);
	}
	return 0;
}
#endif

#if 0
#include <stdio.h>
#include <stdlib.h>
struct foobar{
	unsigned int foo;
	char bar;
	char boo;
}foobar;
int main()
{
	struct foobar tmp;
	printf("address of &tmp is = %p\n\n", &tmp);
	printf("address of tmp->foo = %p \t offset of tmp->foo = %lu\n", 
			&tmp.foo, (unsigned long) &((struct foobar *)0)->foo);
	printf("address of tmp->bar = %p \t offset of tmp->bar = %lu\n", 
			&tmp.bar, (unsigned long) &((struct foobar *)0)->bar);
	printf("address of tmp->boo = %p \t offset of tmp->boo = %lu\n",
			&tmp.boo, (unsigned long) &((struct foobar *)0)->boo);
	printf("computed address of &tmp using: \n");
	printf("\taddress and offset of tmp->foo = %p\n",
			(struct foobar*)(((char*)&tmp.foo) - ((unsigned long)&((struct foobar*)0)->foo)));
	printf("\taddress and offset of tmp->bar = %p\n",
			(struct foobar*)(((char*)&tmp.bar) - ((unsigned long)&((struct foobar*)0)->bar)));
	printf("\taddress and offset of tmp->boo = %p\n",
			(struct foobar*)(((char*)&tmp.boo) - ((unsigned long)&((struct foobar*)0)->boo)));
	
	return 0;
}
#endif

#if 1 
#include <stdio.h>
#include <stdlib.h>
//step 4 
//double linked list
typedef struct _node
{
	struct _node *next;
	struct _node *prev;
}NODE;
void __insert_data(NODE *prev, NODE *next, NODE *temp)
{
	temp->next = next;
	prev->next = temp;
	temp->prev = prev;
	next->prev = temp;
}
void insert_front(NODE *head, NODE *temp)
{
	__insert_data(head, head->next, temp);
}
void insert_back(NODE *head, NODE *temp)
{
	__insert_data(head->prev, head, temp);
}
//-----------------------------------------------------------------------------
typedef struct
{
	char name[20];
	NODE list;
}SAWON;
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE*)0)->MEMBER)
#define list_entry(ptr, type, member) \
	((type*) ((char*)ptr - (unsigned long)&((type*)0)->member)) 
#define container_of(ptr, type, member)   ({     \
				const typeof( ((type*)0)->member) * __mptr = (ptr);		\
				(type *)( (char *)__mptr - offsetof(type,member) ); })
void display(NODE *head)
{
	NODE *temp;
	SAWON *s;
	system("clear");
	printf("[head]");
	for(temp = head->next;temp != head; temp = temp->next)
	{
//		s = (SAWON*)((void*) temp - (sizeof(SAWON)-sizeof(NODE)));
//		s = (SAWON*)((void*) temp - (unsigned long)&((SAWON*)0)->list); 
		s = container_of(temp, SAWON, list);
		printf("<->[%s]",s->name); 
	}
	printf("<->[head]");
	getchar();

}
int main()
{
	int i;
	SAWON s[5] = {{"홍길동", }, {"이순신", }, {"유관순", }, {"안중근", }, {"박문수", }};

	NODE head = {&head, &head};
	display(&head);
	for(i=0;i<5;i++)
	{
		insert_back(&head, &s[i].list);
		display(&head);
	}
	return 0;
}
#endif
