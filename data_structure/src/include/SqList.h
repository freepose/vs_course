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
		
	i--;    // ��˳����߼����ת��Ϊ�������
	for (j = L->length; j > i; j--) {
		L->data[j] = L->data[j - 1];	//��data[i..n]Ԫ�غ���һ��λ��
	}		
	L->data[i] = e;  //����Ԫ��e
	L->length++;  //˳���������1
	return true;   //�ɹ����뷵��true
}

bool ListDelete(SqList *&L, int i, ElemType &e)
{
	int j;
	if (i<1 || i>L->length) //��������ʱ����false
		return false;
	i--;    //��˳����߼����ת��Ϊ�������
	e = L->data[i];
	for (j = i; j<L->length - 1; j++)   //��data[i..n-1]Ԫ��ǰ��
		L->data[j] = L->data[j + 1];
	L->length--;     //˳������ȼ�1
	return true;     //�ɹ�ɾ������true
}

void delnode(SqList *&L, ElemType x)
{
	int i = 0, j = 0;
	for (i = 0; i<L->length; i++) {
		if (L->data[i] != x) {
			L->data[j] = L->data[i];
			j++;
		}
	}
	L->length = j;
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

	int b[] = { 1, 2, 3, 3, 3, 4, 5 };
	SqList* sqlist2 = 0;
	InitList(sqlist2);
	CreateList(sqlist2, b, 7);
	DisplayList(sqlist2);
	delnode(sqlist2, 3);
	DisplayList(sqlist2);
}

#endif 