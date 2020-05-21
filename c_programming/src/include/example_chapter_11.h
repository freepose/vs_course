#pragma once

#include<stdio.h>
#include<string.h>

// Example 11-1£ºÖ¸ÕëÊý×é
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
		printf("%s\t", rings[i]);
	}
	printf("\n");
}

void sort_Olympic_rings_example()
{
	char* rings[5] = { "blue", "yellow", "black", "green", "red" };
	int i, n = 5;

	print_rings(rings, 5);
	sort_rings(rings, 5);
	print_rings(rings, 5);
}



