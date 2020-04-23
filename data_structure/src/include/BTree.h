#pragma once
#include "basic.h"
#include "SqQueue.h"


template<typename T>  struct BTNode
{
	T data;
	BTNode<T> *lchild;
	BTNode<T> *rchild;
};

template<typename T> struct TBTNode
{
	T data;
	int ltag;
	int rtag;
	TBTNode<T> *lchild;
	TBTNode<T> *rchild;
};

template <typename T> struct HTNode
{
	T data;
	double weight;
	int parent;
	int lchild;
	int rchild;
};

template <typename T> struct HCode
{
	T cd[MAX_SIZE];//用来储存每个叶子结点的哈尔曼编码路径
	int start;
};

typedef struct node
{
	int data;		//结点对应人的编号
	int rank;		//结点对应秩
	int parent;		//结点对应双亲下标
}UFSTree;		//并查集树的结点类型

/* The basic operation of the tree (by PHY) */

template<typename T> void CreateBTree(BTNode<T> *&b, char *str)
{
	BTNode<T> *St[MAX_SIZE], *p;       //St数组作为顺序栈
	int top = -1, k, j = 0;            //top为栈顶指针
	T ch;
	b = 0;                             //初始二叉树为空
	ch = str[j];
	while (ch != '\0')                 //循环扫描str中的每个字符
	{
		switch (ch)                    //A(B(D(,G)),C(E,F))
		{
		case'(':top++; St[top] = p; k = 1; break;    //开始处理左孩子结点
		case')':top--; break;                        //栈顶结点的子树处理完毕
		case',':k = 2; break;                        //开始处理右孩子结点
		default:p = new BTNode<T>;
			p->data = ch;
			p->lchild = p->rchild = 0;
			if (b == 0) {                           //若尚未建立根节点，p就为根节点
				b = p;
			}
			else {
				switch (k)
				{
				case 1:St[top]->lchild = p; break;
				case 2:St[top]->rchild = p; break;
				}
			}
		}
		j++;
		ch = str[j];
	}
}

template<typename T> void DestroyBTree(BTNode<T> *&b)
{
	if (b != 0) {         /* if b is empty, do nothing */
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		delete b;
	}
}

template<typename T> void DispBTree(BTNode<T> *b)
{
	if (b != 0) {
		cout << b->data;
		if (b->lchild != 0 || b->rchild != 0) {
			cout << '(';
			DispBTree(b->lchild);
			if (b->rchild != 0) {
				cout << ',';
			}
			DispBTree(b->rchild);
			cout << ')';
		}
	}
}

template<typename T> BTNode<T>* FindNode(BTNode<T> *b, const T x)
{
	BTNode<T> *p;
	if (b == 0) {
		return 0;
	}
	else if (b->data == x) {
		return b;
	}
	else {
		p = FindNode(b->lchild, x);
		if (p != 0) {
			return p;
		}
		else {
			return (FindNode(b->rchild, x));
		}
	}
}

template<typename T> BTNode<T>* LchildNode(BTNode<T> *p)
{
	return p->lchild;
}

template<typename T> BTNode<T>* RchildNode(BTNode<T> *p)
{
	return p->rchild;
}

template<typename T> int BTNodeDepth(BTNode<T> *b)
{
	int lchilddeep, rchilddeep;
	if (b == 0) {
		return 0;
	}
	else {
		lchilddeep = BTNodeDepth(b->lchild);
		rchilddeep = BTNodeDepth(b->rchild);
		return (lchilddeep > rchilddeep) ? (lchilddeep + 1) : (rchilddeep + 1);
	}
}

template<typename T> int BTNodeWidth(BTNode<T> *b)
{
	BTNode<T> *q;
	SqQueue<BTNode<T>*> *Q;   //栈用来存储节点
	int last, temp_width=0, max_width=0;
	InitQueue(Q);
	last = Q->rear;      //last标记队尾下标
	if (b == 0) {
		return 0;
	}
	else {
		enQueue(Q, b);
		while (!QueueEmpty(Q)) {
			deQueue(Q, q);
			temp_width++;       //出队这层节点++
			if (q->lchild != 0) {
				enQueue(Q, q->lchild);
			}
			if (q->rchild != 0) {
				enQueue(Q, q->rchild);
			}
			if (Q->front > last) {    //即上一层节点已数完
				last = Q->rear;
				if (temp_width > max_width) {
					max_width = temp_width;
				}
				temp_width = 0;
			}
		}
	}
	return max_width;
}

