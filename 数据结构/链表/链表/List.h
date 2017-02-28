//[lo,hi)包括下界不包括上界  x后p个
#pragma once
#include "Node.h"
#define NULL 0;
enum SORT{MERGE,SELECTION,INSERTION};
template<class T>class CList
{
protected:
	LNodePos(T) header;//首节点
	LNodePos(T) tailer;//尾节点
	int m_size;//规模

	int copyfrom(T const*, int, int);//数组区间复制
	void init();//链表初始化
	int clear();//链表清理
	void merge(LNodePos(T), int p, CList<T>, LNodePos(T), int q);//归并
	void mergesort(LNodePos(T), int n);//归并排序
	void selectionsort(LNodePos(T), int n);//选择排序
	void insertionsort(LNodePos(T), int n);//插入排序
public:
	CList()//默认构造函数
	{
		init();
	}
	CList(T const* A, int n);//数组整体复制
	CList(T const* A, int lo, int hi);//数组区间复制
	CList(CList<T> const& L, int n);//链表整体复制
	CList(CList<T> const& L, LNodePos(T) x, int n);//链表区间复制
	~CList();//析构函数
	bool empty()const{ return m_size <= 0; }//检查是否为空
	LNodePos(T) first()const{ return header->suc; }
	LNodePos(T) last()const{ return tailer->pre; }
	int copyto(T const*& A);//复制到某个数组中
	int sort(SORT s);//整体排序
	int sort(LNodePos(T), int n, SORT s);//区间排序
	int size()const;//规模
	bool valid(LNodePos(T) p);//判断p的合法性
	LNodePos(T) selectmax(LNodePos(T) x, int p);//选出x后p个中对最大者
	LNodePos(T) selectmax();//选出全局最大者

	LNodePos(T) insertasfirst(T const& d);//作为首节点插入
	LNodePos(T) insertaslast(T const& d);//作为尾节点插入
	LNodePos(T) insertasp(LNodePos(T) x, T const&);//作为前缀插入
	LNodePos(T) insertass(LNodePos(T) x, T const&);//作为后缀插入
	T remove(LNodePos(T) x);//删除合法位置节点
	LNodePos(T) remove(LNodePos(T) x, int n);//链表批量删除
	LNodePos(T) find(T const& d);//整体查找
	LNodePos(T) find(T const& d, LNodePos(T) x, int n);//区间查找
	LNodePos(T) search(T const& d);//整体查找
	LNodePos(T) search(T const& d, LNodePos(T) x, int n);//区间查找
	T operator[](Rank r)const;//[]操作符重载
	void  travel(void(*)(T&));//函数指针遍历
	template<class VST>void travel(VST&);//基于函数对象的全局遍历
	int deduplicate();//无序去重
	int uniquify();//有序去重
	void reverse();//前后倒置
};