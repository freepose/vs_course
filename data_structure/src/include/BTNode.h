/*
*
* Create By ChenXiaoDie,  20180410
*
*/


#include "basic.h"
template <typename T>  struct BTNode
{
	T data;
	BTNode<T> *lchild;
	BTNode<T> *rchild;
};

template <typename T> void CreateBTree(BTNode<T> *&b, T *str)
{
	BTNode<T> *St[MaxSize], *p;
	int top = -1, k, j = 0;
	T ch;
	b = NULL;
	ch = str[j];
	while (ch != '\0') {
		switch (ch) {
			case '(': top++; St[top] = p; k = 1; break;
			case ')': top--; break;
			case ',': k = 2; break;
			default:
				p = new BTNode<T>;
				p->data = ch;
				p->lchild = p->rchild = NULL;
				if (b == NULL) {
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
		ch= str[j];
	}

}

template <typename T> void DestroyBTree(BTNode<T> *&b) 
{
	if (b != NULL) {         /*if b is empty,do nothing*/
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		delete b;
	}
}

template <typename T>  BTNode<T>* FindNode(BTNode<T> *b, T x)
{
	BTNode<T> *p;
	if (b == NULL) {
		return NULL;
	}
	else if (b->data == x) {
		return b;
	}
	else {
		p = FindNode(b->lchild,x);
		if (p != NULL) {
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
	if (b == NULL) {
		return 0;
	}
	else {
		lchilddeep = BTNodeDepth(b->lchild);
		rchilddeep = BTNodeDepth(b->rchild);;
		return (lchilddeep > rchilddeep) ? (lchilddeep + 1) : (rchilddeep + 1);
	}

}

template <typename T> void DispBTree(BTNode<T> *b)
{
	if (b != NULL) {
		cout << b->data;
		if (b->lchild != NULL || b->rchild != NULL) {
			cout << '(';
			DispBTree(b->lchild);
			if (b->rchild != NULL) {
				cout << ',';
				DispBTree(b->rchild);
				cout << ')';
			}
		}
	}
}

void BTNodeexample()
{
	BTNode<char> *b;
	char str[MaxSize] = "A(B(D(,G)),C(E,F))";
	CreateBTree(b, str);
	DispBTree(b);
}