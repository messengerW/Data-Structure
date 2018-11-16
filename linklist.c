#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef char ElemType;
typedef struct link
{
	ElemType data;
	struct link *next;
}link,*linkptr;

typedef struct{
	linkptr head;
	linkptr tail;
}linklist;

void create(struct link *head, struct link *tail, ElemType e)
{
	head = (struct link *)malloc(sizeof(struct link));
	head->data = e;
	tail->next = head;
	tail = head;
	
}



int main()
{
	ElemType e;
	struct link *head = NULL, *tail, *p;
												//初始化，建立头节点
	printf("请依次输入链表元素（以 ? 结束）:");
	while(e != '?'){
		scanf("%c",&e);
		create(head, tail, e);
	}
	
	tail->next = NULL;
	p = head;
	while(p != NULL){
		printf("%c",p->data);
		p->next = p;
	}
	
	return 0;
}

