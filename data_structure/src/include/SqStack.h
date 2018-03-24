#ifndef STACK_H
#define STACK_H 1

#include<memory.h>
#include<iostream>
using namespace std;

#define MAX_SIZE 50
#define ElemType char

typedef struct
{
	ElemType data[MAX_SIZE];
	int top;
} SqStack;

void InitStack(SqStack *& S)
{
	S = new SqStack;
	S->top = -1;
}

bool Push(SqStack* &S, ElemType e)
{
	if (S->top == MAX_SIZE - 1)
		return false;
	S->top++;
	S->data[S->top] = e;	
	return true;
}

bool Pop(SqStack* &S, ElemType &e)
{
	if (S->top == -1)
		return false;
	e = S->data[S->top];
	S->top--;
	return true;
}

void DestroyStack(SqStack* &S)
{
	delete S;
}

void DispStack(SqStack* S, ElemType n)
{
	while (S->top != -1)
	{
		cout << '\t' << S->data[S->top];
		S->top--;
	}
	cout << endl;
}

bool StackEmpty(SqStack * S)
{
	return (S->top == -1);
}

bool GetTop(SqStack *s, ElemType &e)
{
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}

bool Symmetry(ElemType str[])
{
	int i; ElemType e;
	SqStack *st;
	InitStack(st);
	for (i = 0; str[i] != '\0'; i++)
	{
		Push(st, str[i]);
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		Pop(st, e);
		if (str[i] != e)
		{
			DestroyStack(st);
			return false;
		}
	}
	DestroyStack(st);
	return true;
}
void SqStackExample()
{
	ElemType a[] = { '1', '2', '3', '4', '5' };
	ElemType b[] = { 'a', 'b', 'b', 'a', '\0' };
	const int n = 5;
	// SqStack
	SqStack *S;
	InitStack(S);
	if (Symmetry(b))
		cout << "\tYes";
	else
		cout << "\tNo";
	DispStack(S, n);
	DestroyStack(S);

}

#endif