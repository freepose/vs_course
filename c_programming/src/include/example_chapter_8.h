#pragma once

#include<stdio.h>

void pointer_as_variable()
{
	int n, n2;
	int *p = 0;
	p = &n2;
	scanf("%d", p); // store a number by its pointer?
	printf("%d\n", *p);
	printf("%p\n", p);
	(*p) += 1;	// n2 += 1;
	printf("%d\n", n2);
}

void swap0(int f, int s)
{
	int t = f;
	f = s;
	s = t;
}

//void swap2(int &f, int &s)
//{
//	int t = f;
//	f = s;
//	s = t;
//}

// 交换两个指针指向的变量
void swap1(int *f, int *s)
{
	int t = *f;
	*f = *s;
	*s = t;
}

// 交换两个指针
void swap1_0(int *f, int *s)
{
	int* t = f;
	f = s;
	s = t;
}


// Example 8-4，如何通过指针返回多个值（函数参数）
void get_month_day(int year, int day_of_year, int *month, int *day)
{
	// input: year, day_of_year 
	// output: year-month-day
	int tab[2][13] = {
		{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
		{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } };

	int i, run_nian = 0;

	run_nian = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);

	for (i = 1; day_of_year > tab[run_nian][i]; i++)
	{
		day_of_year -= tab[run_nian][i];
	}
	*month = i;
	*day = day_of_year;

	// printf("%d-%d-%d", year, i, day);
}


void bubble_sort(int *a, int n)
{
	int i, j, t;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
	}
}

void bubble_sort_desc(int *a, int n)
{
	int i, j, t;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (a[j] < a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
	}
}

int sum_of_array(int *a, int n)
{
	int i = 0, sum = 0;
	for (i = 0; i < n; i++)
	{
		sum += a[i];
	}
	return sum;
}

int sum_of_array_using_pointer(int *start, int *end)
{
	int *p = 0, sum = 0;
	for (p = start; p <= end; p += 1)
	{
		sum += (*p);
	}
	return sum;
}

// Example 8-6
void pointer_array_test()
{
	int a[2] = {12, 10}, *p, *q;
	p = &a[0];
	q = p + 1;	// q = &a[1]

	printf("p -> %p\nq -> %p\n", p, q);

	printf("%d variable(s).\n", q - p);
	printf("%d bytes\n", (int)q - (int)p);
	printf("%d %d\n", *p, *q);
}