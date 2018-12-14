#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>

#define EQ(a,b) ( (a) == (b) )
#define LT(a,b) ( (a) <  (b) )
#define LQ(a,b) ( (a) <= (b) )
#define MAXSIZE 5

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

void Straight_Insert_Sort(SqList *L)
{
	int i, j;
	for( i = 2; i <= L->length; i++ )
	{
		if( LT(L->r[i].key,L->r[i-1].key) )
		{
			L->r[0] = L->r[i];
			L->r[i] = L->r[i-1]; 
			for( j = i-2; LT(L->r[0].key,L->r[j].key); j-- )
				L->r[j+1] = L->r[j];
			L->r[j+1] = L->r[0];
		}
	}
}

void Print(SqList L)
{
	int i;
	for( i = 1; i <= MAXSIZE; i++ )
	{
		//printf("%c --- %d\n",L.r[i].e,L.r[i].key);	��ϸ��Ϣ��ӡ
		printf("  %d",L.r[i].key);
	}
	printf("\n");
}



int main()
{
	SqList L;
	CreateSqList(&L);
	printf("�㽨����˳���Ϊ��\n");
	Print(L);

	Straight_Insert_Sort(&L);
	printf("���� <ֱ�Ӳ�������> ��\n");
	Print(L);
	
	return 0;
}