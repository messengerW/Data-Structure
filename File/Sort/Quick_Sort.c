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

int Quick_Sort(SqList *L, int low, int high)
{
	int pivotkey, left, right;
	L->r[0] = L->r[low];
	pivotkey = L->r[0].key;
	while( low < high )
	{
		//	�����һ����¼��ǰ������ֱ��ĳ��¼ < ����ʱֹͣ
		while( low < high && L->r[high].key >= pivotkey )
			--high;
		
		L->r[low] = L->r[high];
		//	�ӵ�һ����¼��������ֱ��ĳ��¼ > ����ʱֹͣ
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
		//printf("%c --- %d\n",L.r[i].e,L.r[i].key);	��ϸ��Ϣ��ӡ
		printf("  %d",L.r[i].key);
	}
	printf("\n\n");
}

int main()
{
	SqList L;
	CreateSqList(&L);
	printf("�㽨����˳���Ϊ��\n");
	Print(L);

	printf("����һ�� <��������> ��\n");
	Quick_Sort(&L,1,L.length);
	Print(L);
	
	printf("�������� <��������> ��\n");
	QS(&L,1,L.length);
	Print(L);
	
	return 0;
}