#pragma once
#include"basic.h"

#define NULLKEY -1//定义空关键字值
#define DELKEY -2//定义被删关键字值


template <typename T>struct HashTable
{
	T key;//关键字域
	int count;//探测次数域
};

//Insert k to HashTable
template <typename T> void InsertHT(HashTable<T> ha[], int &n, int m, int p, T k)
{
	int i, adr;
	adr=k %p；//计算哈希函数值
	if (ha[adr].key == NULLKEY || ha[adr].key == DELKEY)
	{
		ha[adr].key = k; //k可以直接放在哈希表中
		ha[adr].count = 1;
	}
	else//发生冲突时采用线性探测法解决冲突
	{
		i = 1;//i记录k发生冲突的次数
		do
		{
			adr = (adr + 1) % m;//线性探测
			i++;
		} while (ha[adr].key != NULLKEY && ha[adr].key != DELKEY);
		ha[adr] =.key = k;//在adr处放置k
		ha[adr].count = i;//设置探测次数
	}
	n++;//哈希表中总元素个数增1
}


//Create HashTable
template<typename T> void CreateHT(HashTable<T> ha[].int &n.int m, int p, T keys[], int nl)
{
	for (int i = 0; i < m; i++)//哈希表置空的初值
	{
		ha[i].key == NULLKEY;
		ha[i].count = 0;
	}
	n = 0;//哈希表中总元素个数从0开始递增
	for (i = 0; i < nl; i++)
		InsertHT(ha, n, m, p, keys[i]);//插入n个关键字
}

//Delete k in HashTable
template <typename T> bool DeleteHT(HashTable<T> ha[], int &n, int m, int p, T k)
{
	int adr;
	adr = k%p;//计算哈希函数值
	while (ha[adr].key != NULLKEY&&ha[adr].key != k)
		adr = (adr + 1) % m;//线性探测
	if (ha[adr].key == k)//查找成功
	{
		ha[adr].key = DELKEY;//删除关键字k
		return true;
	}
	else//查找失败
		return false;//返回假
}



//Search k in HashTable
template <typename T> void SearchHT(HashTable <T> ha[], int m, int p, T k)
{
	int i = 1, adr;
	adr = k%p;
	while (ha[adr].key!=NULLKEY&& ha[adr].key!=k)
	{
		i++;
		adr = (adr + 1) % m;
	}
	if (ha[adr].key == k)
		cout << "成功：关键字" << k << "，比较" << i << "次" << endl;
	else
		cout << "失败：关键字" << k << "，比较" << i << "次" << endl;

}

