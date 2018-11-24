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
	printf("请输入稀疏矩阵的行数：");
	scanf("%d",&M->rows);
	printf("请输入稀疏矩阵的列数：");
	scanf("%d",&M->cols);
	printf("请输入稀疏矩阵非零元的个数：");
	scanf("%d",&M->nums);
	if(M->nums > M->maxnum)
		printf("Error !\n");
	printf("\n请按照行序依次输入 %d 个非零元：\n",M->nums);
	for(i = 0; i < M->nums; i++)
	{
		printf("请输入第%d个非零元的行标、列标、元素值（用空格隔开）：",i+1);
		//	严谨一点的话，这里应该判断一下输入是否合法
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
		int k, p, n;					// k是M中的列标，p是T->[data]的下标，n是M中非零元的序号
		p = 0;
		for(int k = 1; k <= M.cols; k++)		// 从M的第一列开始
		{
			for(int n = 0; n < M.nums; n++)		// 从M的第一个非零元开始
			{
				if( M.data[n].col == k )		// 判断这个非零元是否位于M中第k列
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
		int num[M.cols];		// num数组用来记录M中第col列中非零元个数
		int cpot[M.cols];		// cpot数组用来记录M中第col列中第一个非零元在T.data[]中的下标值
		int i, n, p = 0;		// i表示M中的列标，n表示非零元序号，p表示非零元在T.data[]中对应的的下标值
		for(i = 0; i < M.cols; i++)
			num[i] = 0;						// 初始化
		for(n = 0; n < M.nums; n++)			// 从M的第一个非零元开始xuyuan2018-11-23-21:47:13
			num[M.data[n].col-1]++;			// num[M.data[n].col-1]表示M中第n个非零元所在的的列的非零元的个数
		cpot[0] = 0;						// cpot[0]表示M中第1列第一个非零元在T.data[]中的下标值
		for(i = 1; i < M.cols; i++)			// M第一列第一个非零元的位置已经指定，故从cpot[1]开始
			cpot[i] = cpot[i-1] + num[i-1];	// cpot[i]表示M中第i+1列第一个非零元的位置，它与cpot[i-1]之间隔着num[i-1]个下标
		for(n = 0; n < M.nums; n++)
		{
			p = cpot[M.data[n].col-1]++;	// cpot[M.data[n].col-1]表示M中第n个非零元所在的列的第一个非零元在T.data[]中的下标值
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
	printf("你输入的稀疏矩阵为：\n");
	Print(M);
	
	Transpose(M,&T1);
	printf("一般转置后：\n");
	Print(T1);
	
	Transpose_faster(M,&T2);
	printf("快速转置后：\n");
	Print(T2);
	
	
	return 0;
}


