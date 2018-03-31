#ifndef SQQUEUE_H
#define SQQUEUE_H 1

#include "basic.h"

template <typename T> struct SqQueue {
	T data[MAX_SIZE];
	int front;
	int rear;
};


template <typename T> void InitQueue(SqQueue<T> *&q)
{
	q = new SqQueue<T>;
	q->front = q->rear = -1;
}


template <typename T> void DestroyQueue(SqQueue<T> *&q)
{
	delete q;
}


template <typename T> bool QueueEmpty(SqQueue<T> *q)
{
	return(q->front == q->rear);
}


template <typename T> bool enQueue(SqQueue<T> *&q, T e)
{
	if (q->front == MAX_SIZE - 1) {  //队满上溢出
		return false;
	}
	q->rear++;
	q->data[q->rear] = e;
	return true;
}


template <typename T> bool deQueue(SqQueue<T> *&q, T &e)
{
	if (q->front == q->rear) {  //队空下溢出
		return false;
	}
	q->front++;
	e = q->data[q->front];
	return true;
}


void SqQueueExample()
{
	int a[] = { 1,2,3,4,5 };
	const int n = 5;
	int e, i;
	SqQueue<int> *sqqueue;

	InitQueue(sqqueue);
	for (i = 0; i < n; i++) {
		enQueue(sqqueue, a[i]);
	}
	for (i = 0; i < n; i++) {
		deQueue(sqqueue, e);
		cout << e << '\t';
	}
	cout << endl;
}


#endif
