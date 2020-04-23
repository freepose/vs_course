#pragma once


#include<stdio.h>

void main_example()
{
	int n = 123, a, b;
	printf("%d\n", +n);
	printf("%d\n", -n);

	// n++是先使用n的数值再自加一; ++n是先自加一再使用n累加后的数值
	printf("%d\n", n++);	// 123
	printf("%d\n", ++n);	// 125, n = n+1; n+=1; n++; ++n;

							// n = 125，printf() 执行的时候从右边执行，显示的时候从左边开始：编译器决定
	printf("%d %d\n", n++, ++n);	// 左边到右边：125, 127。右边到左边：126 126

									// n = 127
	printf("%d %d\n", ++n, n++);	// 129, 127

									// n = 129
	printf("%d\n", n--);	// 129
	printf("%d\n", --n);	// 127

							// n = 127
	printf("%d %d\n", n--, --n);


	n = 100;
	n = n << 1;	// 二进制左移，因为计算机存的都是二进制。等价于： n <<= 1;
	printf("%d\n", n);

	n = n >> 2;		// n >>= 2;
	printf("%d\n", n);

	a = 10;	// 1010
	b = 5;	// 0101

	n = a & b;	// 0000
	printf("%d\n", n);

	n = a | b;	// 1111
	printf("%d\n", n);

	a = 9;	// 1001
	b = 3;	// 0011

	n = a & b;	// 0001, 1
	printf("%d\n", n);

	n = a | b;	// 1011, 11
	printf("%d\n", n);

	n = a | b;	// 1011
	printf("%d\n", ~n);

	// ?:
	printf("%d\n", 3 > 2 ? 3 : 2);
}

// why characters are numbers?
// what characters are?
void show_characters()
{
	int i;
	for (i = 'A'; i <= 'Z'; i++)
	{
		printf("%c -> %d\n", i, i);
	}

	for (i = 'a'; i <= 'z'; i++)
	{
		printf("%c -> %d\n", i, i);
	}

	for (i = 91; i <= 96; i++)
	{
		printf("%c -> %d\n", i, i);
	}

	for (i = ' '; i <= ' '; i++)
	{
		printf("%c -> %d\n", i, i);
	}
}