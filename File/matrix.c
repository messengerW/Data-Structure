#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>

#define MAX_SIZE 10000

typedef int ElemType;

typedef struct
{
	int row, col;
	ElemType e;
}Triple;

typedef struct
{
	Triple *data;
	int rows, cols, nums;
	int maxnum;
}Matrix;

void InitMatrix(Matrix *M)
{
	M->maxnum = MAX_SIZE;
	M->data = (Triple *)malloc(sizeof(Triple));
	M->rows = M->cols = M->nums = 0;
}

void DestroyMatrix(Matrix *M)
{
	if(M->data)
		free(M->data);
}

void CreateMatrix(Matrix *M)
{
	int i;
	printf("������ϡ������������");
	scanf("%d",&M->rows);
	printf("������ϡ������������");
	scanf("%d",&M->cols);
	printf("������ϡ��������Ԫ�ĸ�����");
	scanf("%d",&M->nums);
	if(M->nums > M->maxnum)
		printf("Error !\n");
	printf("\n�밴�������������� %d ������Ԫ��\n",M->nums);
	for(i = 0; i < M->nums; i++)
	{
		printf("�������%d������Ԫ���бꡢ�бꡢԪ��ֵ���ÿո��������",i+1);
		//	�Ͻ�һ��Ļ�������Ӧ���ж�һ�������Ƿ�Ϸ�
		scanf("%d %d %d",&M->data[i].row,&M->data[i].col,&M->data[i].e);
	}
	printf("\n");
}

void Print(Matrix M)
{
	int i;
	printf("\n\trow\tcol\te\n");
	for(i = 0; i < M.nums; i++)
		printf("\t %d\t %d\t%d\n",M.data[i].row,M.data[i].col,M.data[i].e);
	printf("\n");
}

void Transpose(Matrix M, Matrix *T)
{
	if( M.nums > T->maxnum )
		printf("Error_1 !\n");
	T->rows = M.cols;
	T->cols = M.rows;
	T->nums = M.nums;
	if(M.nums)
	{
		int k, p, n;					// k��M�е��б꣬p��T->[data]���±꣬n��M�з���Ԫ�����
		p = 0;
		for(int k = 1; k <= M.cols; k++)		// ��M�ĵ�һ�п�ʼ
		{
			for(int n = 0; n < M.nums; n++)		// ��M�ĵ�һ������Ԫ��ʼ
			{
				if( M.data[n].col == k )		// �ж��������Ԫ�Ƿ�λ��M�е�k��
				{
					T->data[p].row = M.data[n].col;
					T->data[p].col = M.data[n].row;
					T->data[p].e = M.data[n].e;
					p++;
				}
				
			}
			
		}
	}
}

void Transpose_faster(Matrix M, Matrix *T)
{
	if( M.nums > T->maxnum )
		printf("Error_2 !\n");
	T->rows = M.cols;
	T->cols = M.rows;
	T->nums = M.nums;
	if(M.nums)
	{
		int num[M.cols];		// num����������¼M�е�col���з���Ԫ����
		int cpot[M.cols];		// cpot����������¼M�е�col���е�һ������Ԫ��T.data[]�е��±�ֵ
		int i, n, p = 0;		// i��ʾM�е��б꣬n��ʾ����Ԫ��ţ�p��ʾ����Ԫ��T.data[]�ж�Ӧ�ĵ��±�ֵ
		for(i = 0; i < M.cols; i++)
			num[i] = 0;						// ��ʼ��
		for(n = 0; n < M.nums; n++)			// ��M�ĵ�һ������Ԫ��ʼxuyuan2018-11-23-21:47:13
			num[M.data[n].col-1]++;			// num[M.data[n].col-1]��ʾM�е�n������Ԫ���ڵĵ��еķ���Ԫ�ĸ���
		cpot[0] = 0;						// cpot[0]��ʾM�е�1�е�һ������Ԫ��T.data[]�е��±�ֵ
		for(i = 1; i < M.cols; i++)			// M��һ�е�һ������Ԫ��λ���Ѿ�ָ�����ʴ�cpot[1]��ʼ
			cpot[i] = cpot[i-1] + num[i-1];	// cpot[i]��ʾM�е�i+1�е�һ������Ԫ��λ�ã�����cpot[i-1]֮�����num[i-1]���±�
		for(n = 0; n < M.nums; n++)
		{
			p = cpot[M.data[n].col-1]++;	// cpot[M.data[n].col-1]��ʾM�е�n������Ԫ���ڵ��еĵ�һ������Ԫ��T.data[]�е��±�ֵ
			T->data[p].row = M.data[n].col;
			T->data[p].col = M.data[n].row;
			T->data[p].e = M.data[n].e;
		}
	}
}

int main()
{
	Matrix M, T1, T2;
	InitMatrix(&M);
	InitMatrix(&T1);
	InitMatrix(&T2);
	
	CreateMatrix(&M);
	printf("�������ϡ�����Ϊ��\n");
	Print(M);
	
	Transpose(M,&T1);
	printf("һ��ת�ú�\n");
	Print(T1);
	
	Transpose_faster(M,&T2);
	printf("����ת�ú�\n");
	Print(T2);
	
	
	return 0;
}


