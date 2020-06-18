
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

void pointer_as_variable()
{
	int n2;
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

void show_sizeof_pointers()
{
	char *p1 = 0; // sizeof(p1)
	int *p2 = 0;
	double *p3 = 0;
	long *p4 = 0;
	char **p5 = 0;

	printf("%d\n", sizeof(p1));
	printf("%d\n", sizeof(p2));
	printf("%d\n", sizeof(p3));
	printf("%d\n", sizeof(p4));
	printf("%d\n", sizeof(p5));
}

// using a pointer to access an array
void pointer_to_arrary(int *arr, int n)
{
	int a[10] = { 0 };
	int *p = 0;	// pointer to a integer variable

	p = &n;	// note
	p = &a[2];
}

void print_char_array(char *s, int n)
{
	int i = 0;
	for (i = 0 ; i < n; i++)
	{
		printf("%c", s[i]);
	}
}

void initialize_2d_array(int **a, int m, int n)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			a[i][j] = 0;
		}
	}
}

void free_2d_array(int **p, int m, int n)
{
	int i;
	for (i = 0; i < m; i++)
	{
		free(p[i]);
	}
	free(p);
	// p = 0;
}


// 如何去传递一个二维数组到函数：不可以用二级指针来串数二维数组
// void print_2d_array(int a[][3], int m, int n)	// 可以用二维数组变量传递，指定低维长度
// void print_2d_array(int (*a)[3], int m, int n)		// 可以用数组指针来传递，指定低维长度
void print_2d_array(int **a, int m, int n)
{
	// s
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n;j++)
		{
			printf("%4d", a[i][j]);
		}
		printf("\n");
	}
}


// dynamic allocation example
void dynamic_allocation_example()
{
	int *a = 0;
	int size = 1024 * 1024;	// 系统无法一次性各一个程序开辟1G * 4B的空间

	a = (int *)malloc(sizeof(int) * size);
	memset(a, 0, sizeof(int) * size);

	print_array(a, size);

	// free memory
	free(a);
	a = 0;
}

// 内存模型：它的内存长什么样子
void dynamic_allocation_2d_array_example()
{
	int m = 1024 * 10;
	int n = 1024;

	int **p = 0;	// 二级指针：指向指针的指针
	int i = 0;

	p = (int **)malloc(sizeof(int *) * m);
	for (i = 0; i < m; i++)
	{
		p[i] = (int *)malloc(sizeof(int) * n);
	}

	initialize_2d_array(p, m, n);
	p[0][0] = 55;
	p[0][1] = 23;
	p[0][2] = 8;
	p[1][0] = 11;
	p[1][1] = 22;
	p[1][2] = 89;
	print_2d_array(p, m, n);
	free_2d_array(p, m, n);
	p = 0;
}
