/*
 *
 * Create By PengHaoyun,20180409
 *
 */

#include "basic.h"

int n = 0;	// p216例7.14全局变量 
char str[] = "A(B(D(,G)),C(E,F))";

template <typename T> void PreOrder(BTNode<T> *b)	//先序遍历递归算法 
{
	if (b != NULL)
	{
		cout << b->data;
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}

template <typename T> void InOrder(BTNode<T> *b)	//中序遍历递归算法 
{
	if (b != NULL)
	{
		InOrder(b->lchild);
		cout << b->data;
		InOrder(b->rchild);
	}
}

template <typename T> void PostOrder(BTNode<T> *b)	//后序遍历递归算法 
{
	if (b != NULL)
	{
		PostOrder(b->lchild);
		PostOrder(b->rchild);
		cout << b->data;
	}
}

template <typename T> int Nodes(BTNode<T> *b)	//结点个数 【例7.11】 
{
	int num1, num2;
	if (b == NULL)
		return 0;
	else
		return Nodes(b->lchild) + Nodes(b->rchild) + 1;
}

template <typename T> void DispLeaf(BTNode<T> *b)	//输出所有叶子结点（从左到右）【例7.12】 
{
	if (b != NULL)
	{
		if (b->lchild == NULL && b->rchild == NULL)
			cout << b->data;
		DispLeaf(b->lchild);
		DispLeaf(b->rchild);
	}
}

template <typename T> void DispLeaf1(BTNode<T> *b)	//输出所有叶子结点（从右到左）【例7.12】 
{
	if (b != NULL)
	{
		if (b->lchild == NULL && b->rchild == NULL)
			cout << b->data;
		DispLeaf(b->rchild);
		DispLeaf(b->lchild);
	}
}

template<typename T> int Level(BTNode<T> *b, char x, int h)	//输入的结点值所在的层次 
{
	int l;
	if (b == NULL)
		return 0;
	else if (b->data == x)
		return h;
	else
	{
		l = Level(b->lchild, x, h + 1);
		if (l != 0)
			return (l);
		else
			return(Level(b->rchild, x, h + 1));
	}
}

template <typename T> void Lnodenum1(BTNode<T> *b, int h, int k)
{
	if (b == NULL)
		return;
	else
	{
		if (h == k)
			n++;
		else if (h<k)
		{
			Lnodenum1(b->lchild, h + 1, k);
			Lnodenum1(b->rchild, h + 1, k);
		}
	}
}

template <typename T> bool Like(BTNode<T> *b1, BTNode<T> *b2)	//p217【例7.15】 两颗二叉树是否相似 
{
	bool like1, like2;
	if (b1 == NULL && b2 == NULL)
		return true;
	else if (b1 == NULL || b2 == NULL)
		return false;
	else
	{
		like1 = Like(b1->lchild, b2->lchild);
		like2 = Like(b1->rchild, b2->rchild);
		return (like1&&like2);
	}
}

template <typename T> bool ancestor(BTNode<T> *b, T x)	//p218【例7.15】输出值为x结点的所有祖先 
{
	if (b == NULL)
		return false;
	else if (b->lchild != NULL && b->lchild->data == x || b->rchild != NULL && b->rchild->data == x)
	{
		cout << b->data;
		return true;
	}
	else if (ancestor(b->lchild, x) || ancestor(b->rchild, x))
	{
		cout << b->data;
		return true;
	}
	else
		return false;
}

void BTreeTraversalExample()
{
	BTNode<char> *T;
	CreateBTree(T, str);
	cout << "显示二叉树：" << endl;
	DispBTree(T);
	cout << endl;
	cout << "先序遍历递归：" << endl;
	PreOrder(T);
	cout << endl;
	cout << "中序遍历递归：" << endl;
	InOrder(T);
	cout << endl;
	cout << "后序遍历递归：" << endl;
	PostOrder(T);
	cout << endl;
	cout << "结点个数:" << endl;
	cout << Nodes<char>(T) << endl;
	cout << "输出所有叶子结点（从左到右）" << endl;
	DispLeaf(T);
	cout << endl;
	cout << "输出所有叶子结点（从右到左）" << endl;
	DispLeaf1(T);
	cout << endl;
	//p215【例7.13】
	int h;
	char x;
	cout << "结点值：" << endl;
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
	Lnodenum1(T, 1, k);
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
	ancestor<char>(T, y);

}