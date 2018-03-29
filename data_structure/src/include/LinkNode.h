#ifndef LINK_NODE_H
#define LINK_NODE_H 1


#include<iostream>
using namespace std;

template <typename T> struct LinkNode {
	T data;
	LinkNode<T> *next;
};

template <typename T> void CreateListF(LinkNode<T>  *&L, T a[], int n)
{
	LinkNode<T> *s;
	L = new LinkNode<T>;
	L->next = 0;
	for (int i = 0; i<n; i++) {
		s = new LinkNode<T>;
		s->data = a[i];
		s->next = L->next;
		L->next = s;
	}
}

template <typename T> void CreateListR(LinkNode<T>  *&L, T a[], int n)
{
	LinkNode<T>  *s, *r;
	L = new LinkNode<T>;
	r = L;
	for (int i = 0; i<n; i++) {
		s = new LinkNode<T>;
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = 0;
}

template <typename T> void ListInsert(LinkNode<T> *&L, T x, int n)
{
	LinkNode<T> *p = L, *S;
	for (int i = 0; i < n - 1; i++)
	{
		p = p->next;
	}
	S = new LinkNode<T>;
	S->data = x;
	S->next = p->next;
	p->next = S;
}

template <typename T> void ListDelete(LinkNode<T> *&L, int n)
{
	LinkNode<T> *p = L, *pre = L;
	for (int i = 0; i < n; i++)
	{
		pre = p;
		p = p->next;
	}
	pre->next = p->next;
	delete p;
}

template <typename T> void DispList(LinkNode<T> *L)
{
	LinkNode<T> *p = L->next;
	while (p != 0) {
		cout << "\t" << p->data;
		p = p->next;
	}
	cout << endl;
}

template <typename T> void DestroyList(LinkNode<T> *L)
{
	LinkNode<T> *pre = L, *p = L->next;
	while (p != 0)
	{
		delete pre;
		pre = p;
		p = pre->next;
	}
	delete pre;
}


template <typename T> void delmaxnode(LinkNode<T> *&L)
{
	LinkNode<T> *p = L->next, *pre = L, *maxp = p, *maxpre = p;
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

template <typename T> void CreateCircularListF(LinkNode<T> *&L, T a[], int n)
{
	LinkNode<T> *s, *r;
	L = new LinkNode<T>;
	L->next = 0;
	for (int i = 0; i<n; i++) {
		s = new LinkNode<T>;
		s->data = a[i];
		if (L->next == 0)
		{
			r = s;
		}
		s->next = L->next;
		L->next = s;
	}

}


template <typename T> void CreateCircularListR(LinkNode<T> *&L, T a[], int n)
{
	LinkNode<T> *s, *r;
	L = new LinkNode<T>;
	r = L;
	for (int i = 0; i<n; i++) {
		s = new LinkNode<T>;
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = L;	// note
}

// L, circle list
template <typename T> void JosephProblem(LinkNode<T> *&L)
{
	LinkNode<T> *p = L, *S;
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
				cout << "\t" << S->data;
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
	LinkNode<int> *linkedlist = 0;
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

	int b[] = { 1, 2, 3, 4, 5, 6 };
	CreateCircularListF(linkedlist, b, 6);
	CreateCircularListR(linkedlist, b, 6);
	JosephProblem(linkedlist);
}

#endif 