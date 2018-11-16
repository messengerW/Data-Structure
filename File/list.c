#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define LIST_INIT_SIZE 5
#define LISTINCREMENT 1
#define ERROR 0
typedef char ElemType;

typedef struct {
	ElemType *elem;
	int length;
	int size;
}sqlist;

int InitList(sqlist *L)
{
	//															��ʼ��˳���
	L->elem = (ElemType *) malloc(sizeof(ElemType));
    if (!L->elem) return ERROR; 
    L->length = 0; 
    L->size = LIST_INIT_SIZE;  
}

void ListAppend(sqlist *L, ElemType e)
{
	// 															����ĩβ���Ԫ�ص���ʽ����˳���
    if (L->size <= L->length)
	{
        L->elem = (ElemType *)realloc(L->elem, (LIST_INIT_SIZE + LISTINCREMENT) * sizeof(ElemType));
        L->size += LISTINCREMENT;
	}
    if(e != '?'){
		L->elem[L->length] = e;
		L->length++;
	}
}

void GetElem(sqlist L, int i) {
	//															����˳����е�iλԪ�أ��±�Ϊi-1��
    if (i <= L.length && i > 0)
		printf("�������ҵ�Ԫ��Ϊ��%c\n",L.elem[i-1]);
    else
		printf("λ�򳬳���Χ������");
}

void LocateElem(sqlist L, ElemType e)
{
	//															����Ԫ��e��˳����е�λ�ã�����i+1
	int i = 0;
    while (L.elem[i] != e && i < L.length) {
        i++;
    }
    if (i >= L.length)
        printf("˳�����û�д�Ԫ�أ�����");
    else
        printf("����ҵ�Ԫ���ڵ�%dλ\n",i+1);
}

int ListInsert(sqlist *L, int i, ElemType e)
{
	//															��˳�����ָ��λ�ò���ָ��Ԫ��
    int k;  
    if (i < 1 || i > L->length + 1) return ERROR;				//λ�򳬳���Χ
    if (L->length >= L->size)
    { 
        L->elem = (ElemType *)realloc(L->elem, (LIST_INIT_SIZE + LISTINCREMENT) * sizeof(ElemType));
        if (!L->elem) return ERROR;								//�ڴ����ʧ��
        L->size += LISTINCREMENT;       
    }
    for (k = L->length - 1; k >= i - 1; k--) 
        L->elem[k + 1] = L->elem[k];        
    L->elem[i-1] = e;
    L->length++;
    return 0;
}

void ListDelete(sqlist *L, int i)
{
	//															ɾ��ָ��λ�õ�Ԫ��
    int k;
    if(i > 0 && i <= L->length){
		for (k = i; k <= L->length; k++) 
			L->elem[k-1] = L->elem[k];
		L->length--;
	}
	else
		printf("λ�򳬳���Χ������\n");
}

void ListPrint(sqlist L)
{
	//															��ӡ˳���Ԫ��
	int i;
	for(i = 0; i < L.length; i++)
		printf(" %c",L.elem[i]);
	printf("\n");
}

int main()
{
	sqlist L;
	ElemType e,ch;
	int m,n,k,j;
	InitList(&L);
	printf("���������뽨����˳����Ԫ�أ��� ? ������");
	while(e != '?')
	{
		scanf("%c",&e);
		ListAppend(&L,e);
	}
	getchar();
	printf("�㽨����˳���Ϊ:");
	ListPrint(L);
	printf("�䳤��Ϊ��%d\n",L.length);
	
	printf("\n");
	
	printf("������������ҵ�Ԫ�أ�");
	scanf("%c",&ch);
	getchar();
	LocateElem(L, ch);
	printf("\n");
	
	printf("��������Ҫ���ҵ�λ��(1~%d)��",L.length);
	scanf("%d",&k);
	getchar();
	GetElem(L,k);
	printf("\n");
	
	printf("������������Ԫ���Լ�λ���ö��Ÿ�������");
	scanf("%c,%d",&e,&m);
	getchar();
	if(m > 0 && m <= L.length + 1)
	{
		ListInsert(&L,m,e);
		printf("������˳���Ϊ��");
		ListPrint(L);
	}
	else
		printf("λ�򳬳���Χ!!!\n");
	printf("\n");
	
	printf("����������ɾ����Ԫ��λ��(1~%d)��",L.length);
	scanf("%d",&j);
	getchar();
	ListDelete(&L,j);
	printf("ɾ�����˳���Ϊ��");
	ListPrint(L);
	printf("\n");
	
	return 0;
	
}

