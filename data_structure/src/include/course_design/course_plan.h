#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

#include"../Graph.h"

void split(char* src, const char* separator, char** dest, int* num)
{
	/*
	src 源字符串的首地址(buf的地址)
	separator 指定的分割字符
	dest 接收子字符串的数组
	num 分割后子字符串的个数
	*/
	char* pNext;
	int count = 0;
	if (src == NULL || strlen(src) == 0) //如果传入的地址为空或长度为0，直接终止 
		return;
	if (separator == NULL || strlen(separator) == 0) //如未指定分割的字符串，直接终止 
		return;
	pNext = (char*)strtok(src, separator); //必须使用(char *)进行强制类型转换(虽然不写有的编译器中不会出现指针错误)
	while (pNext != NULL) {
		*dest++ = pNext;
		++count;
		pNext = (char*)strtok(NULL, separator);  //必须使用(char *)进行强制类型转换
	}
	*num = count;
}


void get_weights(char *filename, Edge *edges, int &n)
{
	FILE* fp = 0;
	if ((fp = fopen(filename, "r")) == 0)
	{
		printf("file not found: %s\n", filename);
	}
	char buffer[1024] = { 0 };
	int counter = 0;

	while (!feof(fp))
	{
		// read lines and parse

		char* revbuf[7] = { 0 };
		int num = 0;
		fgets(buffer, 1024, fp);

		split(buffer, " ", revbuf, &num); // 调用函数进行分割
		if (num == 2)
		{
			int from = atoi(revbuf[0]);
			int to = atoi(revbuf[1]);
			edges[counter].u = from;
			edges[counter].v = to;
			counter++;
		}
	}
	n = counter;
}


void program_entry()
{
	char course_topology_file[256] = "E:/workspace/vs_course/data_structure/src/include/course_design/course_topology.txt";

	Edge edges[20];
	int edge_number = 0;
	get_weights(course_topology_file, edges, edge_number);

}
