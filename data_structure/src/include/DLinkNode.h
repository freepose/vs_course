#ifndef DLINK_NODE_H
#define DLINK_NODE_H 1

#include<iostream>
using namespace std;

#define MAX_SIZE 50
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

void DLinkNodeExample()
{
	int c[] = { 1,2,3,4,5,4 };
	const int n = 6;
	int e=0;
	DLinkNode *dlinknode;

	CreateDListF(dlinknode, c, n);
	if (DListInsert(dlinknode, 3, e)) {
		DispDList(dlinknode);
	}
	if (DListDelete(dlinknode, 3, e)) {
		DispDList(dlinknode);
	}
	if (Del_X_Node(dlinknode, 3)) {
		DispDList(dlinknode);
	}
}

#endif 