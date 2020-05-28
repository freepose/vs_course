
#include<stdio.h>

// 学号,姓名,性别,联系电话,邮箱（必填）,QQ号,微信号,家庭住址,

// FILE

// windows (default): D:\\study\\teaching\\2020春 C语言-理学院19级\\contacts.csv
// macos or linux: "D:/study/teaching/2020春 C语言-理学院19级/contacts.csv"

void read_file_example()
{
	//301101 Zhangwen 91
	//301102 Chenhui 85
	//301103 Wangweidong 76
	//301104 Zhengwei 69
	//301105 Guowentao 55
	FILE *fp = 0;
	// char filename[] = "D:/study/teaching/2020春 C语言-理学院19级/contacts.csv";
	char filename[] = "D:/f12_1.txt";
	char buffer[1024] = {0};
	// 1. open a file
	fp = fopen(filename, "r");
	// 2. if exists
	if (fp == 0)
	{
		printf("file not exist: %s\n", filename);
		return;
	}

	// 3. read
	while (!feof(fp))
	{
		fgets(buffer, 1024, fp);
		printf("%s", buffer);
	}

	// 4. close
	fclose(fp);
}

void read_and_write_file_example()
{
	//301101 Zhangwen 91
	//301102 Chenhui 85
	//301103 Wangweidong 76
	//301104 Zhengwei 69
	//301105 Guowentao 55
	FILE *fp = 0, *fp_write = 0;
	// char filename[] = "D:/study/teaching/2020春 C语言-理学院19级/contacts.csv";
	char filename[] = "D:/f12_1.txt";
	char target[] = "D:/target.txt";
	char buffer[1024] = { 0 };
	int counter = 0;

	// data fields
	char number[6 + 1] = {0};
	char name[20 + 1] = { 0 };
	int score = 0;

	// 1. open a file
	fp = fopen(filename, "r");
	fp_write = fopen(target, "w");

	// 2. if exists
	if (fp == 0)
	{
		printf("file not exist: %s\n", filename);
		return;
	}

	// 3. read
	while (!feof(fp))
	{
		counter++;
		//fgets(buffer, 1024, fp);
		//printf("%s", buffer);
		//fprintf(fp_write, "%d %s", counter, buffer);

		fscanf(fp, "%s %s %d", number, name, &score);
		printf("%d %s %s %d\n", counter, number, name, score);
		fprintf(fp_write, "%d %s %s %d\n", counter, number, name, score);
	}

	// 4. close
	fclose(fp);
	fclose(fp_write);
}