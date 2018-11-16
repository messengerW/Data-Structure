//														堆分配串
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
		printf("初始化失败 !");
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
		printf("位序超出范围 !");
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
		printf("位序超出范围 !");
}

/*void Change(HString *S, int n, char e)
{
	if(n >= 1 && n <= S->length){
		S->ch[n-1] = e;
	}
	else
		printf("位序超出范围 ！");
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
	printf("\t长度：%d",S.length);
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
	
	printf("请依次输入串的元素（以 / 结束）：");
	while(1)
	{
		e = getche();
		Append(&S,e);
		if(e == '/')
			break;
	}
	
	printf("\n你建立的串为：");
	Print(S);
	printf("\n");
	
	printf("请输入你想插入的元素以及位序（用“,”隔开）：");
	scanf("%c,%d",&ch,&n);
	getchar();
	Insert(&S, ch, n);
	printf("新串为：");
	Print(S);
	printf("\n");
	
	printf("你想删除那个位序上的元素（1~%d）？",S.length);
	scanf("%d",&n);
	getchar();
	Delete(&S,n);
	printf("新串为：");
	Print(S);
	printf("\n");
	
	printf("请输入一个位序pos（1~%d）：",S.length);
	scanf("%d",&pos);
	getchar();
	printf("请输入你想截取的长度 len：");
	scanf("%d",&len);
	getchar();
	Substring(S,&Sub,pos,len);
	printf("你截取的子串为：");
	Print(Sub);
	printf("\n");
	
	
	printf("请输入两个串，判断它们是否相同（以 / 结束）：\n");
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
		printf("S1与S2相同");
	else
		printf("S1与S2不相同");
	printf("\n");
	
	printf("S1与S2联接后的新串：");
	Concat(&T,&S1,&S2);
	Print(T);
	printf("\n");
	
	printf("请输入一个串，检索它是否存在于S（以 / 结束）:");
	while(1)
	{
		e3 = getche();
		Append(&s,e3);
		if(e3 == '/')
			break;
	}
	printf("\n");
	if( Index_2(S,s) > 0 )
		printf("它是S的子串，起始位置为：%d，长度为%d.\n",Index_2(S,s),s.length);
	else
		printf("S中不存在这个子串！\n");
	
	printf("\n");
	return 0;
}










/*这个程序的问题：
	1.如果把主函数中Init(&S)和 Init(&Sub)两句调换位置，那么Substring()函数就会出现问题；把主函数里面的
	  Init(Sub)放到Substring()函数里面可以解决这个问题。
	2.如果把主函数里面的Init(&T)放到Concat()函数里面，就会出现之前一直遇到的问题：两个子串的长度一旦超
	  过初始长度程序就会停止运行，小于初始长度的话就不会出问题。
	3.insert时，如果插入数字，只能插入0~9的数字，不能输入超过十的数字。
	4.很佛，串比较时长度超过5有时还会报错，所以我索性把初始长度调大了。
	5.写了两个字串搜索的函数，一个是按照书上的来写的，另一个是通过利用Sub、Compare这两个函数来完成的
	  另外书上还介绍了别的方法，时间复杂度更低，但我还没看。接下来要写二叉树了。
*/











