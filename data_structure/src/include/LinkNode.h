#ifndef LINK_NODE_H
#define LINK_NODE_H 1

#include<iostream>
using namespace std;

typedef struct LNode {
	int data;
	LNode *next;
}LinkNode;

void CreateListF(LinkNode *&L, int a[], int n)
{
	LinkNode *s;
	L = new LinkNode;
	L->next = 0;
	for (int i = 0; i<n; i++) {
		s = new LinkNode;
		s->data = a[i];
		s->next = L->next;
		L->next = s;
	}
}

void CreateListR(LinkNode *&L, int a[], int n)
{
	LinkNode *s, *r;
	L = new LinkNode;
	r = L;
	for (int i = 0; i<n; i++) {
		s = new LinkNode;
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = 0;
}

void ListInsert(LinkNode *&L, int x, int n)
{
	LinkNode *p = L, *S;
	for (int i = 0; i < n-1; i++)
	{
		p = p->next;
	}
	S = new LinkNode;
	S->data = x;
	S->next = p->next;
	p->next = S;
}

void ListDelete(LinkNode *&L, int n)
{
	LinkNode *p = L, *pre = L;
	for (int i = 0; i < n; i++)
	{
		pre = p;
		p = p->next;
	}
	pre->next = p->next;
	delete p;
}

void DispList(LinkNode *L)
{
	LinkNode *p = L->next;
	while (p != 0) {
		cout << "\t" << p->data;
		p = p->next;
	}
	cout << endl;
}

void DestroyList(LinkNode *L)
{
	LinkNode *pre = L, *p = L->next;
	while (p != 0)
	{
		delete pre;
		pre = p;
		p = pre->next;
	}
	delete pre;
}


void delmaxnode(LinkNode *&L)
{
	LinkNode *p = L->next, *pre = L, *maxp = p, *maxpre = p;
	while (p != 0) {
		if (maxp->data < p->data) {
			maxp = p;
			maxpre = pre;
		}
		pre = p;
		p = p->next;
	}
	maxpre->next = maxp->next;
	delete maxp;
}

////////////////////////////////////////////////////////////////////////////////////
/// Cycle list
////////////////////////////////////////////////////////////////////////////////////

void CreateCircularListF(LinkNode *&L, int a[], int n)
{
	LinkNode *s, *r;
	L = new LinkNode;
	L->next = 0;
	for (int i = 0; i<n; i++) {
		s = new LinkNode;
		s->data = a[i];
		if (L->next == 0)
		{
			r = s;
		}
		s->next = L->next;
		L->next = s;
	}

}


void CreateCircularListR(LinkNode *&L, int a[], int n)
{
	LinkNode *s, *r;
	L = new LinkNode;
	r = L;
	for (int i = 0; i<n; i++) {
		s = new LinkNode;
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = L;	// note
}

// L, circle list
void JosephProblem(LinkNode *&L)
{
	LinkNode *p = L, *S;
	int times = 0, n;
	//cin >> n;		// put which number to delete
	n = 3;
	while (p->next->next != p)
	{
		p = p->next;
		if (p != L)
		{
			times++;
			if (times == n - 1)
			{
				S = p->next;
				p->next = p->next->next;
				cout <<"\t"<< S->data;
				delete S;
				times = 0;
			}
		}
	}
	cout << "\t" << p->data << endl;
	delete p;
}


// examples
void LinkNodeExample()
{
	int a[] = { 1, 2, 3, 4, 5 };
	const int n = 5;

	// Linked list
	LinkNode *linkedlist = 0;
	CreateListF(linkedlist, a, n);
	DispList(linkedlist);
	DestroyList(linkedlist);

	CreateListR(linkedlist, a, n);
	DispList(linkedlist);

	ListInsert(linkedlist, 3, 6);
	DispList(linkedlist);

	ListDelete(linkedlist, 6);
	DispList(linkedlist);

	delmaxnode(linkedlist);
	DispList(linkedlist);

	//int b[] = { 1, 2, 3, 4, 5, 6 };
	//CreateCircularListF(linkedlist, b, 6);
	//CreateCircularListR(linkedlist, b, 6);
	//JosephProblem(linkedlist);
}

#endif 