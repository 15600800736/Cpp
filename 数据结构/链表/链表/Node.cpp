#pragma once
#include "Node.h"

template<class T>LNodePos(T) CLNode<T>::insertaspre(T const& d)
{
	LNodePos(T) x = new CLNode<T>(d, pre, this);
	pre->suc = x;
	this->pre = x;
	return x;
}
template<class T>LNodePos(T) CLNode<T>::insertassuc(T const& d)
{
	LNodePos(T) x = new CLNode<T>(d, this, suc);
	suc->pre = x;
	this->suc = x;
	return x;
}