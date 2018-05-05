#pragma once
#define INF 0x3f3f3f3f
#include "basic.h"


/*adjacency matrix */

template<typename T> struct VertexType
{
	int no;         //Vertex number
	T info;		//Other information at the vertex
};

//The storage structure of adjacency matrix 
template<typename T> struct MatGraph
{
	int edges[MAX_SIZE][MAX_SIZE];    //adjacency matrix 
	int n, e;                      //Vertex number, edge number 
	VertexType<T> ves[MAX_SIZE];   //Store vertex information 
};


/* adjacency list*/

//Side node storage structure
template <typename T> struct ArcNode    
{
	int adjvex;  //Terminal number 
	ArcNode<T> *nextarc; 
	T weight; //information
};

//Head node storage structure 
template <typename T> struct VNode        
{
	T info;
	ArcNode<T> *firstarc; //Point to the first side node 
};

//The storage structure of adjacency list
template <typename T> struct AdjGraph
{
	VNode<T> adjlist[MAX_SIZE];  //The number group of Head node 
	int n, e;              
};


//Print adjacency matrix 
template <typename T> void DispMatGraph(MatGraph<T> g)
{
	int i, j;
	for (i = 0; i < g.n; i++) {
		for (j = 0; j < g.n; j++) {
			cout << g.edges[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//Create adjacency list
template <typename T> void CreateAdj(AdjGraph<T> *&G, int A[MAX_SIZE][MAX_SIZE], int n, int e)
{
	int i, j;
	ArcNode<T> *p;
	G = new AdjGraph<T>;
	for (i = 0; i < n; i++) {
		G->adjlist[i].firstarc = 0;        //将所有头结点的指针域置初值
	}
	for (i = 0; i < n; i++) {
		for (j = n - 1; j >= 0; j--) {      //检查邻接矩阵的每个元素
			if (A[i][j] != 0 && A[i][j] != INF) {         //存在一条边
				p = new ArcNode<T>;                       //创建一个结点P
				p->adjvex = j;                          //存放邻接点
				p->weight = A[i][j];                      //存放权
				p->nextarc = G->adjlist[i].firstarc;            //采用头插法插入结点p
				G->adjlist[i].firstarc = p;
			}
		}
	}
	G->n = n; 
	G->e = e;
}

//Print adjacency list
template <typename T> void DispAdj(AdjGraph<T> *&G)
{
	int i;
	ArcNode<T> *p;
	for (i = 0; i < G->n; i++) {
		p = G->adjlist[i].firstarc;
		cout << setw(3) << setfill('0') << i << ": ";   //输出顶点编号
		while (p != 0) {
			cout << setw(3) << setfill('0') << p->adjvex << "[" << p->weight << "]->";
			p = p->nextarc;
		}
		cout << endl;
	}
	cout << endl;
}

//Destroy adjacency list
template <typename T> void DestroyAdj(AdjGraph<T> *&G)
{
	int i;
	ArcNode<T> *p, *pre;
	for (i = 0; i < G->n; i++) {
		pre = G->adjlist[i].firstarc;
		if (pre != 0) {
			p = pre->nextarc;
			while (p != 0) {
				delete pre;
				pre = p; p = p->nextarc;
			}
			delete pre;
		}
	}
	delete G;
}


//p261 例【8.2】 Converting the adjacency matrix into a adjacency list 
template <typename T> void MatToList(MatGraph<T> g, AdjGraph<T> *&G)
{
	int i, j;
	ArcNode<T> *p;
	G = new AdjGraph<T>;
	for (i = 0; i < g.n; i++) {
		G->adjlist[i].firstarc = 0;
	}
	for (i = 0; i < g.n; i++) {
		for (j = g.n-1; j>=0; j--) {      //检查邻接矩阵的每个元素
			if (g.edges[i][j] != 0 && g.edges[i][j] != INF) {         //存在一条边
				p = new ArcNode<T>;                       //创建一个结点P
				p->adjvex = j;                          //存放邻接点
				p->weight = g.edges[i][j];                      //存放权
				p->nextarc = G->adjlist[i].firstarc;            //采用头插法插入结点p
				G->adjlist[i].firstarc = p;
			}
		}
	}
	G->n = g.n; G->e = g.e;
}

//p261 例【8.2】 Converting adjacency tables into adjacency matrices 
template <typename T> void ListToMat(AdjGraph<T> *&G, MatGraph<T> &g)
{
	int i;
	ArcNode<T> *p;
	for (i = 0; i < G->n; i++) {
		p = G->adjlist[i].firstarc;
		while (p != 0) {
			g.edges[i][p->adjvex] = p->weight;
			p = p->nextarc;
		}
	}
	g.n = G->n; g.e = G->e;
}


void GraphExample()
{
	AdjGraph<int> *G;
	int n = 5, e = 7;
	int A[MAX_SIZE][MAX_SIZE] =  //无向图
	{
		{ 0,1,0,1,1 },
		{ 1,0,1,1,0 },
		{ 0,1,0,1,1 },
		{ 1,1,1,0,1 },
		{ 1,0,1,1,0 } 
	};
	CreateAdj(G, A, n, e);
	DispAdj(G);

	//p261 例【8.2】
	MatGraph<int> g;
	memcpy(g.edges, A, MAX_SIZE * MAX_SIZE * sizeof(int));
	g.n = n; g.e = e;
	MatToList(g, G);
	DispAdj(G);

	memset(g.edges, 0, MAX_SIZE * MAX_SIZE * sizeof(int));
	ListToMat(G, g);
	DispMatGraph(g);

	

}

