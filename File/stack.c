#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define STACK_INIT_SIZE 5
#define INCREMENT 1

typedef char ElemType;

typedef struct
{
	int size;
	ElemType *base;
	ElemType *top;
}Stack;

void InitStack(Stack *S)
{
	S->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if(!S->base)
		printf("ERROR !\n");                                                // 初始化失败
	S->top = S->base;
	S->size = STACK_INIT_SIZE;
}

void PushStack(Stack *S, ElemType e)										// 在栈顶添加新元素
{
	if(e != '?')
	{
		if(S->top - S->base >= S->size)                                     //  栈满
		{
			S->base = (ElemType *)realloc(S->base,(STACK_INIT_SIZE + INCREMENT) * sizeof(ElemType));
			S->top = S->base + S->size;
			S->size += INCREMENT;
		}
	*S->top = e;
	S->top ++;
	}
}

ElemType GetTop(Stack S)													// 返回栈顶元素	
{
	return *(S.top - 1);
}

void Delete(Stack *S)														// 删除栈顶元素
{
	free(S->top);
	S->top--;
	S->size--;
}

void Destroy(Stack *S)
{
	S->top = S->base = NULL;
	S->size = 0;
	free(S->base);
}

void Print(Stack S)
{
	while(S.top != S.base){
		printf(" %c",*(S.top - 1));
		*S.top --;
	}
	
	printf("\n");
}

void Print_info(Stack S)
{
	printf("top : %d\n",S.top);
	printf("base : %d\n",S.base);
	printf("size : %d\n",S.size);
}

int main()
{
	Stack S;
	ElemType e, ch1, ch2;
	InitStack(&S);
	
	printf("请依次键入栈元素（以 ? 结束）：");
	while(e != '?'){
		scanf("%c",&e);
		PushStack(&S,e);
	}
	getchar();
	printf("你建立的栈为（按照后进先出的顺序打印）：");
	Print(S);
	Print_info(S);
	printf("\n");
	
	printf("请输入你想添加的元素：");
	scanf("%c",&e);
	getchar();
	PushStack(&S,e);
	printf("添加成功，新的栈为：");
	Print(S);
	Print_info(S);
	printf("\n");
	
	printf("栈顶元素为：%c\n",GetTop(S));
	printf("你确定要删除栈顶元素吗（y/n）？");
	scanf("%c",&ch1);
	getchar();
	if(ch1 == 'y'){
		Delete(&S);
		printf("删除成功，新栈为：");
		Print(S);
		printf("新的栈顶元素为：%c\n",GetTop(S));
	}
	Print_info(S);
	printf("\n");
	
	printf("销毁栈？（y/n）");
	scanf("%c",&ch2);
	getchar();
	if(ch2 == 'y'){
		Destroy(&S);
		printf("销毁成功\n");
	}
	Print_info(S);
	Print(S);
	printf("\n");
	
	return 0;
}



















