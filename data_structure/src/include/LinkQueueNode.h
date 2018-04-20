#pragma once

#include "basic.h"
#include "LinkNode.h"

//单链表
template<typename T> struct DataNode
{
	T data;
	DataNode<T> *next;
};

//链队
template<typename T> struct LinkQueueNode
{
	DataNode<T> *front;
	DataNode<T> *rear;
};


template<typename T> void InitQueue(LinkQueueNode<T> *&q)
{
	q = new LinkQueueNode<T>;
	q->front = q->rear = 0;
}


template<typename T> void DestroyQueue(LinkQueueNode<T> *&q)
{
	DataNode<T> *pre = q->front, *p;
	if (pre != 0) {
		p = pre->next;
		while (p != NULL) {
			delete pre;
			pre = p;
			p = p->next;
		}
		delete pre;//释放最后一个数据结点
	}
	delete q;//释放链队结点
}


template<typename T> bool QueueEmpty(LinkQueueNode<T> *q)
{
	return(q->rear == NULL);
}


template<typename T> void enQueue(LinkQueueNode<T> *&q, T e)
{
	DataNode<T> *p;
	p = new DataNode<T>;//创建新的结点
	p->data = e;
	p->next = NULL;
	if (q->rear == NULL) {
		q->rear = q->front = p;
	}
	else {
		q->rear->next = p;//将结点链到队尾，并用rear指向它
		q->rear = p;
	}
}

template<typename T> bool deQueue(LinkQueueNode<T> *&q, T &e)
{
	DataNode<T> *t;
	if (q->rear == NULL) {
		return false;
	}
	t = q->front;
	if (q->front == q->rear) {//只有一个数据结点时
		q->front = q->rear = NULL;
	}
	else {
		q->front = q->front->next;
	}
	e = t->data;
	delete t;
	return true;
}

///////////////////////////////////////text///////////////////////////////////

void LinkQueueNodeexample()
{
	int i, e;
	int Q[] = { 1,2,3,4,5 };
	LinkQueueNode<int> *q;
	InitQueue(q);
	for (i = 0; i < 5; i++) {
		enQueue(q, Q[i]);
	}
	for (i = 0; i < 5; i++) {
		deQueue(q, e);
		cout << '\t' << e << endl;  //将所有元素出队
	}
	DestroyQueue(q);
	cout << endl;
}

////////////////////////example/////循环单链表储存队列///////////////////////


template<typename T> void InitQueue_S(LinkNode<T> *&rear)
{
	rear = NULL;
}


template<typename T> void enQueue_S(LinkNode<T> *&rear, T e)
{
	LinkNode<T> *p;
	p = new LinkNode<T>;
	p->data = e;
	if (rear == NULL) {
		p->next = p;
		rear = p;
	}
	else {
		p->next = rear->next;
		rear->next = p;
		rear = p;
	}
}


template<typename T> bool deQueue_S(LinkNode<T> *&rear, T &e)
{
	LinkNode<T> *t = 0;
	if (rear == NULL) {
		return false;
	}
	else if (rear->next==rear) {
		e = rear->data;
		delete rear;
		rear = NULL;
	}
	else {
		t = rear->next;
		e = t->data;
		rear->next = t->next;
		delete t;
	}
	return true;
}


template<typename T> bool queueEmpty_S(LinkNode<T> *rear)
{
	return(rear == NULL);
}


void S_LinkQueueNodeexample()
{
	int i, e;
	int M[] = { 6,7,8,9 };
	LinkNode<int> *rear;
	InitQueue_S(rear);
	for (i = 0; i < 4; i++) {
		enQueue_S(rear, M[i]);
	}
	for (i = 0; i < 4; i++) {
		deQueue_S(rear, e);
		cout << '\t' << e << endl; //将所有元素出队
	}
}