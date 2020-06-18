#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>

// Example 7-1: input 10 heights of students, output heights larger than averge.
// 0. store heights 1. average. 2. compare and output
void output_average()
{
	int h[10] = { 55, 23, 8, 11, 22, 89, 0, -1, 78, 186 };
	//int h[10] = { 55, 23, 8 };
	int i, sum = 0;
	double average = 0.0;

	//for (i = 0; i < 10; i++)
	//{
	//	scanf("%d", &h[i]);
	//}

	for (i = 0; i < 10; i++)
	{
		sum += h[i];
	}
	average = sum * 1.0 / 10;

	for (i = 0; i < 10; i++)
	{
		if (h[i] >= average)	// conditional output
		{
			printf("%d ", h[i]);
		}
	}
}

// Example 7-2
void fibonacci_array()
{
	int i;
	double a[100] = { 1, 1 };

	for (i = 2; i < 100; i++)
	{
		a[i] = a[i - 1] + a[i - 2];
	}

	// 
	for (i = 0; i < 100; i++)
	{
		printf("%p: fib[%d] -> %.0lf\n", &a[i], i, a[i]);
	}
}

// Example 7-2: 2 9 8 1 9
void find_array()
{
	int i;
	int x = 9;
	int a[5] = { 0 };

	for (i = 0; i < 5; i++)
	{
		scanf("%d", &a[i]);	// 存一个数据到变量，就是存数据到内存中
	}

	for (i = 0; i < 5; i++)
	{
		printf("%d ", a[i]);	// 存一个数据到变量，就是存数据到内存中
	}

	// sequential access
	for (i = 4; i >= 0; i--)
	{
		if (a[i] == x)
		{
			break;
		}
	}

	// i is find, if i is not equal to 4
	printf("\n%d at a[%d]", x, i);
}

// pass an array to a function.
// Find the target x and return its index.
int find(int a[], int n, int x)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (a[i] == x)
		{
			break;
		}
	}
	return i < n ? i : -1;
}

// find index of the max value
int max_index(int a[], int n)
{
	int i = 0;
	int max_index = 0;
	int max_value = a[max_index];

	for (i = 1; i < n; i++)
	{
		if (max_value < a[i])
		{
			max_value = a[i];
			max_index = i;
		}
	}
	return max_index;
}

int min_index(int a[], int n)
{
	int i = 0;
	int index = 0;
	int min = a[index];

	for (i = 1; i < n; i++)
	{
		if (min > a[i])
		{
			min = a[i];
			index = i;
		}
	}
	return index;
}

void swap(int *a, int *b)
{
	int c;
	c = *a;
	*a = *b;
	*b = c;
}

void select_sort(int a[], int n)
{
	int i; // 当前第i个数最小
	int j;	// 当前最大的数，需要进行交换的数

	for (i = 0; i < n - 1; i++)
	{
		int index = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[index] > a[j])
			{
				index = j;
			}
		}
		if (index > i)	//
		{
			swap(&a[i], &a[index]);
		}
	}
}

void print_array(int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void yanghui_sanjiaoxing()
{
	int i, j, k;
	int N = 10;

	int a[100][100] = { 0 }; // 辅助存储
	a[0][1] = 1;

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N - i + 1; j++)
		{
			printf(" ");
		}
		for (k = 1; k <= i; k++)
		{
			a[i][k] = a[i - 1][k - 1] + a[i - 1][k];
			printf("%4d", a[i][k]);
		}
		printf("\n");
	}
}

void joseph_loop()
{
	int N = 200;
	int m = 5;

	int a[100000] = { 0 };
	int i = 0, j;
	int start = 1, end = 0;

	// 循环结束条件是end-start = 1
	for (i = 1; i <= N; i++) { a[i] = i; }
	end = N + 1;
	i = 1;
	while (end - start > 1)
	{
		if (i % m == 0)
		{
			// 该出去
			for (j = start; j < start + m - 1; j++)
			{
				a[end] = a[j];
				end++;
			}
			start += m; // 扔掉前面m个数
			// printf("%4d", a[start - 1]);
			i = 1;
		}
		i++;
	}
	printf("%d", a[start]);
}

// Example 7-6：如何在一个排序好的数组中高效率的查找一个数
int binary_search(int sorted_a[], int n, int x)
{
	int low = 0, high = n - 1;
	int mid = (low + high) / 2;

	while (low <= high)
	{
		if (sorted_a[mid] > x)
		{
			high = mid - 1;
		}
		else if (sorted_a[mid] < x)
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
		mid = (low + high) / 2;
	}

	return -1;
}


// Example 7-7
void array2d_find_max()
{
	int a[2][3] = { { 55, 23, 8 }, { 11, 22, 89 } };
	int i, j;
	int row = 0, col = 0;
	int a_t[3][2];

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("%4d", a[i][j]);
		}
		printf("%c", '\n');
	}

	// sequential pass 小标标记法
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (a[i][j] > a[row][col])
			{
				row = i;
				col = j;
			}
		}
	}
	printf("max is a[%d][%d] = %d\n", row, col, a[row][col]);

	// transpose
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			a_t[j][i] = a[i][j];
		}
	}

	// 
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 2; j++)
		{
			printf("%4d", a_t[i][j]);
		}
		printf("%c", '\n');
	}
}

void day_of_year(int year, int month, int day)
{
	int tab[2][13] = {
		{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
		{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } };

	int i, sum = 0, run_nian = 0;

	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		run_nian = 1;
	}

	for (i = 1; i < month; i++)
	{
		sum += tab[run_nian][i];
	}
	sum += day;
	printf("%d-%d-%d: %d-th day in this year.\n", year, month, day, sum);
}

// 
void char_array()
{
	char t[5] = { 'H', 'a', 'p', 'p', 'y' };
	char s[6] = { 'H', 'a', 'p', 'p', 'y', 0};
	char s2[6] = { 'H', 'o', 'o', 'd', '!', 0 };

	char buffer[20] = {0};
	char buffer2[20] = { 0 };

	unsigned int i;

	printf("%s\n", t);
	printf("%s\n", s);

	// s -> buffer
	for (i = 0; i < strlen(s); i++)	// string.h
	{
		buffer[i] = s[i];
	}
	buffer[i] = 0; //
	printf("%s\n", buffer);

	// strcpy(buffer2, s);
	memcpy(buffer2, s, sizeof(char) * strlen(s) + 1);
	printf("%s\n", buffer2);

	// compare
	printf("%d", strcmp(s, s2));
}

// 字符串和字符数组的区别。字符串数组和2维字符数组的区别。
// 指针数组：指针类型的数组
//char poetry[4][9 * 2 + 1] = { 0 }; // 等长
//char* poetry[4] = {"", "", "", ""}; // 等长

