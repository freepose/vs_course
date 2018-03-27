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

typedef struct
{
	double data[MAX_SIZE];
	int top;
} SqStack1;

void InitStack(SqStack *& S)
{
	S = new SqStack;
	S->top = -1;
}

void InitStack1(SqStack1 *& S)
{
	S = new SqStack1;
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

bool Push1(SqStack1* &S, double e)
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

bool Pop1(SqStack1* &S, double &e)
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

void DestroyStack1(SqStack1* &S)
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

bool GetTop1(SqStack1 *s, double &e)
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

void trans(char *exp, char postexp[])
{
	char e;
	SqStack *Optr;
	InitStack(Optr);
	int i = 0;
	while (*exp != '\0')
	{
		switch (*exp)
		{
		case'(':
			cout << "(";
			Push(Optr, '(');
			exp++;
			break;
		case')':
			Pop(Optr, e);
			while (e != '(')
			{
				postexp[i++] = e;
				Pop(Optr, e);
			}
			exp++;
			break;
		case'+':
		case'-':
			while (!StackEmpty(Optr))
			{
				GetTop(Optr, e);
				if (e != '(')
				{
					postexp[i++] = e;
					Pop(Optr, e);
				}
				else
					break;
			}
		case'*':
		case'/':
			while (!StackEmpty(Optr))
			{
				GetTop(Optr, e);
				if (e == '*' || e == '/')
				{
					postexp[i++] = e;
					Pop(Optr, e);
				}
				else
					break;
			}
			Push(Optr, *exp);
			exp++;
			break;
		default:
			while (*exp >= '0' && *exp <= '9')
			{
				postexp[i++] = *exp;
				exp++;
			}
			postexp[i++] = '#';
		}
	}
	while (!StackEmpty(Optr))
	{
		Pop(Optr, e);
		postexp[i++] = e;
	}
	postexp[i] = '\0';
	DestroyStack(Optr);
}

double compvalue(char *postexp)
{
	double d, a, b, c, e;
	SqStack1 *Opnd;
	InitStack1(Opnd);
	while (*postexp != '\0')
	{
		switch (*postexp)
		{
		case '+':
			Pop1(Opnd, a);
			Pop1(Opnd, b);
			c = b + a;
			Push1(Opnd, c);
			break;
		case '-':
			Pop1(Opnd, a);
			Pop1(Opnd, b);
			c = b - a;
			Push1(Opnd, c);
			break;
		case '*':
			Pop1(Opnd, a);
			Pop1(Opnd, b);
			c = b * a;
			Push1(Opnd, c);
			break;
		case '/':
			Pop1(Opnd, a);
			Pop1(Opnd, b);
			c = b / a;
			Push1(Opnd, c);
			break;
		default:
			d = 0;
			while (*postexp >= '0' && *postexp <= '9')
			{
				d = 10 * d + *postexp - '0';
				postexp++;
			}
			Push1(Opnd, d);
			break;
		}
		postexp++;
	}
	GetTop1(Opnd, e);
	DestroyStack1(Opnd);
	return e;
}

void SqStackExample()
{
	//ElemType a[] = { '1', '2', '3', '4', '5' };
	//ElemType b[] = { 'a', 'b', 'b', 'a', '\0' };
	//const int n = 5;
	//// SqStack
	//SqStack *S;
	//InitStack(S);
	//if (Symmetry(b))
	//	cout << "\tYes";
	//else
	//	cout << "\tNo";
	//DispStack(S, n);
	//DestroyStack(S);

	char exp[] = "(56-20)/(4+2)";
	char postexp[MAX_SIZE] = { 0 };
	trans(exp, postexp);
	cout << "中缀表达式：" << exp << endl
		<< "后缀表达式：" << postexp << endl
		<< "表达式的值：" << compvalue(postexp) << endl;
}

#endif