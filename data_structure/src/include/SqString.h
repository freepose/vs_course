#pragma once
#include "basic.h"

typedef struct 
{
	char data[MAX_SIZE];
	int length;
} SqString;

void StrAssign(SqString &s, char cstr[])
{

	int i;
	for (i = 0; cstr[i] != '\0'; i++)
	{
		s.data[i] = cstr[i];
	}
	s.length = i;
}

void StrCopy(SqString &s, SqString t)
{
	int i;
	for (i = 0; i < t.length; i++)
	{
		s.data[i] = t.data[i];
	}
	s.length = t.length;
}

bool StrEqual(SqString s, SqString t)
{
	if (s.length != t.length)
		return false;
	else
	{
		for (int i = 0; i < s.length; i++)
		{
			if (s.data[i] != t.data[i])
				return false;
		}
	}
	return true;
}

int StrLength(SqString s)
{
	return s.length;
}

SqString Concat(SqString s, SqString t)
{
	SqString str;
	str.length = s.length + t.length;
	for (int i = 0; i < s.length; i++)
	{
		str.data[i] = s.data[i];
	}
	for (int i = 0; i < t.length; i++)
	{
		str.data[i + s.length] = t.data[i];
	} 
	return str;
}

SqString SubStr(SqString s, int i, int j)
{
	int k;
	SqString str;
	str.length = 0;
	if (i <= 0 || i > s.length || j < 0 || i + j - 1 > s.length)
		return str;
	for (k = i - 1; k < i + j - 1; k++)
	{
		str.data[k - i + 1] = s.data[k];
	}
	str.length = j;
	return str;
}

SqString InsStr(SqString s1, int i, SqString s2)
{
	int j;
	SqString str;
	str.length = 0;
	if (i <= 0 || i > s1.length + 1)
	{
		return str;
	}
	for (j = 0; j < i - 1; j++)
	{
		str.data[j] = s1.data[j];
	}
	for (j = 0; j < s2.length; j++)
	{
		str.data[i + j - 1] = s2.data[j];
	}
	for (j = i - 1; j < s1.length; j++)
	{
		str.data[s2.length + 1] = s1.data[j];
	}
	str.length = s1.length + s1.length;
	return str;
}

SqString DelStr(SqString s, int i, int j)
{
	int k;
	SqString str;
	str.length = 0;
	if (i < 0 || i > s.length || i + j > s.length + 1)
		return str;
	for (k = 0; k < i - 1; k++)
	{
		str.data[k] = s.data[k];
	}
	for (k = i + j - 1; k < s.length; k++)
	{
		str.data[k - j] = s.data[k];
	}
	str.length = s.length - j;
	return str;
}

SqString RepStr(SqString s, int i, int j, SqString t)
{
	int k;
	SqString str;
	str.length = 0;
	if (i <= 0 || i > s.length || i + j - 1 > s.length)
	{
		return str;
	}
	for (k = 0; k < i - 1; k++)
	{
		str.data[k] = s.data[k];
	}
	for (k = 0; k < t.length; k++)
	{
		str.data[i + k - 1] = t.data[k];
	}
	for (k = i + j - 1; k < s.length; k++)
	{
		str.data[t.length + k - j] = s.data[k];
	}
	str.length = s.length - j + t.length;
	return str;
}

/*Algorithm by CXD*/

//Brute-Force
int index(SqString s, SqString t)
{
	int j = 0, i = 0;
	while (i<s.length&&j < t.length) {
		if (s.data[i] == t.data[j]) {
			i++;
			j++;
		}
		else {
			i = i - j + 1;//移到i的下一个
			j = 0;
		}
	}
	if (j >= t.length) {
		return (i - t.length);//所在i的下标减去模式串长度，等于第一个字符所在的下标
	}
	else {
		return -1;
	}
}

//KMP
void GetNext(SqString t, int *next)
{
	int  j = 0, k = -1;
	next[0] = -1;//next[j]代表j前有几个与开头相同的数
	while (j < t.length - 1) {//当j=length-1时，已经把每个字符的next标注完
		if (k == -1 || t.data[k] == t.data[j]) {
			j++;
			k++;
			next[j] = k;
		}
		else {
			k = next[k];
		}
	}
}

int KMPIndex(SqString s, SqString t)
{
	int i = 0, j = 0;
	int next[MAX_SIZE];
	GetNext(t, next);
	while (i < s.length&&j < t.length) {
		if (j == -1 || s.data[i] == t.data[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j >= t.length) {
		return (i - t.length);
	}
	else {
		return -1;
	}
}

//better KMP
void GetNextval(SqString t, int *nextval)
{
	int j = 0, k = -1;
	nextval[0] = -1;
	while (j < t.length) {
		if (k == -1 || t.data[k] == t.data[j]) {
			k++;
			j++;
			if (t.data[k] == t.data[j]) {
				nextval[j] = nextval[k];
			}
			else {
				nextval[j] = k;
			}
		}
		else {
			k = nextval[k];
		}
	}
}

int KMPIndex1(SqString s, SqString t) {
	int nextval[MAX_SIZE];
	int i = 0, j = 0;
	GetNextval(t, nextval);
	while (i < s.length&&j < t.length) {
		if (j == -1 || s.data[i] == t.data[j]) {
			i++;
			j++;
		}
		else {
			j = nextval[j];
		}
	}
	if (j >= t.length) {
		return (i - t.length);
	}
	else {
		return -1;
	}
}


void SqStringexample()
{
	int i;
	SqString t, s;
	char a[5] = "abab";
	char b[13] = "abbaababbaab";
	for (i = 0; i < 4; i++) {
		t.data[i] = a[i];
	}
	t.length = 4;
	for (i = 0; i < 12; i++) {
		s.data[i] = b[i];
	}
	s.length = 12;
	cout << "The position of the substring is:"<<endl;
	cout << index(s, t)<< endl;
	cout << KMPIndex(s, t)<< endl;
	cout << KMPIndex1(s, t)<< endl;
}