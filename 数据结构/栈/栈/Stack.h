#pragma once
#include "..\����\CVector.cpp"
#include "..\����\typedef.h"
template <class T>class CStack : public CVector<T>
{
public:
	void push(T const&e){  insert(size(), e); }
	T pop(){ return remove(size() - 1); }
	T& top(){ return (*this)[size() - 1]; }
};
