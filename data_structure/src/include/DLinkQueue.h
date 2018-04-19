#pragma once
#include"basic.h"

template <typename T> struct DDataNode		//双端链队数据结点类型
{
	T data;
	DDataNode<T> *next;
	DDataNode<T> *prear;
};

template <typename T> struct DLinkQueue		//双端链队节点类型
{
	DDataNode<T> *front;
	DDataNode<T> *rear;
};

template <typename T> void InitDLinkQueue(DLinkQueue<T> *&dq)		//初始化队列
{
	dq = new DLinkQueue<T>;
	dq->front = dq->rear = 0;
}

template <typename T> void DestroyDLinkQueue(DLinkQueue<T> *&dq)		//销毁队列
{
	DDataNode<T> *dpre = dq->front, *p;
	while (dpre != 0)
	{
		p = dpre->next;
		while (p != 0)
		{
			delete dpre;
			dpre = p;
			p = p->next;
		}
		delete p;
	}
	delete dq;
}

template <typename T> bool DLinkQueueEmpty(DLinkQueue<T> *dq)		//判断队列是否为空
{
	return (dq->rear == 0);
}

template <typename T> void enFDLinkQueue(DLinkQueue<T> *&dq, T e)		//头入队
{
	DDataNode<T> *p;
	p = new DDataNode<T>;
	p->data = e;
	p->next = p->prear = 0;
	if (dq->rear == 0)		//如果原队列为空
		dq->front = dq->rear = p;
	else
	{
		dq->front->prear = p;		//将头结点的前一个结点指向p
		p->next = dq->front;		//将p的下一个结点连接到头结点
		dq->front = p;				//头结点改为p结点
	}
}

template <typename T> void enRDLinkQueue(DLinkQueue<T> *&dq, T e)		//尾入队
{
	DDataNode<T> *p;
	p = new DDataNode<T>;
	p->data = e;
	p->next = 0;
	p->prear = dq->rear;		//p的前结点指向尾节点
	if (dq->rear == 0)		//如果原队列为空
		dq->front = dq->rear = p;
	else
	{
		dq->rear->next = p;			//将尾结点的下一个结点连接p
		dq->rear = p;				//尾结点改为p结点
	}
}

template <typename T> bool deFDLinkQueue(DLinkQueue<T> *&dq, T &e)		//头出队
{
	DDataNode<T> *t;
	if (dq->front == 0)		//如果原队列为空
		return false;
	t = dq->front;
	if (dq->front == dq->rear)		//队列中只有一个结点
		dq->front = dq->rear = 0;
	else
		dq->front = dq->front->next;
	e = t->data;
	delete t;
	return true;
}

template <typename T> bool deRDLinkQueue(DLinkQueue<T> *&dq, T &e)		//尾出队
{
	DDataNode<T> *t;
	if (dq->rear == 0)		//如果原队列为空
		return false;
	t = dq->rear;
	if (dq->front == dq->rear)		//队列中只有一个结点
		dq->front = dq->rear = 0;
	else
		dq->rear = dq->rear->prear;
	e = t->data;
	delete t;
	return true;
}

void DLinkQueueExamples()
{
	DLinkQueue<int> *dq;
	InitDLinkQueue(dq);
	int a[] = { 1, 2, 3, 4, 5 };
	for (int i = 0; i < 5; i++)
	{
		enFDLinkQueue(dq, a[i]);
	}
	int e;
	while (!DLinkQueueEmpty(dq))
	{
		deRDLinkQueue(dq, e);
		cout << '\t' << e;
	}
	DestroyDLinkQueue(dq);
}