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
	RedType r[MAXSIZE+1];	// ��Ų����κ�Ԫ�أ��������������ռ�
}SqList;					// ��˳�����Ϊ�洢�ṹ

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

void Select_Sort(SqList *L)
{
	int i, j, min;
	for( i = 1; i <= MAXSIZE; i++ )
	{
		min = L->r[i].key;
		for( j = i; j <= MAXSIZE; j++)
		{
			if( L->r[j].key < min )			//	���������Ѱ�ҵ�һ���� i �Ĺؼ���С�ļ�¼���ͽ�������¼
			{								//	�������ÿռ�r[0]��������
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

	Select_Sort(&L);
	printf("���� < ��ѡ������ > ��\n");
	Print(L);
	
	return 0;
}

/*	...˵ʵ�����Ҿ����ⲻ����ð����...	*/