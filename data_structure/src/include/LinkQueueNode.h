/*
*
* Create By ChenXiaodie,2018
*
*/



#pragma once
#include "basic.h"
#include "LinkNode.h"


template<typename T> struct DataNode
{
	T data;
	DataNode<T> *next;
};

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
		while (p != 0) {
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
	return(q->rear == 0);
}

template<typename T> void enQueue(LinkQueueNode<T> *&q, T e)
{
	DataNode<T> *p;
	p = new DataNode<T>;
	p->data = e;
	p->next = 0;
	if (q->rear == 0) {
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
	if (q->rear == 0) {
		return false;
	}
	t = q->front;
	if (q->front == q->rear) {//只有一个数据结点时
		q->front = q->rear = 0;
	}
	else {
		q->front = q->front->next;
	}
	e = t->data;
	delete t;
	return true;
}

/*Circular LinkQueueNode */

template<typename T> void InitQueue_S(LinkNode<T> *&rear)
{
	rear = 0;
}

template<typename T> void enQueue_S(LinkNode<T> *&rear, T e)
{
	LinkNode<T> *p;
	p = new LinkNode<T>;
	p->data = e;
	if (rear == 0) {
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
	if (rear == 0) {
		return false;
	}
	else if (rear->next==rear) {
		e = rear->data;
		delete rear;
		rear = 0;
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
	return(rear == 0);
}


/*
 *  examples
 */

void LinkQueueNodeexample()
{
	int i, e;
	int Q[] = { 1,2,3,4,5 };
	int M[] = { 6,7,8,9 };
	//LinkQueueNodeexample
	LinkQueueNode<int> *q;
	InitQueue(q);
	for (i = 0; i < 5; i++) {
		enQueue(q, Q[i]);
	}
	for (i = 0; i < 5; i++) {
		deQueue(q, e);
		cout << '\t' << e << endl;  
	}
	DestroyQueue(q);
	cout << endl;
	//Cycle_LinkQueueNodeexample
	LinkNode<int> *rear;
	InitQueue_S(rear);
	for (i = 0; i < 4; i++) {
		enQueue_S(rear, M[i]);
	}
	for (i = 0; i < 4; i++) {
		deQueue_S(rear, e);
		cout << '\t' << e << endl;
	}
}