#pragma once
#include "pre.h"
template <class T>class CBinNode
{
protected:
	BinNodeRe(T) parent;
	BinNodeRe(T) lc;
	BinNodeRe(T) rc;
	T data;
	int npl;
	int height;
	BColor color;
public:
	CBinNode() :parent(NULL), lc(NULL), rc(NULL), data(0), height(0), color(B_RED),npl(1){}
	CBinNode(T e ,BinNodeRe(T) parent = NULL, BinNodeRe(T) l = NULL, BinNodeRe(T) r = NULL, int h = 0, int n = 1, BColor c = B_RED) :parent(p), lc(l), rc(r), data(e), height(h), npl(n), color(c){}
	BinNodeRe(T) insertasr(T const&);
	BinNodeRe(T) insertasl(T const&);
	int size();
	BinNodeRe(T) after();
	template<class VST>void travlevel(VST&);
	template<class VST>void travpre(VST&);
	template<class VST>void travpos(VST&);
	bool operator==(BinNodeRe(T) const&);
	bool operator<(BinNodeRe(T) const&);
	bool operator>(BinNodeRe(T) const&);
	bool operator<=(BinNodeRe(T) const&);
	bool operator>=(BinNodeRe(T)const&);
};