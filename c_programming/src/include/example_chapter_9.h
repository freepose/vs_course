#pragma once

#include<string.h>
#include<memory.h>

// typedef类型重定义
typedef struct  {
	char name[10 * 2];
	char number[10];
	char gender;	// {'M', 'F'}
	char address[256];
	
	// POI
	double longitude;
	double latitude;

	char bank_number[20];	
	char bank_number_bak[20];
} Student;

void initialize_students(Student* students, int n)
{
	int i = 0;
	students = (Student*)malloc(sizeof(Student) * n);
	for (i = 0; i < n; i++)
	{
		memset(&students[i], 0, sizeof(Student));
	}

	// 如何给结构体赋初值
	strcpy(students[0].name, "first");
	strcpy(students[0].number, "2019710001");

	// 结构体变量如何调用


	printf("%s\t%s\n", students[0].name, students[0].number);
}