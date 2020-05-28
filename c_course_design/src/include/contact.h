#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>
// windows (default): D:\\study\\teaching\\2020春 C语言-理学院19级\\contacts.csv
// macos or linux: "D:/study/teaching/2020春 C语言-理学院19级/contacts.csv"
// 字段："学号,姓名,性别,联系电话,邮箱（必填）,QQ号,微信号,家庭住址,"


typedef struct {
	char number[12 + 1];
	char name[6 * 2 + 1];
	char phone[20 + 1];
	char email[20 + 1];
	char qq_id[20 + 1];
	char wechat_id[20 + 1];
	char address[200];
} Student;

typedef struct
{
	Student students[100];
	int num_student;
} StudentArray;

typedef struct
{
	char source_contact_file[200];
	char target_contact_file[200];
} Filename;


void initial_filename(Filename *p)
{
	char source_file[] = "D:/study/teaching/2020春 C语言-理学院19级/contacts.csv";
	char target_file[] = "D:/study/teaching/2020春 C语言-理学院19级/target.csv";
	strcpy(p->source_contact_file, source_file);
	strcpy(p->target_contact_file, target_file);
}

StudentArray* read_students(char *filename)
{
	FILE *fp = 0;
	if ((fp = fopen(filename, "r")) == 0)
	{
		printf("file not found: %s\n", filename);
		return 0;
	}

	StudentArray *pArray = new StudentArray;
	memset(pArray, 0, sizeof(StudentArray));

	int counter = 0;
	char buffer[1024] = {0};
	fgets(buffer, 1024, fp);	// skip first line

	while (!feof(fp))
	{
		// read lines and parse
		Student *pStudent = pArray->students + counter;

		fscanf(fp, "%s,%s,%s,%s,%s,%s,%s,", pStudent->number, 
			pStudent->name, pStudent->phone, pStudent->email, 
			pStudent->qq_id, pStudent->wechat_id, pStudent->address);

		counter++;
	}
	pArray->num_student = counter;

	return pArray;
}

void print_students(StudentArray* pArray)
{
	if (pArray->num_student <= 0)
	{
		printf("No student information.\n");
		return;
	}
	for (int i = 0; i < pArray->num_student; i++)
	{
		Student *pStudent = pArray->students + i;
		printf("%s,%s,%s,%s,%s,%s,%s\n", pStudent->number,
			pStudent->name, pStudent->phone, pStudent->email,
			pStudent->qq_id, pStudent->wechat_id, pStudent->address);
	}
}