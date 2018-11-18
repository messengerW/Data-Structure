#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>

typedef char ElemType;

typedef struct BiTreeNode{
	ElemType data;
	struct BiTreeNode *lchild;
	struct BiTreeNode *rchild;
}BiTreeNode, *BiTree;

void function(BiTree T)
//	Ӧ�ú����������������
{
	printf("%c ",T->data);				//���Ԫ�ش�ӡ
	//printf("%c\t%d",T->data,T);			//��ϸ��Ϣ��ӡ
}

void InitBiTree(BiTree *T)
//	��ʼ��������
{
	T = NULL;
}

void DestroyBiTree(BiTree *T)
//	���ٶ�����
{
	if(*T)
	{
		DestroyBiTree(&(*T)->lchild);
		DestroyBiTree(&(*T)->rchild);
		free(*T);
	}
	*T = NULL;
}

void CreateBiTree(BiTree *T)
//	����������
{
	char ch;
    scanf("%c",&ch);
    if(ch == '#')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTreeNode));
		(*T)->data = ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}

void ClearBiTree(BiTree *T)
//	��ն�����
{
	DestroyBiTree(T);
}

int BiTreeEmpty(BiTree T)
//	�ж϶������Ƿ�Ϊ��
{
	return T == NULL;
}

int BiTreeDepth(BiTree T)
//	��������
{
	int Depth_Left, Depth_Right;
	if(!T)
		return 0;
	Depth_Left = BiTreeDepth(T->lchild);
	Depth_Right = BiTreeDepth(T->rchild);
	return Depth_Left > Depth_Right ? Depth_Left + 1 : Depth_Right + 1;
}

BiTree Locate(BiTree T, ElemType e)
//	�������д���e�Ľ��
{
	if( !T || T->data == e )
		return T;
	else if( Locate(T->lchild,e) )
		return Locate(T->lchild,e);
	else
		return Locate(T->rchild,e);
}

BiTree Root(BiTree T)
//	��������
{
	return T;
}

BiTree Parent(BiTree T, BiTree p)
//	���ҽ��p��˫��
{
	if( T == NULL || T == p )
		return NULL;
	else if( T->lchild == p || T->rchild == p )
		return T;
	else if( Parent(T->lchild,p) )
		return Parent(T->lchild,p);
	else
		return Parent(T->rchild,p);
}

BiTree LeftChild(BiTree T, BiTree p)
//	���ҽ��p������
{
	if(p)
		return p->lchild;
	else
		return NULL;
}

BiTree RightChild(BiTree T, BiTree p)
//	���ҽ��p���Һ���
{
	if(p)
		return p->rchild;
	else
		return NULL;
}

BiTree LeftSibling(BiTree T, BiTree p)
//	���ҽ��p��??�ֵ�
{
	BiTree q;
	q = Parent(T,p);
	if( q && q->rchild == p )
		return q->lchild;
	return NULL;
}

BiTree RightSibling(BiTree T, BiTree p)
//	���ҽ��p��??�ֵ�
{
	BiTree q;
	q = Parent(T,p);
	if( q && q->lchild == p )
		return q->rchild;
	return NULL;
}

BiTree CopyBiTree(BiTree T, BiTree p)
//	���ƶ�����
{
	if(T)
		return NULL;
	p = (BiTree)malloc(sizeof(BiTreeNode));
	p->data = T->data;
	p->lchild = CopyBiTree(T->lchild,p);
	p->rchild = CopyBiTree(T->rchild,p);
	return p;
}

void CountNode(BiTree T, int *n)
//	����������Ľ�����
{
	if(T)
	{
		CountNode(T->lchild,n);
		CountNode(T->rchild,n);
		(*n)++;
	}
}

void PreOrderTraverse(BiTree T, void(*function)(BiTree T))
//	����ݹ����������
{
	if(T)
    {
		function(T);
		PreOrderTraverse(T->lchild,function);
		PreOrderTraverse(T->rchild,function);
	}
}

void InOrderTraverse(BiTree T, void(*function)(BiTree T))
//	����ݹ����������
{
	if(T)
	{
		InOrderTraverse(T->lchild,function);
		function(T);
		InOrderTraverse(T->rchild,function);
	}
}

void PostOrderTraverse(BiTree T, void(*function)(BiTree T))
//	����ݹ����������
{
	if(T)
	{
		PostOrderTraverse(T->lchild,function);
		PostOrderTraverse(T->rchild,function);
		function(T);
	}
}



