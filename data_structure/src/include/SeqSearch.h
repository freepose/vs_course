/*
*
* Create By Kaijin Cui,2018
*
*/


#pragma once
#include"basic.h"

template <typename T, typename K>struct RecType
{
	K key;	//关键字项
	T data;		//其他数据项
};		//查找元素的类型

template <typename T, typename K>int SeqSreach(RecType<T,K> R[], int n, K k)
{
	int i = 0;
	while (i < n && R[i].key != k)		//从表头往后找
		i++;
	if (i > n)							//未找到返回0
		return 0;
	else
		return i + 1;					//找到返回逻辑序号i + 1
}

template <typename T, typename K>int SeqSreach1(RecType<T, K> R[], int n, K k)
{
	int i = 0;
	R[n].key = k;
	while (R[i].key != k)		//从表头往后找
		i++;
	if (i == n)
		return 0;				//未找到返回零
	else
		return i + 1;			//找到返回逻辑序号i + 1
}

void SeqSearchExample()
{
	RecType<int, int> R[MAX_SIZE];
	for (int i = 0; i < 6; i++)
	{
		R[i].key = i;
	}
	
	cout << "顺序查找2的位置为：" << SeqSreach(R, 6, 2) << endl;
	cout << "顺序查找3的位置为：" << SeqSreach(R, 6, 3) << endl;
}