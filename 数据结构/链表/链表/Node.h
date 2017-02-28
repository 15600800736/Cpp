#pragma once

#define NULL 0;
#define LNodePos(T) CLNode<T>*
typedef int Rank;

template<class T>class CLNode
{
	T data;
	LNodePos(T) pre;
	LNodePos(T) suc;
	CLNode(){};
	CLNode(T d, LNodePos(T) p = NULL, LNodePos(T) s = NULL) :data(d), pre(p), suc(s){};
	LNodePos(T) insertaspre(T const& d);
	LNodePos(T) insertassuc(T const& d);
};