/* traverse methods of a tree: recursive traverse (by PHY) */

template<typename T> void PreOrderRecursively(BTNode<T> *b)	
{
	if (b != 0)
	{
		cout << b->data << " ";
		PreOrderRecursively(b->lchild);
		PreOrderRecursively(b->rchild);
	}
}

template<typename T> void InOrderRecursively(BTNode<T> *b)
{
	if (b != 0)
	{
		InOrderRecursively(b->lchild);
		cout << b->data << " ";
		InOrderRecursively(b->rchild);
	}
}

template<typename T> void PostOrderRecursively(BTNode<T> *b)
{
	if (b != 0)
	{
		PostOrderRecursively(b->lchild);
		PostOrderRecursively(b->rchild);
		cout << b->data << " ";
	}
}


/* traverse methods of a tree: non-recursive traverse (by CuiKaijin) */

template<typename T> void PreOrder(BTNode<T> *b)	
{
	BTNode<T> *p;
	SqStack<BTNode<T>*> *st;
	InitStack(st);
	if (b != 0)
	{
		Push(st, b);
		while (!StackEmpty(st))
		{
			Pop(st, p);
			cout << p->data << " ";
			if (p->rchild != 0)
				Push(st, p->rchild);
			if (p->lchild != 0)
				Push(st, p->lchild);
		}
		cout << endl;
	}
	DestroyStack(st);
}

template<typename T> void PreOrderV2(BTNode<T> *b)	
{
	BTNode<T> *p;
	SqStack<BTNode<T>*> *st;
	InitStack(st);
	p = b;
	while (!SqStackExample(st) || p != 0)
	{
		while (p != 0)
		{
			cout << p->data << " ";
			Push(st, p);
			p = p->lchild;
		}
		if (!StackEmpty(st))
		{
			Pop(st, p);
			p = p->rchild;
		}
	}
	cout << endl;
	DestroyStack(st);
}

template<typename T> void InOrder(BTNode<T> *b)
{
	BTNode<T> *p;
	SqStack<BTNode<T>*> *st;
	InitStack(st);
	p = b;
	while (!StackEmpty(st) || p != 0)
	{
		while (p != 0)
		{
			Push(st, p);
			p = p->lchild;
		}
		if (!StackEmpty(st))
		{
			Pop(st, p);
			cout << p->data << " ";
			p = p->rchild;
		}
	}
	cout << endl;
	DestroyStack(st);
}

template<typename T> void PostOrder(BTNode<T> *b)	
{
	BTNode<T> *p, *r;
	bool flag;
	SqStack<BTNode<T>*> *st;
	InitStack(st);
	p = b;
	do
	{
		while (p != 0)
		{
			Push(st, p);
			p = p->lchild;
		}
		r = 0;
		flag = true;
		while (!StackEmpty(st) && flag)
		{
			GetTop(st, p);
			if (p->rchild == r)
			{
				cout << p->data << " ";
				Pop(st, p);
				r = p;
			}
			else
			{
				p = p->rchild;
				flag = false;
			}
		}
	} while (!StackEmpty(st));
	cout << endl;
	DestroyStack(st);
}

template<typename T> void LevelOrder(BTNode<T> *b)
{
	BTNode<T> *p;
	SqQueue<BTNode<T>* > *qu;                      
	InitQueue(qu);
	enQueue(qu, b);
	while (!QueueEmpty(qu)) {
		deQueue(qu, p);
		cout << p->data << " ";
		if (p->lchild != 0) {
			enQueue(qu, p->lchild);
		}
		if (p->rchild != 0) {
			enQueue(qu, p->rchild);
		}
	}
}


/* Cue methodThe of a tree (by ChenXiaodie) */

TBTNode<char> *pre;//全局变量

template <typename T> void TCreateBTree(TBTNode<T> *&b, char *str)
{
	TBTNode<T> *St[MAX_SIZE], *p;       //St数组作为顺序栈
	int top = -1, k, j = 0;            //top为栈顶指针
	T ch;
	b = 0;                             //初始二叉树为空
	ch = str[j];
	while (ch != '\0')                 //循环扫描str中的每个字符
	{
		switch (ch)                    //A(B(D(,G)),C(E,F))
		{
		case'(':top++; St[top] = p; k = 1; break;    //开始处理左孩子结点
		case')':top--; break;                        //栈顶结点的子树处理完毕
		case',':k = 2; break;                        //开始处理右孩子结点
		default:p = new TBTNode<T>;
			p->data = ch;
			p->lchild = p->rchild = 0;
			if (b == 0) {                           //若尚未建立根节点，p就为根节点
				b = p;
			}
			else {
				switch (k)
				{
				case 1:St[top]->lchild = p; break;
				case 2:St[top]->rchild = p; break;
				}
			}
		}
		j++;
		ch = str[j];
	}
}

