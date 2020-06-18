
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

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
		char detail[256];	//
	} address;

	// score

	// friendships

	// neighbors

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
// 找到返回指针，补不到则返回0
Student * find_student(Student *p, int n, char *target_number)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (strcmp(p[i].number, target_number) == 0)	// 如何比较字符串
		{
			// print_student(&p[i]);
			return &p[i];
		}
	}
	return 0;
}

void update_student(Student *p)
{
	printf("rename %s to ", p->name);
	scanf("%s", p->name);
	printf("revise gender '%s' to ", p->gender);
	scanf("%s", p->gender);
}

void sort_sutdent_by_number(Student *students, int n)
{
	int i; // 当前第i个数最小
	int j;	// 当前最大的数，需要进行交换的数
	Student temp;

	for (i = 0; i < n - 1; i++)
	{
		int index = i;
		for (j = i + 1; j < n; j++)
		{
			if (strcmp(students[index].number, students[j].number) > 0)
			{
				index = j;
			}
		}
		if (index > i)	//
		{
			temp = students[i];
			students[i] = students[index];
			students[index] = temp;
		}
	}
}

void sort_sutdent_by_name(Student *students, int n)
{
	int i; // 当前第i个数最小
	int j;	// 当前最大的数，需要进行交换的数
	Student temp;

	for (i = 0; i < n - 1; i++)
	{
		int index = i;
		for (j = i + 1; j < n; j++)
		{
			if (strcmp(students[index].name, students[j].name) > 0)
			{
				index = j;
			}
		}
		if (index > i)	//
		{
			temp = students[i];
			students[i] = students[index];
			students[index] = temp;
		}
	}
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
	printf("5. 按学号更新指定学生信息\n");
	printf("6. 按学号排序所有学生信息\n");
	printf("7. 按姓名排序所有学生信息\n");
	printf("0. 退出程序\n");
	printf("input your choice: ");
}

void menu(Student *students, int *p_n, int choice)
{
	int i;
	Student *p = 0;
	char target_number[13] = {0};

	switch (choice)
	{
	case 1:
		printf("input the number of students (n): ");
		scanf("%d", p_n);
		for (i = 0; i < *p_n; i++)
		{
			read_student(&students[i]);
		}
		break;
	case 2:
		for (i = 0; i < *p_n; i++)
		{
			print_student(&students[i]);
		}
		if (*p_n == 0)
		{
			printf("no student records.\n");
		}
		break;
	case 3:
		printf("input student number (no.): ");
		scanf("%s", target_number);
		p = find_student(students, *p_n, target_number);	// the simplest design
		if (p != 0)
		{
			print_student(p);
		}
		else
		{
			printf("can't find student with number %s.\n", target_number);
		}
		break;
	case 4:
		read_student(&students[*p_n]);
		*p_n += 1;
		break;
	case 5:
		printf("input student number (no.): ");
		scanf("%s", target_number);
		p = find_student(students, *p_n, target_number);
		if (p != 0)
		{
			update_student(p);
		}
		else
		{
			printf("can't find student with number %s.\n", target_number);
		}
		break;
	case 6:
		sort_sutdent_by_number(students, *p_n);
		for (i = 0; i < *p_n; i++)
		{
			print_student(&students[i]);
		}
		break;
	case 7:
		sort_sutdent_by_name(students, *p_n);
		for (i = 0; i < *p_n; i++)
		{
			print_student(&students[i]);
		}
		break;
	default:
		break;
	}

}