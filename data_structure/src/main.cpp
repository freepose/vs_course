#include"include/basic.h"
#include"include/SqList.h"
#include"include/LinkNode.h"
#include"include\SqStack.h"

int main()
{
	int a[] = {1, 2, 3, 4, 5};
	const int n = 5;
	print_array(a, n);

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

	// Linked list
	LinkNode *linkedlist = 0;
	CreateListF(linkedlist, a, n);
	DispList(linkedlist);
	DestroyList(linkedlist);	

	CreateListR(linkedlist, a, n);
	DispList(linkedlist);

	

	int b[] = { 1, 2, 3, 4, 5, 6 };

	CreateCircleListR(linkedlist, b, 6);
	JosephProblem(linkedlist);
	// insert & delete


	// SqStack
	SqStack *S;
	CreateSqStack(S);
	InitStack(S, a, n);
	DispStack(S, n);
	DestroyStack(S);
	// insert & delete

	return 0;
}