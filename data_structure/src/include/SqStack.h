/*
*
* Create By TangNi,  20180408
*
*/


#ifndef STACK_H
#define STACK_H 1

#include "basic.h"


template <typename T> struct SqStack {
	T data[MAX_SIZE];
	int top;
};


template <typename T> void InitStack(SqStack<T> *& S)
{
	S = new SqStack<T>;
	S->top = -1;
}

template <typename T> bool Push(SqStack<T>* &S, T e)
{
	if (S->top == MAX_SIZE - 1)
		return false;
	S->top++;
	S->data[S->top] = e;	
	return true;
}

template <typename T> bool Pop(SqStack<T>* &S, T &e)
{
	if (S->top == -1)
		return false;
	e = S->data[S->top];
	S->top--;
	return true;
}

template <typename T> void DestroyStack(SqStack<T>* &S)
{
	delete S;
}

template <typename T> void DispStack(SqStack<T>* S)
{
	while (S->top != -1)
	{
		cout << '\t' << S->data[S->top];
		S->top--;
	}
	cout << endl;
}

template <typename T> bool StackEmpty(SqStack<T> * S)
{
	return (S->top == -1);
}

template <typename T> bool GetTop(SqStack<T> *s, T &e)
{
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}

// 
// Examples: comments, code styles
//

bool Symmetry(char str[])
{
	int i; char e;
	SqStack<char> *st;
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

void SymmetryExample()
{
	char a[] = { '1', '2', '3', '4', '5' };
	char b[] = { 'a', 'b', 'b', 'a', '\0' };
	const int n = 5;

	SqStack<char> *S;
	InitStack(S);

	if (Symmetry(b)) {
		cout << b <<": a symmetric string." << endl;
	}		
	else {
		cout << b << ": an asymmetric string." << endl;
	}		
	DispStack(S);
	DestroyStack(S);
}

void trans(char *exp, char postexp[])
{
	char e;
	SqStack<char> *Optr;
	InitStack(Optr);
	int i = 0;
	while (*exp != '\0')
	{
		switch (*exp)
		{
		case'(':
			//cout << "(";
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
	SqStack<double> *Opnd;
	InitStack(Opnd);
	while (*postexp != '\0')
	{
		switch (*postexp)
		{
		case '+':
			Pop(Opnd, a);
			Pop(Opnd, b);
			c = b + a;
			Push(Opnd, c);
			break;
		case '-':
			Pop(Opnd, a);
			Pop(Opnd, b);
			c = b - a;
			Push(Opnd, c);
			break;
		case '*':
			Pop(Opnd, a);
			Pop(Opnd, b);
			c = b * a;
			Push(Opnd, c);
			break;
		case '/':
			Pop(Opnd, a);
			Pop(Opnd, b);
			c = b / a;
			Push(Opnd, c);
			break;
		default:
			d = 0;
			while (*postexp >= '0' && *postexp <= '9')
			{
				d = 10 * d + *postexp - '0';
				postexp++;
			}
			Push(Opnd, d);
			break;
		}
		postexp++;
	}
	GetTop(Opnd, e);
	DestroyStack(Opnd);
	return e;
}

void PostExpressionExample()
{
	char exp[] = "(56-20)/(4+2)";
	char postexp[200] = { 0 };
	trans(exp, postexp);
	cout << "中缀表达式：" << exp << endl;
	cout << "后缀表达式：" << postexp << endl;
	cout << "表达式的值：" << compvalue(postexp) << endl;
}

bool JudgeLegal(const string &s1, const string &s2)
{
	SqStack<char> *sc ;
	InitStack(sc);
	int i = 0, j = 0;
	char e;
	while (s1[i] != '\0')//入栈序列不为空 
	{
		GetTop(sc, e);
		if (s2[j] !=e  || (StackEmpty(sc)))//判断出栈序列所指元素与sc栈顶是否相同 
		{
			Push(sc, s1[i]);
			i++;
		}
		else if (s2[j] == e)//相同，则退栈并将出栈序列后移一位，进行下轮判断 
		{
			Pop(sc, e);
			j++;
		}
	}
	while (!StackEmpty(sc)) {//若sc未出栈完，接着判断
		GetTop(sc, e);
		if (s2[j] != e) {
			return false;
		}
		Pop(sc, e);
		j++;
	}
	return true;
}

void JudgeLegalExample()
{
	string s1 = "1234567", s2 = "2175643";
	if (JudgeLegal(s1, s2)) {
		cout << "input order:" << s1 << ", check order:" <<s2 << ", is legal." << endl;
	}		
	else {
		cout << "input order:" << s1 << ", check order:" << s2 << ", is illegal." << endl;
	}
}

void SqStackExample()
{
	SymmetryExample();
	PostExpressionExample();
	JudgeLegalExample();
}

#endif