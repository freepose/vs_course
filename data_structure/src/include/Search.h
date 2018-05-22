#pragma once
#include"BTree.h"
#include"basic.h"

/*
*  Binary search tree, by CXD, 2018
*/

template<typename T> bool InsertBST(BTNode<T> *&bt, T k)
{
	if (bt == 0) {
		bt = new BTNode<T>;
		bt->data = k; bt->lchild = bt->rchild = 0;
		return true;
	}
	else if (k == bt->data) {
		return false;
	}
	else if (k < bt->data) {
		return InsertBST(bt->lchild, k);
	}
	else {
		return InsertBST(bt->rchild, k);
	}
}

template<typename T> BTNode<T>*  CreateBST(T *A, int n)
{
	BTNode<T> *bt = 0;
	int i;
	for (i = 0; i<n; i++) {
		InsertBST(bt, A[i]);   //将A[i]插入二叉排序树bt中
	}
	return bt;
}

template<typename T> BTNode<T>* SearchBST(BTNode<T> *bt, T k)
{
	if (bt == 0 || bt->data == k) {
		return bt;
	}
	else if (k<bt->data) {
		return SearchBST(bt->lchild, k);
	}
	else {
		return SearchBST(bt->rchild, k);
	}
}

//f is the  parents node
template<typename T> BTNode<T>* SearchBSTf(BTNode<T> *bt, T k, BTNode<T> *f1, BTNode<T> *&f)
{
	if (bt == 0) {
		f = 0;
		return 0;
	}
	else if (k == bt->data) {
		f = f1;
		return bt;
	}
	else if (k < bt->data) {
		return SearchBSTf(bt->lchild, k, bt, f);
	}
	else {
		return SearchBSTf(bt->rchild, k, bt, f);
	}
}

//The deleted p is only the right subtree
template<typename T> bool deletek(BTNode<T> *&bt, T k)
{
	if (bt != 0) {
		if (k == bt->data) {     //查找到了被删结点bt
			deletep(bt);         //调用deletep函数删除结点P
			return true;
		}
		else if (k < bt->data) {
			deletek(bt->lchild, k);  //在左子树中查找
		}
		else {
			deletek(bt->rchild, k);  //在右子树查找
		}
	}
	else return false;
}

//P only has a right subtree
template<typename T> void deletep(BTNode<T> *&p)
{
	BTNode<T> *q;
	q = p;   //让q指向p结点
	p = p->rchild;    //p指向右孩子
	delete q;
}

//P is unkonwn
template<typename T> bool DeleteBST(BTNode<T> *&bt, T k)
{
	if (bt == 0) {
		return false;
	}
	else {
		if (k < bt->data) {         // //递归在左子树中删除为k的结点
			return DeleteBST(bt->lchild, k);
		}
		else if (k > bt->data) {    //递归在右子树中删除为k的结点
			return DeleteBST(bt->rchild, k);
		}
		else {             //找到了要删除的结点bt
			Delete(bt);    //调用Delete函数删除结点bt
			return true;   //删除成功，返回真
		}
	}
}

template<typename T> void Delete(BTNode<T> *&p)
{
	BTNode<T> *q;
	if (p->lchild==0) {     //结点P没有左孩子
		q = p;     
		p = p->rchild;              //用结点P的右孩子代替它
		delete q;
	}
	else if (p->rchild == 0) {  //结点P没有右孩子
		q = p;
		p = p->lchild;                  //用结点P的右孩子代替它
		delete q;
	}
	else {
		Deletel(p, p->lchild);    //结点P既有左孩子又有右孩子
	}
}

template<typename T> void Deletel(BTNode<T> *p, BTNode<T> *&r)
{
	BTNode<T> *q;
	if (r->rchild != 0) {
		Deletel(p, r->rchild);    //递归找结点r的最右下结点
	}
	else {                        //找到了最右下结点r（它没有右子树）
		p->data = r->data;        //将结点r的值存放到结点p中（结点值替代）
		q = r;                    //删除结点r
		r = r->lchild;            //用结点r的左孩子替代它
		delete q;                 //释放结点q的空间
	} 
}


/*
*Example
*/

//P329 例【9.4】 find the maxlnode and the minrnode
template<typename T> void MaxMinnode(BTNode<T>* bt)
{
	if (bt != 0) {
		if (bt->lchild != 0) {
			cout << "The maxlnode is " << Maxlnode(bt->lchild) << endl;
		}
		if (bt->rchild != 0) {
			cout << "The maxrnode is " << Minrnode(bt->rchild) << endl;
		}
	}
}

template<typename T> T Maxlnode(BTNode<T>* bt)
{
	while (bt->rchild != 0) {
		bt = bt->rchild;
	}
	return bt->data;
}

template<typename T> T Minrnode(BTNode<T>* bt)
{
	while (bt->lchild != 0) {
		bt = bt->lchild;
	}
	return bt->data;
}


void SearchExample()
{
	BTNode<int> *bt;
	BTNode<char> *bf;

	//P329 例【9.3】
	int A[MAX_SIZE] = { 25,18,46,2,53,39,32,4,74,67,60,11 };
	bt=CreateBST(A, 12);
	cout << "The Binary search tree is: ";
	DispBTree(bt); cout << endl;

	//P329 例【9.4】 
	MaxMinnode(bt); 

	DeleteBST(bt, 25);
	cout << "Delete the 25 node: ";
	DispBTree(bt); cout << endl;
	DestroyBTree(bt); 

	//P332 图【9.13】
	char k = '1';
	char B[MAX_SIZE] = "3(1(,2))";
	CreateBTree(bf, B);
	cout <<endl<< "The Binary search tree is: "; DispBTree(bf); 
	deletek(bf, k);
	cout <<endl<< "Delete the 1 node: "; DispBTree(bf);
	DestroyBTree(bf);
}