template<typename T> void Thread(TBTNode<T> *&p)
{
	if (p != 0) {
		Thread(p->lchild);
		if (p->lchild == 0) {
			p->lchild = pre;
			p->ltag = 1;
		}
		else {
			p->ltag = 0;
		}
		if (pre->rchild == 0) {
			pre->rchild = p;
			pre->rtag = 1;
		}
		else {
			pre->rtag = 0;
		}
		pre = p;
		Thread(p->rchild);
	}
}

template<typename T> TBTNode<T>* CreateThread(TBTNode<T> *b)
{
	TBTNode<T> *root;
	root = new TBTNode<T>;//create the head of the tree
	root->ltag = 0;root->rtag = 1;
	root->rchild = b;
	if (b == 0) {
		root->lchild = root;
	}
	else {
		root->lchild = b;
		pre = root;
		Thread(b);
		pre->rtag = 1;
		pre->rchild = root;
		root->rchild = pre;
	}
	return root;
}

template<typename T> void InOderThread(TBTNode<T> *tb)
{
	TBTNode<T> *p = tb->lchild;//Point to the root node
	while (p != tb) {
		while (p->ltag == 0) {
			p = p->lchild;//find the first node
		}
		cout << p->data << " ";
		while (p->rtag == 1&&p->rchild!=tb) {
			p = p->rchild;
			cout << p->data << " ";
		}
		p = p->rchild;
	}
	cout << endl;
}


/*Create a tree (by TangNi)*/

//Create a tree  by the known preorder and middle sequence sequence
// pre save preorder sequence,in save midlle sequence，n is node number，return the root node
BTNode<char> *CreateBT1(char *pre, char *in, int n)
{
	BTNode<char> *b;
	char *p;
	int k;
	if (n <= 0) {
		return 0;
	}
	b = new BTNode<char>;     //创建二叉树结点*s
	b->data = *pre;
	for (p = in; p < in + n; p++) {           //在中序序列中找等于*ppos的位置k
		if (*p == *pre) {                    //pre指向根结点
			break;                             //在in中找到后退出循环
		}
	}
	k = int(p - in);                               //确定根结点在in中的位置
	b->lchild = CreateBT1(pre + 1, in, k);        //递归构造左子树
	b->rchild = CreateBT1(pre + k + 1, p + 1, n - k - 1); //递归构造右子树
	return b;
}

//Create a tree  by the known preorder and postorder  sequence sequence
// pre save postorder sequence,in save midlle sequence，n is node number，return the root node
BTNode<char> *CreateBT2(char *post, char *in, int n)
{
	BTNode<char> *b;
	char r, *p;
	int k;
	if (n <= 0) {
		return 0;
	}
	r = *(post + n - 1);
	b = new BTNode<char>;
	b->data = r;
	for (p = in; p < in + n; p++) {
		if (*p == r) {
			break;
		}
	}
	k = int(p - in);
	b->lchild = CreateBT2(post, in, k);
	b->rchild = CreateBT2(post + k, p + 1, n - k - 1);
	return b;
}

// P216【例7.19】change the sequence binary tree to chian binary tree
template<typename T> BTNode<T> *transStoL(T *a, int i)
{
	BTNode<T> *b;
	if (i > MAX_SIZE) {
		return 0;
	}
	if (a[i] == '#') {
		return 0;
	}
	b = new BTNode<T>;
	b->data = a[i];
	b->lchild = transStoL(a, 2 * i);
	b->rchild = transStoL(a, 2 * i + 1);
	return b;
}


/*Huffman tree and Huffman coding by CXD */

