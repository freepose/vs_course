#pragma once

#include "basic.h"

template <typename T>  struct BTNode
{
	T data;
	BTNode<T> *lchild;
	BTNode<T> *rchild;
};


template <typename T> void CreateBTree(BTNode<T> *& b, char *str)
{
	BTNode<T> *St[MAX_SIZE], *p;
	int top = -1, k, j = 0;
	T ch;
	b = 0;
	ch = str[j];
	while (ch != '\0') {
		switch (ch) {
		case '(': top++; St[top] = p; k = 1; break;
		case ')': top--; break;
		case ',': k = 2; break;
		default:
			p = new BTNode<T>;
			p->data = ch;
			p->lchild = p->rchild = 0;
			if (b == 0) {
				b = p;
			}
			else {
				switch (k) {
				case 1: St[top]->lchild = p; break;
				case 2: St[top]->rchild = p; break;
				}
			}
		}
		j++;
		ch = str[j];
	}

}

template <typename T> void DestroyBTree(BTNode<T> *&b)
{
	if (b != 0) {         /* if b is empty, do nothing */
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		delete b;
	}
}

template <typename T> void DispBTree(BTNode<T> *b)
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

template <typename T>  BTNode<T>* FindNode(BTNode<T> *b, const T x)
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

template <typename T>  BTNode<T>* LchildNode(BTNode<T> *p)
{
	return p->lchild;
}

template <typename T> BTNode<T>* RchildNode(BTNode<T> *p)
{
	return p->rchild;
}

template <typename T> int BTNodeDepth(BTNode<T> *b)
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


/*  traverse methods of a tree: recursive traverse  */


template <typename T> void PreOrder(BTNode<T> *b)	//先序遍历递归算法 
{
	if (b != 0)
	{
		cout << b->data << " ";
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}

template <typename T> void InOrder(BTNode<T> *b)	//中序遍历递归算法 
{
	if (b != 0)
	{
		InOrder(b->lchild);
		cout << b->data << " ";
		InOrder(b->rchild);
	}
}

template <typename T> void PostOrder(BTNode<T> *b)	//后序遍历递归算法 
{
	if (b != 0)
	{
		PostOrder(b->lchild);
		PostOrder(b->rchild);
		cout << b->data << " ";
	}
}

template <typename T> int Nodes(BTNode<T> *b)	//结点个数 【例7.11】 
{
	if (b == 0) {
		return 0;
	}
	else {
		return Nodes(b->lchild) + Nodes(b->rchild) + 1;
	}		
}

// Display node value from left to right
template <typename T> void DispLeafL(BTNode<T> *b)	//输出所有叶子结点（从左到右）【例7.12】 
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


// Display node value from right to left
template <typename T> void DispLeafR(BTNode<T> *b)	//输出所有叶子结点（从右到左）【例7.12】 
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


template<typename T> int Level(BTNode<T> *b, char x, int h)	// 输入的结点值所在的层次 
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

// h = 1, n = 0
template <typename T> void Lnodenum(BTNode<T> *b, int h, int k, int &n)
{
	if (b == 0){
		return;
	}		
	else
	{
		if (h == k) {
			n++;
		}			
		else if (h < k)
		{
			Lnodenum(b->lchild, h + 1, k, n);
			Lnodenum(b->rchild, h + 1, k, n);
		}
	}
}

template <typename T> bool Like(BTNode<T> *b1, BTNode<T> *b2)	//p217【例7.15】 两颗二叉树是否相似 
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


template <typename T> bool Ancestor(BTNode<T> *b, const T x)	//p218【例7.15】输出值为x结点的所有祖先 
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

void BTreeTraversalExample()
{
	BTNode<char> *T = 0;
	char str[] = "A(B(D(,G)),C(E,F))";
	CreateBTree(T, str);
	cout << "显示二叉树：";
	DispBTree(T);
	cout << endl << "先序遍历递归：";
	PreOrder(T);
	cout << endl << "中序遍历递归：";
	InOrder(T);
	cout << endl << "后序遍历递归：";
	PostOrder(T);
	cout << endl << "结点个数:" << Nodes<char>(T) << endl;
	cout << "输出所有叶子结点（从左到右）:";
	DispLeafL(T);
	cout << endl << "输出所有叶子结点（从右到左）:";
	DispLeafR(T);

	//p215【例7.13】
	int h;
	char x;
	cout << endl << "结点值：";
	cin >> x;
	h = Level<char>(T, x, 1);
	if (h == 0)
		cout << "T中不存在" << x << "结点" << endl;
	else
		cout << "在T中" << x << "结点的层次为" << h << endl;
	//p216【例7.14】
	int k;
	cout << "第几层？" << endl;
	cin >> k;
	int  n = 0;	// p216例7.14全局变量 
	Lnodenum(T, 1, k, n);
	cout << n << endl;
	//p217【例7.15】
	BTNode<char> *G;
	CreateBTree(G, str);
	if (Like(T, G) == true)
		cout << "相似！" << endl;
	else
		cout << "不相似！" << endl;
	//p218【例7.16】
	char y;
	cout << "输入值y" << endl;
	cin >> y;
	Ancestor<char>(T, y);
}
