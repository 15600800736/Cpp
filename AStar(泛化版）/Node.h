


//Node.h

/*
*
*	A class that abstracts data structure-Node.
*	Node is implemented by std::set at bottom.
*	Node has three members G,H,F to represent the cost of moving from one to another.
*	Node's iterator is an repackaging set's iterator which redefine operator* and -> 
*	to make the set<Node*>::iterator act as set<Node>::iterator
*	Node is only identificated by member-_order,
*	which means that a node equals another one only when they have same order.
*	Node's data is used for restoring extra data.
*
*/
#ifndef NODE_H
#define NODE_H

#include <set>
#include <stack>
#include <algorithm>
#include <stddef.h>
#include <string>

#include "NodeIterator.h"
#include "Coord.h"
namespace huger
{
template<typename T>
class NodeFactory;
template<typename T>
class Node
{
public:
	typedef int distanceType;
	typedef typename T valueType;
	typedef typename T* pointerType;
	typedef typename T& referenceType;

	typedef typename std::set<Node*>::iterator localIterator;
	typedef typename std::set<Node*>::reverse_iterator reverseLocalIterator;
	typedef typename NodeIterator<Node, localIterator> iterator;
	typedef typename NodeIterator<Node, reverseLocalIterator> reverseIterator;


	////////////////////////////////////////////////////////////////////////
	//	-Node's copy constructor
	//	-assigned by the other node
	//	@parameter otherNode - the source
	Node(const Node& otherNode)
	{
		_order = otherNode._order;
		_coord = otherNode._coord;
		_data = otherNode._data;
		_neighbor.clear();
		_neighbor = otherNode._neighbor;
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
		return _neighbor.begin();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return node's end for iterator
	inline localIterator end()
	{
		return _neighbor.end();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return node's last element for reverse_iterator
	inline reverseLocalIterator rbegin()
	{
		return _neighbor.rbegin();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return node's end for reverse_iterator
	inline reverseLocalIterator rend()
	{
		return _neighbor.rend();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-get parent
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
	//	-get coord
	inline Coord getCoord()const
	{
		return _coord;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-set Coord
	inline void setCoord(Coord coord)
	{
		_coord = coord;
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
	inline void connectTo(Node& otherNode)
	{
		_neighbor.insert(&otherNode);
	}
	/////////////////////////////////////////////////////////////////////////
	//	-cut the connection with an neighbor unilateral
	//	@parameter neighbor - the neighbor to cut with
	inline void cutTo(Node& neighbor)
	{
		_neighbor.erase(&neighbor);
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
		_g = abs(start._coord.X - _coord.X) + abs(start._coord.Y - _coord.Y);
	}
	/////////////////////////////////////////////////////////////////////////
	//	-caculate the h value
	//	@parameter start - the node which you come from
	//	@parameter parent - the node which you are going to
	inline void caculateH(Node& start, Node& destination)
	{
		Coord vecStartToCurrent(_coord - start._coord);
		Coord vecStartToDestination(destination._coord - start._coord);
		_h = abs(destination._coord.X - _coord.X) + abs(destination._coord.Y - _coord.Y) + vecStartToCurrent.cross(vecStartToDestination);
	}
	/////////////////////////////////////////////////////////////////////////
	//	-get the f value
	//	-with different algorithm of combinning g and h
	inline void caculateF()
	{
		_f = _g + 5 * _h;
	}

	friend class NodeFactory < T > ;
	//fields
protected:
	int _order;
	std::set<Node*> _neighbor;
	valueType _data;
	int _g;
	int _h;
	int _f;
	Node* _parent;
	Coord _coord;
private:
	///////////////////////////////////////////////////////////////////////
	//	-Node's contructor
	//	-create an node with empty neighbor
	//	@parameter order - the only identifaction of node
	//	@parameter coord - the abstract of position
	//	@parameter data - extra data of the node
	//	@parameter g,h - cost of moving
	//	@parameter parent - the node when it takes backward
	Node(int order,
		Coord coord,
		valueType data = NULL,
		Node* parent = NULL) :
		_order(order),
		_coord(coord),
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
	*	Node factory to create nodes with insurance order
	*	Make sure that different nodes has different order
	*
	*/
template<typename T>
class NodeFactory
{
public:
	///////////////////////////////////////////////////////////////////////////////////
	//	-constructor
	//	@paramater startFrom - the minimum order of this factor's nodes
	NodeFactory(int startFrom = 0)
	{
		_availiableOrder.push(startFrom);
	}
	virtual ~NodeFactory()
	{
	}
	///////////////////////////////////////////////////////////////////////////////////
	//	-Creat a node in heap
	//	-destruct with function NodeFactor<T>::destruct
	Node<T>* createNodeInHeap(
		Coord coord,
		typename Node<T>::valueType data = NULL,
		Node<T>* parent = NULL)
	{
		if (_availiableOrder.size() == 1)
		{
			Node<int>* node = new Node<int>(_availiableOrder.top(), coord);
			int tmp = _availiableOrder.top();
			_availiableOrder.pop();
			_availiableOrder.push(++tmp);
			return node;
		}
		else
		{
			Node<int>* node = new Node<int>(_availiableOrder.top(), coord);
			_availiableOrder.pop();
			return node;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
	//	-Creat a node in stack
	Node<T> createNodeInStack(
		Coord coord,
		typename Node<T>::valueType data = NULL,
		Node<T>* parent = NULL)
	{
		if (_availiableOrder.size() == 1)
		{
			Node<int> node(_availiableOrder.top(), coord);
			int tmp = _availiableOrder.top();
			_availiableOrder.pop();
			_availiableOrder.push(++tmp);
			return node;
		}
		else
		{
			Node<int> node(_availiableOrder.top(), coord);
			_availiableOrder.pop();
			return node;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////
	//	-Destruct a node in stack
	//	-record the order
	void destruct(Node<T>* node)
	{
		_availiableOrder.push(node->order());
		node->~Node();
	}
private:
	std::stack<int> _availiableOrder;
};

///////////////////////////////////////////////////////////////////////////////////////
//	`-connet two nodes with each other
//	@parameter firstNode - the first node to connect
//	@paramater secondNode - the second node to connect
template<typename T>void connectWith(Node<T>& firstNode, Node<T>& secondNode)
{
	if ((&firstNode) != NULL && (&secondNode) != NULL)
	{
		firstNode.connectTo(secondNode);
		secondNode.connectTo(firstNode);
	}
}
///////////////////////////////////////////////////////////////////////////////////////
//	`-seperate two nodes
//	@parameter firstNode - the first node to cut
//	@paramater secondNode - the second node to cut
template<typename T>void cutWith(Node<T>& firstNode, Node<T>& secondNode)
{
	if ((&firstNode) != NULL && (&secondNode) != NULL)
	{
		firstNode.cutTo(secondNode);
		secondNode.cutTo(firstNode);
	}
}
}
#endif
