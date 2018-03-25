#pragma once
#include<iostream>
using namespace std;
typedef char ElemType;

typedef struct linknode
{
	ElemType data;
	struct linknode *next;
}LinkStNode;


void InitStack(LinkStNode *&s)
{
	s = new LinkStNode;
	s->next = 0;
}


void DestroyStack(LinkStNode *&s)
{
	LinkStNode *pre = s, *p = s->next;
	while (p != 0) {
		delete pre;
		pre = p;
		p = pre->next;
	}
	delete pre;
}


bool StackEmpty(LinkStNode *s)
{
	return(s->next == 0);
}


void Push(LinkStNode *&s, ElemType e)
{
	LinkStNode *p;
	p = new LinkStNode;
	p->data = e;
	p->next = s->next;
	s->next = p;
}


bool Pop(LinkStNode *&s, ElemType &e)
{
	LinkStNode *p;
	if (s->next== 0) {
		return false;
	}
	p = s->next;
	e = p->data;
	s->next = p->next;
	delete p;
	return true;
}


bool GetTop(LinkStNode *&s, ElemType &e)
{
	if (s->next == 0) {
		return false;
	}
	e = s->next->data;
	return true;
}


bool Match(char exp[], int n)
{
	int i = 0;
	char e;
	bool match = true;
	LinkStNode *st;
	InitStack(st);
	while (i < n&&match) {
		if (exp[i] == '(') {
			Push(st, exp[i]);
		}
		else if (exp[i] == ')') {
			if (GetTop(st,e) == true) {
				if (e != '(') {
					match = false;
				}
				else {
					Pop(st,e);
				}
			}
			else {
				match = false;    //the stack is empty
			}
		}
		i++;
	}
	if (!StackEmpty(st)){//the stack is not empty,so false
		match = false;
	}
	DestroyStack(st);
	return match;
}


void LinkStNodeExample()
{
	ElemType a[20];
	int n=10;
	cout << "ÇëÊäÈë10¸ö×Ö·û";
	cin >> a;
	if (Match(a, n)) {
		cout << "Yes"<<endl;
	}
	else {
		cout << "Not" << endl;
	}
}
