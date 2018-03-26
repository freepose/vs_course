#pragma once
#ifndef MaxSize
#define MaxSize 50

#include"SqStack.h"

typedef struct
{
	double data[MAX_SIZE];
	int top;
} SqStack1;

void InitStack1(SqStack1 *& S)
{
	S = new SqStack1;
	S->top = -1;
}


bool Push1(SqStack1* &S, double e)
{
	if (S->top == MAX_SIZE - 1)
		return false;
	S->top++;
	S->data[S->top] = e;
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

bool GetTop1(SqStack1 *s, double &e)
{
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}

void DestroyStack1(SqStack1* &S)
{
	delete S;
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
		switch(*postexp)
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

void ArithmeticExample()
{
	char exp[] = "(56-20)/(4+2)";
	char postexp[MaxSize] = { 0 };
	trans(exp, postexp);
	cout << "中缀表达式：" << exp << endl
		<< "后缀表达式：" << postexp << endl
		<< "表达式的值：" << compvalue(postexp) << endl;
}
#endif // !MaxSize