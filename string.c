//														�ѷ��䴮
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>

#define INIT_SIZE 50
#define INCRESMENT 10

typedef struct
{
	char *ch;
	int length;
	int size;
}HString;

void Init(HString *S)
{
	S->ch = (char *)malloc(sizeof(char));
	if(!S->ch)
		printf("��ʼ��ʧ�� !");
	S->length = 0;
	S->size = INIT_SIZE;
}

void Append(HString *S, char e)
{
	if( e != '/')
	{
		if(S->length >= S->size)
		{
			S->ch = (char *)realloc(S->ch,(INIT_SIZE + INCRESMENT) * sizeof(char));
			S->size += INCRESMENT;
		}
		S->ch[S->length] = e;
		S->length++;
	}
}

void Insert(HString *S, char e, int n)
{
	int i;
	if(n >= 1 && n <= S->length + 1)
	{
		if(S->length >= S->size)
		{
			S->ch = (char *)realloc(S->ch,(INIT_SIZE + INCRESMENT) * sizeof(char));
			S->size += INCRESMENT;
		}
		for(i = S->length; i >= n; i--)
		{
			S->ch[i] = S->ch[i-1];
		}
		S->ch[n-1] = e;
		S->length++;
	}
	else
		printf("λ�򳬳���Χ !");
}

void Delete(HString *S, int n)
{
	int i;
	if(n >= 1 && n <= S->length){
		for(i = n; i < S->length; i++)
		{
			S->ch[i-1] = S->ch[i];
		}
		S->length--;
	}
	else
		printf("λ�򳬳���Χ !");
}

/*void Change(HString *S, int n, char e)
{
	if(n >= 1 && n <= S->length){
		S->ch[n-1] = e;
	}
	else
		printf("λ�򳬳���Χ ��");
}*/

void Substring(HString S, HString *Sub, int pos, int len)
{
	int i;
	Init(Sub);
	if(Sub->length != 0)
		free(Sub->ch);
	if( pos >= 1 && pos <= S.length && len >= 0 && pos+len-1 <= S.length )
	{
		Sub->ch = (char *)realloc(Sub->ch,len * sizeof(char));
		Sub->size += len;
		for(i = 0; i < len; i++)
		{
			Sub->ch[i] = S.ch[pos-1];
			Sub->length++;
			pos++;
		}
	}
	/*
	else
		printf("ERROR !\n");
	*/
}

int Compare(HString S1, HString S2)
{
	int i;
	if(S1.length != S2.length)
		return -1;
	else
	{
		for(i = 0; i < S1.length; i++)
		{
			if(S1.ch[i] == S2.ch[i])
				continue;
			else
			{
				return -1;
				break;
			}	
		}
	}
	return 1;
}

void Concat(HString *T, HString *S1, HString *S2)
{
	int i, j;
	if(T->length != 0)
		free(T->ch);
	T->ch = (char *)realloc(T->ch,(S1->length + S2->length) * sizeof(char));
	T->length = S1->length + S2->length;
	for(i = 0; i < S1->length; i++)
	{
		T->ch[i] = S1->ch[i];
	}
	for(j = 0,i = S1->length; j < S2->length; j++,i++)
	{
		T->ch[i] = S2->ch[j];
	}
}

int Index_1(HString S, HString T)
{
	int i = 0, j = 0;
	if(T.length <= 0 || T.length > S.length)
		return -1;
	else
	{
		while(i < S.length && j < T.length)
		{
			if(S.ch[i] == T.ch[j])
			{
				i++;
				j++;
			}
			else
			{
				i++;
				j=0;
			}
		}
		if(j >= T.length)
			return i-j+1;
		else
			return -1;
	}
}

int Index_2(HString S, HString T)
{
	HString t;
	int len = T.length;
	int i;
	for(i = 0; i+len-1 <= S.length; i++)
	{
		Substring(S,&t,i,len);
		if( Compare(T,t) >= 0 ){
			return i;
			break;
		}
		else
			continue;
	}
	return -1;
}

