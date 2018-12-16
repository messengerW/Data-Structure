#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>

#define EQ(a,b) ( (a) == (b) )
#define LT(a,b) ( (a) <  (b) )
#define LQ(a,b) ( (a) <= (b) )
#define MAXSIZE 8
#define N 10

typedef int KeyType;
typedef char ElemType;

typedef struct{
	KeyType key;
	//ElemType e;		 Ϊ������ԣ�������ʱ�����������ֻ����ؼ���
}RedType;

typedef struct{
	int length;
	RedType r[MAXSIZE+1];
}SqList;				// ��˳�����Ϊ�洢�ṹ

int CreateSqList(SqList *L)
{
	int i;
	L->length = 0;
	for( i = 1; i <= MAXSIZE; i++ )
	{
		printf("������� %d �����ݣ�",i);
		scanf("%d",&L->r[i].key);
		L->length++;
	}
	printf("\n������ϡ�");
}

void Shell_Insert_Sort(SqList *L, int d)
{
	int i, j;
	for( i = d+1; i <= L->length; i++ )
	{
		if( LT(L->r[i].key,L->r[i-d].key) )
		{
			L->r[0] = L->r[i];
			for( j = i-d; j>0 && LT(L->r[0].key,L->r[j].key); j-=d )
				L->r[j+d] = L->r[j];
			L->r[j+d] = L->r[0];
		}
	}
}

void Shell_Sort(SqList *L, int t, int dalt[])
{
	int k;
	for( k = 0; k < t; k++ )
		Shell_Insert_Sort(L,dalt[k]);
}

void Print(SqList L)
{
	int i;
	for( i = 1; i <= MAXSIZE; i++ )
	{
		//printf("%c --- %d\n",L.r[i].e,L.r[i].key);
		printf("  %d",L.r[i].key);
	}
	printf("\n");
}

int main()
{
	int i, n, k, arr[N];		//  arr[]��������ÿ�ε�����
	SqList L;
	CreateSqList(&L);
	printf("�㽨����˳���Ϊ��\n");
	Print(L);
	
	for( i = 0; i < N; i++ )
		arr[i] = -1;			// ��ʼ����������
	n = (int) log2(L.length);
	for( i = 0; i < n; i++ )
	{
		k = L.length/pow(2,i+1);
		arr[i] = k;
	}
	Shell_Sort(&L,n,arr);
	printf("���� <ϣ����������> ��\n");
	Print(L);
	
	/*for( i = 0; i < N; i++ )
		printf("%d ",arr[i]);*/
		
	return 0;
}