int main()
{
	int n = 0;
	ElemType ch1,ch2,ch3,ch4, flag1, flag2;
	BiTree T, p, p1, p2, copy;
	
	InitBiTree(&T);
	InitBiTree(&p);
	InitBiTree(&p1);
	InitBiTree(&p2);
	InitBiTree(&copy);

	printf("�밴����Ӧ����˳��������ֵ��");
	CreateBiTree(&T);
	printf("\n");
	
	printf("���������������");
	PreOrderTraverse(T,function);
	printf("\n");
	printf("���������������");
	InOrderTraverse(T,function);
	printf("\n");
	printf("���������������");
	PostOrderTraverse(T,function);
	printf("\n\n");
	
	CountNode(T,&n);
	printf("�˶����������Ϊ��%d\t�ڵ���Ϊ��%d\n",BiTreeDepth(T),n);
	printf("�����ĵ�ַΪ��%d\t������������Ԫ��Ϊ��%c\n",Root(T),Root(T)->data);
	
	printf("\n������һ���ַ����������������ڵĽ�㣺");
	ch1 = getche();
	if( Locate(T,ch1) )
	{
		printf("\n������ַ��Ľ���ַΪ��%d\n",Locate(T,ch1));
	}
	else
		printf("\n��������û�иý�㣡\n");
	printf("\n");
	
	printf("������һ���ַ���������������˫�ף�");
	ch2 = getche();
	p = Locate(T,ch2);
	if( p == Root(T) )
		printf("\n�ý��Ϊ����㣬��˫��\n");
	else if(p)
		printf("\n�ý���˫�׵�ַΪ��%d\t�������Ԫ��Ϊ��%c\n",Parent(T,p),Parent(T,p)->data);
	else
		printf("\n��������û�иý�㣡\n");
	printf("\n");
	
	printf("������һ���ַ��������������ĺ��ӣ�");
	ch3 = getche();
	p1 = Locate(T,ch3);
	if(p1)
	{
		if( BiTreeDepth(p1) >= 1 )
		{
			if( BiTreeDepth(p1)==1 )
				printf("\n�ý��ΪҶ�ӽ�㣬û�к���\n");
			if( !BiTreeEmpty(p1->lchild) )
			{
				printf("\n�ý�������Ϊ��%d\t�������Ԫ��Ϊ��%c\n",LeftChild(T,p1),LeftChild(T,p1)->data);
				if( !BiTreeEmpty(p1->rchild) )
					printf("�ý����Һ���Ϊ��%d\t�������Ԫ��Ϊ��%c\n",RightChild(T,p1),RightChild(T,p1)->data);
			}
		}
	}
	else
		printf("\n��������û�иý�㣡\n");
	printf("\n");
	
	printf("������һ���ַ����������������ֵܣ�");
	ch4 = getche();
	p2 = Locate(T,ch4);
	if(p2)
	{
		if( p2 == Root(T) )
			printf("\n�ý��Ϊ����㣬û�к���\n");
		else if( LeftSibling(T,p2) )
			printf("\n�ý������ֵ�Ϊ��%d\t�������Ԫ��Ϊ��%c\n",LeftSibling(T,p1),LeftSibling(T,p1)->data);
		else
			printf("\n�ý������ֵ�Ϊ��%d\t�������Ԫ��Ϊ��%c\n",RightSibling(T,p1),RightSibling(T,p1)->data);
	}
	else
		printf("\n��������û�иý�㣡\n");
	printf("\n");
	
	printf("����Ҫ������ö������𣿣� y / n ��");
	flag1 = getche();
	if( flag1 == 'y' )
	{
		CopyBiTree(T,copy);
		printf("\n���Ƴɹ�\t");
		printf("���������������");
		PreOrderTraverse(T,function);
		printf("\n");
	}
	printf("\n");
	
	printf("��Ҫ��ն������𣿣� y / n ��");
	flag2 = getche();
	if( flag2 == 'y' )
	{
		DestroyBiTree(&T);
		printf("\n��ճɹ�\t");
		printf("���������������");
		PreOrderTraverse(T,function);
		printf("\n");
	}
	printf("\n");
	
	printf("\n");
	return 0;
}





/*
	1.Locate���Һ��������������м����ַ�chʱ����scanf�ͻ�����⣬�鲻��Ҫ����ַ�������
	  �����getche�Ϳ��Բ鵽�������Ҿ������Locate����Ҳ�е����⣬���Ҫ���ҵ��ַ�����
	  �������С������� ���ԣ�����û���⣬�����ڵĻ��ͻ᷵��0.
	2.CountNode����ͳ�Ƶ������н��ĸ���.
	3.��������ͷǵݹ������ûд������ûʱ���� ��Щ��д.
*/

