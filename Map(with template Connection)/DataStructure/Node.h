


//Node.h

/*
*
*	A class that abstracts data structure-Node.
*	Node is implemented by std::map at bottom.
*	Node has three members G,H,F to represent the cost of moving from one to another.
*	Node's iterator is an repackaging map's iterator which redefine operator* and -> 
*	to make the map<Node*,Connection>::iterator act as set<Node>::iterator
*	Node is only identificated by member-_order,
*	which means that a node equals another one only when they have same order.
*	Node's data is used for restoring extra data.
*
*/
#ifndef NODE_H
#define NODE_H

#include <map>
#include <vector>
#include <algorithm>
#include <stddef.h>
#include <string>
#include "Connection.h"
#include "Coord.h"
namespace map
{
template<typename NodeType>
class NodeFactory;
template<typename T,typename Connection = Connection>
class Node
{
public:
	typedef typename T valueType;
	typedef typename T* pointerType;
	typedef typename T& referenceType;

	typedef typename std::map<Node*,Connection>::iterator iterator;
	typedef typename std::map<Node*,Connection>::reverse_iterator reverseIterator;

	typedef typename Connection connectionType;
	typedef typename NodeFactory<Node<T,Connection> > factory;
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
	inline iterator begin()
	{
		return _neighbor.begin();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return node's end for iterator
	inline iterator end()
	{
		return _neighbor.end();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return node's last element for reverse_iterator
	inline reverseIterator rbegin()
	{
		return _neighbor.rbegin();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-return node's end for reverse_iterator
	inline reverseIterator rend()
	{
		return _neighbor.rend();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-get parent
	inline Node getParent()const
	{
		return *_parent;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-map parent
	//	@parameter otherNode - the source
	inline void setParent(Node parent)
	{
		_parent = new Node(parent);
	}
	/////////////////////////////////////////////////////////////////////////
	//	-get coord
	inline Coord getCoord()const
	{
		return _coord;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-map Coord
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
	//	@parameter connection - the connection provided
	//	@parameter otherNode - the node to connect to
	inline void connectTo(Node& otherNode)
	{
		if (isNeighbor(otherNode) == _neighbor.end())
		{
			Connection connection = createConnection(otherNode);
			_neighbor.insert(std::make_pair(&otherNode, connection));
		}
	}
	/////////////////////////////////////////////////////////////////////////
	//	-cut the connection with an neighbor unilateral
	//	@parameter neighbor - the neighbor to cut with
	inline void cutTo(Node& neighbor)
	{
		iterator iter = isNeighbor(neighbor);
		if (iter != _neighbor.end())
		{
			_neighbor.erase(iter);
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////
	//	-Compare another node according value F
	//	-if this < other ,return -1
	//	-if this == other,return 0
	//	-if this > other,return 1
	//	@parameter otherNode -  the other node to compare
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
	/////////////////////////////////////////////////////////////////////////
	//	-get all node connected with this node
	//	-and restore them in vector
	// -all Node should implement this interface
	inline std::vector<Node> getNeighbor()
	{
		std::vector<Node> neighbor;
		for (iterator iter = _neighbor.begin();
			iter != _neighbor.end();
			iter++)
		{
			neighbor.push_back(*(iter->first));
		}
		return neighbor;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-get if a node is the neighbor of this node
	//	@parameter node - the neighbor
	inline iterator isNeighbor(Node node)
	{
		iterator iterNode = std::find_if(
			_neighbor.begin(), 
			_neighbor.end(),
			[&](std::pair<Node*,Connection> pair)
			{
				return pair.first->order() == node.order();
			}
		);
		return iterNode;
	}
	friend class NodeFactory<Node<T,Connection> >;
	//fields
protected:
	/////////////////////////////////////////////////////////////////////////
	Connection createConnection(Node<T, Connection>& otherNode)
	{
		otherNode.caculateG(*this);
		Connection connection(otherNode.getG());
		return connection;
	}

	int _order;
	std::map<Node*,Connection> _neighbor;
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



}
#endif
