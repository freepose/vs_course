/*
*
* Create By Kaijin Cui
*
*/


#pragma once
#include "basic.h"
#include"SqList.h"
#include"LinkNode.h"

typedef struct LinkNode<char> LinkStrNode;

void StrAssignLink(LinkStrNode *&s, char cstr[])
{
	int i;
	LinkStrNode *r, *p;
	s = new LinkStrNode;
	r = s;
	for (i = 0; cstr[i] != '\0'; i++)
	{
		p = new LinkStrNode;
		p->data = cstr[i];
		r->next = p;
		r = p;
	}
	r->next = NULL;
}

void DestroyStrLink(LinkStrNode *&s)
{
	LinkStrNode *pre = s, *p = s->next;
	while (p != 0)
	{
		delete pre;
		pre = p;
		p = p->next;
	}
	delete pre;
}

void StrCopyLink(LinkStrNode *&s, LinkStrNode *t)
{
	LinkStrNode *p = t->next, *q, *r;
	s = new LinkStrNode;
	r = s;
	while (p != 0)
	{
		q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
}

bool StrEqualLink(LinkStrNode *s, LinkStrNode *t)
{
	LinkStrNode *p = s->next, *q = t->next;
	while (p != 0 && q != 0 && p->data == t->data)
	{
		p = p->next;
		q = q->next;
	}
	if (p == 0 && q == 0)
		return true;
	else
		return false;
}

int StrLengthLink(LinkStrNode *s)
{
	int i = 0;
	LinkStrNode *p = s->next;
	while (p != NULL)
	{
		i++;
		p = p->next;
	}
	return i;
}

LinkStrNode *ConcatLink(LinkStrNode *s, LinkStrNode *t)
{
	LinkStrNode *str, *p = s->next, *q, *r;
	str = new LinkStrNode;
	r = str;
	while (p != NULL)
	{
		q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	p = t->next;
	while (p != NULL)
	{
		q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
}

LinkStrNode *SubStrLink(LinkStrNode *s, int i, int j)
{
	int k;
	LinkStrNode *str, *p = s->next, *q, *r;
	str = new LinkStrNode;
	str->next = NULL;
	r = str;
	if (i <= 0 || i > StrLengthLink(s) || j < 0 || i + j - 1 > StrLengthLink(s))
	{
		return str;
	}
	for (k = 1; k < i; k++)
	{
		p = p->next;
	}
	for (k = 1; k <= j; k++)
	{
		q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
}

LinkStrNode *InsStrLink(LinkStrNode *s, int i, LinkStrNode *t)
{
	int k;
	LinkStrNode *str, *p = s->next, *p1 = t->next, *q, *r;
	str = new LinkStrNode;
	str->next = NULL;
	r = str;
	if (i <= 0 || i > StrLengthLink(s) + 1)
		return str;
	for (k = 1; k < i; k++)
	{
		q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	while (p1 != NULL)
	{
		q = new LinkStrNode;
		q->data = p1->data;
		r->next = q;
		r = q;
		p1 = p1->next;
	}
	while (p != NULL)
	{
		q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
}

LinkStrNode *DelStrLink(LinkStrNode *s, int i, int j)
{
	int k;
	LinkStrNode *str, *p = s->next, *q, *r;
	str = new LinkStrNode;
	str->next = NULL;
	r = str;
	if (i <= 0 || i > StrLengthLink(s) || j < 0 || i + j - 1 > StrLengthLink(s))
		return str;
	for (k = 1; k < i; k++)
	{
		q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	for (k = 0; k < j; k++)
		p = p->next;
	while (p != NULL)
	{
		q = new LinkStrNode;
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
}

LinkStrNode *RepStr(LinkStrNode *s, int i, int j, LinkStrNode *t)
{
	int k;
	LinkStrNode *str, *p = s->next, *p1 = t->next, *q, *r;
	str = new LinkStrNode;
	str->next = NULL;
	r = str;
	if (i <= 0 || i > StrLengthLink(s) || j < 0 || i + j - 1 > StrLengthLink(s))
		return str;
	for (k = 0; k < i - 1; k++)
	{
		q = new LinkStrNode;
		q->data = p->data;
		q->next = NULL;
		r->next = q;
		r = q;
		p = p->next;
	}
	for (k = 0; k < j; k++)
		p = p->next;
	while (p1 != NULL)
	{
		q = new LinkStrNode;
		q->data = p1->data;
		q->next = NULL;
		r->next = q;
		r = q;
		p1 = p1->next;
	}
	while (p != NULL)
	{
		q = new LinkStrNode;
		q->data = p->data;
		q->next = NULL;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
}

void DispStrLink(LinkStrNode *s)
{
	LinkStrNode *p = s->next;
	while (p != NULL)
	{
		cout << p->data;
		p = p->next;
	}
	cout << endl;
}


/*
*Examples
*/

//P133 Àư¡¾4.3¡¿Change the first substring "ab" in the string s to "xyz"
void Repl(LinkStrNode *&s)
{
	LinkStrNode *p = s->next, *q;
	bool find = false;
	while (p != NULL && p->next != NULL && !find)
	{
		if (p->data == 'a' && p->next->data == 'b')
		{
			p->data = 'x';
			p->next->data = 'z';
			q = new LinkStrNode;
			q->data = 'y';
			q->next = p->next;
			p->next = q;
			find = true;
		}
		else p = p->next;
	}
}


void LinkStringExample()
{
	LinkStrNode *s1, *s2;
	char str1[] = "abcdefg", str2[] = "123";
	StrAssignLink(s1, str1);
	DispStrLink(s1);

	StrAssignLink(s2, str2);
	StrCopyLink(s1, s2);
	DispStrLink(s1);

	if (StrEqualLink(s1, s2))
	cout << "Yes";
	else
	cout << "No";
	cout << endl << "s1->length = " << StrLengthLink(s1) << endl;

	DispStrLink(s1);
	s1 = ConcatLink(s1, s2);
	DispStrLink(s1);

	DispStrLink(s1);
	s1 = SubStrLink(s1, 1, 5);
	DispStrLink(s1);

	StrAssignLink(s2, str1);
	DispStrLink(s1);
	DispStrLink(s2);
	s1 = InsStrLink(s1, 3, s2);
	DispStrLink(s1);

	DispStrLink(s1);
	s1 = DelStrLink(s1, 2, 4);
	DispStrLink(s1);

	DispStrLink(s1);
	DispStrLink(s2);
	s1 = RepStr(s1, 2, 2, s2);
	DispStrLink(s1);

	DispStrLink(s1);
	Repl(s1);
	DispStrLink(s1);

	DestroyStrLink(s1);
	DestroyStrLink(s2);
}