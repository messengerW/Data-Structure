#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef char ElemType;

typedef struct QueueNode
{
	ElemType data;
	struct QueueNode *next;
}QueueNode;

typedef struct
{
	QueueNode *head;
	QueueNode *tail;
}LinkQueue;

void InitQueue(LinkQueue *Q)
{
	Q->head = Q->tail = (QueueNode *)malloc(sizeof(QueueNode));
	if(!Q->head)
		printf("Error !\n");								//初始化失败
	Q->head->next = NULL;
}

void AppendQueue(LinkQueue *Q, ElemType e)                  //队尾添加元素
{
	QueueNode *p;
	if(e != '?'){
		p = (QueueNode *)malloc(sizeof(QueueNode));
		p->data = e;
		p->next = NULL;
		Q->tail->next = p;                                      // 让原来的队尾下一个元素指向p
		Q->tail = p;											// 让p作新的队尾
	}
}

void DeleteHead(LinkQueue *Q)
{
	QueueNode *p;
	if(Q->head == Q->tail)
		printf("ERROR !\n");								//队列为空
	else
	{
		p = Q->head->next;
		Q->head->next = Q->head->next->next;                // 删除队首元素并释放内存
		free(p);
	}
}

ElemType GetHead(LinkQueue Q)								// 返回队头元素
{
	return Q.head->next->data;
}

void DestroyQueue(LinkQueue *Q)								//	 销毁队列
{
	while(Q->head){
		Q->tail = Q->head->next;
		free(Q->head);
		Q->head = Q->tail;
	}
}

void Print(LinkQueue Q)
{
	while(Q.head != Q.tail){
		printf(" %c",Q.head->next->data);
		Q.head = Q.head->next;
	}
	printf("\n");
}

int main()
{
	LinkQueue Q;
	ElemType e, ch1, ch2;
	InitQueue(&Q);                                          //初始化
	
	printf("请依次输入队列的元素（以 ? 结束）：");
	while(e != '?'){
		scanf("%c",&e);
		AppendQueue(&Q,e);
	}
	getchar();
	printf("你创建的队列为：");
	Print(Q);
	printf("\n");
	
	printf("队头元素为%c\n",GetHead(Q));
	printf("你确定要删除队头吗（y/n）:");
	scanf("%c",&ch1);
	getchar();
	if(ch1 == 'y'){
		DeleteHead(&Q);
		printf("删除成功，新的队列为：");
		Print(Q);
		printf("新的队头元素为%c\n",GetHead(Q));
	}
	printf("\n");
	
	printf("输入你想增加的元素：");
	scanf("%c",&e);
	getchar();
	AppendQueue(&Q,e);
	printf("添加成功，新的队列为：");
	Print(Q);
	printf("\n");
	
	printf("销毁队列？（y/n）:");
	scanf("%c",&ch2);
	getchar();
	if(ch2 == 'y'){
		DestroyQueue(&Q);
		printf("销毁成功\n");
	}
	printf("\n");
	
	return 0;
}




















