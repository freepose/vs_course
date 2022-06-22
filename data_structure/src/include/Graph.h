/*
*
* Create By ChenXiaodie, TangNi, CKj, PengHaoyun, 2018
*
*/


#pragma once
#define INF 0x3f3f3f3f
#include "basic.h"
#include "SqQueue.h"


/*
*
* Create By ChenXiaodie,2018
*
*/


/*adjacency matrix */

template<typename T> struct VertexType
{
	int no;         //Vertex number
	T info;		//Other information at the vertex
};

/* adjacency matrix*/

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

//use for topological sorting
template <typename T> struct NewVNode
{
	VertexType<T> data;  //information
	int count;   //The degree of entry of the vertex.
	ArcNode<T> *firstarc;
};

//The storage structure of adjacency list
template <typename T> struct AdjGraph
{
	T adjlist[MAX_SIZE];  //The number group of Head node 
	int n, e;
};

//use for Kruskal's algrithm
typedef struct
{
	int u;	//边的起始顶点
	int v;	//边的终止顶点
	int w;	//边的权值
}Edge;

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
	ArcNode<int> *p;
	G = new AdjGraph<T>;
	for (i = 0; i < n; i++) {
		G->adjlist[i].firstarc = 0;        //将所有头结点的指针域置初值
	}
	for (i = 0; i < n; i++) {
		for (j = n - 1; j >= 0; j--) {      //检查邻接矩阵的每个元素
			if (A[i][j] != 0 && A[i][j] != INF) {         //存在一条边
				p = new ArcNode<int>;                       //创建一个结点P
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

template <typename T> void CreateMatGraph(MatGraph<T> *&G, int A[MAX_SIZE][MAX_SIZE], int n, int e)
{
	G = new MatGraph<T>;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			G->edges[i][j] = A[i][j];
		}
		G->ves[i].no = i;
	}
	G->e = e; G->n = n;
}

//Print adjacency list
template <typename T> void DispAdj(AdjGraph<T> *&G)
{
	int i;
	ArcNode<int> *p;
	for (i = 0; i < G->n; i++) {
		p = G->adjlist[i].firstarc;
		cout << setw(3) << setfill('0') << i << ": ";   //输出顶点编号
		while (p != 0) {
			cout << setw(3) << setfill('0') << p->adjvex << "[" << p->weight << "] ->";
			if (p->nextarc == 0)
				cout << "Λ";
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
	ArcNode<int> *p, *pre;
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
template <typename T1, typename T2> void MatToList(MatGraph<T1> g, AdjGraph<T2> *&G)
{
	int i, j;
	ArcNode<T1> *p;
	G = new AdjGraph<T2>;
	for (i = 0; i < g.n; i++) {
		G->adjlist[i].firstarc = 0;
	}
	for (i = 0; i < g.n; i++) {
		for (j = g.n - 1; j >= 0; j--) {      //检查邻接矩阵的每个元素
			if (g.edges[i][j] != 0 && g.edges[i][j] != INF) {         //存在一条边
				p = new ArcNode<T1>;                       //创建一个结点P
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
template <typename T1, typename T2> void ListToMat(AdjGraph<T2> *&G, MatGraph<T1> &g)
{
	int i;
	ArcNode<T1> *p;
	for (i = 0; i < G->n; i++) {
		p = G->adjlist[i].firstarc;
		while (p != 0) {
			g.edges[i][p->adjvex] = p->weight;
			p = p->nextarc;
		}
	}
	g.n = G->n; g.e = G->e;
}


/*
*
* Create By TangNi,2018
*
*/

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
	ArcNode<int> *p;
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
	ArcNode<int> *p;
	SqQueue<int> *qu;          //定义环形队列指针
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
template<typename T> void N_Con_DFS(AdjGraph<T> *G)
{
	int i;
	int visited[MAX_SIZE] = { 0 };        //标记置零
	for (i = 0; i < G->n; i++) {
		if (visited[i] == 0) {
			DFS(G, i, visited);
		}
	}
}

//Non-connected graph Breadth First Search, visited every vertex
template<typename T> void N_Con_BFS(AdjGraph<T> *G)
{
	int i;
	int visited[MAX_SIZE] = { 0 };         //标记置零
	for (i = 0; i < G->n; i++) {
		if (visited[i] == 0) {
			BFS(G, i, visited);
		}
	}
}

// P269【例8.3】Determine whether the undirected graph is connected
template<typename T> bool Connect(AdjGraph<T> *G)
{
	int i;
	bool flag = true;
	int visited[MAX_SIZE] = { 0 };         //标记置零
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
	ArcNode<int> *p;
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
	ArcNode<int> *p;
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
	ArcNode<int> *p;
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
	ArcNode<int> *p;
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
	ArcNode<int> *p;
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


/*Application based on Breadth First Search*/


// P276【例8.9】Inverse disp the shortest path from u to v
template<typename T> void ShortPath(AdjGraph<T> *G, int u, int v, int visited[])
{
	ArcNode<int> *p;
	int w, i;
	Quere<T> qu[MAX_SIZE];       //非环形队列
	int front = -1, rear = -1;   //队列的头指针、尾指针
	rear++;
	qu[rear].data = u;           //顶点u进队
	qu[rear].parent = -1;
	visited[u] = 1;
	while (front != rear) {     //队不空循环
		front++;                //出队顶点w
		w = qu[front].data;
		if (w == v) {            //遇到v时输出逆路径，退出
			i = front;
			while (qu[i].parent != -1) {    //通过队列输出逆路径
				cout << qu[i].data << " ";
				i = qu[i].parent;
			}
			cout << qu[i].data << endl;
			break;
		}
		p = G->adjlist[w].firstarc;     //w的第一个邻接点
		while (p != 0) {
			if (visited[p->adjvex] == 0) {  //将w未访问过的邻接点进队
				rear++;
				qu[rear].data = p->adjvex;
				qu[rear].parent = front;
			}
			p = p->nextarc;        //找w的下一个邻接点
		}
	}
}


// P277【例8.10】Find the furthest vertex from v, using SqQueue instead of Qu[]
template<typename T> int Maxdist(AdjGraph<T> *G, int v, int visited[])
{
	ArcNode<int> *p;
	SqQueue<int> *qu;
	InitCycleQueue(qu);
	int j, k = 0;
	enCycleQueueF(qu, v);    //顶点v进队
	visited[v] = 1;      //标记v已访问
	while (!QueueEmpty(qu)) {
		deCycleQueueR(qu, k);   //顶点k出队
		p = G->adjlist[k].firstarc;     //找第一个邻接点
		while (p != 0) {                //所有未被访问过的邻接点进队
			j = p->adjvex;              //邻接点为顶点j
			if (visited[j] == 0) {
				visited[j] = 1;
				enCycleQueueF(qu, j);
			}
			p = p->nextarc;
		}
	}
	return k;
}

/*
*
* Create By PHY,2018
*
*/

//Display the shotest path
template<typename T>void Dispath(MatGraph<T> g, int dist[],int path[], int S[], int v)
{
	int i, j, k;
	int apath[MAX_SIZE], d;   //存放一条最短路路径（逆向）及其顶点个数
	for(i=0;i<g.n;i++)       //循环输出从顶点v到i的路径
		if (S[i] == 1 && i != v)
		{
			cout << "从顶点" << v << "到顶点" << i << "的路径长度为：" << dist[i] << '\t' << "路径为：";
			d = 0;
			apath[d] = i;  //添加路径上的终点
			k = path[i];
			if (k == -1)  //没有路径的情况
				cout << "无路径" << endl;
			else       //存在路径时输出该路径
			{
				while (k != v)
				{
					d++;
					apath[d] = k;
					k = path[k];
				}
				d++;
				apath[d] = v;   //添加路径上的起点
				cout << apath[d];   //先输出起点
				for (j = d - 1; j >= 0; j--)   //再输出其他顶点
					cout << "," << apath[j];
				cout << endl;
			}
		}
}


//Display the shotest path by Dijkstra
template<typename T> void Dijkstra(MatGraph<T> g, int v)
{
	int dist[MAX_SIZE], path[MAX_SIZE];
	int S[MAX_SIZE];     //S[i]=1表示顶点i在S中，S[i]=0表示顶点i在U中
	int MINdis, i, j, u;
	for (i = 0; i < g.n; i++)
	{
		dist[i] = g.edges[v][i];    //距离初始化
		S[i] = 0;//S[]置空
		if (g.edges[v][i] < INF)    //路径初始化
			path[i] = v;    //顶点v到顶点i有边时，置顶点i的前一个顶点为v
		else
			path[i] = -1;    //顶点v到顶点i没边时，置顶点i的前一个顶点为-1
	}
	S[v] = 1;
	path[v] = 0;    //源点编号v放入S中
	for (i = 0; i < g.n - 1; i++)   //循环直到所有顶点的最短路径都求出
	{
		MINdis = INF;   //MINdis置最大长度初值
		for(j=0;j<g.n;j++)    //选取不在S中（即U中）且具有最小最短路径长度的顶点v
			if (S[j] == 0 && dist[j] < MINdis)
			{
				u = j;
				MINdis = dist[j];
			}
		S[u] = 1;   //顶点u加入S中
		for(j=0;j<g.n;j++)   //修改不在S中（即U中）的顶点的最短路径
			if(S[j]==0)
				if (g.edges[u][j] < INF&&dist[u] + g.edges[u][j] < dist[j])
				{
					dist[j] = dist[u] + g.edges[u][j];
					path[j] = u;
				}
	}
	Dispath(g, dist, path, S, v);   //输出最短路径
}


/*
*
* Create By CXD,2018
*
*/

//topological sorting
template <typename T> void TopSort(AdjGraph<T> *G)
{
	int i, j;
	int St[MAX_SIZE];  //用顺序栈存放入度为0的顶点
	int top = -1;     //栈顶指针
	ArcNode<int> *p;
	for (i = 0; i < G->n; i++) {
		G->adjlist[i].count = 0;      //入度置初值0
	}
	for (i = 0; i < G->n; i++) {     //求所有顶点的入度
		p = G->adjlist[i].firstarc;
		while (p != 0) {
			G->adjlist[p->adjvex].count++;
			p = p->nextarc;
		}
	}
	for (i = 0; i < G->n; i++) {      //将入度为0的顶点入栈
		if (G->adjlist[i].count == 0) {
			top++;
			St[top] = i;
		}
	}
	while (top > -1) {   //栈不空时循环
		i = St[top]; top--;    //出栈一个顶点
		cout << i;            //输出该顶点
		p = G->adjlist[i].firstarc;       //找第一个邻接点
		while (p != 0) {       //将顶点i的出边邻接点的入度减1
			j = p->adjvex;
			G->adjlist[j].count--;
			if (G->adjlist[j].count == 0) {   //将入度为0的邻接点进栈
				top++;
				St[top] = j;
			}
			p = p->nextarc;       //找下一个邻接点
		}
	}
	cout << endl;
}


/*
*
* Create By CKJ,2018
*
*/

template <typename T> void Prim(MatGraph<T> *g, int v)
{
	int lowcost[MAX_SIZE];
	int MIN;
	int closest[MAX_SIZE], i, j, k = 0;
	for (i = 0; i < g->n; i++)		//给lowcost[]和closest[]置初值
	{
		lowcost[i] = g->edges[v][i];
		closest[i] = v;
	}
	for (i = 1; i < g->n; i++)		//找出(n-1)个结点
	{
		MIN = INF;
		for (j = 0; j < g->n; j++)		//在(V-U)中找出离U最近的顶点k
		{
			if (lowcost[j] != 0 && lowcost[j] < MIN)
			{
				MIN = lowcost[j];
				k = j;		//记录最近顶点的编号
			}
		}
		cout << "边（" << closest[k] << "," << k << "）权为：" << MIN << endl;	//输出最小生成树的一条边
		lowcost[k] = 0;		//标记k已经加入到U
		for (j = 0; j < g->n; j++)		//对(V-U)中的顶点j进行调整
		{
			if (lowcost[j] != 0 && g->edges[k][j] < lowcost[j])
			{
				lowcost[j] = g->edges[k][j];
				closest[j] = k;		//修改数组lowcost和closest
			}
		}
	}
}

void InserSort(Edge a[], int n)
{
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			if (a[j].w > a[j + 1].w) {
				swap(a[j], a[j + 1]);
			}
		}
	}
}

template <typename T> void Kruskal(MatGraph<T> *g)
{
	int i, j, u1, v1, sn1, sn2, k;
	int vset[MAX_SIZE];
	Edge E[MAX_SIZE];		//存放图中的所有边
	k = 0;					//e数组的下标从0开始计
	for (i = 0; i < g->n; i++)		//由g产生边集E，不重复选取同一条边
	{
		for (j = 0; j <= i; j++)
		{
			if (g->edges[i][j] != 0 && g->edges[i][j] != INF)
			{
				E[k].u = i; E[k].v = j; E[k].w = g->edges[i][j];
				k++;
			}
		}
	}
	InserSort(E, g->e);		//采用直接插入排序对E数组按权值递增排序
	for (i = 0; i < g->e; i++)		//初始化辅助数组
	{
		vset[i] = i;
	}
	k = 1;		//k表示当前构造生成树的第几条边，初值为1
	j = 0;		//E中边的下标，初值为0
	while (k < g->n)
	{
		u1 = E[j].u; v1 = E[j].v;		//取一条边的两个顶点
		sn1 = vset[u1];
		sn2 = vset[v1];		//分别得到两个顶点所属的集合编号
		if (sn1 != sn2)		//两个顶点属于不同的集合，该边是最小生成树的一条边
		{
			cout << "(" << u1 << "," << v1 << "): " << E[j].w << endl;		//输出最小生成树的一条边
			k++;		//生成边数增1
			for (i = 0; i < g->n; i++)		//两个集合统一编号
				if (vset[i] == sn2)			//集合编号为sn2的改为sn1
					vset[i] = sn1;
		}
		j++;		//扫描下一条边
	}
}

template <typename T> void DisMatGraphPath(MatGraph<T> *g, int A[][MAX_SIZE], int path[][MAX_SIZE])
{
	int i, j, k, s;
	int apath[MAX_SIZE], d;		//存放一条最短路径中间顶点（反向）及其顶点个数
	for (i = 0; i < g->n; i++)
	{
		for (j = 0; j < g->n; j++)
		{
			if (A[i][j] != INF && i != j)	//若顶点i和j之间存在路径
			{
				cout << "从" << i << "到" << j << "之间的路径为：";
				k = path[i][j];
				d = 0; apath[d] = j;	//路径上添加终点
				while (k != -1 && k != i)	//路径上添加中间点
				{
					d++; apath[d] = k;
					k = path[i][k];
				}
				d++; apath[d] = i;		//路径上添加起点
				cout << apath[d];		//输出起点
				for (s = d - 1; s >= 0; s--)		//输出路径上的中间顶点
					cout << "," << apath[s];
				cout << "\t路径长度为：" << A[i][j] << endl;
			}
		}
	}
}

template <typename T> void Floyd(MatGraph<T> *g)
{
	int A[MAX_SIZE][MAX_SIZE], path[MAX_SIZE][MAX_SIZE];
	int i, j, k;
	for (i = 0; i < g->n; i++)
		for (j = 0; j < g->n; j++)
		{
			A[i][j] = g->edges[i][j];
			if (i != j && g->edges[i][j] < INF)
				path[i][j] = i;		//顶点i到j有边时
			else
				path[i][j] = -1;	//顶点i到j没有边时
		}
	for (k = 0; k < g->n; k++)		//依次考察所有顶点
	{
		for(i = 0; i < g->n; i++)
			for(j = 0; j < g->n; j++)
				if (A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];	//修改最短路径长度
					path[i][j] = path[k][j];		//修改最短路径
				}
	}
	DisMatGraphPath(g, A, path);	//输出最短路径
}


void GraphExample()
{
	AdjGraph<VNode<int>> *G;
	int n = 5, e = 8;
	int A[MAX_SIZE][MAX_SIZE] =  //无向图
	{
		{ 0,1,0,1,1 },
		{ 1,0,1,1,0 },
		{ 0,1,0,1,1 },
		{ 1,1,1,0,1 },
		{ 1,0,1,1,0 }
	};
	CreateAdj(G, A, n, e);

	//p261 例【8.2】
	MatGraph<int> g;
	memcpy(g.edges, A, MAX_SIZE * MAX_SIZE * sizeof(int));
	g.n = n; g.e = e;
	MatToList(g, G);
	cout << "图G:\n";
	DispAdj(G);

	memset(g.edges, 0, MAX_SIZE * MAX_SIZE * sizeof(int));
	ListToMat(G, g);
	cout << "图g:\n";
	DispMatGraph(g);

	int visited[MAX_SIZE] = { 0 };
	cout << "Depth First Search: "; DFS(G, 0, visited);
	cout << endl << "Breadth First Search: "; BFS(G, 0, visited);
	cout << endl << "Non-connected graph Depth First Search: "; N_Con_DFS(G);
	cout << endl << "Non-connected graph Breadth First Search: "; N_Con_BFS(G);
	cout << endl;
	
	// P269【例8.3】
	if (Connect(G)) {
		cout << " is connected graph. " << endl;
	}
	cout << endl;

	// P269【例8.4】 P270【例8.5】 P271【例8.6】
	int d = -1, path[MAX_SIZE] = { 0 };
	int u = 1, v = 4;
	bool has = false;
	Zero(G, visited);         //标记置零
	ExistPath(G, u, v, has,visited);
	if (has) {
		cout << "Can find the simple path of " << u << " to " << v << endl;
		Zero(G, visited);
		cout << "A simple path of " << u << " to " << v << " is: "; 
		FindaPath(G, u, v, path, d, visited);
		Zero(G, visited);  //置问初始值
		d = -1;
		cout << "All simple path of " << u << " to " << v << " is: "<<endl; 
		FindAllPath(G, u, v, path, d, visited);
	}
	cout << endl;

	// P272【例8.7】
	Zero(G, visited);  //置问初始值
	int Path[MAX_SIZE] = { 0 };
    u = 1;
    v = 4;
	int l = 3;
	cout << "图G:\n";
	DispAdj(G);
	cout << "All " << l << " length simple path of " << u << " to " << v << " is: " << endl;
	PathLenAll(G, u, v, l, Path, -1, visited);
	cout << endl;

	//P274【例8.8】
	AdjGraph<VNode<int>>  *G1;
	int A1[MAX_SIZE][MAX_SIZE] =
	{
		{ 0,1,1,0,0 },
		{ 0,0,1,0,0 },
		{ 0,0,0,1,1 },
		{ 0,0,0,0,1 },
		{ 1,0,0,0,0 }
	};
	CreateAdj(G1, A1, 5, 7);
	int k = 1;
	cout << "All the cycle path through "<<k <<" is :" << endl; FindCyclePath(G1, k, k, path, d, visited);

	// P276【例8.9】
	Zero(G1, visited);
	cout << "Inverse disp the shortest path from "<<u <<" to " <<v <<" : "; ShortPath(G1, u, v, visited);

	// P277【例8.10】
	Zero(G1, visited);
	int ver;
	ver = Maxdist(G1, v, visited);
	cout << "The furthest vertex from " <<v<<" is " << k << endl;

	//P303 例【8.14】
	AdjGraph<NewVNode<int>> *M;
	int C[MAX_SIZE][MAX_SIZE] =
	{
		{ 0,1,INF,INF,INF,INF },
		{ INF,0,1,INF,INF,INF },
		{ INF,INF,0,1,INF,INF },
		{ INF,INF,INF,0,INF,INF },
		{ INF,1,INF,INF,0 ,1 },
		{ INF ,INF ,INF ,1,INF ,0 }
	};
	n = 6; e = 6;
	CreateAdj(M, C, n, e);
	cout << "图M:\n"; 
	DispAdj(M);
	cout << "A topological sort of M:";  TopSort(M); 
	DestroyAdj(M);
	cout << endl;

	//P284 Prim arithmatic
	int A2[MAX_SIZE][MAX_SIZE] = {
		{ 0, 28, INF, INF, INF, 10, INF },
		{ 28, 0, 16, INF, INF, INF, 14 },
		{ INF, 16, 0, 12, INF, INF, INF },
		{ INF, INF, 12, 0, 22, INF, 18 },
		{ INF, INF, INF, 22, 0, 25, 24 },
		{ 10, INF, INF, INF, 25, 0, INF },
		{ INF, 14, INF, 18, 24, INF, 0 }
	};
	MatGraph<int> *Q;
	CreateMatGraph(Q, A2, 7, 9);
	Prim(Q, 0);

	//P288 Kruskal algrethm
	Kruskal(Q);
	int A3[MAX_SIZE][MAX_SIZE] =
	{
		{ 0, 5, INF, 7, INF, INF },
		{ INF, 0, 4, INF, INF, INF },
		{ 8, INF, 0, INF, INF, 9 },
		{ INF, INF, 5, 0, INF, 6 },
		{ INF, INF, INF, 5, 0, INF },
		{ 3, INF, INF, INF, 1, 0 },
	};
	MatGraph<int> *g1;
	CreateMatGraph(g1, A3, 6, 10);
	Floyd(g1);

	DestroyAdj(G);
}
