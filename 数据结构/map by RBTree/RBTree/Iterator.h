
//µü´úÆ÷

//Iterator.h

//--------------

#pragma once
#include "Defination.h"
#include "RBNode.h"
//Declare
//CMapIterator
template<class K,class D>class CMapIterator
{
public:
	//constructor
	CMapIterator(){}//empty iterator
	CMapIterator(Node(K, D) n) :m_node(n){}
	CMapIterator(const CMapIterator<K, D>& it){ m_node = *it; }

	/*~virtual CMapIterator();*/
	//Only Read Interface
	Node(K, D) GetNode()const{ return m_node; }

	//Written
	void SetNode(Node(K, D) node){ m_node = node; }

	//operator overloading
	Node(K,D) operator*()const;
	bool operator==(const CMapIterator<K, D> it) { return m_node == *it; }
	bool operator!=(const CMapIterator<K, D> it){ return !(*this == it); }
	CMapIterator<K,D> operator++();
	CMapIterator<K,D> operator++(int);
	CMapIterator<K,D> operator--();
	CMapIterator<K,D> operator--(int);
	Node(K,D) operator[](K);//visit by []

protected:
	Node(K,D) m_node;
};

//Def
template<class K,class D>
Node(K,D) CMapIterator<K, D>::operator*()const
{
	return m_node;
}
template<class K,class D>
CMapIterator<K,D> CMapIterator<K, D>::operator++()
{
	Node(K, D) tmpnode = m_node;
	m_node = m_node->GetSucc();
	if (!m_node)m_node = tmpnode;
	return *this;
}
template<class K,class D>
CMapIterator<K,D> CMapIterator<K, D>::operator--()
{
	Node(K, D) tmpnode = m_node;
	m_node = m_node->GetFore();
	if (!m_node)m_node = tmpnode;
	return *this;
}
template<class K,class D>
Node(K, D) CMapIterator<K, D>::operator[](K key)
{
	while (m_node->GetKey() != key)
	{
		Node(K, D) tmpnode = m_node;
		m_node->GetKey() > key ?
			--(*this) :
			++(*this);
		if (m_node == tmpnode)break;
	}
	return m_node;
}//what if the key doesn't exit in the tree and is in the middle of the keys