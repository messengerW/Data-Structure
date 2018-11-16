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
		printf("Error !\n");								//��ʼ��ʧ��
	Q->head->next = NULL;
}

void AppendQueue(LinkQueue *Q, ElemType e)                  //��β���Ԫ��
{
	QueueNode *p;
	if(e != '?'){
		p = (QueueNode *)malloc(sizeof(QueueNode));
		p->data = e;
		p->next = NULL;
		Q->tail->next = p;                                      // ��ԭ���Ķ�β��һ��Ԫ��ָ��p
		Q->tail = p;											// ��p���µĶ�β
	}
}

void DeleteHead(LinkQueue *Q)
{
	QueueNode *p;
	if(Q->head == Q->tail)
		printf("ERROR !\n");								//����Ϊ��
	else
	{
		p = Q->head->next;
		Q->head->next = Q->head->next->next;                // ɾ������Ԫ�ز��ͷ��ڴ�
		free(p);
	}
}

ElemType GetHead(LinkQueue Q)								// ���ض�ͷԪ��
{
	return Q.head->next->data;
}

void DestroyQueue(LinkQueue *Q)								//	 ���ٶ���
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
	InitQueue(&Q);                                          //��ʼ��
	
	printf("������������е�Ԫ�أ��� ? ��������");
	while(e != '?'){
		scanf("%c",&e);
		AppendQueue(&Q,e);
	}
	getchar();
	printf("�㴴���Ķ���Ϊ��");
	Print(Q);
	printf("\n");
	
	printf("��ͷԪ��Ϊ%c\n",GetHead(Q));
	printf("��ȷ��Ҫɾ����ͷ��y/n��:");
	scanf("%c",&ch1);
	getchar();
	if(ch1 == 'y'){
		DeleteHead(&Q);
		printf("ɾ���ɹ����µĶ���Ϊ��");
		Print(Q);
		printf("�µĶ�ͷԪ��Ϊ%c\n",GetHead(Q));
	}
	printf("\n");
	
	printf("�����������ӵ�Ԫ�أ�");
	scanf("%c",&e);
	getchar();
	AppendQueue(&Q,e);
	printf("��ӳɹ����µĶ���Ϊ��");
	Print(Q);
	printf("\n");
	
	printf("���ٶ��У���y/n��:");
	scanf("%c",&ch2);
	getchar();
	if(ch2 == 'y'){
		DestroyQueue(&Q);
		printf("���ٳɹ�\n");
	}
	printf("\n");
	
	return 0;
}




















