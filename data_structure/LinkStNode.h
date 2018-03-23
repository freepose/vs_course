#pragma once
typedef int ElemType;

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
	p->data = s;
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

