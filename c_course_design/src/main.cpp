#define _CRT_SECURE_NO_WARNINGS 1

//#include"include\contact.h"
//
//// https://blog.csdn.net/QiHsMing/article/details/102688106
//
//int main()
//{
//	Filename files;
//	initial_filename(&files);
//	StudentArray* list = read_students(files.source_contact_file);
//
//	sort_student_by_number(list);
//	printf("#(students) = %d\n", list->num_student);
//	print_students(list);
//
//	write_student(list, files.target_contact_file);
//
//	return 0;
//}
#include <stdio.h>
#include <stdlib.h>
//以某指针作为一连串struct 型空间的起始地址，p=(io*)malloc(sizeof(io)*n);

typedef struct {
	char name[10];
	int bir;
	char tel[20];
} io;
int main()
{
	int n, i, j;
	scanf("%d", &n);
	io *p, tmp;
	// p = (io*)malloc(sizeof(io)*n);
	//
	p = new io[n];

	for (i = 0; i<n; i++)
	{
		scanf("%s %d %s", p[i].name, &p[i].bir, p[i].tel);
	}
	for (i = 0; i<n - 1; i++)
	{
		for (j = 0; j<n - 1 - i; j++)
		{
			if (p[j].bir>p[j + 1].bir)
			{
				tmp = p[j + 1];
				p[j + 1] = p[j];
				p[j] = tmp;
			}
		}
	}
	for (i = 0; i<n; i++)
	{
		printf("%s %d %s\n", p[i].name, p[i].bir, p[i].tel);
	}
	return 0;
}