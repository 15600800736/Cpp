


//Node.h

/*
 *
 *	A class that abstracts data structure-Node.
 *	Node is implemented by std::list at bottom.
 *	Node has three members G,H,F to represent the cost of moving from one to another.
 *	Node's iterator is an repackaging list's iterator which redefine operator* and -> 
 *	to make the list<Node*>::iterator act as list<Node>::iterator
 *	Node is only identificated by member-_order,
 *	which means that a node equals another one only when they have same order.
 *	Node's data is used for restoring extra data.
 *
 */
#ifndef NODE_H
#define NODE_H

#include <list>
#include <queue>
#include <algorithm>
#include <stddef.h>
#include <string>

#include "NodeIterator.h"
namespace huger
{
template<typename T>
class NodeFactor;
template<typename T>
class Node
{
public:
	typedef int distanceType;
	typedef typename T valueType;
	typedef typename T* pointerType;
	typedef typename T& referenceType;

	typedef typename std::list<Node*>::iterator localIterator;
	typedef typename std::list<Node*>::reverse_iterator reverseLocalIterator;
	typedef typename NodeIterator<Node,localIterator> iterator;
	typedef typename NodeIterator<Node, reverseLocalIterator> reverseIterator;


	////////////////////////////////////////////////////////////////////////
	//	-Node's copy constructor
	//	-assigned by the other node
	//	@parameter otherNode - the source
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
	////////////////////////////////////////////////////////////////////////
	//	-Node's destructor
	virtual ~Node()
	{
	}
	//-----operator overloading.

	////////////////////////////////////////////////////////////////////////
	//	-overlaoding operator==
	//	-when an node's order equals the other node's order
	//	@parameter otherNode - the source
	inline bool operator==(const Node& otherNode)
	{
		return _order == otherNode._order ? true : false;
	}
	////////////////////////////////////////////////////////////////////////
	//	-overlaoding operator!=
	//	-when an node's order doesn't equal the other node's order
	//	@parameter otherNode - the source
	inline bool operator!=(const Node& otherNode)
	{
		return !(*this == otherNode);
	}
	////////////////////////////////////////////////////////////////////////
	//	-overlaoding operator<
	//	-when an node's order is less than the other node's order
	//	@parameter otherNode - the source
	inline bool operator<(const Node& otherNode)
	{
		return _order < otherNode._order ? true : false;
	}
	////////////////////////////////////////////////////////////////////////
	//	-overlaoding operator>
	//	-when an node's order is bigger than the other node's order
	//	@parameter otherNode - the source
	inline bool operator>(const Node& otherNode)
	{
		return !(*this < otherNode || *this == otherNode);
	}
	//I/O interface