void Print(HString S)
{
	int i;
	for(i = 0; i < S.length; i++)
	{
		printf(" %c",S.ch[i]);
	}
	printf("\t���ȣ�%d",S.length);
	printf("\n");
}

int main()
{
	int n, pos, len;
	char e, e1, e2, e3, ch;
	HString S, S1, S2, T, Sub, s;
	
	Init(&S);
	Init(&S1);
	Init(&S2);
	Init(&T);
	Init(&s);
	
	printf("���������봮��Ԫ�أ��� / ��������");
	while(1)
	{
		e = getche();
		Append(&S,e);
		if(e == '/')
			break;
	}
	
	printf("\n�㽨���Ĵ�Ϊ��");
	Print(S);
	printf("\n");
	
	printf("��������������Ԫ���Լ�λ���á�,����������");
	scanf("%c,%d",&ch,&n);
	getchar();
	Insert(&S, ch, n);
	printf("�´�Ϊ��");
	Print(S);
	printf("\n");
	
	printf("����ɾ���Ǹ�λ���ϵ�Ԫ�أ�1~%d����",S.length);
	scanf("%d",&n);
	getchar();
	Delete(&S,n);
	printf("�´�Ϊ��");
	Print(S);
	printf("\n");
	
	printf("������һ��λ��pos��1~%d����",S.length);
	scanf("%d",&pos);
	getchar();
	printf("�����������ȡ�ĳ��� len��");
	scanf("%d",&len);
	getchar();
	Substring(S,&Sub,pos,len);
	printf("���ȡ���Ӵ�Ϊ��");
	Print(Sub);
	printf("\n");
	
	
	printf("���������������ж������Ƿ���ͬ���� / ��������\n");
	printf("S1 : ");
	while(1)
	{
		e1 = getche();
		Append(&S1,e1);
		if(e1 == '/')
			break;
	}
	printf("\n");
	printf("S2 : ");
	while(1)
	{
		e2 = getche();
		Append(&S2,e2);
		if(e2 == '/')
			break;
	}
	printf("\n\n");
	if( Compare(S1,S2) >= 0 )
		printf("S1��S2��ͬ");
	else
		printf("S1��S2����ͬ");
	printf("\n");
	
	printf("S1��S2���Ӻ���´���");
	Concat(&T,&S1,&S2);
	Print(T);
	printf("\n");
	
	printf("������һ�������������Ƿ������S���� / ������:");
	while(1)
	{
		e3 = getche();
		Append(&s,e3);
		if(e3 == '/')
			break;
	}
	printf("\n");
	if( Index_2(S,s) > 0 )
		printf("����S���Ӵ�����ʼλ��Ϊ��%d������Ϊ%d.\n",Index_2(S,s),s.length);
	else
		printf("S�в���������Ӵ���\n");
	
	printf("\n");
	return 0;
}










/*�����������⣺
	1.�������������Init(&S)�� Init(&Sub)�������λ�ã���ôSubstring()�����ͻ�������⣻�������������
	  Init(Sub)�ŵ�Substring()����������Խ��������⡣
	2.����������������Init(&T)�ŵ�Concat()�������棬�ͻ����֮ǰһֱ���������⣺�����Ӵ��ĳ���һ����
	  ����ʼ���ȳ���ͻ�ֹͣ���У�С�ڳ�ʼ���ȵĻ��Ͳ�������⡣
	3.insertʱ������������֣�ֻ�ܲ���0~9�����֣��������볬��ʮ�����֡�
	4.�ܷ𣬴��Ƚ�ʱ���ȳ���5��ʱ���ᱨ�����������԰ѳ�ʼ���ȵ����ˡ�
	5.д�������ִ������ĺ�����һ���ǰ������ϵ���д�ģ���һ����ͨ������Sub��Compare��������������ɵ�
	  �������ϻ������˱�ķ�����ʱ�临�Ӷȸ��ͣ����һ�û����������Ҫд�������ˡ�
*/











