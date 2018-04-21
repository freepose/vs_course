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


/* The basic operation of the tree (by PHY) */

template <typename T> void CreateBTree(BTNode<T> *&b, char *str)
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
				DispBTree(b->rchild);
				cout << ')';
			}
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
		rchilddeep = BTNodeDepth(b->rchild);;
		return (lchilddeep > rchilddeep) ? (lchilddeep + 1) : (rchilddeep + 1);
	}
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


/*
 *  Examples
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

/* P216【例7.14】Display the level of X node
 * h = 1, n = 0
 * h: variable of level, k: given level
 * return: #nodes of k-th level
 */
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


void BTreeTraversalExample()
{
	BTNode<char> *T = 0;
	char str[] = "A(B(D(,G)),C(E,F))";
	CreateBTree(T, str);
	cout << "Display the tree ："; DispBTree(T);
	
	cout << endl <<"Height Of The Tree Is " << BTNodeDepth(T) << endl;

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

	// P226 【例7.17】
	cout << "Using BTNode display node value from leaf to root：" << endl; AllPath1(T);
	// P226 【例7.18】
	cout << "Using SqQueue display node value from leaf to root：" << endl; AllPath2(T);
	DestroyBTree(T);

}
