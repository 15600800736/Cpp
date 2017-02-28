#pragma once
#include "typedef.h"
#define DEFAULT_CAPACITY 20
enum SORT{BUBBLE,SELECTION,MERGE,QUICK};
enum BINORFIB {BIN,FIB};
template <class T>class CVector
{
protected:
	//��Ա����
	Rank m_size;//������ģ;
	int m_capacity;//��������
	T* m_elem;//����������
	//��Ա����
	void copyfrom(T const* A, Rank lo, Rank hi);//���临��
	bool shrink();//����
	bool bubble(Rank lo, Rank hi);//ɨ�轻��
	void bubblesort(Rank lo, Rank hi);//ɨ�轻������
	Rank max(Rank lo, Rank hi);//�������Ԫ��
	void selectionsort(Rank lo, Rank hi);//ѡ������
	void merge(Rank lo, Rank mi, Rank hi);//�鲢
	void mergesort(Rank lo, Rank hi);//�鲢����
	Rank partition(Rank lo, Rank hi);//��㹹���㷨
	void quicksort(Rank lo, Rank hi);//��������
	//void heapsort(Rank lo, Rank hi);//������
	void swap(T &e, T &l);
	T* init(int c,int s,T v);
	Rank fibsearch(T const &e, Rank lo, Rank hi);
	Rank binsearch(T const &E, Rank lo, Rank hi);
public:
	//���캯��
	CVector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0);//Ĭ�Ϲ��캯��
	CVector(T const*A, Rank n);//�������鸴��
	CVector(T const*A, Rank lo, Rank hi);//�������鸴��
	CVector(CVector<T> const& V);//������������
	CVector(CVector<T> const& V, Rank lo, Rank hi);//������������
	//��������
	virtual ~CVector();
	//ֻ�����ʽӿ�
	Rank size()const;//���ع�ģ
	bool empty()const;//���������Ƿ�Ϊ��
	bool disordered()const;//���������Ƿ�����
	Rank find(T const &e);//���������������
	Rank find(T const &e, Rank lo, Rank hi);//���������������
	Rank search(T const &e, BINORFIB n);//���������������
	Rank search(T const &e, Rank lo, Rank hi, BINORFIB n);//���������������
	//��д���ʽӿ�
	CVector<T> & operator= (CVector<T> const& V);//���ز�����=
	SORT sort(Rank lo, Rank hi,SORT s);//��[lo,hi)����
	SORT sort(SORT s);//��������
	void unsort(Rank lo, Rank hi);//��[lo,hi)����
	void unsort();//��������
	int deduplicate();//����ȥ��
	int uniquify();//����ȥ��
	//����
	void traverse(void(*)(T&));//ʹ�ú���ָ�룬�ֲ��޸�
	template <class VST>void traverse(VST&);//ʹ�ú�������ȫ���޸�
	//��ջ���ɷ��ʽӿ�
protected:
	Rank insert(Rank r, T const& e);//��e��������Ϊr��λ��
	Rank insertAsL(T const& e);//��e��ΪĩԪ�ز���
	Rank insertAsF(T const& e);//��e��Ϊ��Ԫ�ز���
	T remove(Rank r);//ɾ����Ϊr��Ԫ��
	int remove(Rank lo, Rank hi);//ɾ������[lo,hi)������Ԫ��
	bool expand();//����
	T& operator[](Rank r)const;//����[]������
};
//
//