template<typename T> void CreateHT(HTNode<T> *ht, int n0)
{
	int lnode, rnode, k, i;
	double min1, min2;
	for (i = 0; i < 2 * n0 - 1; i++) {
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
	}
	for (i = n0; i < 2 * n0 - 1; i++)
	{
		min1 = min2 = 32767;//赋予最小值新的初值，寻找每次的最小值
		lnode = rnode = -1;
		for (k = 0; k <= i - 1; k++) {//在i-1里面找,当有新的结点后，树逐渐扩大
			if (ht[k].parent == -1) {
				if (ht[k].weight < min1) {
					min2 = min1;
					rnode = lnode;
					min1 = ht[k].weight;
					lnode = k;
				}
				else if (ht[k].weight < min2) {
					min2 = ht[k].weight;
					rnode = k;
				}
			}
		}
		ht[i].weight = min1 + min2;
		ht[i].lchild = lnode;ht[i].rchild = rnode;
		ht[lnode].parent = ht[rnode].parent = i;
	}
}

template<typename T> void CreateHCode(HTNode<T> *ht, HCode<T> *hcd, int n0)
{
	HCode<char> hc;
	int i, f, c;//f用来存储parent位置,c用来存储结点的位置
	for (i = 0; i < n0; i++) {
		hc.start = n0;//从n0开始递减，依次储存哈尔曼编码
		c = i;
		f = ht[i].parent;
		while (f != -1) {
			if (ht[f].lchild == c) {
				hc.cd[hc.start--] = '0';
			}
			else {
				hc.cd[hc.start--] = '1';
			}
			c = f;
			f = ht[f].parent;
		}
		hc.start++;//当f=-1时，start指的是根结点，要++，指向哈夫曼编码的开头结点
		hcd[i] = hc;
	}
}

void MAKE_SET(UFSTree t[], int n)		//初始化并查集树
{
	for (int i = 0; i <= n; i++)
	{
		t[i].data = i;		//数据为该人的编号
		t[i].rank = 0;		//秩初始化为0
		t[i].parent = i;	//双亲初始化指向自己
	}
}

int FIND_SET(UFSTree t[], int x)		//在x所在的子树中查找集合编号
{
	if (x != t[x].parent)		//双亲不是自己
		return(FIND_SET(t, t[x].parent));		//递归在双亲中找x
	else
		return x;		//双亲是自己，返回x
}

void UNION(UFSTree t[], int x, int y)		//将x和y所在的子树合并
{
	x = FIND_SET(t, x);			//查找x所在分离集合数的编号
	y = FIND_SET(t, y);			//查找y所在分离集合数的编号
	if (t[x].rank > t[y].rank)	//y结点的秩小于x结点的秩
		t[y].parent = x;		//将y连到x结点上，x作为y的双亲结点
	else						//y结点的秩大于x结点的秩
	{
		t[x].parent = y;		//将x连到y结点上，y作为x的双亲结点
		if (t[x].rank == t[y].rank)	//x和y的结点秩相同
			t[y].rank++;		//y的结点秩增加1
	}
}


/*
*Example
*/

//P213【例7.11】The number of a tree
template<typename T> int Nodes(BTNode<T> *b)	
{
	if (b == 0) {
		return 0;
	}
	else {
		return Nodes(b->lchild) + Nodes(b->rchild) + 1;
	}		
}

// P214【例7.12】Display leaf node value
//from left to right
template<typename T> void DispLeafL(BTNode<T> *b)	//输出所有叶子结点（从左到右）【例7.12】 
{
	if (b != 0)
	{
		if (b->lchild == 0 && b->rchild == 0) {
			cout << b->data;
		}
		DispLeafL(b->lchild);
		DispLeafL(b->rchild);
	}
}

//from right to left
template<typename T> void DispLeafR(BTNode<T> *b)	//输出所有叶子结点（从右到左）【例7.12】 
{
	if (b != 0)
	{
		if (b->lchild == 0 && b->rchild == 0) {
			cout << b->data;
		}			
		DispLeafR(b->rchild);
		DispLeafR(b->lchild);
	}
}

// P215【例7.13】Display the level of X node
template<typename T> int Level(BTNode<T> *b, char x, int h)	
{
	int l;
	if (b == 0) {
		return 0;
	}		
	else if (b->data == x) {
		return h;
	}		
	else
	{
		l = Level(b->lchild, x, h + 1);
		if (l != 0) {
			return (l);
		}
		else {
			return(Level(b->rchild, x, h + 1));
		}			
	}
}

