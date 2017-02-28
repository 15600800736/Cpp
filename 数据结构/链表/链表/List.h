//[lo,hi)�����½粻�����Ͻ�  x��p��
#pragma once
#include "Node.h"
#define NULL 0;
enum SORT{MERGE,SELECTION,INSERTION};
template<class T>class CList
{
protected:
	LNodePos(T) header;//�׽ڵ�
	LNodePos(T) tailer;//β�ڵ�
	int m_size;//��ģ

	int copyfrom(T const*, int, int);//�������临��
	void init();//�����ʼ��
	int clear();//��������
	void merge(LNodePos(T), int p, CList<T>, LNodePos(T), int q);//�鲢
	void mergesort(LNodePos(T), int n);//�鲢����
	void selectionsort(LNodePos(T), int n);//ѡ������
	void insertionsort(LNodePos(T), int n);//��������
public:
	CList()//Ĭ�Ϲ��캯��
	{
		init();
	}
	CList(T const* A, int n);//�������帴��
	CList(T const* A, int lo, int hi);//�������临��
	CList(CList<T> const& L, int n);//�������帴��
	CList(CList<T> const& L, LNodePos(T) x, int n);//�������临��
	~CList();//��������
	bool empty()const{ return m_size <= 0; }//����Ƿ�Ϊ��
	LNodePos(T) first()const{ return header->suc; }
	LNodePos(T) last()const{ return tailer->pre; }
	int copyto(T const*& A);//���Ƶ�ĳ��������
	int sort(SORT s);//��������
	int sort(LNodePos(T), int n, SORT s);//��������
	int size()const;//��ģ
	bool valid(LNodePos(T) p);//�ж�p�ĺϷ���
	LNodePos(T) selectmax(LNodePos(T) x, int p);//ѡ��x��p���ж������
	LNodePos(T) selectmax();//ѡ��ȫ�������

	LNodePos(T) insertasfirst(T const& d);//��Ϊ�׽ڵ����
	LNodePos(T) insertaslast(T const& d);//��Ϊβ�ڵ����
	LNodePos(T) insertasp(LNodePos(T) x, T const&);//��Ϊǰ׺����
	LNodePos(T) insertass(LNodePos(T) x, T const&);//��Ϊ��׺����
	T remove(LNodePos(T) x);//ɾ���Ϸ�λ�ýڵ�
	LNodePos(T) remove(LNodePos(T) x, int n);//��������ɾ��
	LNodePos(T) find(T const& d);//�������
	LNodePos(T) find(T const& d, LNodePos(T) x, int n);//�������
	LNodePos(T) search(T const& d);//�������
	LNodePos(T) search(T const& d, LNodePos(T) x, int n);//�������
	T operator[](Rank r)const;//[]����������
	void  travel(void(*)(T&));//����ָ�����
	template<class VST>void travel(VST&);//���ں��������ȫ�ֱ���
	int deduplicate();//����ȥ��
	int uniquify();//����ȥ��
	void reverse();//ǰ����
};