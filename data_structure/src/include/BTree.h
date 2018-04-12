#pragma once

#include "basic.h"

typedef char ElemType;

typedef ElemType SqBinTree[MAX_SIZE];

typedef struct node
{
	ElemType data;	//数据元素 
	struct node *lchild;	//指向左孩子节点 
	struct node *rchild;	//指向右孩子节点 
}BTNode;

int n = 0;	//p216例7.14全局变量 

void CreateBTree(BTNode *&b, char *str)
{
	BTNode *St[MAX_SIZE], *p;	//St数组作为顺序栈 
	int top = -1, k, j = 0;	//top为栈顶指针 
	char ch;
	b = NULL; 	//初始时二叉链为空 
	ch = str[j];
	while (ch != '\0') 	//循环扫描str中的每个字符 
	{
		switch (ch)
		{
		case '(': top++; St[top] = p; k = 1; break;	//开始处理左孩子结点 
		case ')': top--; break;	//栈顶结点的子树处理完毕 
		case ',': k = 2; break; 	//开始处理右孩子结点 
		default: p = new BTNode; 	//创建一个结点，由p指向它 
			p->data = ch; 	//存放结点值 
			p->lchild = p->rchild = NULL; 	//左右指针都设置为空 
			if (b == NULL) 	//尚未建立根结点 
				b = p;	//p所指结点就作为根结点 
			else 	//已建立二叉树根结点 
			{
				switch (k)
				{
				case 1: St[top]->lchild = p; break; 	//新建结点作为栈顶结点的左孩子 
				case 2: St[top]->rchild = p; break; 	//新建结点作为栈顶结点的右孩子
				}
			}
		}
		j++;	//继续扫描str 
		ch = str[j];
	}
}


void DispBTree(BTNode *b)
{
	if (b != NULL)
	{
		cout << b->data;
		if (b->lchild != NULL || b->rchild != NULL)
		{
			cout << "(";
			DispBTree(b->lchild);
			if (b->rchild != NULL)
				cout << ",";
			DispBTree(b->rchild);
			cout << ")";
		}
	}
}

void PreOrder(BTNode *b)	//先序遍历递归算法 
{
	if (b != NULL)
	{
		cout << b->data;
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}

void InOrder(BTNode *b)	//中序遍历递归算法 
{
	if (b != NULL)
	{
		InOrder(b->lchild);
		cout << b->data;
		InOrder(b->rchild);
	}
}

void PostOrder(BTNode *b)	//后序遍历递归算法 
{
	if (b != NULL)
	{
		PostOrder(b->lchild);
		PostOrder(b->rchild);
		cout << b->data;
	}
}

int Nodes(BTNode *b)	//结点个数 【例7.11】 
{
	int num1, num2;
	if (b == NULL)
		return 0;
	else
		return Nodes(b->lchild) + Nodes(b->rchild) + 1;
}

void DispLeaf(BTNode *b)	//输出所有叶子结点（从左到右）【例7.12】 
{
	if (b != NULL)
	{
		if (b->lchild == NULL && b->rchild == NULL)
			cout << b->data;
		DispLeaf(b->lchild);
		DispLeaf(b->rchild);
	}
}

void DispLeaf1(BTNode *b)	//输出所有叶子结点（从右到左）【例7.12】 
{
	if (b != NULL)
	{
		if (b->lchild == NULL && b->rchild == NULL)
			cout << b->data;
		DispLeaf(b->rchild);
		DispLeaf(b->lchild);
	}
}

int Level(BTNode *b, ElemType x, int h)	//输入的结点值所在的层次 
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

void Lnodenum1(BTNode *b, int h, int k)
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

bool Like(BTNode *b1, BTNode *b2)	//p217【例7.15】 两颗二叉树是否相似 
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

bool ancestor(BTNode *b, ElemType x)	//p218【例7.15】输出值为x结点的所有祖先 
{
	if (b == NULL)
		return false;
	else if (b->lchild != NULL&&b->lchild->data == x || b->rchild != NULL&&b->rchild->data == x)
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

void BTreeExample()
{
	BTNode *T;
	CreateBTree(T, "A(B(D(,G)),C(E,F))");
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
	cout << Nodes(T) << endl;
	cout << "输出所有叶子结点（从左到右）" << endl;
	DispLeaf(T);
	cout << endl;
	cout << "输出所有叶子结点（从右到左）" << endl;
	DispLeaf1(T);
	cout << endl;
	//p215【例7.13】
	int h;
	ElemType x;
	cout << "结点值：" << endl;
	cin >> x;
	h = Level(T, x, 1);
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
	BTNode *G;
	CreateBTree(G, "A(B(D(,G)),C(E,F))");
	if (Like(T, G) == true)
		cout << "相似！" << endl;
	else
		cout << "不相似！" << endl;
	//p218【例7.16】
	ElemType y;
	cout << "输入值y" << endl;
	cin >> y;
	ancestor(T, y);

}