// P216【例7.14】Display the level of X node
// h = 1, n = 0
// h: variable of level, k: given level
// return: #nodes of k-th level
template<typename T> int Lnodenum(BTNode<T> *b, int h, int k) //输出某个层次的结点数
{
	int n = 0;
	if (b != 0) {
		if (h == k) {
			return 1;
		}
		else if (h < k) {
			return Lnodenum(b->lchild, h + 1, k) + Lnodenum(b->rchild, h + 1, k);
		}
		return 0;
	}
	else {
		return 0;
	}
}

// P217【例7.15】 Judge two binary trees is similar
template<typename T> bool Like(BTNode<T> *b1, BTNode<T> *b2)	//p217【例7.15】 两颗二叉树是否相似 
{
	bool like1, like2;
	if (b1 == 0 && b2 == 0) {
		return true;
	}		
	else if (b1 == 0 || b2 == 0) {
		return false;
	}		
	else
	{
		like1 = Like(b1->lchild, b2->lchild);
		like2 = Like(b1->rchild, b2->rchild);
		return (like1 && like2);
	}
}

// P217【例7.16】 Display all the parents node of X node
template<typename T> bool Ancestor(BTNode<T> *b, const T x)	//p218【例7.16】输出值为x结点的所有祖先 
{
	if (b == 0) {
		return false;
	}		
	else if (b->lchild != 0 && b->lchild->data == x || b->rchild != 0 && b->rchild->data == x)
	{
		cout << b->data;
		return true;
	}
	else if (Ancestor(b->lchild, x) || Ancestor(b->rchild, x))
	{
		cout << b->data;
		return true;
	}
	else {
		return false;
	}		
}

// P225【例7.17】Using binary tree(BTNode) display node value from leaf to root 
template<typename T> void AllPath1(BTNode<T> *b)
{
	BTNode<T> *p, *r;
	bool flag;
	SqStack<BTNode<T>*> *st;
	InitStack(st);
	p = b;
	do
	{
		while (p != 0)
		{
			Push(st, p);
			p = p->lchild;
		}
		r = 0;
		flag = true;
		while (!StackEmpty(st) && flag)
		{
			GetTop(st, p);
			if (p->rchild == r)
			{
				if (p->lchild == 0 && p->rchild == 0)
				{
					for (int i = st->top; i > 0; i--)
						cout << st->data[i]->data << "->";
					cout << st->data[0]->data << endl;
				}
				Pop(st, p);
				r = p;
			}
			else
			{
				p = p->rchild;
				flag = false;
			}
		}
	} while (!StackEmpty(st));
}

// P227【例7.18】Using sequence queue(SqQueue) display node value from leaf to root 
template<typename T> struct NodeType {
	T pt;
	int parent;
};

template<typename T> void AllPath2(BTNode<T> *b)
{
	int k;
	BTNode<T> *p;
	NodeType<BTNode<T>*> qelem;
	SqQueue<NodeType<BTNode<T>*>> *qu;
	InitQueue(qu);                     //非环形队列
	qelem.pt = b;
	qelem.parent = -1;                 //创建跟结点对应的队列元素
	enQueue(qu, qelem);                //根节点进队
	while (!QueueEmpty(qu)) {
		deQueue(qu, qelem);            //出队元素qelem ，在队中的下标为qu->front
		p = qelem.pt;
		if (p->lchild == 0 && p->rchild == 0) {
			k = qu->front;
			while (qu->data[k].parent != -1) {
				cout << qu->data[k].pt->data << "->";
				k = qu->data[k].parent ;
			}
			cout << qu->data[k].pt->data << endl;;
		}
		if (p->lchild != 0) {
			qelem.pt = p->lchild;
			qelem.parent = qu->front;
			enQueue(qu, qelem);
		}
		if (p->rchild != 0) {
			qelem.pt = p->rchild;
			qelem.parent = qu->front;
			enQueue(qu, qelem);
		}
	}
}

//P241 Kinship question
/*
  第一部分以N, M开始。N为问题涉及的人的个数（1 <= N <= 20,000）。这些人的编号为1，2，3，…，N。
  下面有M行（1 <= M <= 1,000,000），每行有两个数x，y，表示已知x 和 y是亲戚。
  第二部分以Q开始。以下Q行对应Q个询问（1 <= Q <= 1,000,000），每行为x，y，表示询问x和y是否为亲戚
*/
void KinshipQuestion()
{
	UFSTree t[MAX_SIZE];
	int N, M, x, y;
	cin >> N >> M;
	MAKE_SET(t, N);
	for (int i = 0; i < M; i++)
	{
		cin >> x >> y;
		UNION(t, x, y);
	}
	int Q;
	cin >> Q;
	for (int i = 0; i < Q; i++)
	{
		cin >> x >> y;
		if (FIND_SET(t, x) == FIND_SET(t, y))
			cout << "Yes, they are relatives.\n";
		else
			cout << "NO\n";
	}
}

