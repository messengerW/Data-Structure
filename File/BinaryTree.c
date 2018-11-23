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
	//printf("%c\t%d\n",T->data,T);			//详细信息打印
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
//	查找结点p的左兄弟
{
	BiTree q;
	q = Parent(T,p);
	if( q->lchild && q->lchild != p )		//p有左兄弟而且不是p自己
		return q->lchild;
	else
		return NULL;
}

BiTree RightSibling(BiTree T, BiTree p)
//	查找结点p的右兄弟
{
	BiTree q;
	q = Parent(T,p);
	if( q->rchild && q->rchild != p )		//p有右兄弟而且不是p自己
		return q->rchild;
	else
		return NULL;
}

void InsertChild(BiTree *T, BiTree *p, char flag, BiTree *c)
{
	BiTree q;
	if( *T && *c && !((*c)->rchild) )		//T不空，c不空，c右子树空
	{
		if( flag == 'l' )			//flag值为l，插入c为p的左子树
		{
			q = (*p)->lchild;
			(*p)->lchild = *c;
			(*c)->rchild = q;
		}
		else if( flag == 'r' )		//flag值为r，插入c为p的右子树
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
	ElemType ch, flag;
	BiTree T, p, p1, p2, p3, p4, copy, child, New;
	
	InitBiTree(&T);
	InitBiTree(&p);
	InitBiTree(&p1);
	InitBiTree(&p2);
	InitBiTree(&copy);
	InitBiTree(&child);

	printf("= = = > 请按照相应遍历顺序输入结点值：");
	CreateBiTree(&T);
	getchar();
	printf("\t先序遍历二叉树：");
	PreOrderTraverse(T,function);
	printf("\n\t中序遍历二叉树：");
	InOrderTraverse(T,function);
	printf("\n\t后序遍历二叉树：");
	PostOrderTraverse(T,function);
	printf("\n");
	
	CountNode(T,&n);
	printf("\t此二叉树的深度为：%d\t节点数为：%d\n",BiTreeDepth(T),n);
	printf("\t根结点的地址为：%d\t根结点所储存的元素为：%c\n",Root(T),Root(T)->data);
	
	printf("\n= = = > 你想删除哪个结点的子树？ ");
	ch = getche();
	p = Locate(T,ch);
	printf("\n\t你想删除 %c 的左子树还是右子树？（ l / r ）");
	flag = getche();
	DeleteChild(&T,&p,flag);
	printf("\n\t删除成功，先序遍历删除后的新树：");
	PreOrderTraverse(T,function);
	printf("\n");
	
	printf("\n= = = > 你输入一个字符，我来查找它的地址：");
	ch = getche();
	if( Locate(T,ch) )
	{
		printf("\n\t储存该字符的结点地址为：%d\n",Locate(T,ch));
	}
	else
		printf("\n\t二叉树中没有该结点！\n");
	printf("\n");
	
	printf("= = = > 你输入一个字符，我来查找它的双亲：");
	ch = getche();
	p = Locate(T,ch);
	if( p == Root(T) )
		printf("\n\t该结点为根结点，无双亲\n");
	else if(p)
		printf("\n\t该结点的双亲地址为：%d\t所储存的元素为：%c\n",Parent(T,p),Parent(T,p)->data);
	else
		printf("\n\t二叉树中没有该结点！\n");
	printf("\n");
	
	printf("= = = > 你输入一个字符，我来查找它的孩子：");
	ch = getche();
	p1 = Locate(T,ch);
	if(p1)
	{
		if( BiTreeDepth(p1) >= 1 )
		{
			if( BiTreeDepth(p1)==1 )
				printf("\n\t该结点为叶子结点，没有孩子\n");
			if( !BiTreeEmpty(p1->lchild) )
			{
				printf("\n\t该结点的左孩子为：%d\t所储存的元素为：%c\n",LeftChild(T,p1),LeftChild(T,p1)->data);
				if( !BiTreeEmpty(p1->rchild) )
					printf("\t该结点的右孩子为：%d\t所储存的元素为：%c\n",RightChild(T,p1),RightChild(T,p1)->data);
			}
		}
	}
	else
		printf("\n\t二叉树中没有该结点！\n");
	printf("\n");
	
	printf("= = = > 你输入一个字符，我来查找它的兄弟：");
	ch = getche();
	p2 = Locate(T,ch);		//定位
	p3 = Parent(T,p2);		//p3表示p2的父母
	if(p2)
	{
		if( p2 == Root(T) )
			printf("\n\t该结点为根结点，没有兄弟\n");
		if( LeftSibling(T,p2) )
			printf("\n\t该结点的左兄弟为：%d\t所储存的元素为：%c\n",LeftSibling(T,p2),LeftSibling(T,p2)->data);
		if( RightSibling(T,p2) )
			printf("\n\t该结点的右兄弟为：%d\t所储存的元素为：%c\n",RightSibling(T,p2),RightSibling(T,p2)->data);
		
	}
	else
		printf("\n\t二叉树中没有该结点！\n");
	printf("\n");
	
	printf("= = = > 按照相应顺序输入你想插入的子树：");
	CreateBiTree(&child);
	printf("\t输入你想插入的位置：");
	ch = getche();
	p4 = Locate(T,ch);
	printf("\t%d\n",p4);
	printf("\t你想插入到%c的左子树还是右子树（ l / r ）？",p4->data);
	flag = getche();
	InsertChild(&T,&p4,flag,&child);
	printf("\n\tBingo ! 先序遍历新树：");
	PreOrderTraverse(T,function);
	printf("\n");
	
	printf("\n= = = > 你想要复制这棵二叉树吗？（ y / n ）");
	flag = getche();
	if( flag == 'y' )
	{
		CopyBiTree(T,copy);
		printf("\n\tBingo ! 先序遍历二叉树：");
		PreOrderTraverse(T,function);
		printf("\n");
	}
	printf("\n");
	
	printf("= = = > 你要清空二叉树吗？（ y / n ）");
	flag = getche();
	if( flag == 'y' )
	{
		DestroyBiTree(&T);
		printf("\n\tBingo ! 先序遍历二叉树：");
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

	1.Locate查找函数，在主函数中键入字符ch时，用scanf就会出问题，查不到要查的字符，但是
	  如果用getche就可以查到。另外我觉得这个Locate函数也有点问题，如果要查找的字符不在
	  二叉树中。。。诶 不对，好像没问题，不存在的话就会返回0.
	2.CountNode函数统计的是所有结点的个数.
	3.层序遍历和非递归遍历还没写，今天没时间了 晚些再写.
*/

