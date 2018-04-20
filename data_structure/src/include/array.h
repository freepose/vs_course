/*
*
* Create By Kaijin Cui
*
*/


#pragma once
#include"basic.h"


template<typename T> void read_array(T a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
}

template<typename T> void print_array(const T a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "\t" << a[i];
	}
	cout << endl;
}

template<typename T> void select_sort_array(T a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] > a[j])
			{
				swap(a[i], a[j]);
			}
		}
	}
}

template<typename T> void buble_sort_array(T a[], int n)
{
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
			}
		}
	}
}

// KMP algorithm
void cal_next(char *s, int len, int *next)
{
	next[0] = -1;
	int k = -1;
	for (int q = 1; q < len; q++)
	{
		while (k > -1 && s[k + 1] != s[q])
		{
			k = next[k];
		}
		if (s[k + 1] == s[q])
		{
			k = k + 1;
		}
		next[q] = k;
	}
}

void KMP(char *s1, int len1, char *s2, int len2)
{
	int *next = new int[5];
	cal_next(s2, len2, next);
	int k = -1;
	for (int i = 0; i < len1; i++)
	{
		while (k > -1 && s1[i] != s2[k + 1])
		{
			k = next[k];
		}
		if (s1[i] == s2[k + 1])
		{
			k = k + 1;
		}
		if (k == len2 - 1)
		{
			cout << "在位置" << i - len2 + 1 << endl;
			k = -1;
			i = i - len2 + 1;
		}
	}
}


void  arrayExample()
{
	int n = 6;
	int a[8] = { 1, 3, 3, 34, 2, 5 };
	// read_array(a,n);
	//buble_sort_array(a, n);//调用冒泡排序
	//print_array(a, n);
	//select_sort_array(a, n);//调用选择排序
	//print_array(a, n);
	char *s1 = "abbaababbaab", *s2 = "abab";
	KMP(s1, 12, s2, 4);
}

