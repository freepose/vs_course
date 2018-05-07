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
		for (j = g.n - 1; j >= 0; j--) {      //检查邻接矩阵的每个元素
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

//Zero the tag
template<typename T> void Zero(AdjGraph<T> *G, int visited[])
{
	for (int i = 0; i < G->n; i++) {
		visited[i] = 0;
	}
}

//Depth First Search
template<typename T> void DFS(AdjGraph<T> *G, int v, int visited[])
{
	ArcNode<T> *p;
	visited[v] = 1;                //置以访问标记
	cout << v << " ";                     //输出被访问顶点的编号
	p = G->adjlist[v].firstarc;    //p指向顶点v的第一个邻接点
	while (p != 0) {
		if (visited[p->adjvex] == 0) {
			DFS(G, p->adjvex, visited);     //若p->adjvex顶点未被访问，递归访问它
		}
		p = p->nextarc;            //p指向顶点v的下一个邻接点
	}
}

//Breadth First Search
template<typename T> void BFS(AdjGraph<T> *G, int v, int visited[])
{
	int w;
	ArcNode<T> *p;
	SqQueue<T> *qu;          //定义环形队列指针
	InitQueue(qu);          //初始化队列
	cout << v << " ";
	Zero(G, visited);         //标记置零
	visited[v] = 1;
	enQueue(qu, v);
	while (!QueueEmpty(qu)) {
		deQueue(qu, w);         //出队一个顶点w
		p = G->adjlist[w].firstarc;  //指向w的第一个邻接点
		while (p != 0) {             //查找w的所有邻接点
			if (visited[p->adjvex] == 0) {
				cout << p->adjvex << " ";
				visited[p->adjvex] = 1;
				enQueue(qu, p->adjvex); //该顶点进队
			}
			p = p->nextarc;
		}
	}
}

//Non-connected graph Depth First Search, visited every vertex
template<typename T> void N_Con_DFS(AdjGraph<T> *G, int visited[])
{
	int i;
	Zero(G, visited);         //标记置零
	for (i = 0; i < G->n; i++) {
		if (visited[i] == 0) {
			DFS(G, i, visited);
		}
	}
}

//Non-connected graph Breadth First Search, visited every vertex
template<typename T> void N_Con_BFS(AdjGraph<T> *G, int visited[])
{
	int i;
	Zero(G, visited);         //标记置零
	for (i = 0; i < G->n; i++) {
		if (visited[i] == 0) {
			BFS(G, i, visited);
		}
	}
}

// P269【例8.3】Determine whether the undirected graph is connected
template<typename T> bool Connect(AdjGraph<T> *G, int visited[])
{
	int i;
	bool flag = true;
	Zero(G, visited);         //标记置零
	DFS(G, 0, visited);        //从顶点0开始深度优先遍历
	for (i = 0; i < G->n; i++) {
		if (visited[i] == 0) {
			flag = false;     //若有顶点没有被访问到，说明是不连通的
			break;
		}
	}
	return flag;
}


/*Application based on Depth First Search*/


// P269【例8.4】Find simple path of u to v
template<typename T> void ExistPath(AdjGraph<T> *G, int u, int v, bool &has, int visited[])
{
	int w;
	ArcNode<T> *p;
	visited[u] = 1;        //置以访问标记
	if (u == v) {
		has = true;
		return;
	}
	p = G->adjlist[u].firstarc;  //p指向顶点u的第一个邻接点
	while (p != 0) {
		w = p->adjvex;                //w为顶点u的第一个邻接点
		if (visited[w] == 0) {       //若w顶点为访问，递归访问他
			ExistPath(G, w, v, has, visited);
		}
		p = p->nextarc;
	}
}

// P270【例8.5】Disp simple path of u to v, d is the length of path
template<typename T> void FindaPath(AdjGraph<T> *G, int u, int v, int path[], int d, int visited[])
{
	int w, i;
	ArcNode<T> *p;
	visited[u] = 1;
	d++;
	path[d] = u;        //路径长度d增加1，顶点u加入到路径中
	if (u == v) {
		for (i = 0; i <= d; i++) {
			cout << path[i] << " ";
		}
		cout << endl;
		return;
	}
	p = G->adjlist[u].firstarc;  //p指向顶点u的第一个邻接点
	while (p != 0) {
		w = p->adjvex;                //w为顶点u的邻接点
		if (visited[w] == 0) {       //若w顶点为访问，递归访问他
			FindaPath(G, w, v, path, d, visited);
		}
		p = p->nextarc;
	}
}

// P271【例8.6】Disp all the simple pathes of u to v.
template<typename T> void FindAllPath(AdjGraph<T> *G, int u, int v, int path[], int d, int visited[])
{
	int w, i;
	ArcNode<T> *p;
	d++;
	path[d] = u;
	visited[u] = 1;
	if (u == v && d >= 0) {
		for (i = 0; i <= d; i++) {
			cout << path[i] << " ";
		}
		cout << endl;
	}
	p = G->adjlist[u].firstarc;
	while (p != 0) {
		w = p->adjvex;
		if (visited[w] == 0) {
			FindAllPath(G, w, v, path, d, visited);
		}
		p = p->nextarc;
	}
	visited[u] = 0;    //恢复环境，使该顶点可重新使用
}

// P272【例8.7】Disp all paths of length l from u to v
template<typename T> void PathLenAll(AdjGraph<T> *G, int u, int v, int l, int path[], int d, int visited[])
{
	int w, i;
	ArcNode<T> *p;
	visited[u] = 1;
	d++;
	path[d] = u;
	if (v == u && d == l) {              //长度为l时输出路径
		for (i = 0; i <= d; i++) {
			cout << path[i] << " ";
		}
		cout << endl;
	}
	p = G->adjlist[u].firstarc;
	while (p != 0) {
		w = p->adjvex;
		if (visited[w] == 0) {
			PathLenAll(G, w, v, l, path, d, visited);
		}
		p = p->nextarc;
	}
	visited[u] = 0;
}

//P274【例8.8】Disp all the simple cycle which through k
template<typename T> void FindCyclePath(AdjGraph<T> *G, int u, int v, int path[], int d, int visited[])
{
	int w, i;
	ArcNode<T> *p;
	visited[u] = 1;
	d++;
	path[d] = u;
	p = G->adjlist[u].firstarc;
	while (p != 0) {
		w = p->adjvex;
		if (w == v && d > 0) {
			for (i = 0; i <= d; i++) {
				cout << path[i] << " ";
			}
			cout << v << endl;
		}
		if (visited[w] == 0) {
			FindCyclePath(G, w, v, path, d, visited);
		}
		p = p->nextarc;
	}
	visited[u] = 0;
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

	int visited[MAX_SIZE] = { 0 };
	cout << "Depth First Search: "; DFS(G, 0, visited);
	cout << endl << "Breadth First Search: "; BFS(G, 0, visited);
	cout << endl << "Non-connected graph Depth First Search: "; N_Con_DFS(G, visited);
	cout << endl << "Non-connected graph Breadth First Search: "; N_Con_BFS(G, visited);
	
	// P269【例8.3】
	cout << endl;
	if (Connect(G, visited)) {
		cout << " is connected graph. " << endl;
	}

	// P269【例8.4】 P270【例8.5】 P271【例8.6】
	int d = -1, path[MAX_SIZE] = { 0 };
	int u = 1, v = 4;
	bool has = false;
	Zero(G, visited);         //标记置零
	ExistPath(G, u, v, has,visited);
	if (has) {
		cout << "Can find the simple path of u to v. " << endl;
		Zero(G, visited);
		cout << "A simple path of u to v is: "; FindaPath(G, u, v, path, d, visited);
		Zero(G, visited);  //置问初始值
		d = -1;
		cout << "All simple path of u to v is: "<<endl; FindAllPath(G, u, v, path, d, visited);
	}

	// P272【例8.7】
	Zero(G, visited);  //置问初始值
	d = -1;
	int l = 2;
	cout << "All l length simple path of u to v is: " << endl; PathLenAll(G, u, v, l, path, d, visited);

	//P274【例8.8】
	int k = 1;
	cout << "All the cycle path through k is :" << endl; FindCyclePath(G, k, k, path, d, visited);

}