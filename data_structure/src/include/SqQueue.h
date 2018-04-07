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


//circular queue
template <typename T> void InitCQueue(SqQueue<T> *&q)
{
	q = new SqQueue<T>;
	q->front = q->rear = 0;
}


template <typename T> void DestroyCQueue(SqQueue<T> *&q)
{
	delete q;
}


template <typename T> bool CQueueEmpty(SqQueue<T> *q)
{
	return(q->front == q->rear);
}


template <typename T> bool enCQueue(SqQueue<T> *&q, T e)
{
	if ((q->rear + 1) % MAX_SIZE == q->front) {
		return false;
	}
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->data[q->rear] = e;
	return true;
}


template <typename T> bool deCQueue(SqQueue<T> *&q, T e)
{
	if (q->front == q->rear) {
		return false;
	}
	q->front = (q->front + 1) % MAX_SIZE;
	e = q->data[q->front];
	return true;
}


//例3.7 count代替队尾指针
template <typename T> struct QuType
{
	T data[MAX_SIZE];
	int front;
	int count;
};

template <typename T> void InitQueue1(QuType<T> *&qu)
{
	qu = new QuType<T>;
	qu->front = 0;
	qu->count = 0;
}


template <typename T> bool EnQueue1(QuType<T>  *&qu, T x)
{
	int rear;
	if (qu->count == MAX_SIZE) {
		return false;
	}
	else {
		rear = (qu->front + qu->count) % MAX_SIZE;  //求队尾位置
		rear = (rear + 1) % MAX_SIZE;
		qu->data[MAX_SIZE] = x;
		qu->count++;
		return true;
	}
}


template <typename T> bool DeQueue1(QuType<T>  *&qu, T &x)
{
	if (qu->count == 0) {
		return false;
	}
	else {
		qu->front = (q->front + 1) % MAX_SIZE;
		x = qu->data[qu->front];
		qu->count--;
		return true;
	}
}


template <typename T> bool QueueEmpty1(QuType<T>  *qu)
{
	return (qu->count == 0);
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
		cout << '\t' << e;
	}
	cout << endl;
}


#endif
