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
	//															初始化顺序表
	L->elem = (ElemType *) malloc(sizeof(ElemType));
    if (!L->elem) return ERROR; 
    L->length = 0; 
    L->size = LIST_INIT_SIZE;  
}

void ListAppend(sqlist *L, ElemType e)
{
	// 															以在末尾添加元素的形式创建顺序表
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
	//															查找顺序表中第i位元素（下标为i-1）
    if (i <= L.length && i > 0)
		printf("你所查找的元素为：%c\n",L.elem[i-1]);
    else
		printf("位序超出范围！！！");
}

void LocateElem(sqlist L, ElemType e)
{
	//															索引元素e在顺序表中的位置，返回i+1
	int i = 0;
    while (L.elem[i] != e && i < L.length) {
        i++;
    }
    if (i >= L.length)
        printf("顺序表中没有此元素！！！");
    else
        printf("你查找的元素在第%d位\n",i+1);
}

int ListInsert(sqlist *L, int i, ElemType e)
{
	//															在顺序表中指定位置插入指定元素
    int k;  
    if (i < 1 || i > L->length + 1) return ERROR;				//位序超出范围
    if (L->length >= L->size)
    { 
        L->elem = (ElemType *)realloc(L->elem, (LIST_INIT_SIZE + LISTINCREMENT) * sizeof(ElemType));
        if (!L->elem) return ERROR;								//内存分配失败
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
	//															删除指定位置的元素
    int k;
    if(i > 0 && i <= L->length){
		for (k = i; k <= L->length; k++) 
			L->elem[k-1] = L->elem[k];
		L->length--;
	}
	else
		printf("位序超出范围！！！\n");
}

void ListPrint(sqlist L)
{
	//															打印顺序表元素
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
	printf("请输入你想建立的顺序表的元素，以 ? 结束：");
	while(e != '?')
	{
		scanf("%c",&e);
		ListAppend(&L,e);
	}
	getchar();
	printf("你建立的顺序表为:");
	ListPrint(L);
	printf("其长度为：%d\n",L.length);
	
	printf("\n");
	
	printf("请输入你想查找的元素：");
	scanf("%c",&ch);
	getchar();
	LocateElem(L, ch);
	printf("\n");
	
	printf("输入你想要查找的位序(1~%d)：",L.length);
	scanf("%d",&k);
	getchar();
	GetElem(L,k);
	printf("\n");
	
	printf("输入你想插入的元素以及位序（用逗号隔开）：");
	scanf("%c,%d",&e,&m);
	getchar();
	if(m > 0 && m <= L.length + 1)
	{
		ListInsert(&L,m,e);
		printf("插入后的顺序表为：");
		ListPrint(L);
	}
	else
		printf("位序超出范围!!!\n");
	printf("\n");
	
	printf("请输入你想删除的元素位序(1~%d)：",L.length);
	scanf("%d",&j);
	getchar();
	ListDelete(&L,j);
	printf("删除后的顺序表为：");
	ListPrint(L);
	printf("\n");
	
	return 0;
	
}

