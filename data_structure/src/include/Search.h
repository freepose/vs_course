/*
*
* Create By Kaijin Cui,2018
*
*/


#pragma once
#include"basic.h"
#include"BTree.h"


template <typename T, typename K>struct RecType
{
	K key;	//关键字项
	T data;		//其他数据项
};		//查找元素的类型

template <typename K>struct IdxType
{
	K key;
	int link;
};

//HashTable
#define NULLKEY -1	//定义空关键字值
#define DELKEY -2	//定义被删关键字值


template <typename T>struct HashTable
{
	T key;//关键字域
	int count;//探测次数域
};


template <typename T, typename K>int SeqSreach(RecType<T, K> R[], int n, K k)
{
	int i = 0;
	while (i < n && R[i].key != k)		//从表头往后找
		i++;
	if (i > n)							//未找到返回0
		return 0;
	else
		return i + 1;					//找到返回逻辑序号i + 1
}

template <typename T, typename K>int SeqSreach1(RecType<T, K> R[], int n, K k)
{
	int i = 0;
	R[n].key = k;
	while (R[i].key != k)		//从表头往后找
		i++;
	if (i == n)
		return 0;				//未找到返回零
	else
		return i + 1;			//找到返回逻辑序号i + 1
}

template <typename T, typename K>int BinSearch(RecType<T, K> R[], int n, K k)	//折半查找算法
{
	int low = 0, high = n - 1, mid;
	while (low <= high)		//当前区间存在元素时循环
	{
		mid = (low + high) / 2;
		if (k == R[mid].key)		//查找成功返回其逻辑序号 mid + 1
			return mid + 1;
		if (k < R[mid].key)			//继续在R[low..mid - 1]中查找
			high = mid - 1;
		else						//k > R[mid].key
			low = mid + 1;			//继续在R[mid + 1..high]中查找
	}
	return 0;						//未找到时返回0（查找失败）
}

