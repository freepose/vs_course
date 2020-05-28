#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Example 11-1：指针数组
void Olympic_rings()
{
	char* rings[5] = {"blue", "yellow", "black", "green", "red"};
	int i, n = 5;

	char buffer[256] = {0};

	for (i = 0; i < n; i++)
	{
		printf("%s\n", rings[i]);
	}

	scanf("%s", buffer);
	for (i = 0; i < n; i++)
	{
		if (strcmp(buffer, rings[i]) == 0)
		{
			printf("found at %d\n", i + 1);
			break;	// note
		}
	}

	if (i == n)
	{
		printf("Not found\n");
	}
}


// 使用数组类型的指针或二级指针来访问字符指针数组
void Olympic_rings_v2()
{
	char* rings[5] = { "blue", "yellow", "black", "green", "red" };
	int i, n = 5;

	char buffer[256] = { 0 };
	char **p;

	p = rings;

	for (i = 0; i < n; i++)
	{
		printf("%s\n", rings[i]);
	}

	scanf("%s", buffer);
	for (i = 0; i < n; i++)
	{
		if (strcmp(buffer, *(p + i)) == 0)
		{
			printf("found at %d\n", i + 1);
			break;	// note
		}
	}

	if (i == n)
	{
		printf("Not found\n");
	}
}

// 二维数组存储多个字符串
void Olympic_rings_v3()
{
	char rings[][7] = { "blue", "yellow", "black", "green", "red" };
	int i, n = 5;

	char buffer[256] = { 0 };
	//char **p;
	//p = rings;

	for (i = 0; i < n; i++)
	{
		printf("%s\n", rings[i]);
	}

	scanf("%s", buffer);
	for (i = 0; i < n; i++)
	{
		if (strcmp(buffer, rings[i]) == 0)
		{
			printf("found at %d\n", i + 1);
			break;	// note
		}
	}

	if (i == n)
	{
		printf("Not found\n");
	}
}

void sort_rings(char* rings[], int n)
{
	int i, j;
	char* temp;

	for (i = 0; i < n - 1; i++)
	{
		int index = i;
		for (j = i + 1; j < n; j++)
		{
			if (strcmp(rings[index], rings[j]) > 0)
			{
				index = j;
			}
		}
		if (index > i)	//
		{
			temp = rings[i];
			rings[i] = rings[index];
			rings[index] = temp;
		}
	}
}

void print_rings(char* rings[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%s\n", rings[i]);
	}
	printf("\n");
}

void sort_Olympic_rings_example()
{
	char* rings[5] = { "blue", "yellow", "black", "green", "red" };
	int n = 5;

	print_rings(rings, 5);
	sort_rings(rings, 5);
	print_rings(rings, 5);
}

// 解密藏头诗
void jiemi()
{
	char* poem[4] = {"一叶轻舟向东流", "帆梢轻握杨柳手", "风纤碧波微起舞", "顺水任从雅客悠"};
	int i, n = 4;
	print_rings(poem, 4);
	for (i = 0; i < n; i++)
	{
		char buffer[3] = {0};
		buffer[0] = poem[i][0];
		buffer[1] = poem[i][1];
		printf("%s", buffer);
	}

	// 有两个要注意的事项
	// 1. 中文占两个字符
	// 2. 字符不对齐会产生乱码

	// 这些会影响到字段设置和其他的
	// 还有另外一种做法是宽字符
}


// Example 11-6
void strings_reverse_output()
{
	int counter = 0, i;
	char buffer[256] = {0};
	char strings[500][256] = {0};

	do
	{
		gets(buffer);
		strcpy(strings[counter], buffer);
		counter++;
	} while (strcmp(buffer, "#") != 0);

	for (i = counter - 1 - 1; i >= 0; i--)
	{
		puts(strings[i]);
	}
}

// 指针函数 vs. 函数指针
// 函数指针：函数类型的指针

int func(int r, int h)
{
	return r + h;
}

int func_B(int r, int h)
{
	return r * h;
}

void print_func(int(*funptr)(int, int), int r, int h)
{
	printf("%d\n", funptr(r, h));
}

// 结构体指针

struct StudentLinkNode
{
	int data;	// 可以放更多数据
	
	struct StudentLinkNode *next;
};

struct StudentLinkNode *create_students()
{
	struct StudentLinkNode * head = 0, *tail = 0, *p = 0;
	int data;
	scanf("%d", &data);
	while (data != 0)
	{
		p = (struct StudentLinkNode *)malloc(sizeof(struct StudentLinkNode));
		p->data = data;
		p->next = 0;

		if (head == 0)
		{
			head = p;
		}
		else
		{
			tail->next = p;
		}
		tail = p;
		scanf("%d", &data);
	}
	return head;
}

void print_linked_students(struct StudentLinkNode *head)
{
	struct StudentLinkNode *p = head;
	while(p)
	{
		printf("%d -> ", p->data);
		p = p->next;
	}
}

struct StudentLinkNode * find_StudentLinkNode(struct StudentLinkNode *head, int target)
{
	struct StudentLinkNode *p = head;
	while (p)
	{
		if (p->data == target)
		{
			return p;
		}
		p = p->next;
	}
	return 0;
}

void add_StudentLinkNode(struct StudentLinkNode *tail, int data)
{
	// add to tail or add to head
}
