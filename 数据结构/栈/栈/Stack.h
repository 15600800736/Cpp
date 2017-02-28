#pragma once
#include "..\向量\CVector.cpp"
#include "..\向量\typedef.h"
template <class T>class CStack : public CVector<T>
{
public:
	void push(T const&e){  insert(size(), e); }
	T pop(){ return remove(size() - 1); }
	T& top(){ return (*this)[size() - 1]; }
};
