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
	//printf("%c\t%d\n",T->data,T);			//��ϸ��Ϣ��ӡ
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
//	���ҽ��p�����ֵ�
{
	BiTree q;
	q = Parent(T,p);
	if( q->lchild && q->lchild != p )		//p�����ֵܶ��Ҳ���p�Լ�
		return q->lchild;
	else
		return NULL;
}

BiTree RightSibling(BiTree T, BiTree p)
//	���ҽ��p�����ֵ�
{
	BiTree q;
	q = Parent(T,p);
	if( q->rchild && q->rchild != p )		//p�����ֵܶ��Ҳ���p�Լ�
		return q->rchild;
	else
		return NULL;
}

void InsertChild(BiTree *T, BiTree *p, char flag, BiTree *c)
{
	BiTree q;
	if( *T && *c && !((*c)->rchild) )		//T���գ�c���գ�c��������
	{
		if( flag == 'l' )			//flagֵΪl������cΪp��������
		{
			q = (*p)->lchild;
			(*p)->lchild = *c;
			(*c)->rchild = q;
		}
		else if( flag == 'r' )		//flagֵΪr������cΪp��������
		{
			q = (*p)->rchild;
			(*p)->rchild = *c;
			(*c)->rchild = q;
		}
		else
			printf("Error !\n");
	}
	else
		printf("Error !\n");
}

void DeleteChild(BiTree *T, BiTree *p, char flag)
{
	if( *T && *p )
	{
		if( flag == 'l' )
		{
			free( (*p)->lchild );
			(*p)->lchild = NULL;
		}
		else if( flag == 'r' )
		{
			free( (*p)->rchild );
			(*p)->rchild = NULL;
		}
		else
			printf("Error !\n");
	}
	else
		printf("Error !\n");
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
	ElemType ch, flag;
	BiTree T, p, p1, p2, p3, p4, copy, child, New;
	
	InitBiTree(&T);
	InitBiTree(&p);
	InitBiTree(&p1);
	InitBiTree(&p2);
	InitBiTree(&copy);
	InitBiTree(&child);

	printf("= = = > �밴����Ӧ����˳��������ֵ��");
	CreateBiTree(&T);
	getchar();
	printf("\t���������������");
	PreOrderTraverse(T,function);
	printf("\n\t���������������");
	InOrderTraverse(T,function);
	printf("\n\t���������������");
	PostOrderTraverse(T,function);
	printf("\n");
	
	CountNode(T,&n);
	printf("\t�˶����������Ϊ��%d\t�ڵ���Ϊ��%d\n",BiTreeDepth(T),n);
	printf("\t�����ĵ�ַΪ��%d\t������������Ԫ��Ϊ��%c\n",Root(T),Root(T)->data);
	
	printf("\n= = = > ����ɾ���ĸ����������� ");
	ch = getche();
	p = Locate(T,ch);
	printf("\n\t����ɾ�� %c ���������������������� l / r ��");
	flag = getche();
	DeleteChild(&T,&p,flag);
	printf("\n\tɾ���ɹ����������ɾ�����������");
	PreOrderTraverse(T,function);
	printf("\n");
	
	printf("\n= = = > ������һ���ַ��������������ĵ�ַ��");
	ch = getche();
	if( Locate(T,ch) )
	{
		printf("\n\t������ַ��Ľ���ַΪ��%d\n",Locate(T,ch));
	}
	else
		printf("\n\t��������û�иý�㣡\n");
	printf("\n");
	
	printf("= = = > ������һ���ַ���������������˫�ף�");
	ch = getche();
	p = Locate(T,ch);
	if( p == Root(T) )
		printf("\n\t�ý��Ϊ����㣬��˫��\n");
	else if(p)
		printf("\n\t�ý���˫�׵�ַΪ��%d\t�������Ԫ��Ϊ��%c\n",Parent(T,p),Parent(T,p)->data);
	else
		printf("\n\t��������û�иý�㣡\n");
	printf("\n");
	
	printf("= = = > ������һ���ַ��������������ĺ��ӣ�");
	ch = getche();
	p1 = Locate(T,ch);
	if(p1)
	{
		if( BiTreeDepth(p1) >= 1 )
		{
			if( BiTreeDepth(p1)==1 )
				printf("\n\t�ý��ΪҶ�ӽ�㣬û�к���\n");
			if( !BiTreeEmpty(p1->lchild) )
			{
				printf("\n\t�ý�������Ϊ��%d\t�������Ԫ��Ϊ��%c\n",LeftChild(T,p1),LeftChild(T,p1)->data);
				if( !BiTreeEmpty(p1->rchild) )
					printf("\t�ý����Һ���Ϊ��%d\t�������Ԫ��Ϊ��%c\n",RightChild(T,p1),RightChild(T,p1)->data);
			}
		}
	}
	else
		printf("\n\t��������û�иý�㣡\n");
	printf("\n");
	
	printf("= = = > ������һ���ַ����������������ֵܣ�");
	ch = getche();
	p2 = Locate(T,ch);		//��λ
	p3 = Parent(T,p2);		//p3��ʾp2�ĸ�ĸ
	if(p2)
	{
		if( p2 == Root(T) )
			printf("\n\t�ý��Ϊ����㣬û���ֵ�\n");
		if( LeftSibling(T,p2) )
			printf("\n\t�ý������ֵ�Ϊ��%d\t�������Ԫ��Ϊ��%c\n",LeftSibling(T,p2),LeftSibling(T,p2)->data);
		if( RightSibling(T,p2) )
			printf("\n\t�ý������ֵ�Ϊ��%d\t�������Ԫ��Ϊ��%c\n",RightSibling(T,p2),RightSibling(T,p2)->data);
		
	}
	else
		printf("\n\t��������û�иý�㣡\n");
	printf("\n");
	
	printf("= = = > ������Ӧ˳��������������������");
	CreateBiTree(&child);
	printf("\t������������λ�ã�");
	ch = getche();
	p4 = Locate(T,ch);
	printf("\t%d\n",p4);
	printf("\t������뵽%c�������������������� l / r ����",p4->data);
	flag = getche();
	InsertChild(&T,&p4,flag,&child);
	printf("\n\tBingo ! �������������");
	PreOrderTraverse(T,function);
	printf("\n");
	
	printf("\n= = = > ����Ҫ������ö������𣿣� y / n ��");
	flag = getche();
	if( flag == 'y' )
	{
		CopyBiTree(T,copy);
		printf("\n\tBingo ! ���������������");
		PreOrderTraverse(T,function);
		printf("\n");
	}
	printf("\n");
	
	printf("= = = > ��Ҫ��ն������𣿣� y / n ��");
	flag = getche();
	if( flag == 'y' )
	{
		DestroyBiTree(&T);
		printf("\n\tBingo ! ���������������");
		PreOrderTraverse(T,function);
		printf("\n");
	}
	printf("\n");
	
	printf("\n");
	return 0;
}





/*		
	-+a##*b##-c##d##/e##f##

	T:	12##3##
		
	c:	45###

	1.Locate���Һ��������������м����ַ�chʱ����scanf�ͻ�����⣬�鲻��Ҫ����ַ�������
	  �����getche�Ϳ��Բ鵽�������Ҿ������Locate����Ҳ�е����⣬���Ҫ���ҵ��ַ�����
	  �������С������� ���ԣ�����û���⣬�����ڵĻ��ͻ᷵��0.
	2.CountNode����ͳ�Ƶ������н��ĸ���.
	3.��������ͷǵݹ������ûд������ûʱ���� ��Щ��д.
*/

