#pragma once

#include<stdio.h>
#include<math.h>


// Example 4-1
// 使用格雷戈里公式求π的近似值（while）
// + 输出：π的近似值且精确到最后一项的绝对值小于10^–4 。

void pi_estimate()
{
	double n = 1;	
	double sum = 0.0;
	double sign = 1.0;

	while (fabs(1.0 / (2 * n - 1)) > 10e-9)
	{
		sum += sign / (2.0 * n - 1);
		sign = -sign;
		n = n + 1.0;
	}
	printf("%lf", sum * 4.0);
}

void sum(int n)
{
	// given n > 0
	// sum of 1 -> n
	int i = 1, sum = 0;
	while (i <= n)
	{
		sum += i;
		i++;
	}
	printf("%d", sum);
}

void sum_for(int n)
{
	int i, sum = 0;
	for (i = 1; i <= n; i++)
	{
		sum += i;
	}
	printf("%d", sum);
}

// example 4, fact
int fact(int n)
{
	int i = 2, _fact = 1;

	for (; i <= n; i++)
	{
		_fact *= i;
	}
	return _fact;
}

// Example 4-2
// sum for scores
void sum_for_scores()
{
	double score = 0.0;	// note
	double sum = 0.0, average = 0.0;
	int counter = 0, fail_counter = 0;

	scanf("%lf", &score);
	while (score != -1)
	{
		sum += score;
		counter++;
		scanf("%lf", &score);
		if (score < 60)
		{
			fail_counter++;
		}
	}
	
	if (counter > 1)
	{
		average = sum / counter;
	}
	printf("%d students -> average, %lf, %d fails.\n", counter, average, fail_counter);
}

// Example 4-3, 改进版

void decompose_v0()
{
	int read = 0, n;
	int weight = 1, i;
	scanf("%d", &read);
	n = read;
	// 辗转求余
	do {
		printf("%d\t", read % 10);
		read /= 10;
		weight *= 10;
	} while (read > 0);
	weight /= 10;

	for (i = weight; i > 0; i /= 10)
	{
		printf("\n%d\t", n / i); // 2
		n = n - (n / i) * i;
	}
}

void decompose(int n)
{
	if (n > 0)
	{
		decompose(n / 10);
		printf("%d\t", n % 10);
	}
}

// Example 4-4
int is_prime(int n)
{
	int i;
	if (n < 2)	// note
	{
		return 0;
	}
	if (n == 2 || n == 3)
	{
		return 1;
	}
	for (i = 2; i < n; i++)	
	{
		if (n % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

// Example 4-5
void max_score()
{
	double score = 0.0;	// note
	double sum = 0.0;
	double max = -2, min = 1000;
	
	scanf("%lf", &score);
	while (score != -1)
	{
		if (max < score)
		{
			max = score;
		}
		if (min > score)
		{
			min = score;
		}
		scanf("%lf", &score);
	}
	printf("max is %lf, min is %lf\n", max, min);
}

// Example 4-7
void sum_of_factorials(int n)
{
	int i, j;
	double sum = 1.0, fact;
	for (i = 2; i <= n; i++)
	{
		fact = 1.0;	// reset fact value
		for (j = 2; j <= i; j++)
		{
			fact *= j;
		}
		sum += fact;
	}
	printf("%.0lf\n", sum);
}

void sum_of_factorials_v1(int n)
{
	int i;
	long double sum = 1.0, fact = 1.0;

	for (i = 2; i <= n; i++)
	{
		fact *= i;
		sum += fact;
	}
	printf("%.0lf\n", sum);
}

// static version

// Example 4-11, Fibonacci -> 澳大利亚的兔子

void fibonacci(int n)
{
	int i;
	double a = 1;
	double b = 1;
	double c;

	printf("%0.lf\t%0.lf\t", a, b);
	for (i = 3; i <= n; i++)
	{
		c = a + b;
		printf("%0.lf\t", c);
		a = b;
		b = c;
	}
}

void data_types()
{
	int a = '0';	// 字符转数字
	double f = 250.250;
	printf("char: %c -> int: %d\n", a, a);
	printf("double: %lf -> int: %d\n", f, (int)f);
	printf("int: %d -> double: %lf\n", a, a * 1.0);
}

// conditions for while
void while_test()
{
	int a = 5;
	int b = 2;

	// 1 && 1 

	if (a > b && a > 0)
	{
		a--;
		printf("%d\n", a);
	}
	printf("===============\n");
	while (a > b && a > 0)
	{
		a--;
		printf("%d\n", a);
	}

}

// loops in loops
void print_stars(int n)
{
	int i, j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= i; j++)
		{
			printf("*");
		}
		printf("\n");
	}
}

void print_mulitiplication(int n)
{
	int i, j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= i; j++)
		{
			printf("%d*%d=%-3d", i, j, i*j);
		}
		printf("\n");
	}
}

void print_daosanjiao(int n)
{
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			printf(" ");
		}
		for (k = 0; k <= i; k++)
		{
			printf("*");
		}
		printf("\n");
	}
}

void print_deyaosanjiao(int n)
{
	int i, j, k;
	int mid;
	mid = n / 2 + 1;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= abs(i - mid); j++)
		{
			printf(" ");
		}
		
		for (k = 1; k <= (mid - abs(i - mid)) * 2 - 1; k++)
		{
			printf("%d", i);
		}
		printf("\n");
	}
}