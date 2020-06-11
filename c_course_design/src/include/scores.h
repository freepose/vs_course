#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>


typedef struct {
	float scores[100];
	int num_scores;
} ScoreList;

typedef struct {
	char number[20 + 1];
	char name[10 * 2 + 1];
	char classroom[20 + 1];
	ScoreList scores;
} Student;

typedef struct {
	Student students[100];
	int num_students;
} StudentList;


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

StudentList* read_scores(char *filename)
{
	FILE *fp = 0;
	if ((fp = fopen(filename, "r")) == 0)
	{
		printf("file not found: %s\n", filename);
		return 0;
	}

	StudentList *list = new StudentList;
	memset(list, 0, sizeof(StudentList));

	int counter = 0;
	char buffer[1024] = { 0 };
	fgets(buffer, 1024, fp);	// skip first line

	while (!feof(fp))
	{
		// read lines and parse
		Student *pStudent = list->students + counter;

		char *revbuf[7] = { 0 };
		int num = 0;
		fgets(buffer, 1024, fp);

		split(buffer, ",", revbuf, &num); //调用函数进行分割
		if (num == 7)
		{
			strcpy(pStudent->number, revbuf[0]);
			strcpy(pStudent->name, revbuf[1]);
			strcpy(pStudent->classroom, revbuf[2]);
			pStudent->scores.scores[0] = atoi(revbuf[3]);
			pStudent->scores.scores[1] = atoi(revbuf[4]);
			pStudent->scores.scores[2] = atoi(revbuf[5]);
			pStudent->scores.scores[3] = atoi(revbuf[6]);
			counter++;
		}
	}
	list->num_students = counter;

	return list;
}

void print_student_scores(Student *student)
{
	printf("%s,%s,%s,%.1f,%.1f,%.1f,%.1f\n",
		student->number, student->name, student->classroom,
		student->scores.scores[0], student->scores.scores[1],
		student->scores.scores[2], student->scores.scores[3]);
}

void print_students(StudentList* list)
{
	if (list->num_students <= 0)
	{
		printf("No student information.\n");
		return;
	}
	for (int i = 0; i < list->num_students; i++)
	{
		Student *student = list->students + i;
		printf("%s,%s,%s,%.1f,%.1f,%.1f,%.1f\n", 
			student->number, student->name, student->classroom, 
			student->scores.scores[0], student->scores.scores[1],
			student->scores.scores[2], student->scores.scores[3]);
	}
}

void write_students(StudentList* list, char * target_file)
{
	FILE *fp = 0;
	if ((fp = fopen(target_file, "w")) == 0)
	{
		printf("directory not exist: %s\n", target_file);
		return;
	}

	for (int i = 0; i < list->num_students; i++)
	{
		Student *student = list->students + i;
		fprintf(fp, "%s,%s,%s,%.1f,%.1f,%.1f,%.1f\n",
			student->number, student->name, student->classroom,
			student->scores.scores[0], student->scores.scores[1],
			student->scores.scores[2], student->scores.scores[3]);
	}
	fclose(fp);
}

void sort_student_by_number(StudentList* p)
{
	int i, j;
	Student t;
	for (i = 0; i < p->num_students - 1; i++)
	{
		for (j = 0; j < p->num_students - i - 1; j++)
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

int binary_search_by_number(StudentList* sorted_list, char* target_number)
{
	int low = 0, high = sorted_list->num_students - 1;
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

void display_scores_by_classroom(StudentList* list, char *classroom)
{
	for (int i = 0; i < list->num_students; i++)
	{
		Student *student = list->students + i;

		if (strcmp(student->classroom, classroom) == 0)
		{
			printf("%s,%s,%s,%.1f,%.1f,%.1f,%.1f\n",
				student->number, student->name, student->classroom,
				student->scores.scores[0], student->scores.scores[1],
				student->scores.scores[2], student->scores.scores[3]);
		}
	}
}

void student_scores_average(StudentList* list)
{
	for (int i = 0; i < list->num_students; i++)
	{
		Student *student = list->students + i;
		float average = student->scores.scores[0] + student->scores.scores[1] + student->scores.scores[2] + student->scores.scores[3];
		printf("%s, %s, average = %.1f\n", student->number, student->name, average / 4.0);
	}
}

void scores_example()
{
	// 1. read score information from given file.
	char *filename = "D:/data/c_course/scores.csv";
	char *target_filename = "D:/data/c_course/scores.target.csv";

	StudentList* list = read_scores(filename);
	sort_student_by_number(list);

	int index = binary_search_by_number(list, "201921145075");
	if (index > 0)
	{
		Student *given_student = list->students + index;
		print_student_scores(given_student);
	}

	display_scores_by_classroom(list, "光电1912");


	student_scores_average(list);

	delete list;
}