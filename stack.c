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
		printf("ERROR !\n");                                                // ��ʼ��ʧ��
	S->top = S->base;
	S->size = STACK_INIT_SIZE;
}

void PushStack(Stack *S, ElemType e)										// ��ջ�������Ԫ��
{
	if(e != '?')
	{
		if(S->top - S->base >= S->size)                                     //  ջ��
		{
			S->base = (ElemType *)realloc(S->base,(STACK_INIT_SIZE + INCREMENT) * sizeof(ElemType));
			S->top = S->base + S->size;
			S->size += INCREMENT;
		}
	*S->top = e;
	S->top ++;
	}
}

ElemType GetTop(Stack S)													// ����ջ��Ԫ��	
{
	return *(S.top - 1);
}

void Delete(Stack *S)														// ɾ��ջ��Ԫ��
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
	
	printf("�����μ���ջԪ�أ��� ? ��������");
	while(e != '?'){
		scanf("%c",&e);
		PushStack(&S,e);
	}
	getchar();
	printf("�㽨����ջΪ�����պ���ȳ���˳���ӡ����");
	Print(S);
	Print_info(S);
	printf("\n");
	
	printf("������������ӵ�Ԫ�أ�");
	scanf("%c",&e);
	getchar();
	PushStack(&S,e);
	printf("��ӳɹ����µ�ջΪ��");
	Print(S);
	Print_info(S);
	printf("\n");
	
	printf("ջ��Ԫ��Ϊ��%c\n",GetTop(S));
	printf("��ȷ��Ҫɾ��ջ��Ԫ����y/n����");
	scanf("%c",&ch1);
	getchar();
	if(ch1 == 'y'){
		Delete(&S);
		printf("ɾ���ɹ�����ջΪ��");
		Print(S);
		printf("�µ�ջ��Ԫ��Ϊ��%c\n",GetTop(S));
	}
	Print_info(S);
	printf("\n");
	
	printf("����ջ����y/n��");
	scanf("%c",&ch2);
	getchar();
	if(ch2 == 'y'){
		Destroy(&S);
		printf("���ٳɹ�\n");
	}
	Print_info(S);
	Print(S);
	printf("\n");
	
	return 0;
}



















