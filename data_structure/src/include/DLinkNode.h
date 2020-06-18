/*
 *
 * Create By TangNi,  20180420
 *
 */


#pragma once
#include "basic.h"


template <typename T> struct DLinkNode
{
	int data;
	DLinkNode<T> *prior;
	DLinkNode<T> *next;
};


/* The basic operation of the double linked list */
template <typename T> void CreateDListF(DLinkNode<T> *&L, T a[], int n)
{
	DLinkNode<T> *s;
	L = new DLinkNode<T>;
	L->prior = L->next = 0;
	for (int i = 0; i<n; i++) {
		s = new DLinkNode<T>;
		s->data = a[i];
		s->next = L->next;
		if (L->next != 0) {
			L->next->prior = s;
		}
		L->next = s;
		s->prior = L;
	}
}

template <typename T> void CreateDListR(DLinkNode<T> *&L, T a[], int n)
{
	DLinkNode<T> *s, *r;
	L = new DLinkNode<T>;
	r = L;
	for (int i = 0; i < n; i++) {
		s = new DLinkNode<T>;
		s->data = a[i];
		r->next = s;
		s->prior = r;
		r = s;
	}
	r->next = 0;
}

template <typename T> void DispDList(DLinkNode<T> *L)
{
	DLinkNode<T> *p = L->next;
	while (p != 0) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

template <typename T> bool DListInsert(DLinkNode<T> *&L, int i, T e)
{
	int j = 0;
	DLinkNode<T> *p = L, *s;
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
		s = new DLinkNode<T>;
		s->data = e;
		s->prior = p;
		s->next = p->next;
		p->next = s;
		s->next->prior = s;
	}
	return true;
}

template <typename T> bool DListDelete(DLinkNode<T> *&L, int i, T &e)
{
	DLinkNode<T> *p = L, *q;
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


// Two ways to destroy the linked list
template <typename T> void DestroyDListUsingPre(DLinkNode<T> *L)
{
	DLinkNode<T> *pre = L, *p = L->next;
	while (p != 0)
	{
		delete pre;
		pre = p;
		p = pre->next;
	}
	delete pre;
}

template <typename T> void DestroyDListUsingPrior(DLinkNode<T> *&L)
{
	DLinkNode<T> *p = L->next, *q = p->prior;
	while (p != 0) {
		delete q;
		q = p;
		p = p->next;
	}
	delete q;
}

// P60 【例2.12】Delete X Node
template <typename T> bool Del_X_Node(DLinkNode<T> *&L, T x)
{
	DLinkNode<T> *p = L->next;
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


/*cycle double linked list*/

template <typename T> void CreateCycleDListF(DLinkNode<T> *&L, T a[], int n)
{
	DLinkNode<T> *s;
	L = new DLinkNode<T>;
	L->prior = L->next = 0;
	for (int i = 0; i < n; i++) {
		s = new DLinkNode<T>;
		s->data = a[i];
		s->next = L->next;
		if (L->next != 0) {
			L->next->prior = s;
		}
		L->next = s;
		s->prior = L;
		if (s->next == 0) {
			s->next = L;
			L->prior = s;
		}
	}
}

template <typename T> void CreateCycleDListR(DLinkNode<T> *&L, T a[], int n)
{
	DLinkNode<T> *r, *s;
	L = new DLinkNode<T>;
	r = L;
	for (int i = 0; i < n; i++) {
		s = new DLinkNode<T>;
		s->data = a[i];
		r->next = s;
		s->prior = r;
		r = s;
	}
	r->next = L;
	L->prior = r;
}

template <typename T> void DispCycleDList(DLinkNode<T> *L)//循环双链表的输出
{
	DLinkNode<T> *p = L->next;
	while (p != L) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

// P60 【例2.13】Jugde the double linked list is symmetry？
template <typename T> bool Symm(DLinkNode<T> *L)//判断循环双链表的数据结点是否对称
{
	bool same = true;  //same表示L是否对称
	DLinkNode<T> *p = L->next, *q = L->prior;
	while (same) {
		if (p->data != q->data) {
			same = false;
		}
		else {
			if (p == q || p == q->prior) {
				break;
			}
			else {
				q = q->prior;
				p = p->next;
			}
		}
	}
	return same;
}


void DLinkNodeExample()
{
	int c[] = { 1,2,3,4,5,4 };
	const int n = 6;
	int e = 0;
	DLinkNode<int> *dlinknode;

	CreateDListF(dlinknode, c, n);
	DispDList(dlinknode);

	//DestroyDListUsingPre(dlinknode);
	DestroyDListUsingPrior(dlinknode);

	CreateDListR(dlinknode, c, n);
	//DispDList(dlinknode);

	if (DListInsert(dlinknode, 3, e)) {
		DispDList(dlinknode);
	}
	if (DListDelete(dlinknode, 3, e)) {
		DispDList(dlinknode);
	}
	if (Del_X_Node(dlinknode, 4)) {
		DispDList(dlinknode);
	}

	//Cycle Double list
	int c1[] = { 1,2,3,4,5,6 };
	DLinkNode<int> *cdlinknode = 0;

	CreateCycleDListR(cdlinknode, c1, n);
	DispCycleDList(cdlinknode);
	if (Symm(cdlinknode)) {
		cout << "Symmetry!" << endl;
	}
	else {
		cout << "Not Symmetry!" << endl;
	}
}
