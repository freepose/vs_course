#ifndef SQ_LIST_H
#define SQ_LIST_H 1

typedef int ElemType;
#define MAX_SIZE 50

typedef struct
{
	ElemType data[MAX_SIZE];
	int length;
}SqList;


void InitList(SqList* &L)
{
	L = new SqList;
	L->length = 0;
}


void CreateList(SqList *&L,int a[],int n)
{
	for(int i=0;i<n;i++){		
		L->data[i]=a[i];
	}
	L->length = n;
}


void DisplayList(SqList *&L)
{
	for(int i=0;i<L->length;i++){		
		cout<<"\t"<<L->data[i];
	}
	cout<<endl;
}


void DestoryList(SqList* &L)
{
	delete L;
	L = 0;
}

bool ListEmpty(SqList* L)
{
	return (L->length == 0);
}

int ListLength(SqList* L)
{
	return (L->length);
}

// 1-based
bool GetElem(SqList* L, int i, ElemType &e)
{
	if (i < 1 || i > L->length) {
		return false;
	}
	e = L->data[i - 1];
	return true;
}

// 1-based
int LocateElem(SqList *L, ElemType e)
{
	int i = 0;
	while (i<L->length && L->data[i] != e)
		i++;
	if (i >= L->length)  return 0;
	else  return i + 1;
}

bool ListInsert(SqList *&L, int i, ElemType e)
{
	int j;
	if (i<1 || i>L->length + 1) {
		return false; 
	}
		
	i--;    // 将顺序表逻辑序号转化为物理序号
	for (j = L->length; j > i; j--) {
		L->data[j] = L->data[j - 1];	//将data[i..n]元素后移一个位置
	}		
	L->data[i] = e;  //插入元素e
	L->length++;  //顺序表长度增1
	return true;   //成功插入返回true
}

bool ListDelete(SqList *&L, int i, ElemType &e)
{
	int j;
	if (i<1 || i>L->length) //参数错误时返回false
		return false;
	i--;    //将顺序表逻辑序号转化为物理序号
	e = L->data[i];
	for (j = i; j<L->length - 1; j++)   //将data[i..n-1]元素前移
		L->data[j] = L->data[j + 1];
	L->length--;     //顺序表长度减1
	return true;     //成功删除返回true
}


void SqListExample()
{
	int a[] = { 1, 2, 3, 4, 5 };
	const int n = 5;
	//print_array(a, n);

	// Sequence List
	SqList* sqlist = 0;

	InitList(sqlist);
	CreateList(sqlist, a, n);
	DisplayList(sqlist);

	ListInsert(sqlist, 6, 6);
	DisplayList(sqlist);

	int deletedElement;
	ListDelete(sqlist, 6, deletedElement);
	DisplayList(sqlist);
}

#endif 