void BTreeTraversalExample()
{
	BTNode<char> *T = 0;
	char str[] = "A(B(D(,G)),C(E,F))";
	CreateBTree(T, str);
	cout << "Display the tree ："; DispBTree(T);
	
	cout << endl <<"Height Of The Tree Is " << BTNodeDepth(T) << endl;
	cout  << "Width Of The Tree Is " << BTNodeWidth(T) << endl;

	cout << "Preorder Recursive Traversal："; PreOrderRecursively(T);
	cout << endl << "Inorder Recursive Traversal："; InOrderRecursively(T);
	cout << endl << "Postorder Recursive Traversal："; PostOrderRecursively(T);

	cout <<endl<<"Preorder non-recursive Traversal："; PreOrder(T);
	cout << "Inorder non-recursive Traversal："; InOrder(T);
	cout << "Postorder non-recursive Traversal："; PostOrder(T);
	cout << "Levelorder non-recursive Traversal: "; LevelOrder(T);
	TBTNode<char> *b;
	TCreateBTree(b, str);
	cout << endl << "InOrderThread Recursive Traversal："; InOderThread(CreateThread(b));

	cout << endl << "Num Of Nodes Is " << Nodes(T);
	cout << endl << "Display leaf node（form left to right）:"; DispLeafL(T);
	cout << endl << "Display leaf node（form right to left）:"; DispLeafR(T);

	// P215【例7.13】
	int h;
	char x;
	cout <<endl << "which node's level do you want to know?";
	cin >> x;
	h = Level(T, x , 1);
	if (h == 0) {
		cout << "Can't find the " << x << " node" << endl;
	}
	else {
		cout  << x << "'s height is " << h << endl;
	}
	
	// P216【例7.14】
	int k;
	cout << "which level'node do you want to know?";
	cin >> k;
	int n = 0;
	n = Lnodenum(T, 1, k);
	cout << "Num of node is："<<n << endl;
	
	// P217【例7.15】
	BTNode<char> *G;
	CreateBTree(G, str);
	if (Like(T, G) == true) {
		cout << "Similar！" << endl;
	}
	else {
		cout << "Not Similar！" << endl;
	}

	// p218【例7.16】
	char y;
	cout << "Enter the node:";
	cin >> y;
	cout << "Parent's node is ：";
	Ancestor(T, y);
	cout << endl;

	// P226 【例7.17】
	cout << "Using BTNode display node value from leaf to root：" << endl; AllPath1(T);
	// P226 【例7.18】
	cout << "Using SqQueue display node value from leaf to root：" << endl; AllPath2(T);
	

	char *pre = "ABDGCEF", *in = "DGBAECF", *post = "GDBEFCA";
	BTNode<char> *b1;
	b1 = CreateBT1(pre, in, 7);
	DispBTree(b1); cout << endl;

	BTNode<char> *b2;
	b2 = CreateBT2(post, in, 7);
	DispBTree(b2); cout << endl;

	// P216【例7.19】
	char a[] = " ABCD#EF#G#############";
	DispBTree(transStoL(a, 1)); cout << endl;

	//P240【例7.20】
	HTNode<char> ht[MAX_SIZE];
	HCode<char> hcd[50], p;
	int i, j, n0 = 8;
	char H[9] = "abcdefgh";
	double weight[9] = { 0.07,0.19,0.02,0.06,0.32,0.03,0.21,0.10 };
	for (i = 0; i < n0; i++) {
		ht[i].data = H[i];
		ht[i].weight = weight[i];
	}
	CreateHT(ht, n0);
	CreateHCode(ht, hcd, n0);
	cout<< "every leaf node's Huffman coding is:" << endl;
	for (i = 0; i < 8; i++) {
		cout<< ht[i].data << ':';
		p = hcd[i];
		for (j = p.start; j <= n0; j++) {
			cout << p.cd[j] << " ";
		}
		cout << endl;
	}

	//KinshipQuestion();

	DestroyBTree(T);

}

