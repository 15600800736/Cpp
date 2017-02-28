#pragma once
#include "typedef.h"
#define DEFAULT_CAPACITY 20
enum SORT{BUBBLE,SELECTION,MERGE,QUICK};
enum BINORFIB {BIN,FIB};
template <class T>class CVector
{
protected:
	//成员变量
	Rank m_size;//向量规模;
	int m_capacity;//向量容量
	T* m_elem;//向量数据区
	//成员函数
	void copyfrom(T const* A, Rank lo, Rank hi);//区间复制
	bool shrink();//缩容
	bool bubble(Rank lo, Rank hi);//扫描交换
	void bubblesort(Rank lo, Rank hi);//扫描交换排序
	Rank max(Rank lo, Rank hi);//返回最大元素
	void selectionsort(Rank lo, Rank hi);//选择排序
	void merge(Rank lo, Rank mi, Rank hi);//归并
	void mergesort(Rank lo, Rank hi);//归并排序
	Rank partition(Rank lo, Rank hi);//轴点构造算法
	void quicksort(Rank lo, Rank hi);//快速排序
	//void heapsort(Rank lo, Rank hi);//堆排序
	void swap(T &e, T &l);
	T* init(int c,int s,T v);
	Rank fibsearch(T const &e, Rank lo, Rank hi);
	Rank binsearch(T const &E, Rank lo, Rank hi);
public:
	//构造函数
	CVector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0);//默认构造函数
	CVector(T const*A, Rank n);//整体数组复制
	CVector(T const*A, Rank lo, Rank hi);//区间数组复制
	CVector(CVector<T> const& V);//整体向量复制
	CVector(CVector<T> const& V, Rank lo, Rank hi);//区间向量复制
	//析构函数
	virtual ~CVector();
	//只读访问接口
	Rank size()const;//返回规模
	bool empty()const;//返回向量是否为空
	bool disordered()const;//返回向量是否有序
	Rank find(T const &e);//无序向量整体查找
	Rank find(T const &e, Rank lo, Rank hi);//无需向量区间查找
	Rank search(T const &e, BINORFIB n);//有序向量整体查找
	Rank search(T const &e, Rank lo, Rank hi, BINORFIB n);//有序向量区间查找
	//可写访问接口
	CVector<T> & operator= (CVector<T> const& V);//重载操作符=
	SORT sort(Rank lo, Rank hi,SORT s);//对[lo,hi)排序
	SORT sort(SORT s);//整体排序
	void unsort(Rank lo, Rank hi);//对[lo,hi)置乱
	void unsort();//整体置乱
	int deduplicate();//无序去重
	int uniquify();//有序去重
	//遍历
	void traverse(void(*)(T&));//使用函数指针，局部修改
	template <class VST>void traverse(VST&);//使用函数对象，全局修改
	//对栈不可访问接口
protected:
	Rank insert(Rank r, T const& e);//将e插入至秩为r的位置
	Rank insertAsL(T const& e);//将e作为末元素插入
	Rank insertAsF(T const& e);//将e作为首元素插入
	T remove(Rank r);//删除秩为r的元素
	int remove(Rank lo, Rank hi);//删除区间[lo,hi)的所有元素
	bool expand();//扩容
	T& operator[](Rank r)const;//重载[]操作符
};
//
//