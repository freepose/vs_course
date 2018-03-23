#ifndef STACK_H
#define STACK_H 1

#include<memory.h>
#include<iostream>
using namespace std;

#define MAX_SIZE 50
typedef int ElemType;

typedef struct
{
	ElemType data[MAX_SIZE];
	int top;
} SqStack;

void CreateSqStack(SqStack* &S)
{
	S = new SqStack;
	memset(S, 0, sizeof(SqStack));
	S->top = -1;
}

bool push(SqStack* &S, ElemType e)
{
	if (S->top == MAX_SIZE - 1)
		return false;
	S->top++;
	S->data[S->top] = e;	
	return true;
}

bool pop(SqStack* &S, ElemType &e)
{
	if (S->top == -1)
		return false;
	S->data[S->top] = e;
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

void InitStack(SqStack* &S, ElemType a[], ElemType n)
{
	for (int i = 0; i < n; i++)
	{
		push(S, a[i]);
	}
}


void SqStackExample()
{
	int a[] = { 1, 2, 3, 4, 5 };
	const int n = 5;

	// SqStack
	SqStack *S;
	CreateSqStack(S);
	InitStack(S, a, n);
	DispStack(S, n);
	DestroyStack(S);

}

#endif