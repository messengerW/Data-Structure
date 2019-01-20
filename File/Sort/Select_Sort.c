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
	RedType r[MAXSIZE+1];	// 零号不存任何元素，用来当作辅助空间
}SqList;					// 用顺序表作为存储结构

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

void Select_Sort(SqList *L)
{
	int i, j, min;
	for( i = 1; i <= MAXSIZE; i++ )
	{
		min = L->r[i].key;
		for( j = i; j <= MAXSIZE; j++)
		{
			if( L->r[j].key < min )			//	遍历，如果寻找到一个比 i 的关键字小的记录，就交换两纪录
			{								//	利用闲置空间r[0]辅助交换
				min = L->r[j].key;
				L->r[0] = L->r[i];
				L->r[i] = L->r[j];
				L->r[j] = L->r[0];
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

	Select_Sort(&L);
	printf("经过 < 简单选择排序 > 后：\n");
	Print(L);
	
	return 0;
}

/*	...说实话，我觉得这不还是冒泡嘛...	*/