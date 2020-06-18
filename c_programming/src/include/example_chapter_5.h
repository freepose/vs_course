
#include <stdio.h>
#include <math.h>

#include "example_chapter_4.h"

double cylinder(int r, int h) // r, h -> ÐÎ²Î
{
	double pi = 3.141592653;
	return pi * r * r * h;
}


int is_even(int n)
{
	return n % 2 == 0;
}

int even_sum()
{
	int i, sum = 0;
	for (i = 1; i <= 100; i++)
	{
		if (is_even(i))
		{
			sum += i;
		}
	}
	printf("%d", sum);
	return sum;
}

double estimate_pi(double accuracy)
{
	int i = 1, sign = 1;
	double item = .0, pi = .0;
	item = 1.0 / (2.0 * i - 1);
	
	while (item > accuracy)
	{
		item = 1.0 / (2.0 * i - 1);
		pi += (sign * item);
		sign = -sign;
		i++;
	}
	return pi * 4;	
}

void prime_under(int n)
{
	int i, counter = 0;
	for (i = 2; i <= n; i++)
	{
		if (is_prime(i))
		{
			printf("%6d", i);
			counter++;
			if (counter % 10 == 0)
			{
				printf("\n");
			}
		}
	}
}


// loops in loops
// Example 5-5
void print_pymarid(int n)
{
	int i, j, k;
	for (i = 1; i <= n; i++)
	{
		// spaces
		for (k = 1; k <= n - i; k++)
		{
			printf(" ");
		}
		// stars
		for (j = 1; j <= i; j++)
		{
			printf("%2d", i);
		}
		printf("\n");
	}
	return ;
}

int fact_s(int n)
{
	// sum of factorials
	// 1! + 2! + ... + n!
	static int f = 1;
	f *= n;
	return f;
}

void dectobin(int n)
{
	int i, k = 1, result = 0;
	while (n)
	{

		i = n % 2;
		result += k*i;
		k *= 10;
		n /= 2;
	}
	printf("%d", result);
}

void dectobin_v2(int n)
{
	int weight = 1, sum = 0;
	do
	{
		// printf("%d", n % 2);
		sum += weight * (n % 2);
		weight *= 10;
		n /= 2;
	} while (n > 0);

	printf("%d", sum);
}

void dectoct(int n)
{
	if (n > 0)
	{
		dectobin(n / 8);
		printf("%d", n % 8);
	}
}