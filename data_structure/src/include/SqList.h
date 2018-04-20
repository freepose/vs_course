/*
*
* Create By Kaijin Cui,  20180401
*
*/
#pragma once
#include "basic.h"


template<typename T>  struct SqList {
    T data[MAX_SIZE];
	int length;
};


template<typename T> void InitList(SqList<T> *&L)
{
	L = new SqList<T>;
	L->length = 0;
}

template<typename T> void CreateList(SqList<T> *&L,T a[],int n)
{
	for(int i=0;i<n;i++){		
		L->data[i]=a[i];
	}
	L->length = n;
}

template<typename T> void DisplayList(SqList<T> *&L)
{
	for(int i=0;i<L->length;i++){		
		cout<<"\t"<<L->data[i];
	}
	cout<<endl;
}

template<typename T> void DestoryList(SqList<T> *&L)
{
	delete L;
	L = 0;
}

template<typename T> bool ListEmpty(SqList<T> *L)
{
	return (L->length == 0);
}

template<typename T> int ListLength(SqList<T> *L)
{
	return (L->length);
}

// 1-based
template<typename T> bool GetElem(SqList<T> *L, int i, T &e)
{
	if (i < 1 || i > L->length) {
		return false;
	}
	e = L->data[i - 1];
	return true;
}

// 1-based
template<typename T> int LocateElem(SqList<T> *L, T e)
{
	int i = 0;
	while (i<L->length && L->data[i] != e)
		i++;
	if (i >= L->length)  return 0;
	else  return i + 1;
}

template<typename T> bool ListInsert(SqList<T> *&L, int i, T e)
{
	int j;
	if (i<1 || i>L->length + 1) {
		return false; 
	}
		
	i--;    // 将顺序表逻辑序号转化为物理序号
	for (j = L->length; j > i; j--) {
		L->data[j] = L->data[j - 1];	//将data[i..n]元素后移一个位置
	}		
	L->data[i] = e;  //插入元素e
	L->length++;  //顺序表长度增1
	return true;   //成功插入返回true
}

template<typename T> bool ListDelete(SqList<T> *&L, int i, T &e)
{
	int j;
	if (i<1 || i>L->length) //参数错误时返回false
	{
		return false;
	}
		
	i--;    //将顺序表逻辑序号转化为物理序号
	e = L->data[i];
	for (j = i; j < L->length - 1; j++)   //将data[i..n-1]元素前移
	{
		L->data[j] = L->data[j + 1];
	}		
	L->length--;     //顺序表长度减1
	return true;     //成功删除返回true
}

template<typename T> void DeleteAllXNode(SqList<T> *&L, T x)
{
	int i = 0, j = 0;
	for (i = 0; i<L->length; i++) {
		if (L->data[i] != x) {
			L->data[j] = L->data[i];
			j++;
		}
	}
	L->length = j;
}


void SqListExample()
{
	int a[] = { 1, 2, 3, 4, 5 };
	const int n = 5;
	//print_array(a, n);

	// Sequence List
	SqList<int> *sqlist = 0;

	InitList(sqlist);
	CreateList(sqlist, a, n);
	DisplayList(sqlist);

	ListInsert(sqlist, 6, 6);
	DisplayList(sqlist);

	int deletedElement;
	ListDelete(sqlist, 6, deletedElement);
	DisplayList(sqlist);

	int b[] = { 1, 2, 3, 3, 3, 4, 5 };
	SqList<int> *sqlist2 = 0;
	InitList(sqlist2);
	CreateList(sqlist2, b, 7);
	DisplayList(sqlist2);
	DeleteAllXNode(sqlist2, 3);
	DisplayList(sqlist2);
}
