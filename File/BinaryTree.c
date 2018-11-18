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
//	应用函数，可视情况更改
{
	printf("%c ",T->data);				//结点元素打印
	//printf("%c\t%d",T->data,T);			//详细信息打印
}

void InitBiTree(BiTree *T)
//	初始化二叉树
{
	T = NULL;
}

void DestroyBiTree(BiTree *T)
//	销毁二叉树
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
//	创建二叉树
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
//	清空二叉树
{
	DestroyBiTree(T);
}

int BiTreeEmpty(BiTree T)
//	判断二叉树是否为空
{
	return T == NULL;
}

int BiTreeDepth(BiTree T)
//	计算树深
{
	int Depth_Left, Depth_Right;
	if(!T)
		return 0;
	Depth_Left = BiTreeDepth(T->lchild);
	Depth_Right = BiTreeDepth(T->rchild);
	return Depth_Left > Depth_Right ? Depth_Left + 1 : Depth_Right + 1;
}

BiTree Locate(BiTree T, ElemType e)
//	查找树中储存e的结点
{
	if( !T || T->data == e )
		return T;
	else if( Locate(T->lchild,e) )
		return Locate(T->lchild,e);
	else
		return Locate(T->rchild,e);
}

BiTree Root(BiTree T)
//	返回树根
{
	return T;
}

BiTree Parent(BiTree T, BiTree p)
//	查找结点p的双亲
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
//	查找结点p的左孩子
{
	if(p)
		return p->lchild;
	else
		return NULL;
}

BiTree RightChild(BiTree T, BiTree p)
//	查找结点p的右孩子
{
	if(p)
		return p->rchild;
	else
		return NULL;
}

BiTree LeftSibling(BiTree T, BiTree p)
//	查找结点p的??兄弟
{
	BiTree q;
	q = Parent(T,p);
	if( q && q->rchild == p )
		return q->lchild;
	return NULL;
}

BiTree RightSibling(BiTree T, BiTree p)
//	查找结点p的??兄弟
{
	BiTree q;
	q = Parent(T,p);
	if( q && q->lchild == p )
		return q->rchild;
	return NULL;
}

BiTree CopyBiTree(BiTree T, BiTree p)
//	复制二叉树
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
//	计算二叉树的结点个数
{
	if(T)
	{
		CountNode(T->lchild,n);
		CountNode(T->rchild,n);
		(*n)++;
	}
}

void PreOrderTraverse(BiTree T, void(*function)(BiTree T))
//	先序递归遍历二叉树
{
	if(T)
    {
		function(T);
		PreOrderTraverse(T->lchild,function);
		PreOrderTraverse(T->rchild,function);
	}
}

void InOrderTraverse(BiTree T, void(*function)(BiTree T))
//	中序递归遍历二叉树
{
	if(T)
	{
		InOrderTraverse(T->lchild,function);
		function(T);
		InOrderTraverse(T->rchild,function);
	}
}

void PostOrderTraverse(BiTree T, void(*function)(BiTree T))
//	后序递归遍历二叉树
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

	printf("请按照相应遍历顺序输入结点值：");
	CreateBiTree(&T);
	printf("\n");
	
	printf("先序遍历二叉树：");
	PreOrderTraverse(T,function);
	printf("\n");
	printf("中序遍历二叉树：");
	InOrderTraverse(T,function);
	printf("\n");
	printf("后序遍历二叉树：");
	PostOrderTraverse(T,function);
	printf("\n\n");
	
	CountNode(T,&n);
	printf("此二叉树的深度为：%d\t节点数为：%d\n",BiTreeDepth(T),n);
	printf("根结点的地址为：%d\t根结点所储存的元素为：%c\n",Root(T),Root(T)->data);
	
	printf("\n你输入一个字符，我来查找它所在的结点：");
	ch1 = getche();
	if( Locate(T,ch1) )
	{
		printf("\n储存该字符的结点地址为：%d\n",Locate(T,ch1));
	}
	else
		printf("\n二叉树中没有该结点！\n");
	printf("\n");
	
	printf("你输入一个字符，我来查找它的双亲：");
	ch2 = getche();
	p = Locate(T,ch2);
	if( p == Root(T) )
		printf("\n该结点为根结点，无双亲\n");
	else if(p)
		printf("\n该结点的双亲地址为：%d\t所储存的元素为：%c\n",Parent(T,p),Parent(T,p)->data);
	else
		printf("\n二叉树中没有该结点！\n");
	printf("\n");
	
	printf("你输入一个字符，我来查找它的孩子：");
	ch3 = getche();
	p1 = Locate(T,ch3);
	if(p1)
	{
		if( BiTreeDepth(p1) >= 1 )
		{
			if( BiTreeDepth(p1)==1 )
				printf("\n该结点为叶子结点，没有孩子\n");
			if( !BiTreeEmpty(p1->lchild) )
			{
				printf("\n该结点的左孩子为：%d\t所储存的元素为：%c\n",LeftChild(T,p1),LeftChild(T,p1)->data);
				if( !BiTreeEmpty(p1->rchild) )
					printf("该结点的右孩子为：%d\t所储存的元素为：%c\n",RightChild(T,p1),RightChild(T,p1)->data);
			}
		}
	}
	else
		printf("\n二叉树中没有该结点！\n");
	printf("\n");
	
	printf("你输入一个字符，我来查找它的兄弟：");
	ch4 = getche();
	p2 = Locate(T,ch4);
	if(p2)
	{
		if( p2 == Root(T) )
			printf("\n该结点为根结点，没有孩子\n");
		else if( LeftSibling(T,p2) )
			printf("\n该结点的左兄弟为：%d\t所储存的元素为：%c\n",LeftSibling(T,p1),LeftSibling(T,p1)->data);
		else
			printf("\n该结点的右兄弟为：%d\t所储存的元素为：%c\n",RightSibling(T,p1),RightSibling(T,p1)->data);
	}
	else
		printf("\n二叉树中没有该结点！\n");
	printf("\n");
	
	printf("你想要复制这棵二叉树吗？（ y / n ）");
	flag1 = getche();
	if( flag1 == 'y' )
	{
		CopyBiTree(T,copy);
		printf("\n复制成功\t");
		printf("先序遍历二叉树：");
		PreOrderTraverse(T,function);
		printf("\n");
	}
	printf("\n");
	
	printf("你要清空二叉树吗？（ y / n ）");
	flag2 = getche();
	if( flag2 == 'y' )
	{
		DestroyBiTree(&T);
		printf("\n清空成功\t");
		printf("先序遍历二叉树：");
		PreOrderTraverse(T,function);
		printf("\n");
	}
	printf("\n");
	
	printf("\n");
	return 0;
}





/*
	1.Locate查找函数，在主函数中键入字符ch时，用scanf就会出问题，查不到要查的字符，但是
	  如果用getche就可以查到。另外我觉得这个Locate函数也有点问题，如果要查找的字符不在
	  二叉树中。。。诶 不对，好像没问题，不存在的话就会返回0.
	2.CountNode函数统计的是所有结点的个数.
	3.层序遍历和非递归遍历还没写，今天没时间了 晚些再写.
*/

