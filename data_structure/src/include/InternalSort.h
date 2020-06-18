/*
 *
 * Create By TangNi , 2018
 *
 */


#pragma once

#include "basic.h"
#include "Search.h"


template<typename T, typename K> void ResetSort(RecType<T,K> R[], int n)
{
	int i, j = 0;
	for (i = n - 1; i >= 0; i--) {
		R[j].key = i;
		j++;
	}

}

template<typename T, typename K> void DispSort(RecType<T, K> R[], int n)
{
	for (int i = 0; i < n; i++) {
		cout << R[i].key << " ";
	}
	cout << endl;
}

//Straight insertion sort
template<typename T, typename K> void InsertSort(RecType<T, K> R[], int n)
{
	int i, j;
	RecType<T, K> tmp;
	for (i = 1; i < n; i++) {             //初始时有序区只有R[0]
		if (R[i].key < R[i - 1].key) {    //反序时
			tmp = R[i];
			j = i - 1;
			do {                         //寻找R[i]的插入位置
				R[j + 1] = R[j];         //后移
				j--;
			} while (j >= 0 && R[j].key>tmp.key);
			R[j + 1] = tmp;             //j+1处插入
		}
	}
}


//Binary insertion sort
template<typename T, typename K> void BinInsertSort(RecType<T, K> R[], int n)
{
	int i, j, low, high, mid;
	RecType<T, K> tmp;
	for (i = 1; i < n; i++) {
		if (R[i].key < R[i - 1].key) {        //反序时
			tmp = R[i];
			low = 0;
			high = i - 1;
			while (low <= high) {           //折半查找插入位置
				mid = (low + high) / 2;
				if (tmp.key < R[mid].key) {
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
			}
			for (j = i - 1; j >= high + 1; j--) {  //找到位置high，后移
				R[j + 1] = R[j];
			}
			R[high + 1] = tmp;          //插入tmp
		}
	}
}

//Shell sort
template<typename T, typename K> void ShellSort(RecType<T, K> R[], int n)
{
	int i, j, d;
	RecType<T, K> tmp;
	d = n / 2;           //增量置初值
	while (d > 0) {
		for (i = d; i < n; i++) {     //对每一小组采用直接插入排序
			tmp = R[i];
			j = i - d;
			while (j >= 0 && tmp.key < R[j].key) {
				R[j + d] = R[j];
				j = j - d;
			}
			R[j + d] = tmp;
		}
		d = d / 2;     //减小增量
	}
}



void InternalSortExmaple()
{
	RecType<int,int> R[MAX_SIZE];
	int n = 10;
	ResetSort(R, n);

	cout << "Original sequence is : "; DispSort(R, n);

	InsertSort(R, n);
	cout << "After Straight insertion sort : "; DispSort(R, n);

	ResetSort(R, n);
	BinInsertSort(R, n);
	cout << "After Binary insertion sort : "; DispSort(R, n);

	ResetSort(R, n);
	ShellSort(R, n);
	cout << "After Shell sort : "; DispSort(R, n);
}