template <typename K, typename T>int IdxSearch(IdxType<K> I[], int b, RecType<T, K> R[], int n, K k)
{
	int s = (n + b - 1) / b;		
	int low = 0, high = n - 1, mid, i;
	while (low <= high)			//在索引表中进行折半查找，找到的位置为high + 1
	{
		mid = (low + high) / 2;
		if (I[mid].key >= k)
			high = mid - 1;
		else
			low = mid + 1;
	}
	//应先在索引表的high + 1块中查找，再在主数据表中进行顺序查找
	i = I[high + 1].link;
	while (i <= I[high + 1].link + s - 1 && R[i].key != k)
		i++;
	if (i <= I[high + 1].link + s - 1)
		return i + 1;		//查找成功，返回该元素的逻辑序号
	else
		return 0;			//查找失败，返回0
}

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
		return false; // note
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
	if (p->lchild == 0) {     //结点P没有左孩子
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
		r = r->lchild;            //用结点r的左孩子替代它，此时r的右孩子一定为空
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


//Insert k to HashTable
template <typename T> void InsertHT(HashTable<T> ha[], int &n, int m, int p, T k)
{
	int i, adr;
	adr = k%p;//计算哈希函数值
	if (ha[adr].key == NULLKEY || ha[adr].key == DELKEY)
	{
		ha[adr].key = k; //k可以直接放在哈希表中
		ha[adr].count = 1;
	}
	else//发生冲突时采用线性探测法解决冲突
	{
		i = 1;//i记录k发生冲突的次数
		do
		{
			adr = (adr + 1) % m;//线性探测
			i++;
		} while (ha[adr].key != NULLKEY && ha[adr].key != DELKEY);
		ha[adr].key = k;//在adr处放置k
		ha[adr].count = i;//设置探测次数
	}
	n++;//哈希表中总元素个数增1
}

//Create HashTable
template<typename T> void CreateHT1(HashTable<T> ha[], int &n, int m, int p, T keys[])
{
	int n1 = n, i;
	for (i = 0; i < m; i++)//哈希表置空的初值
	{
		ha[i].key = NULLKEY;
		ha[i].count = 0;
	}
	n = 0;//哈希表中总元素个数从0开始递增
	for (i = 0; i < n1; i++)
		InsertHT(ha, n, m, p, keys[i]);//插入n个关键字
}

//Delete k in HashTable
template <typename T> bool DeleteHT(HashTable<T> ha[], int &n, int m, int p, T k)
{
	int adr;
	adr = k%p;//计算哈希函数值
	while (ha[adr].key != NULLKEY&&ha[adr].key != k)
		adr = (adr + 1) % m;//线性探测
	if (ha[adr].key == k)//查找成功
	{
		ha[adr].key = DELKEY;//删除关键字k
		return true;
	}
	else//查找失败
		return false;//返回假
}

//Search k in HashTable
template <typename T> void SearchHT(HashTable <T> ha[], int m, int p, T k)
{
	int i = 1, adr;
	adr = k%p;
	while (ha[adr].key != NULLKEY&& ha[adr].key != k)
	{
		i++;
		adr = (adr + 1) % m;
	}
	if (ha[adr].key == k)
		cout << "成功：关键字" << k << "，比较" << i << "次" << endl;
	else
		cout << "失败：关键字" << k << "，比较" << i << "次" << endl;

}

template<typename T> void ASL(HashTable<T> ha[], int n, int m, int p)
{
	int i, j;
	int succ = 0, unsucc = 0, s;
	for (i = 0; i < m; i++)
		if (ha[i].key != NULLKEY)
			succ += ha[i].count;
	cout << "成功情况下ASL(" << n << ")=" << succ*1.0 / n << endl;

	for (i = 0; i < p; i++)
	{
		s = 1; j = i;
		while (ha[i].key != NULLKEY)
		{
			s++;
			j = (j + 1) % m;
		}
		unsucc += s;
	}
	cout << "不成功情况下ASL(" << n << ")=" << unsucc*1.0 / p << endl;
}

template <typename T>void DispHT(HashTable<T> ha[], int n, int m)    //输出哈希表  
{
	int i;
	cout << " 哈希表地址:" << "\t";
	for (i = 0; i < m; i++)
		cout << setw(3) << setfill(' ') << i;
	cout << endl;
	cout << " 哈希表关键字:" << "\t";
	for (i = 0; i<m; i++)
		if (ha[i].key == NULLKEY || ha[i].key == DELKEY)
			cout << "    ";         //输出3个空格  
		else
			cout << setw(3) << setfill(' ') << ha[i].key;
	cout << endl;
	printf(" 搜索次数:\t");
	for (i = 0; i<m; i++)
		if (ha[i].key == NULLKEY || ha[i].key == DELKEY)
			cout << "    ";         //输出3个空格  
		else
			cout << setw(3) << setfill(' ') << ha[i].count;
	cout << endl;

}


void SearchExample()
{
	RecType<int, int> R[MAX_SIZE];
	for (int i = 0; i < 6; i++)
	{
		R[i].key = i;
	}

	cout << "The position of the order finding 2 is: " << SeqSreach(R, 6, 2) << endl;
	cout << "The position of the order finding 3 is: " << SeqSreach(R, 6, 3) << endl;
	cout << "The position of the order finding 3 is(BinSearch): " << BinSearch(R, 6, 3) << endl;

	BTNode<int> *bt;
	BTNode<char> *bf;

	//P329 例【9.3】
	int A[MAX_SIZE] = { 25,18,46,2,53,39,32,4,74,67,60,11 };
	bt = CreateBST(A, 12);
	cout << endl << "The Binary search tree is: ";
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
	cout << endl << "The Binary search tree is: "; DispBTree(bf);
	deletek(bf, k);
	cout << endl << "Delete the 1 node: "; DispBTree(bf);
	DestroyBTree(bf);

	//HashTable
	int x[] = { 16,74,60,43,54,90,46,31,29,88,77 };
	int n = 11, m = 13, p = 13, t = 29;
	HashTable<int> ha1[MAX_SIZE];
	CreateHT1(ha1, n, m, p, x);
	cout << endl;
	DispHT(ha1, n, m);
	SearchHT(ha1, m, p, t);
	k = 77;
	cout << " 删除关键字" << t << endl;
	DeleteHT(ha1, n, m, p, t);
	DispHT(ha1, n, m);
	SearchHT(ha1, m, p, t);
	cout << " 插入关键字" << t << endl;
	InsertHT(ha1, n, m, p, t);
	DispHT(ha1, n, m);
	cout << endl;
	ASL(ha1, n, m, p);


}
