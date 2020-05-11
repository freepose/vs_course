#pragma once

#include<string.h>
#include<memory.h>

// typedef类型重定义
typedef struct  {
	// basic information
	char number[13];		// e.g., 201921145022
	char name[4 * 2 + 2];	// 最长4个汉字
	char gender[2 * 1 + 2];	// {'男', '女'}

	// address
	struct
	{
		double longitude;	// 
		double latitude;	// 
		char detail[256];	// 福建省莆田市
	} address;

	

} Student;	// 最简设计：方便以后增加成员变量，不需要随便修改以前的函数


void read_student(Student *p)
{
	printf("请输入学号：");
	scanf("%s", p->number);
	printf("请输入姓名：");
	scanf("%s", p->name);
	printf("请输入性别：");
	scanf("%s", p->gender);

	// TODO
}

void print_student(Student *p)
{
	printf("%s\t%s\t%s\n", p->number, p->name, p->gender);
}

// 从很多个学生里面查找一个学生
// 从数组里面找到一个目标变量
Student * find_student(Student *p, int n, char *target_number)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (strcmp(p[i].number, target_number) == 0)	// 如何比较字符串
		{
			print_student(&p[i]);
			return &p[i];
		}
	}
	printf("未找到学号：%s\n", target_number);
	return 0;
}

void update_student(Student *p)
{
	printf("请输入待修改的姓名：");
	scanf("%s", p->name);
}

void delete_student(Student *p, int n, char *number)
{

}

void show_tips()
{
	printf("1. 输入若干个学生信息\n");
	printf("2. 显示若干个学生信息\n");
	printf("3. 按学号查找并显示学生信息\n");
	printf("4. 插入一个学生信息\n");
	printf("0. 退出程序\n");
}

void menu(int sel)
{
	int n, i;
	Student students[200], *p = 0;
	char target_name[13] = {0};

	switch (sel)
	{
	case 1:
		printf("待输入的学生个数: ");
		scanf("%d", &n);
		for (i = 0; i < n; i++)
		{
			read_student(&students[i]);
		}
		break;
	case 2:
		// display all
		for (i = 0; i < n; i++)
		{
			print_student(&students[i]);
		}
		break;
	case 3:
		printf("待查找学号: ");
		scanf("%s", target_name);
		p = find_student(students, n, target_name);
		break;

	default:
		break;
	}

}