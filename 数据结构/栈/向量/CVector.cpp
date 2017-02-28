#ifndef _CVECTOR
#define _CVECTOR
#include "iostream"
#include "CVector.h"
#include "Fib.h"

//函数实现(protected)
template <class T>bool CVector<T>::expand()
{
	if (m_size < m_capacity) return false;
	if (m_capacity < DEFAULT_CAPACITY) m_capacity = DEFAULT_CAPACITY;
	T *m_oldelem = m_elem;
	m_elem = new T[m_capacity <<= 1];
	for (int i = 0; i < m_size; m_elem[i] = m_oldelem[i++]);
	delete[] m_oldelem;
	m_oldelem = NULL;
	return true;
}
template <class T>bool CVector<T>::shrink()
{
	if (m_capacity >> 1 < DEFAULT_CAPACITY) return false;
	if (m_size > m_capacity >> 4) return false;
	T *m_oldelem = m_elem;
	m_elem = new T[m_capacity >>= 1];
	for (int i = 0; i < m_size; m_elem[i] = m_oldelem[i++]);
	delete[] m_oldelem;
	m_oldelem = NULL;
	return true;
}
template <class T>bool CVector<T>::bubble(Rank lo, Rank hi)
{
	bool sorted = true;
	while (++lo < hi)
		if (m_elem[lo - 1] > m_elem[lo])
		{
			sorted = false;
			swap(m_elem[lo-1], m_elem[lo]);
		}
	return sorted;
}
template <class T>void CVector<T>::bubblesort(Rank lo, Rank hi)
{
	while (!bubble(lo, hi--));
}
template <class T>Rank CVector<T>::max(Rank lo, Rank hi)
{
	Rank maxr = lo;
	for(int i = lo+1;i<hi;i++)  
		maxr = (m_elem[maxr]>m_elem[i]) ? maxr : i;
	return maxr;
}
template <class T>void CVector<T>::selectionsort(Rank lo, Rank hi)
{
	while (lo < hi)
	{
		int maxr = max(lo, hi);
		swap(m_elem[maxr],m_elem[hi - 1]);
		hi--;
	}
}
template <class T>void CVector<T>::merge(Rank lo,Rank mi, Rank hi)
{
	T* A = m_elem + lo;
	int lb = mi - lo;
	T* B = new T[lb];
	for (Rank i = 0; i < lb; B[i] = A[i++]);
	int lc = hi - mi;
	T* C = m_elem + mi;
	for (Rank i = 0, j = 0, k = 0;( j < lb) || (k < lc);)
	{
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];
		if ((k < lc) && (!(j<lb) || (B[j] >  C[k]))) A[i++] = C[k++];
	}
	delete[] B;
	B = NULL;
}
template<class T>void CVector<T>::mergesort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return;
	int mi = (hi + lo) >> 1;
	mergesort(lo, mi); mergesort(mi,hi);
	merge(lo, mi, hi);
}
template<class T>void CVector<T>::quicksort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return;
	Rank key = partition(lo, hi-1);
	quicksort(lo, key);
	quicksort(key + 1, hi);
}
template<class T>Rank CVector<T>::partition(Rank lo, Rank hi)
{
	swap(m_elem[lo], m_elem[lo + rand() % (hi - lo + 1)]);
	T pivot = m_elem[lo];
	while (lo < hi)
	{
		while (lo < hi)
			if (pivot < m_elem[hi])
				hi--;
			else
			{
				m_elem[lo++] = m_elem[hi];
				break;
			}
		while (lo < hi)
			if (pivot > m_elem[lo])
				lo++;
			else
			{
				m_elem[hi--] = m_elem[lo];
				break;
			}
	}
	m_elem[lo] = pivot;
	return lo;
}
//template<class T>void CVector<T>::quicksort(Rank lo, Rank hi)
//{
//	if (hi - lo < 2) return;
//	Rank key = partition(lo, hi);
//	quicksort(lo, key); quicksort(key + 1, hi);
//}
template <class T>void CVector<T>::swap(T &e, T &l)
{
	T temp = e;
	e = l;
	l = temp;
}
//构造函数
template <class T>void CVector<T>::copyfrom(T const* A, Rank lo, Rank hi)
{
	m_elem = new T[m_capacity = ((hi - lo) << 1)];
	m_size = 0;
	while (lo < hi) m_elem[m_size++] = A[lo++];
}
template <class T>T* CVector<T>::init(int c,int s,T v)
{
	m_elem = new T[c];
	m_size = s;
	for (int i=0; i< s; i++)
		m_elem[i] = v;
	return m_elem;
}
template <class T>CVector<T>::CVector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
{
	init(c, s, v);
}
template <class T>CVector<T>::CVector(T const*A, Rank n)
{
	init(n,0,0);
	copyfrom(A, 0, n);
}
template <class T>CVector<T>::CVector(T const*A, Rank lo, Rank hi)
{
	init(hi-lo+1,0,0);
	copyfrom(A, lo, hi);
}
template <class T>CVector<T>::CVector(CVector<T> const& V)
{
	init(V.m_capacity, 0, 0);
	copyfrom(V.m_elem, 0, V.m_size);
}
template <class T>CVector<T>::CVector(CVector<T> const& V, int lo, int hi)
{
	init(hi - lo + 1, 0, 0);
	copyfrom(V.m_elem, lo, hi);
}
//析构函数
template <class T>CVector<T>::~CVector()
{
	m_size = 0;
	m_capacity = 0;
	delete[] m_elem;
	m_elem = NULL;
}
//只读访问接口
template <class T>Rank CVector<T>::size()const
{
	return m_size;
}
template <class T>bool CVector<T>::empty()const
{
	return !m_size;
}
template <class T>bool CVector<T>::disordered()const
{
	bool ordered = true;
	for (int i = 1; i < m_size; i++)
		if (m_elem[i - 1] > m_elem[i]) ordered = false;
	return ordered;
}
template <class T>Rank CVector<T>::find(T const& e)
{
	return find(e, 0, m_size);

}
template <class T>Rank CVector<T>::find(T const&e, Rank lo, Rank hi)
{
	while ((lo < hi--) && (e != m_elem[hi]));
	return hi;
}
template <class T>Rank CVector<T>::search(T const&e,BINORFIB n)
{
	return search(e, 0, m_size,n);
}
template <class T>Rank CVector<T>::search(T const&e, Rank lo, Rank hi,BINORFIB n)
{
	switch (n)
	{
	case BIN:
		return binsearch(e, lo, hi);
		break; 
	case FIB:
		return fibsearch(e, lo, hi);
		break;
	}
}
template <class T>Rank CVector<T>::fibsearch(T const& e, Rank lo, Rank hi)
{
	CFib *fib = new CFib(hi - lo);
	while (lo < hi)
	{
		while (hi - lo < fib->get()) fib->prev();
		Rank mi = lo + fib->get() - 1;//<hi-1
		if (e < m_elem[mi]) hi = mi;
		else if (e > m_elem[mi]) lo = mi + 1;
		else return mi;
	}
	delete[] fib;
	fib = NULL;
}
template <class T>Rank CVector<T>::binsearch(T const&e, Rank lo, Rank hi)
{
	while (lo<hi)
	{
		Rank mi = (lo + hi) >> 1;
		(e < m_elem[mi]) ? hi = mi : lo = mi + 1;
	}
	return --lo;
}
template <class T>T& CVector<T>::operator[](Rank r)const
{
	return m_elem[r];
}
//可写访问接口
template <class T>CVector<T>& CVector<T>::operator = (CVector<T> const& V)
{
	if (m_elem) delete[] m_elem;
	copyfrom(V, 0, V.size());
	return *this;
}
template <class T>int CVector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi)return 0;
	for (; hi < m_size; m_elem[lo++] = m_elem[hi++]);
	m_size = lo;
	shrink();
	return hi - lo;
}
template <class T>T CVector<T>::remove(Rank r)
{
	T e = m_elem[r];
	remove(r, r + 1);
	return e;
}
template <class T>Rank CVector<T>::insert(Rank r, T const& e)
{
	m_size++;
	expand();
	for (int i = m_size-1; i > r; i--) 
		m_elem[i] = m_elem[i - 1];
	m_elem[r] = e;
	return r;
}
template <class T>Rank CVector<T>::insertAsF(T const&e)
{
	return insert(0, e);
}
template <class T>Rank CVector<T>::insertAsL(T const&e)
{
	return insert(m_size, e);
}
template <class T>SORT CVector<T>::sort(Rank lo, Rank hi, SORT s)
{
	switch (s)
	{
	case BUBBLE:
		bubblesort(lo, hi); break;
	case QUICK:
		quicksort(lo, hi); break;
	case SELECTION:
		selectionsort(lo, hi); break;
	case MERGE:
		mergesort(lo, hi); break;
	}
	return s;
}
template <class T>SORT CVector<T>::sort(SORT s)
{
	sort(0, m_size, s);
	return s;
}
template <class T>void CVector<T>::unsort(Rank lo,Rank hi)
{
	T* V = m_elem + lo;
	for (Rank i = hi - lo; i > 0; i--)
		swap(V[i - 1], V[rand() & i]);
}
template <class T>void CVector<T>::unsort()
{
	unsort(0, m_size);
}
template <class T>int CVector<T>::deduplicate()
{
	int m_oldsize = m_size;
	Rank i = 1;
	while (i < m_size)
		(find(m_elem[i], 0, i)<0) ? i++ : remove(i);
	return m_oldsize - m_size;
}
template <class T>int CVector<T>::uniquify()
{
	Rank i = 0, j = 0;
	while (++j < m_size)
	{
		if (m_elem[i] != m_elem[j])
			m_elem[++i] = m_elem[j];
	}
	m_size = i+1;
	shrink();
	return j - i;
}
//遍历
template <class T>void CVector<T>::traverse(void(*visit)(T&))
{
	for (int i = 0; i < m_size; i++)visit(m_elem[i]);
}
template <class T>template <class VST>void CVector<T>::traverse(VST& visit)
{
	for (int i = 0; i < m_size; i++)visit(m_elem[i]);
}
#endif