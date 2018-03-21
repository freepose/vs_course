#ifndef BASIC_H
#define BASIC_H 1

#include<iostream>
using namespace std;


void swap(int &f, int &s)
{
	int t = f;
	f = s;
	s = t;
}


void read_array(int a[], int n)
{
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
}

void print_array(int a[], int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<"\t"<<a[i];
	}
	cout<<endl;
}

void select_sort_array(int a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i+1; j < n;j++)
		{
			if (a[i] > a[j])
			{
				swap(a[i], a[j]);
			}
		}
	}

}


#endif