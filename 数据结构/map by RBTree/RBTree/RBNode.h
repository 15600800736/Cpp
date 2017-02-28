
//红黑树节点类

//RBNode.h

//-----------



//precompile area
#pragma once

#include <stdio.h>
#include "Defination.h"
#include <iostream>
template<class F,class S>

//Declare class
//CPair
//It's a data structure with two members to combine two different type variables
class CPair
{
public:
	CPair(){};
	CPair(F f, S s) :first(f), second(s){}
	CPair(const CPair<F, S>& pair)
	{
		first = pair.first;
		second = pair.second;
	}
	~CPair(){};
	F first;
	S second;
};

//Declare class
//CRBNode
//RBNode is the node of the RBTree
//It has the only read interface to get the information of node
//and the written interface to change the information of node
//It's the basic unit of rbtree

//problem:what do we get parent from the empty node?Or should we?
template<class K, class D>class CRBNode
{
public:
	//Read Only
	inline void OutPut()const
	{
		if (this)
			std::cout << "关键码		" << m_node.first << std::endl << "数据		" << m_node.second << std::endl
			<< "父亲		" << m_parent << std::endl << "左孩子		" << m_lc << std::endl << "右孩子	" << m_rc << std::endl
			<< "颜色	" << ((m_color == 0) ? "红色" : "黑色") << std::endl << "高度	" << m_height << std::endl << "规模	" << m_size << std::endl;
		else
			cout << "该节点不存在" << endl;
	}
	inline CPair<K, D> GetNode()const
	{
		if (this)
			return m_node;
	}
	inline K GetKey()const
	{ 
		if (this)
			return m_node.first;
		else
			return NULL;
	}
	inline D GetData()const
	{ 
		if (this)
			return m_node.second;
		else
			return NULL;
	}
	inline Node(K,D) GetLC()const
	{ 
		if (this)
			return m_lc;
		else
			return NULL;
	}
	inline Node(K, D)GetRC()const
	{
		if (this)
			return m_rc;
		else
			return NULL;
	}
	inline Node(K, D)GetParent()const
	{ 
			return m_parent; 
	}
	inline Color GetColor()const
	{ 
		if (this)
			return m_color;
		else
			return Black;//regard null as black
	}
	inline int GetHeight()const
	{ 
		if (this)
			return m_height;
		else
			return 0;
	}
	inline unsigned int GetSize()const
	{ 
		if (this)
			return m_size;
		else
			return 0;
	}
	Node(K,D) GetSucc();
	Node(K, D) GetFore();

	//Written
	inline void SetKey(K k){ m_node.first = k; }
	inline void SetData(D d){ m_node.second = d; }
	inline void SetLC(Node(K, D) l)
	{
		m_lc = l;
	}
	inline void SetRC(Node(K, D) r)
	{
		m_rc = r;
	}
	inline void SetParent(Node(K, D) p)
	{
		m_parent = p;
	}
	inline void SetColor(Color c)
	{
		m_color = c;
	}
	inline bool SetHeight(int h)
	{
		if (h > -2)
		{
			m_height = h;
			return true;
		}
		return false;
	}
	inline void SetSize(int s){ m_size = s; }


	//constructor

	//Create a new empty node with all members default variables
	CRBNode():m_node(NULL),m_parent(NULL),m_color(0),m_lc(NULL),m_rc(NULL)
						m_height(0),m_size(0){}

	//Create a new node with a pair contained key and data
	//the other members define as default value
	//the height of node is defined depend on the color of the node and its left child and right child
	explicit CRBNode(CPair<K, D> n, Node(K, D) p = NULL, Color c = Red,Node(K, D) l = NULL, Node(K, D) r = NULL ) :
		m_node(n), 
		m_lc(l), 
		m_rc(r), 
		m_parent(p), 
		m_color(c), 
		m_height(0),
		m_size(1){}

	//Create a new node with the certain key and data
	//the other members define as default value
	//the height of node is defined depend on the color of the node and its left child and right child
	explicit CRBNode(K k,D d, Node(K, D) p = NULL, Color c = Red, Node(K, D) l = NULL, Node(K, D) r = NULL) :
		m_node(k,d),
		m_lc(l),
		m_rc(r),
		m_parent(p),
		m_color(c),
		m_height(0),
		m_size(1){}
	
	//copy constructor
	//It just simply make this object's member equals the other one
	CRBNode(const CRBNode<K, D>& node)
	{
		m_color = node.GetColor();
		m_height = node.GetHeight();
		m_lc = node.GetLC();
		m_rc = node.GetRC();
		m_node = node.GetNode();
		m_parent = node.GetParent();
		m_size = node.GetSize();
	}

	//destroyed consturctor
	//to clear all the members
	virtual ~CRBNode()
	{
		m_node.first = NULL;
		m_node.second = NULL;
		m_parent = NULL;
		m_lc = NULL;
		m_rc = NULL;
		m_height = 0;
		m_size = 0;
	}
protected:
	CPair<K,D> m_node;
	Node(K, D) m_parent;
	Color m_color;
	Node(K, D) m_lc;
	Node(K, D) m_rc;
	//height of black
	int m_height;
	//the number of nodes below this one,it equals the sum of left child and right child
	unsigned int m_size;
};

//Define functions area
template<class K,class D>
Node(K, D) CRBNode<K, D>::GetSucc()
{ 
	Node(K, D) succ = NULL;
	if (HAVERC(this))
	{
		succ = this->GetRC();//turn to RC
		while (HAVELC(succ))
		{
			succ = succ->GetLC();
		}//turn to the most left node in the right tree
	}	
	else
	{
		if (ISLC(this)) succ = this->GetParent();
		else
		{
			succ = this;
			while (ISRC(succ))
				succ = succ->GetParent();
			succ = succ->GetParent();
		}
	}
	return succ;
}
template<class K,class D>
Node(K, D) CRBNode<K, D>::GetFore()
{
	Node(K, D) fore = NULL;
	if (HAVELC(this))
	{
		fore = this->GetLC();
		while (HAVERC(fore))
			fore = fore->GetRC();
	}
	else
	{
		if (ISRC(this)) fore = this->GetParent();
		else
		{
			fore = this;
			while (ISLC(fore)) fore = fore->GetParent();
			fore = fore->GetParent();
		}
	}
	return fore;
}