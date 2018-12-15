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

int Quick_Sort(SqList *L, int low, int high)
{
	int pivotkey, left, right;
	L->r[0] = L->r[low];
	pivotkey = L->r[0].key;
	while( low < high )
	{
		//	从最后一个记录向前遍历，直到某记录 < 枢轴时停止
		while( low < high && L->r[high].key >= pivotkey )
			--high;
		
		L->r[low] = L->r[high];
		//	从第一个记录向后遍历，直到某记录 > 枢轴时停止
		while( low < high && L->r[low].key <= pivotkey )
			++low;
		
		L->r[high] = L->r[low];
	}
	L->r[low] = L->r[0];
	return high;
}

void QS(SqList *L, int low, int high)
{
	int pos;
	pos = Quick_Sort(&(*L),low,high);
	if( low < high )
	{
		pos = Quick_Sort(L,low,high);
		QS(&(*L),low,pos-1);
		QS(&(*L),pos+1,high);
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
	printf("\n\n");
}

int main()
{
	SqList L;
	CreateSqList(&L);
	printf("你建立的顺序表为：\n");
	Print(L);

	printf("经过一趟 <快速排序> 后：\n");
	Quick_Sort(&L,1,L.length);
	Print(L);
	
	printf("经过整个 <快速排序> 后：\n");
	QS(&L,1,L.length);
	Print(L);
	
	return 0;
}