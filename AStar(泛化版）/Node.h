


//Node.h

#ifndef NODE_H
#define NODE_H

#include <list>
#include <algorithm>
namespace huger
{
template<typename dataType>
struct Node
{
	Node(int order,
		dataType data = NULL,
		std::list<Node> around = NULL,
		int num = 0,
		int f = 0,
		int g = 0,
		int h = 0,
		Node* parent = NULL);
	Node(const Node& otherNode);
	inline bool operator==(const Node& otherNode);
	inline bool operator!=(const Node& otherNode);
	inline bool operator<(const Node& otherNode);
	inline bool operator>(const Node& otherNode);
	int _order;
	dataType _data;
	std::list<Node> _around;
	int _f;
	int _g;
	int _h;
	Node* _parent;
};


//-------------------implements----------------------
template<typename dataType>
Node<dataType>::Node(int order,
	dataType data,
	std::list<Node> around,
	int num,
	int f,
	int g,
	int h,
	Node* parent) :
							_order(order),
							_data(data),
							_around(around),
							_f(f),
							_g(g),
							_h(h),
							_parent(parent)
{
	//do something
}
template<typename dataType>
Node<dataType>::Node(const Node& otherNode)
{
	_order = otherNode._order;
	_data = otherNode._data;
	_around.clear();
	std::copy<typename std::list<Node>::iterator, typename std::list<Node>::iterator>
		(otherNode._around.begin(), otherNode._around.end(),
		_around.begin());
	_f = otherNode._f;
	_g = otherNode._g;
	_h = otherNode._h;
	delete _parent;
	_parent = otherNode._parent;
}
template<typename dataType>
bool Node<dataType>::operator==(const Node& otherNode)
{
	return _order = otherNode._order ? true : false;
}
template<typename dataType>
bool Node<dataType>::operator!=(const Node& otherNode)
{
	return !(*this == otherNode);
}
template<typename dataType>
bool Node<dataType>::operator<(const Node& otherNode)
{
	return _f < otherNode._f ? true : false;
}
template<typename dataType>
bool Node<dataType>::operator>(const Node& otherNode)
{
	return !(*this < otherNode || *this == otherNode);
}
#endif
}