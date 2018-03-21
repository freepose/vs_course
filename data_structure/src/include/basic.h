#ifndef BASIC_H
#define BASIC_H 1

#include<iostream>
using namespace std;




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

//void bubble_sort_array(int a[], int n)
//{
//
//}


#endif