#ifndef DLINK_NODE_H
#define DLINK_NODE_H 1

#include<iostream>
using namespace std;

#define MAX_SIZE 250
typedef int ElemType;

typedef struct DLink
{
	int data;
	DLink *prior;
	DLink *next;
}DLinkNode;


void CreateDListF(DLinkNode *&L, ElemType a[], int n)
{
	DLinkNode *s;
	L = new DLinkNode;
	L->prior = L->next = 0;
	for (int i = 0; i<n; i++) {
		s = new DLinkNode;
		s->data = a[i];
		s->next = L->next;
		if (L->next != 0) {
			L->next->prior = s;
		}
		L->next = s;
		s->prior = L;
	}
}


void CreateDListR(DLinkNode *&L, ElemType a[], int n)
{
	DLinkNode *s ,*r;
	L = new DLinkNode;
	r = L;
	for (int i = 0; i < n; i++) {
		s = new DLinkNode;
		s->data = a[i];
		r->next = s;
		s->prior = r;
		r = s;
	}
	r->next = 0;
}


void DispDList(DLinkNode *L)
{
	DLinkNode *p = L->next;
	while (p != 0) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}


bool DListInsert(DLinkNode *&L, int i, ElemType e)
{
	int j = 0;
	DLinkNode *p = L, *s;
	if (i <= 0) {
		return false;
	}
	while (j<i - 1 && p != 0) {
		j++;
		p = p->next;
	}
	if (p == 0) {
		return false;
	}
	else {
		s = new DLinkNode;
		s->data = e;
		s->prior = p;
		s->next = p->next;
		p->next = s;
		s->next->prior = s;
	}
	return true;
}


bool DListDelete(DLinkNode *&L, int i, ElemType &e)
{
	DLinkNode *p = L, *q;
	if (i <= 0) {
		return false;
	}
	int j = 0;
	while (j<i - 1 && p != 0) {
		j++;
		p = p->next;
	}
	if (p == 0) {
		return false;
	}
	else {
		q = p->next;
		e = q->data;
		p->next = q->next;
		p->next->prior = p->prior;
		delete q;
	}
	return true;
}


//销毁双链表的两种方法
void DestroyDList_pre(DLinkNode *L)
{
	DLinkNode *pre = L, *p = L->next;
	while (p != 0)
	{
		delete pre;
		pre = p;
		p = pre->next;
	}
	delete pre;
}


void DestroyDList_prior(DLinkNode *&L)
{
	DLinkNode *p = L->next, *q = p->prior;
	while (p != 0) {
		delete q;
		q = p;
		p = p->next;
	}
	delete q;
}


bool Del_X_Node(DLinkNode *&L, ElemType x)
{
	DLinkNode *p = L->next;
	while (p != 0 && p->data != x) {
		p = p->next;
	}
	if (p == 0) {
		return false;
	}
	else {
		p->prior->next = p->next;
		p->next->prior = p->prior;
		delete p;
	}
	return true;
}


////////////////////////////////////////////////////////////////////////////////////
/// Cycle list
////////////////////////////////////////////////////////////////////////////////////


void CreateCircularDListF(DLinkNode *&L, int a[], int n)
{
	DLinkNode *s;
	L = new DLinkNode;
	L->next = 0;
	for (int i = 0; i<n; i++) {
		s = new DLinkNode;
		s->data = a[i];
		if (s->next == 0)
		{
			s->next = L;
		}
		s->next = L->next;
		L->next = s;
	}
}


void CreateCircularDListR(DLinkNode *&L, int a[], int n)
{
	DLinkNode *s, *r;
	L = new DLinkNode;
	r = L;
	for (int i = 0; i > n; i++) {
		s = new DLinkNode;
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = L;
}


void DispCDList(DLinkNode *L)
{
	DLinkNode *p = L->next;
	while (p != L) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}


void DLinkNodeExample()
{
	int c[] = { 1,2,3,4,5,4 };
	const int n = 6;
	int e=0;
	DLinkNode *dlinknode;

	CreateDListF(dlinknode, c, n);
	//DispDList(dlinknode);

	//DestroyDList_pre(dlinknode);
	DestroyDList_prior(dlinknode);

	CreateDListR(dlinknode, c, n);
	//DispDList(dlinknode);

	if (DListInsert(dlinknode, 3, e)) {
		//DispDList(dlinknode);
	}
	if (DListDelete(dlinknode, 3, e)) {
		//DispDList(dlinknode);
	}
	if (Del_X_Node(dlinknode, 4)) {
		//DispDList(dlinknode);
	}

	//Cycle list
	int c1[] = { 1,2,3,4,5,6 };
	DLinkNode *cdlinknode = 0;

	CreateCircularDListF(cdlinknode, c1, n);
	DispDList(cdlinknode);

}

#endif 