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
// Examples
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
	SqStack<char> *sc = new SqStack<char>;
	InitStack(sc);

	int i = 0, j = 0;
	char e;
	while (s2[i] != '\0')
	{
		if (s1[j] != s2[i] && s1[j] != '\0')
		{
			Push(sc, s1[j]);
			j++;
		}
		else if (s1[j] == s2[i])
		{
			i++;
			j++;
		}
		else
		{
			Pop(sc, e);
			if (e != s2[i])
				return false;
			i++;
		}
	}
	return true;
}

void JudgeLegalExample()
{
	string s1 = "12345", s2 = "45132";
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

// 迷宫求解

typedef struct
{
	int i;	//当前方块的行号
	int j;	//当前方块的列号
	int di;	//di是下一可走相邻方位的方位号
} Box;		//定义方块类型


int mg[8 + 2][8 + 2] =
{
	{ 1, 1,1,1,1,1,1,1,1,  1 },
	{ 1, 0,0,1,0,0,0,1,0,  1 },
	{ 1, 0,0,1,0,0,0,1,0,  1 },
	{ 1, 0,0,0,0,1,1,0,0,  1 },
	{ 1, 0,1,1,1,0,0,0,0,  1 },
	{ 1, 0,0,0,1,0,0,0,0,  1 },
	{ 1, 0,1,0,0,0,1,0,0,  1 },
	{ 1, 0,1,1,1,0,1,1,0,  1 },
	{ 1, 1,0,0,0,0,0,0,0,  1 },
	{ 1, 1,1,1,1,1,1,1,1,  1 }
};


bool mgpath(int xi, int yi, int xe, int ye)	//求解路径为:(xi,yi)->(xe,ye)
{
	Box path[MAX_SIZE], e;  int i, j, di, i1, j1, k;   bool find;
	SqStack<Box> *st = 0;			//定义栈st
	InitStack(st);				//初始化栈顶指针
	e.i = xi; e.j = yi; e.di = -1;			//设置e为入口
	Push(st, e);				//方块e进栈
	mg[xi][yi] = -1;	//入口的迷宫值置为-1避免重复走到该方块

	while (!StackEmpty(st))		//栈不空时循环
	{
		GetTop(st, e);		//取栈顶方块e
		i = e.i; j = e.j; di = e.di;
		if (i == xe && j == ye)		//找到了出口,输出该路径
		{
			printf("一条迷宫路径如下:\n");
			k = 0;
			while (!StackEmpty(st))
			{
				Pop(st, e);		//出栈方块e
				path[k++] = e;	//将e添加到path数组中
			}
			while (k >= 1)
			{
				k--;
				printf("\t(%d,%d)", path[k].i, path[k].j);
				if ((k + 2) % 5 == 0)  //每输出每5个方块后换一行
					printf("\n");
			}
			printf("\n");
			DestroyStack(st);//销毁栈
			return true;	//输出一条迷宫路径后返回true
		}
		find = false;
		while (di<4 && !find)   //找相邻可走方块(i1,j1)
		{
			di++;
			switch (di)
			{
			case 0:i1 = i - 1; j1 = j;   break;
			case 1:i1 = i;   j1 = j + 1; break;
			case 2:i1 = i + 1; j1 = j;   break;
			case 3:i1 = i;   j1 = j - 1; break;
			}
			if (mg[i1][j1] == 0)  find = true;
			//找到一个相邻可走方块，设置find为真
		}
		if (find)  		//找到了一个相邻可走方块(i1,j1)
		{
			st->data[st->top].di = di;	  //修改原栈顶元素的di值
			e.i = i1; e.j = j1; e.di = -1;
			Push(st, e);		  //相邻可走方块e进栈
			mg[i1][j1] = -1;
			//(i1,j1)迷宫值置为-1避免重复走到该方块
		}
		else			//没有路径可走,则退栈
		{
			Pop(st, e);	//将栈顶方块退栈
			mg[e.i][e.j] = 0;
			//让退栈方块的位置变为其他路径可走方块
		}
	}
	DestroyStack(st);	//销毁栈
	return false;		//表示没有可走路径
}

void mgpath_example()
{
	if (!mgpath(1, 1, 8, 8)) {
		printf("该迷宫问题没有解!");
	}
}

#endif