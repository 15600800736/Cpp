


//Node.h

#ifndef NODE_H
#define NODE_H

#include <list>
#include <algorithm>
#include <stddef.h>
#include "NodeIterator.h"
namespace huger
{
template<typename T>
class Node
{
public:
	typedef int orderType;
	typedef int distanceType;
	typedef typename T valueType;
	typedef typename T* pointerType;
	typedef typename T& referenceType;

	typedef typename std::list<Node*>::iterator localIterator;
	typedef typename NodeIterator<Node> iterator;
	//-----constructor
	Node(int order,
		std::list<Node*> around,
		valueType data = NULL,
		int f = 0,
		int g = 0,
		int h = 0,
		Node* parent = NULL) :
		_order(order),
		_data(data),
		_around(around),
		_f(f),
		_g(g),
		_h(h),
		_parent(parent)
	{

	}
	Node(const Node& otherNode)
	{
		_order = otherNode._order;
		_data = otherNode._data;
		_around.clear();
		std::copy<typename std::list<Node>::const_iterator, typename std::list<Node>::iterator>
			(otherNode._around.begin(), otherNode._around.end(),
			_around.begin());
		_f = otherNode._f;
		_g = otherNode._g;
		_h = otherNode._h;
		delete _parent;
		_parent = otherNode._parent,
	}
	~Node()
	{
		delete
	}
	//-----operator overloading
	inline bool operator==(const Node& otherNode)
	{
		return _order == otherNode._order ? true : false;
	}
	inline bool operator!=(const Node& otherNode)
	{
		return !(*this == otherNode);
	}
	inline bool operator<(const Node& otherNode)
	{
		return _f < otherNode._f ? true : false;
	}
	inline bool operator>(const Node& otherNode)
	{
		return !(*this < otherNode || *this == otherNode);
	}
	//I/O interface
	inline localIterator begin()
	{
		return _around.begin();
	}
	inline localIterator end()
	{
		return _around.end();
	}
	inline Node* getParent()const
	{
		return _parent;
	}
	inline void setParent(Node* parent)
	{
		_parent = parent;
	}
	inline orderType& order()
	{
		return _order;
	}
	inline valueType& data()
	{
		return _data;
	}
	inline int& F()
	{
		return _f;
	}
	inline int& G()
	{
		return _g;
	}
	inline int& H()
	{
		return _h;
	}
	//functional
	inline void connectTo(Node* otherNode)
	{
		_around.push_back(otherNode);
	}
	inline void connectWith(Node* otherNode)
	{
		connectTo(otherNode);
		otherNode->connectTo(this);
	}
	//fields


protected:
	orderType _order;
	std::list<Node*> _around;
	valueType _data;
	int _f;
	int _g;
	int _h;
	Node* _parent;
};
}
#endif