	/////////////////////////////////////////////////////////////////////////
	//	-return node's first element for iterator
	inline localIterator begin()
	{
		return _around.begin();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return node's end for iterator
	inline localIterator end()
	{
		return _around.end();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return node's last element for reverse_iterator
	inline reverseLocalIterator rbegin()
	{
		return _around.rbegin();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return node's end for reverse_iterator
	inline reverseLocalIterator rend()
	{
		return _around.rend();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-get parent.
	inline Node* getParent()const
	{
		return _parent;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-set parent
	//	@parameter otherNode - the source
	inline void setParent(Node* parent)
	{
		_parent = parent;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return reference for order
	//	-convenience for reading and writing
	inline int& order()
	{
		return _order;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return reference for data
	//	-convenience for reading and writing
	inline valueType& data()
	{
		return _data;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return f
	inline int getF()const
	{
		return _f;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return g
	inline int getG()const
	{
		return _g;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return h
	inline int getH()const
	{
		return _h;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-transfer all of the member's value to string to output
	std::string toString()
	{
		char cResult[128];
		sprintf_s(cResult, "order = %d, data = %d, f = %d, g = %d, h = %d.", _order, _data, _f, _g, _h);
		std::string result = cResult;
		return result;
	}
	//functional

	/////////////////////////////////////////////////////////////////////////
	//	-build the connection unilateral
	//	-which means this node can reach to otherNode,but contrary,can't
	//	@parameter otherNode - the node to connect to
	inline void connectTo(Node* otherNode)
	{
		_around.push_back(otherNode);
	}
	/////////////////////////////////////////////////////////////////////////
	//	-build the connection between the two nodes
	//	-you can reach to the other one starting from anyone
	//	@parameter otherNode - the node to connect with
	inline void connectWith(Node* otherNode)
	{
		connectTo(otherNode);
		otherNode->connectTo(this);
	}
	/////////////////////////////////////////////////////////////////////////
	//	-compared another node by F value
	//	-return 0 if equlas,1 if this node bigger than other and -1 for the contrary
	//	@parameter otherNode - source to compare
	inline int compareByF(const Node& otherNode)
	{
		return _f < otherNode._f ? -1 : (_f == otherNode._f ? 0 : 1);
	}
	/////////////////////////////////////////////////////////////////////////
	//	-caculate the g value
	//	@parameter parent - the node which you start from
	inline void caculateG(Node& start)
	{

	}
	/////////////////////////////////////////////////////////////////////////
	//	-caculate the h value
	//	@parameter parent - the node which you are going to
	inline void caculateH(Node& destination)
	{

	}
	/////////////////////////////////////////////////////////////////////////
	//	-get the f value
	//	-with different algorithm of combinning g and h
	inline void caculateF()
	{
		_f = caculateFwithGH();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-caculate the f value
	//	-the algorithm of caculate f with certain g and h
	inline int caculateFwithGH()
	{
		return _g + _h;
	}
	friend class NodeFactor<T>;
	//fields
protected:
	int _order;
	std::list<Node*> _around;
	valueType _data;
	int _g;
	int _h;
	int _f;
	Node* _parent;
private:
	///////////////////////////////////////////////////////////////////////
	//	-Node's contructor
	//	-create an node with empty neighbor
	//	@parameter order - the only identifaction of node
	//	@parameter data - extra data of the node
	//	@parameter g,h - cost of moving
	//	@parameter parent - the node when it takes backward
	Node(int order,
		valueType data = NULL,
		Node* parent = NULL) :
		_order(order),
		_data(data),
		_g(0),
		_h(0),
		_f(0),
		_parent(parent)
	{
	}
};

/*
 *
 *	Node factory to creato nodes with insurance order
 *	Make sure that different nodes has different order
 *
 */
template<typename T>
class NodeFactor
{
public:
	///////////////////////////////////////////////////////////////////////////////////
	//	-Creat a node in heap
	//	-destruct with function NodeFactor<T>::destruct
	static Node<T>* createNodeInHeap(
		typename Node<T>::valueType data = NULL,
		Node<T>* parent = NULL)
	{
		if (_availiableOrder->empty())
		{
			return new Node<T>(_order++, data, parent);
		}
		else
		{
			int order = _availiableOrder->front();
			_availiableOrder->pop();
			return new Node<T>(order, data, parent);
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
	//	-Creat a node in stack
	static Node<T> createNodeInStack(
		typename Node<T>::valueType data = NULL,
		Node<T>* parent = NULL)
	{
		if (_availiableOrder->empty())
		{
			Node<T> node(_order++, data, parent);
			return node;
		}
		else
		{
			int order = _availiableOrder->front();
			_availiableOrder->pop();
			Node<T> node(order, data, parent);
			return node;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
	//	-Destruct a node in stack
	//	-record the order
	static void destruct(Node<T>* node)
	{
		_availiableOrder->push(node->order());
		node->~Node();
	}
private:
	static int _order;
	static std::queue<int>* _availiableOrder;
};
template<typename T>
int NodeFactor<T>::_order = 0;
template<typename T>
std::queue<int>*  NodeFactor<T>::_availiableOrder  = new std::queue<int>();
}
#endif
