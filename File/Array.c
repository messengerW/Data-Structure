#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>
#include<stdarg.h>

#define MAX_DIM 8

typedef int ElemType;

typedef struct{
	ElemType *base;
	int dim;
	int *bounds;
	int *constants;
}Array;

void InitArray(Array *A, int dim,...)
{
	int i, elemtotal;
	va_list ap;
	
	if( dim < 1 || dim > MAX_DIM )
		printf("Error_1 !\n");
	A->dim = dim;
	A->bounds = (int *)malloc(dim * sizeof(int));
	if(!A->bounds)
		printf("Error_2 !\n");
	elemtotal = 1;
	va_start(ap,dim);
	for(i = 0; i < dim; i++)
	{
		A->bounds[i] = va_arg(ap,int);
		if( A->bounds[i] < 0 )
			printf("Error_3 !\n");
		elemtotal *= A->bounds[i];
	}
	va_end(ap);
	A->base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
	if(!A->base)
		printf("Error_4 !\n");
	A->constants = (int *)malloc(dim * sizeof(int));
	if(!A->constants)
		printf("Error_5\n");
	A->constants[dim-1] = 1;
	for(i = dim - 2; i >= 0; --i)
	{
		A->constants[i] = A->bounds[i+1] * A->constants[i+1];
	}
	printf("Initialized successfully. The number of elems is : %d\n",elemtotal);
}

void CreateArray(Array *A)
{
	int i, n, elemtotal = 1;
	for(i = 0; i < A->dim; i++)
		elemtotal *= A->bounds[i];
	printf("你创建的是一个 %d 维数组，一共有 %d 个元素\n",A->dim,elemtotal);
	printf("\n= = = > 请按照行序，从低维度到高纬度依次键入这 %d 个元素：\n",elemtotal);
	for(n = 0; n < elemtotal; n++)
	{
		printf("\t%d => ",n+1);
		scanf("%d",&A->base[n]);
	}
	printf("\nThe ayyar has been created successfully.\n");
}

void DestroyArray(Array *A)
{
	if(!A->base)
		printf("Error_6\n");
	free(A->base);
	A->base = NULL;
	
	if(!A->bounds)
		printf("Error_7\n");
	free(A->bounds);
	A->bounds = NULL;
	
	if(!A->constants)
		printf("Error_8\n");
	free(A->constants);
	A->constants = NULL;
}

int Locate(Array A, int dim, ...)
{
	int i, ind, off = 0;
	va_list ap;
	
	va_start(ap,dim);
	for(i = 0; i < A.dim; i++)
	{
		ind = va_arg(ap,int);
		if( ind < 0 || ind >= A.bounds[i] )
			return 0;						// 键入的维长度非法
		off += A.constants[i] * ind;
	}
	return off;			// off即为多维坐标在一维数组base[]中对应的的下标值
}

void Value(Array A, ElemType *e, int pos)
{
	*e = A.base[pos];
}

void Assign(Array *A, ElemType e, int pos)
{
	A->base[pos] = e;
}

int main()
{
	Array A;
	ElemType e;
	int dim, i, n, len[MAX_DIM], pos[MAX_DIM];
	
	printf("= = = > 你想建立一个几维的数组（不超过8维）？");
	scanf("%d",&dim);
	for(i = 0; i < MAX_DIM; i++)
		len[i] = pos[i] = 0;	
	printf("\n= = = > 请输入各维的长度\n");
	for(i = 0; i < dim; i++)
	{
		printf("\t第%d维的长度： ",i+1);
		scanf("%d",&len[i]);
	}
	InitArray(&A,dim,len[0],len[1],len[2],len[3],len[4],len[5],len[6],len[7]);
	CreateArray(&A);
	
	printf("\n= = = > 请输入各维的坐标\n");
	for(i = 0; i < dim; i++)
	{
		printf("\t第%d维的下标： ",i+1);
		scanf("%d",&pos[i]);
	}
	// 注意：键入的下标值一定要减一后再传入Locate函数
	n = Locate(A,dim,pos[0]-1,pos[1]-1,pos[2]-1,pos[3]-1,pos[4]-1,pos[5]-1,pos[6]-1,pos[7]-1);
	printf("\t你查找的坐标对应的元素为： %d\n",A.base[n]);
	printf("\n= = = > 你想将该坐标上的元素重新赋值： ");
	scanf("%d",&e);
	Assign(&A,e,n);
	printf("\t赋值成功，新的元素值为：%d\n",A.base[n]);
	
	return 0;
}















