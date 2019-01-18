#include<stdio.h>

#define MAXSIZE 8

typedef int KeyType;
typedef char ElemType;

typedef struct{
	KeyType key;
	//ElemType e;		 为方便测试，这里暂时不储存数据项，只储存关键字
}RedType;

typedef struct{
	int length;
	RedType r[MAXSIZE+1];
}SqList;				// 用顺序表作为存储结构

int CreateSqList(SqList *L)
{
	int i;
	L->length = 0;
	for( i = 1; i <= MAXSIZE; i++ )
	{
		printf("请输入第 %d 个数据：",i);
		scanf("%d",&L->r[i].key);
		L->length++;
	}
	printf("\n创建完毕。");
}

void Bubble_Sort(SqList *L)
{
	int i, j;
	for( i = 2; i <= L->length; i++ )
	{
		for( j = i; j > 1; j-- )
		{
			if( L->r[j].key < L->r[j-1].key )
			{
				//	用闲置的r[0]作为中转栈
				L->r[0] = L->r[j];
				L->r[j] = L->r[j-1];
				L->r[j-1] = L->r[0];
			}
		}
	}
}

void Print(SqList L)
{
	int i;
	for( i = 1; i <= MAXSIZE; i++ )
	{
		//printf("%c --- %d\n",L.r[i].e,L.r[i].key);	详细信息打印
		printf("  %d",L.r[i].key);
	}
	printf("\n");
}



int main()
{
	SqList L;
	CreateSqList(&L);
	printf("你建立的顺序表为：\n");
	Print(L);

	Bubble_Sort(&L);
	printf("经过 < 冒泡排序 > 后：\n");
	Print(L);
	
	return 0;
}