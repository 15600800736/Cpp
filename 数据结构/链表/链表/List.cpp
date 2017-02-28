#pragma once
#include "List.h"

template<class T>int CList<T>::copyfrom(T const* A, int lo, int hi)
{
	while (lo < hi)
	{
		insertasfirst(A[hi - 1]);
		hi--;
	}
	return 0;
}
template<class T>void CList<T>::init()
{
	header = new CLNode<T>();
	tailer = new CLNode<T>();
	m_size = 0;
}
template<class T>int CList<T>::clear()
{
	while (m_size > 0)
	{
		remove(first());
	}
	m_size = 0;
	delete header;
	delete tailer;
	return 0;
}
template<class T>void CList<T>::merge(LNodePos(T) x, int p, CList<T> L, LNodePos(T) y, int q)
{
	LNodePos(T) temp = x;

}