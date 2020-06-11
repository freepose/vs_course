#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>


// windows (default): D:\\study\\teaching\\2020春 C语言-理学院19级\\contacts.csv
// macos or linux: "D:/study/teaching/2020春 C语言-理学院19级/contacts.csv"
// 字段："学号,姓名,性别,联系电话,邮箱（必填）,QQ号,微信号,家庭住址,"


typedef struct {
	char number[20 + 1];
	char name[10 * 2 + 1];
	char gender[1 * 2 + 1];
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
	// char source_file[] = "D:/study/teaching/2020春 C语言-理学院19级/contacts.csv";
	char source_file[] = "D:/data/contacts.csv";
	char target_file[] = "D:/data/contacts.target.csv";
	strcpy(p->source_contact_file, source_file);
	strcpy(p->target_contact_file, target_file);
}

void split(char *src, const char *separator, char **dest, int *num) 
{
	/*
	src 源字符串的首地址(buf的地址)
	separator 指定的分割字符
	dest 接收子字符串的数组
	num 分割后子字符串的个数
	*/
	char *pNext;
	int count = 0;
	if (src == NULL || strlen(src) == 0) //如果传入的地址为空或长度为0，直接终止 
		return;
	if (separator == NULL || strlen(separator) == 0) //如未指定分割的字符串，直接终止 
		return;
	pNext = (char *)strtok(src, separator); //必须使用(char *)进行强制类型转换(虽然不写有的编译器中不会出现指针错误)
	while (pNext != NULL) {
		*dest++ = pNext;
		++count;
		pNext = (char *)strtok(NULL, separator);  //必须使用(char *)进行强制类型转换
	}
	*num = count;
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

		char *revbuf[9] = { 0 };
		int num = 0;
		fgets(buffer, 1024, fp);

		split(buffer, ",", revbuf, &num); //调用函数进行分割
		if (num == 9)
		{
			strcpy(pStudent->number, revbuf[0]);
			strcpy(pStudent->name, revbuf[1]);
			strcpy(pStudent->gender, revbuf[2]);
			strcpy(pStudent->phone, revbuf[3]);
			strcpy(pStudent->email, revbuf[4]);
			strcpy(pStudent->qq_id, revbuf[5]);
			strcpy(pStudent->wechat_id, revbuf[6]);
			strcpy(pStudent->address, revbuf[7]);
			counter++;
		}
		
	}
	pArray->num_student = counter;

	return pArray;
}

void print_students(StudentArray* p)
{
	if (p->num_student <= 0)
	{
		printf("No student information.\n");
		return;
	}
	for (int i = 0; i < p->num_student; i++)
	{
		Student *student = p->students + i;
		printf("%s,%s,%s,%s,%s,%s,%s,%s\n", student->number,
			student->name, student->gender, student->phone, student->email,
			student->qq_id, student->wechat_id, student->address);
	}
}

void sort_student_by_number(StudentArray* p)
{
	int i, j;
	Student t;
	for (i = 0; i < p->num_student - 1; i++)
	{
		for (j = 0; j < p->num_student - i - 1; j++)
		{
			if (strcmp(p->students[j].number, p->students[j + 1].number) > 0)
			{
				t = p->students[j];
				p->students[j] = p->students[j + 1];
				p->students[j + 1] = t;
			}
		}
	}
}

void sort_student_by_name(StudentArray* p)
{
	int i, j;
	Student t;
	for (i = 0; i < p->num_student - 1; i++)
	{
		for (j = 0; j < p->num_student - i - 1; j++)
		{
			if (strcmp(p->students[j].name, p->students[j + 1].name) > 0)
			{
				t = p->students[j];
				p->students[j] = p->students[j + 1];
				p->students[j + 1] = t;
			}
		}
	}
}


bool insert_student(StudentArray* L, int i, Student e)
{
	int j;
	if (i < 0 || i > L->num_student) {
		return false;
	}

	i--;    // 将顺序表逻辑序号转化为物理序号
	for (j = L->num_student; j > i; j--) {
		L->students[j] = L->students[j - 1];	//将data[i..n]元素后移一个位置
	}
	L->students[i] = e;  //插入元素e
	L->num_student++;  //顺序表长度增1
	return true;   //成功插入返回true
}

bool delete_student(StudentArray* L, int i, Student &e)
{
	int j;
	if (i<0 || i > L->num_student - 1) //参数错误时返回false
	{
		return false;
	}

	e = L->students[i];	// backup the student
	for (j = i; j < L->num_student - 1; j++)   //将data[i..n-1]元素前移
	{
		L->students[j] = L->students[j + 1];
	}
	L->num_student--;     //顺序表长度减1
	return true;     //成功删除返回true
}


Student* binary_search_by_number(StudentArray* sorted_list, char* target_number)
{
	int low = 0, high = sorted_list->num_student - 1;
	int mid = (low + high) / 2;

	while (low <= high)
	{
		if (strcmp(sorted_list->students[mid].number, target_number) > 0)
		{
			high = mid - 1;
		}
		else if (strcmp(sorted_list->students[mid].number, target_number) < 0)
		{
			low = mid + 1;
		}
		else
		{
			return sorted_list->students + mid;
		}
		mid = (low + high) / 2;
	}
	return 0;
}

int binary_search_by_number_v2(StudentArray* sorted_list, char* target_number)
{
	int low = 0, high = sorted_list->num_student - 1;
	int mid = (low + high) / 2;

	while (low <= high)
	{
		if (strcmp(sorted_list->students[mid].number, target_number) > 0)
		{
			high = mid - 1;
		}
		else if (strcmp(sorted_list->students[mid].number, target_number) < 0)
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
		mid = (low + high) / 2;
	}
	return -1;
}

int update_student_by_number(StudentArray* list, Student *to_update)
{
	Student *student = binary_search_by_number(list, to_update->number);
	if (0 == student)
	{
		return 0;	// can't find the target number
	}

	*student = *to_update;	// hard copy

	return 1;	// update success
}

void write_student(StudentArray* list, char * target_file)
{
	FILE *fp = 0;
	if ((fp = fopen(target_file, "w")) == 0)
	{
		printf("directory not exist: %s\n", target_file);
		return ;
	}

	for (int i = 0; i < list->num_student; i++)
	{
		Student *student = list->students + i;
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", student->number,
			student->name, student->gender, student->phone, student->email,
			student->qq_id, student->wechat_id, student->address);

		//fputs(student->number, fp);
		//fputs("\n", fp);
	}
	fclose(fp);
}
