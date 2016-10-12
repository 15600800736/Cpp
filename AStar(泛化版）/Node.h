


//Node.h

#ifndef NODE_H
#define NODE_H

#include <list>
#include <algorithm>
#include <stddef.h>
#include "NodeIterator.h"
#include <string>
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
		valueType data = NULL,
		int f = 0,
		int g = 0,
		int h = 0,
		Node* parent = NULL) :
		_order(order),
		_data(data),
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
		_around = otherNode._around;
		_f = otherNode._f;
		_g = otherNode._g;
		_h = otherNode._h;
		_parent = otherNode._parent;
	}
	~Node()
	{
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
		return _order < otherNode._order ? true : false;
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
	std::string outPutInfo()
	{
		char cResult[128];
		sprintf_s(cResult, "order = %d, data = %d, f = %d, g = %d, h = %d.", _order, _data, _f, _g, _h);
		std::string result = cResult;
		return result;
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
	inline int compareByF(const Node& otherNode)
	{
		return _f < otherNode._f ? -1 : (_f == otherNode._f ? 0 : 1);
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
