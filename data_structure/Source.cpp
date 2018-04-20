#include<iostream>
#define Maxsize 100 

using namespace std;

typedef int ElemType;

typedef struct node {
	ElemType data;
	struct node *lchild;                 //左孩子
	struct node *rchild;                 //右孩子
}BTN;

BTN *p;

void createBTN(BTN *&p, char *str);
void preorder(BTN *p);
void displeaf(BTN *p);
int level(BTN *p, ElemType x, int h);
int wideth(BTN *p);

int main()
{
	char x;
	int h;
	cin >> x;
	createBTN(p, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I))) ");
	preorder(p);
	displeaf(p);
	h = level(p, x, 1);
	cout << h;
	wideth(p);
}

void createBTN(BTN *&p, char *str)              //创建二叉树
{
	BTN *st[Maxsize], *b;
	int top = -1, k, j = 0;
	char ch;
	p = NULL;

	ch = str[j];
	while (ch != '\0') {
		switch (ch)
		{
		case '(':top++; st[top] = b; k = 1; break;   //左孩子进栈
		case ')':top--; break;                       //出栈
		case ',':k = 2; break;                       //右孩子进栈
		default:b = new BTN;
			b->data = ch;
			b->lchild = b->rchild = NULL;
			if (p == NULL) {
				p = b;
			}
			else {
				switch (k) {
				case '1':st[top]->lchild = p; break;
				case '2':st[top]->rchild = p; break;
				}
			}
		}
		j++;
		ch = str[j];
	}
}

void preorder(BTN *p)                        //先序遍历输出P的节点
{
	if (p != NULL) {
		cout << p->data;
		preorder(p->lchild);
		preorder(p->rchild);
	}
}

void displeaf(BTN *p)                           //先序遍历输出所有叶子节点
{
	if (p != NULL) {
		if (p->lchild == NULL&&p->rchild == NULL) {
			cout << p->data;
			displeaf(p->lchild);
			displeaf(p->rchild);
		}
	}
}

int level(BTN *p, ElemType x, int h)
{
	int l;

	if (p == NULL) {
		return 0;
	}
	else if (p->data == x) {
		return h;
	}
	else {
		l = level(p->lchild, x, h + 1);
		if (l != 0) {
			return l;
		}
		else {
			return level(p->rchild, x, h + 1);
		}
	}
}

int wideth(BTN *p)
{
	BTN *b;
	BTN *qu[Maxsize];

	int front, rear;
	front = rear = -1;
	rear++;
	qu[rear] = p;

	int lastwideth, curwideth, nwideth, size = 1, t;

	if (p == NULL) {
		cout << 0;
	}

	nwideth = 1;
	lastwideth = 1;

	while (front != rear) {
		while (lastwideth != 0) {
			front = (front + 1) % Maxsize;
			b = qu[front];
			size--;
			if (b->lchild != NULL) {
				rear = (rear + 1) % Maxsize;
				qu[rear] = b->lchild;
				size++;
			}
			if (b->rchild != NULL) {
				rear = (rear + 1) % Maxsize;
				qu[rear] = b->rchild;
				size++;
			}
			t = size;
			lastwideth--;
		}
		curwideth = t;
		nwideth = curwideth > nwideth ? curwideth : nwideth;
		lastwideth = curwideth;
	}
	cout << nwideth;
	return 0;
}