
#pragma once

#define NodePos(T) CNode<T>*
#define NULL 0
template<class T>class CNode
{
public:
	CNode(T d= NULL, NodePos(T) p = NULL, NodePos(T) lc = NULL, NodePos(T) rc = NULL,int h =0,int s = 1) :m_data(d), m_parent(p), m_lc(lc), m_rc(rc),m_height(h),m_size(s){};
	virtual ~CNode(){};
	//只读
	T GetData()const{ return m_Data; }
	NodePos(T) GetParent()const{ return m_parent; }
	NodePos(T) GetLc()const{ return m_lc; }
	NodePos(T) GetRc()const{ return m_rc; }
	int GetHeight()const{ return m_height; }
	int GetSize()const{ return m_size; }
	//可写
	inline void SetHeight(int h){ m_height = h; }
	inline void SetSize(int s){ m_size = s; }
	inline void SetLc(NodePos(T) lc){ m_lc = lc; }
	inline void SetRc(NodePos(T) rc){ m_rc = rc; }
	inline void SetParent(NodePos(T) p){ m_parent = p; }
	inline void SetData(T d){ m_data = d; }
private:
	T m_data;
	NodePos(T) m_parent;
	NodePos(T) m_lc;
	NodePos(T) m_rc;
	int m_height;//当前节点的高度
	int m_size;//以当前节点为根的子树规模
};