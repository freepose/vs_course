/*
 *
 * Create By TangNi, 20180408
 *
 */
#pragma once
#include "basic.h"


template<typename T> struct SqQueue {
	T data[MAX_SIZE];
	int front;
	int rear;
};


template<typename T> void InitQueue(SqQueue<T> *&q)
{
	q = new SqQueue<T>;
	q->front = q->rear = -1;
}

template<typename T> void DestroyQueue(SqQueue<T> *&q)
{
	delete q;
}

template<typename T> bool QueueEmpty(SqQueue<T> *q)
{
	return(q->front == q->rear);
}

template<typename T> bool enQueue(SqQueue<T> *&q, T e)
{
	if (q->front == MAX_SIZE - 1) {  //队满上溢出
		return false;
	}
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

template<typename T> bool deQueue(SqQueue<T> *&q, T &e)
{
	if (q->front == q->rear) {  //队空下溢出
		return false;
	}
	q->front++;
	e = q->data[q->front];
	return true;
}

//circular queue
template<typename T> void InitCycleQueue(SqQueue<T> *&q)
{
	q = new SqQueue<T>;
	q->front = q->rear = 0;
}

//从队尾进队
template<typename T> bool enCycleQueueR(SqQueue<T> *&q, T e)
{
	if ((q->rear + 1) % MAX_SIZE == q->front) {
		return false;
	}
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->data[q->rear] = e;
	return true;
}

//从队头进队
template<typename T> bool enCycleQueueF(SqQueue<T> *&q,T e)
{
	if ((q->rear + 1) % MAX_SIZE == q->front) {
		return false;
	}
	q->data[q->front] = e;
	q->front = (q->front - 1 + MAX_SIZE) % MAX_SIZE;  //修改头指针
	return true;
}

//从队头删除
template<typename T> bool deCycleQueueF(SqQueue<T> *&q, T &e)
{
	if (q->front == q->rear) {
		return false;
	}
	q->front = (q->front + 1) % MAX_SIZE;
	e = q->data[q->front];
	return true;
}

//从队尾删除
template<typename T> bool deCycleQueueR(SqQueue<T> *&q, T &e)
{
	if (q->rear == q->front) {
		return false;
	}
	e = q->data[q->rear];
	q->rear = (q->rear - 1 + MAX_SIZE) % MAX_SIZE;
	return true;
}

//P102 例【3.7】Count instead of p->rear;
template<typename T> struct QuType
{
	T data[MAX_SIZE];
	int front;
	int count;
};

template<typename T> void InitQueue_count(QuType<T> *&qu)
{
	qu = new QuType<T>;
	qu->front = 0;
	qu->count = 0;
}

template<typename T> bool EnQueue_count(QuType<T>  *&qu, T x)
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

template<typename T> bool DeQueue_count(QuType<T>  *&qu, T &x)
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

template<typename T> bool QueueEmpty_count(QuType<T>  *qu)
{
	return (qu->count == 0);
}


//P108 The number problem
void number(int n)
{
	int i;
	int e=0;
	SqQueue<int> *q;        //环形队列指针q
	InitCycleQueue(q);
	for (i = 1; i <=n; i++) {
		enCycleQueueR(q, i);
	}
	cout << "报数出列顺序：" << endl;
	while (!QueueEmpty(q)) {
		enCycleQueueF(q, e);
		cout << '\t' << e;
		if (!QueueEmpty(q)) {
			deCycleQueueR(q, e);
			enCycleQueueR(q, e);
		}
	}
	cout << endl;
	DestroyQueue(q);
}


void SqQueueExample()
{
	int n = 8;
	cout << "初始序列" << endl;
	for (int i = 1; i <= n; i++) {
		cout << '\t' << i;
	}
	cout << endl;
	number(n);
}
