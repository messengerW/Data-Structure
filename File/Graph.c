#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>
#include<string.h>
#include"queue.h"

#define MAX_NAME 3
#define MAX_VERTEX_NUM 20

typedef int InfoType;
typedef char VertexType[MAX_NAME];

enum GraphKind{DG, DN, UDG, UDN};

typedef struct ArcNode{
	int adjvex;
	InfoType *info;
	struct ArcNode *nextrac;
}ArcNode;

typedef struct VNode{
	VertexType data;
	ArcNode *firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct ALGraph{
	AdjList vertices;
	int vexnum, arcnum;
	int kind;
}ALGraph;

int LocateVex(ALGraph G, VertexType v)
{
	int i;
	for( i = 0; i < G.vexnum; i++ )
	{
		if( strcmp(v,G.vertices[i].data) == 0 )
			return i;	
	}
	return -1;
}

void CreateGraph(ALGraph *G)
{
	int i, j, k, w;
	VertexType va, vb;
	ArcNode *p;
	ALGraph g = *G;
	printf("请输入图的类型（0.有向图，1.有向网，2.无向图，3.无向网）：");
	scanf("%d",&G->kind);
	printf("请输入图的顶点数目和边弧的数目（用空格隔开）：");
	scanf("%d %d",&G->vexnum,&G->arcnum);
	printf("请输入%d个顶点的元素（长度控制在%d以内）：\n",G->vexnum,MAX_NAME);
	for( i = 0; i < G->vexnum; i++)
	{
		scanf("%c",&G->vertices[i].data);
		G->vertices[i].firstarc = NULL;
	}
	if( G->kind == 1 || G->kind == 3 )
		printf("请顺序输入每条弧的权值、弧尾和弧头（用空格隔开）：\n");
	else
		printf("请输入每条弧的弧尾和弧头（用空格隔开）：\n");
	for( k = 0; k < G->arcnum; k++ )
	{
		if( G->kind == 1 || G->kind == 3 )
			scanf("%d %c %c",&w,&va,&vb);
		else
			scanf("%c %c",&va,&vb);
		i = LocateVex(g,va);
		j = LocateVex(g,vb);
		p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = j;
		
		if( G->kind == 1 || G->kind == 3 )
		{
			p->info = (int *)malloc(sizeof(int));
			*(p->info) = w;
		}
		else
			p->info = NULL;
		
		p->nextrac = G->vertices[i].firstarc;
		G->vertices[i].firstarc = p;
		
		if( G->kind >= 2 )
		{
			p = (ArcNode *)malloc(sizeof(ArcNode));
			p->adjvex = i;
			if( G->kind == 3 )
			{
				p->info = (int *)malloc(sizeof(int));
				*(p->info) = w;
			}
			else
				p->info = NULL;
			p->nextrac = G->vertices[i].firstarc;
			G->vertices[i].firstarc = p;
		}
	}
}

void DestroyGraph(ALGraph *G)
{
	int i;
	ArcNode *p, *q;
	G->vexnum = 0;
	G->arcnum = 0;
	for( i = 0; i < G->vexnum; i++ )
	{
		p = G->vertices[i].firstarc;
		while(p)
		{
			q = p->nextrac;
			if( G->kind == 1 || G->kind == 3 )
				p->info = NULL;
			p = NULL;
			p = q;
		}
	}
}

VNode GetVex(ALGraph G, int pos)
{
	if( pos >= G.vexnum || pos < 0 )
		printf("Error1 !\n");
	return G.vertices[pos];
}

void PutVex(ALGraph *G, VertexType v, VertexType e)
{
	int i;
	ALGraph g = *G;
	i = LocateVex(g,v);
	if( i > -1 )
		strcpy(G->vertices[i].data,e);
	else
		printf("Error2 !\n");
}

int FirstAdjVex(ALGraph G, int pos)
{
	ArcNode *p;
	p = G.vertices[pos].firstarc;
	if(p)
		return p->adjvex;
	else
		return -1;
}

int NextAdjVex(ALGraph G, int pos1, int pos2)
{
	ArcNode *p;
	p = G.vertices[pos1].firstarc;
	while( p && p->adjvex != pos2)
		p = p->nextrac;
	if( p && p->nextrac )
		return p->nextrac->adjvex;
	else
		return -1;
}

void InsertVex(ALGraph *G, VertexType v)
{
	strcpy(G->vertices[G->vexnum].data,v);
	G->vertices[G->vexnum].firstarc = NULL;
	G->vexnum++;
}

void DeleteVex(ALGraph *G, VertexType v)
{
	int i, j;
	ALGraph g = *G;
	ArcNode *p, *q;
	j = LocateVex(g,v);
	if( j < 0 )
		printf("Error3 !\n");
	p = G->vertices[j].firstarc;
	while(p)
	{
		q = p;
		p = p->nextrac;
		if( G->kind == 1 || G->kind == 3 )
			q->info = NULL;
		q = NULL;
		G->arcnum--;
	}
	G->vexnum--;
	for( i = j; i < G->vexnum; i++)
		G->vertices[i] = G->vertices[i+1];
	for( i = 0; i < G->vexnum; i++)
	{
		p = G->vertices[i].firstarc;
		while(p)
		{
			if( p->adjvex == j )
			{
				if( p == G->vertices[i].firstarc )
				{
					G->vertices[i].firstarc = p->nextrac;
					if( G->kind == 1 || G->kind == 3 )
						p->info = NULL;
					p = NULL;
					p = G->vertices[i].firstarc;
					if( G->kind == 0 || G->kind == 2 )
						G->arcnum--;
				}
				else
				{
					q->nextrac == p->nextrac;
					if( G->kind == 1 || G->kind == 3 )
						p->info = NULL;
					p = NULL;
					p = q->nextrac;
					if( G->kind == 0 || G->kind == 2 )
						G->arcnum--;
				}
			}
			else
			{
				if( p->adjvex > j )
					p->adjvex--;
				q = p;
				p = p->nextrac;
			}
		}
	}
}

void InsertArc(ALGraph *G, VertexType v1, VertexType v2)
{
	int i, j, w;
	ArcNode *p;
	ALGraph g = *G;
	i = LocateVex(g,v1);
	j = LocateVex(g,v2);
	if( i < 0 || j < 0 )
		printf("Error3 !\n");
	G->arcnum++;
	if( G->kind == 1 || G->kind == 3 )
	{
		printf("请输入边(%s,%s)的权值：");
		scanf("%d",&w);
	}
	p = (ArcNode *)malloc(sizeof(ArcNode));
	p->adjvex = j;
	if( G->kind == 1 || G->kind == 3 )
	{
		p->info = (int *)malloc(sizeof(int));
		*(p->info) = w;
	}
	else
		p->info = NULL;
	p->nextrac = G->vertices[i].firstarc;
	G->vertices[i].firstarc = p;
	if( G->kind >= 2 )
	{
		p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = i;
		if( G->kind == 3 )
		{
			p->info = (int *)malloc(sizeof(int));
			*(p->info) = w;
		}
		else
			p->info = NULL;
		p->nextrac = G->vertices[j].firstarc;
		G->vertices[j].firstarc = p;
	}
}

void DeleteArc(ALGraph *G, VertexType v1, VertexType v2)
{
	int i, j;
	ArcNode *p, *q;
	ALGraph g = *G;
	i = LocateVex(g,v1);
	j = LocateVex(g,v2);
	if( i < 0 || j < 0 || i == j )
		printf("Error4!\n");
	p = G->vertices[i].firstarc;
	while( p && p->adjvex != j )
	{
		q = p;
		p = p->nextrac;
	}
	if( p && p->adjvex == j )
	{
		if( p == G->vertices[i].firstarc )
			G->vertices[i].firstarc = p->nextrac;
		else
			q->nextrac = p->nextrac;
		if( G->kind == 1 || G->kind == 3 )
			p->info = NULL;
		p = NULL;
		G->arcnum--;
	}
	if( G->kind >= 2 )
	{
		p = G->vertices[j].firstarc;
		while( p && p->adjvex != i )
		{
			q = p;
			p = p->nextrac;
		}
		if( p && p->adjvex == i )
		{
			if( p == G->vertices[j].firstarc )
				G->vertices[j].firstarc = p->nextrac;
			else
				q->nextrac = p->nextrac;
			if( G->kind == 3 )
				p->info = NULL;
			p = NULL;
		}
	}
}

int visited[MAX_VERTEX_NUM];		//访问标志数组
void (*VisitFunc)(char* v);

void DFS(ALGraph G, int pos1)
{
	int pos2;
	visited[pos1] = 1;
	VisitFunc(G.vertices[pos1].data);
	for( pos2 = FirstAdjVex(G,pos1); pos2 >= 0; pos2 = NextAdjVex(G,pos1,pos2) )
		if( !visited[pos2] )
			DFS(G,pos2);
}

void DFSTracerse(ALGraph G, void(*Visit)(char*))
{
	int pos;
	VisitFunc = Visit;
	for( pos = 0; pos < G.vexnum; pos++ )
		visited[pos] = 0;
	printf("深度优先遍历的结果是：\n");
	for( pos = 0; pos < G.vexnum; pos++ )
		if( !visited[pos] )
			DFS(G,pos);
}














int main()
{

}


















