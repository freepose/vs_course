#pragma once
#include<stdio.h>
#include<math.h>

void say_hello()
{
	printf("hello from example_chapter_3.h\n");
}


// Example 3-1
void guess_number()
{
	int  mynumber = 38;
	int  yournumber;
	printf("Input your number: ");
	scanf("%d", &yournumber);
	if (yournumber == mynumber) {
		printf("Ok! you are right!\n");
	}
	else {
		if (yournumber > mynumber) {
			printf("Sorry! your number is bigger than my number!\n");
		}
		else {
			printf("Sorry! your number is smaller than my number!\n");
		}
	}
}

// example 3-1 changed
void guess_number_v2()
{
	int  mynumber = 38;
	int  yournumber;
	printf("Input your number: ");
	scanf("%d", &yournumber);
	if (yournumber == mynumber) {
		printf("Ok! you are right!\n");
	}
	else if (yournumber > mynumber) {
		printf("Sorry! your number is bigger than my number!\n");
	}
	else {
		printf("Sorry! your number is smaller than my number!\n");
	}
}

void water_charge()
{
	double x = 200;
	double charge = 0.0;
	printf("Input water (t): ");
	scanf("%lf", &x);
	if (x < 0) 
	{
		charge = 0;
	}
	else if (x <= 15)
	{
		charge = 4.0 * x / 3;
	}
	else 
	{
		charge = 2.5 * x - 10.5;
	}
	printf("%.2f\n", charge);
}

// example 3-2
void odd_or_even()
{
	int number = 0;
	scanf("%d", &number);
	if (number % 2 == 0)
	{
		printf("even\n");
	}
	else
	{
		printf("odd\n");
	}
}

// example 3-5
void operations()
{
	float a = .0, b = .0, result = .0;
	char op;	// 字符类型
	scanf("%f%c%f", &a, &op, &b);
	
	if (op == '+')
	{
		result = a + b;
	}
	else if (op == '-')
	{
		result = a - b;
	}
	else if (op == '*')
	{
		result = a * b;
	}
	else if (op == '/')
	{
		if (b != 0) {
			result = a / b;
		}
		else
		{
			printf("division 0 error!\n");
		}
	}
	printf("%.2f%c%.2f=%.2f\n", a, op, b, result);
}

// example 3-5 (changed)
void operations_switch()
{
	float a = .0, b = .0, result = .0;
	char op;	// 字符类型
	scanf("%f%c%f", &a, &op, &b);

	switch (op)
	{
	case'+': result = a + b; break;
	case'-': result = a - b; break;
	case'*': result = a * b; break;
	case'/': 
		if (b != 0) 
		{ 
			result = a / b; 
		}
		else
		{
			printf("division 0 error!\n");
		}
		break;
	default: break;
	}
	printf("%.2f%c%.2f=%.2f\n", a, op, b, result);
}


// exercise
void check_triangle()
{
	double a = 3, b = 3, c;

	c = 3 * sqrt(2.0);
	// scanf("%lf %lf %lf", &a, &b, &c);
	if ((a + b > c) && (b + c > a) && (a + c > b))	// add operation of conditions
	{
		// this is triangle
		if ((a == b) && (b == c)) // for easy reading
		{
			printf("Equilateral triangle\n");
		}
		else if ( ((a == b) || (b == c) || (a == c)) // bug
			&& ((a*a + b*b == c*c) || (a*a == b*b + c*c) || (a*a + c*c == b*b)))
		{
			printf("right angled isosceles triangle\n");
		}
		else if (((a == b) || (b == c) || (a == c)))
		{
			printf("isosceles triangle\n");
		}
		else if ((a*a + b*b == c*c) || (a*a == b*b + c*c) || (a*a + c*c == b*b))
		{
			printf("right triangle\n");
		}
	}
	else
	{
		printf("Not a triangle.\n");
	}
}

//
void logic_operation()
{
	int x = 2;
	if (!(x > 1))	//
	{
		printf("!(x > 1)");
	}
	else //default as x > 1
	{
		printf("(x > 1)");
	}
}

// Example 3-7
void character_counter()
{
	// test case: as123sd+-3
	char ch = '0';
	int n = 10, i;
	int character_counter = 0, number_counter = 0, others=0;

	// 循环读入10个数
	for (i = 0; i < n; i++)
	{
		// loop body
		ch = getchar();
		// 判断一个字符是数字还是字母？
		if ((ch >= 'A' && ch <= 'Z') || // is alphabet
			(ch >= 'a' && ch <= 'z'))
		{
			character_counter++;
		}
		else if (ch >= '0' && ch <= '9') // is number
		{
			
			number_counter++;
		}
		else // is others
		{	
			others++;
		}
	}
	printf("#characters: %d\n#numbers: %d\n#others: %d\n", 
		character_counter, number_counter, others);
}