#include<stdio.h>

#define MAXSIZE 8

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

void Bubble_Sort(SqList *L)
{
	int i, j;
	for( i = 2; i <= L->length; i++ )
	{
		for( j = i; j > 1; j-- )
		{
			if( L->r[j].key < L->r[j-1].key )
			{
				//	�����õ�r[0]��Ϊ��תջ
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

	Bubble_Sort(&L);
	printf("���� < ð������ > ��\n");
	Print(L);
	
	return 0;
}