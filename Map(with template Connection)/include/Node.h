


//Node.h

/*
 *
 *	A class that abstracts value structure-Node.
 *	Node is implemented by std::map at bottom with the pointer of node as key, node's connection as value
 *	and sort by node's order
 *	Node has three members G,H,F to represent the cost of moving from one to another.
 *	Node is only identificated by member-_order with overloding operator==
 *	which means that a node equals another one only when they have same order
 *	you can connect or cut to another node with any equal-order-node
 *	for order controlling,the constructor of node has been declared in private fields and customs can't create a node directly
 *	but a factory is provided to create a node ( see factory doc in details)
 *	Node's value is used for restoring extra value.
 *
 */
#ifndef NODE_H
#define NODE_H

#include <map>
#include <vector>
#include <algorithm>
#include <stddef.h>
#include <string>
#include "SimpleRelation.h"
#include "Coord.h"
namespace graphic
{
template<typename NodeType>
class NodeFactory;
template<typename nodeType>
class NodeCopmareByOrder;
template<typename T,typename Connection = SimpleRelation>
class Node
{
public:
	typedef typename T valueType;
	typedef typename T* pointerType;
	typedef typename T& referenceType;

	typedef typename std::map<Node*,Connection*>::iterator iterator;
	typedef typename std::map<Node*,Connection*>::reverse_iterator reverseIterator;

	typedef typename Connection connectionType;
	typedef typename NodeFactory<Node<T,Connection> > factory;
	////////////////////////////////////////////////////////////////////////
	//	-create an empty node with nothing in it
	Node()
	{ }
	////////////////////////////////////////////////////////////////////////
	//	-Node's copy constructor
	//	-assigned by the other node
	//	@parameter otherNode - the source
	Node(const Node& otherNode)
	{
		_order = otherNode._order;
		_inDegree = otherNode._inDegree;
		_coord = otherNode._coord;
		_value = otherNode._value;
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
	//	-as the convention,if a node's order equals another
	//	-you can connect or cut connection with any one of them
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
	//	-return reference for value
	//	-convenience for reading and writing
	inline valueType& value()
	{
		return _value;
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
	//	-get how many nodes is connected from this node
	inline int getOutDegree()const
	{
		return _neighbor.size();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-get how many nodes connect to this node
	inline int getInDegree()const
	{
		return _inDegree;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-set how many nodes connect to this node
	//	-it only should be called by it's child class,but how to do it?
	void setInDegree(int inDegree)
	{
		_inDegree = inDegree;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-transfer all of the member's value to string to output
	std::string toString()
	{
		char cResult[128];
		sprintf_s(cResult, "order = %d, value = %d, f = %d, g = %d, h = %d.", _order, _value, _f, _g, _h);
		std::string result = cResult;
		return result;
	}
	//functional

	/////////////////////////////////////////////////////////////////////////
	//	-build the connection unilateral
	//	-which means this node can reach to otherNode,but contrary,can't
	//	@parameter otherNode - the node to connect to
	virtual inline void connectTo(Node& otherNode)
	{
		if (isNeighbor(otherNode) == _neighbor.end())
		{
			Connection* connection = createConnection(abs(otherNode._order - _order));
			_neighbor.insert(std::make_pair(&otherNode, connection));
			otherNode._inDegree++;
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
			delete iter->second;
			_neighbor.erase(iter);
			neighbor._inDegree--;
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
	inline void caculateG(const Node& start)
	{
		_g = abs(start._order - _order) * (abs(start._coord.X - _coord.X) + abs(start._coord.Y - _coord.Y));
	}
	/////////////////////////////////////////////////////////////////////////
	//	-caculate the h value
	//	@parameter start - the node which you come from
	//	@parameter parent - the node which you are going to
	inline void caculateH(const Node& start,const Node& destination)
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
	//	-all Node should implement this interface
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
	//	-if node is the neighbor of this node
	//	-it will return the position in this node's neighbor
	//	-if node isn't the neighbor of this node
	//	-it will return the end
	//	@parameter node - the neighbor
	inline iterator isNeighbor(Node& node)
	{
		iterator iterNode = std::find_if(
			_neighbor.begin(), 
			_neighbor.end(),
			[&](std::pair<Node*,Connection*> pair)
			{
				return pair.first->order() == node.order();
			}
		);
		return iterNode;
	}
	/////////////////////////////////////////////////////////////////////////
	//	-clear all connection to other node
	inline void clear()
	{
		_neighbor.clear();
	}
	/////////////////////////////////////////////////////////////////////////
	//	-get the connection of this node to a neighbor
	//	-if the neighbor isn't a really neighbor
	//	-it will return NULL
	//	@parameter neighbor - the neighbor
	inline Connection* getConnection(Node& neighbor)
	{
		Connection* connection = NULL;
		iterator iter = isNeighbor(neighbor);
		if (iter != _neighbor.end())
		{
			connection = iter->second;
		}
		return connection;
	}
	friend class NodeFactory<Node<T,Connection> >;
	//fields
protected:
	Connection* createConnection(int cost)
	{
		Connection* connection = new Connection();
		connection->setDistance(cost);
		return connection;
	}

	int _order;
	int _inDegree;
	std::map < Node*, Connection*,NodeCopmareByOrder<Node*> > _neighbor;
	valueType _value;
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
	//	@parameter value - extra value of the node
	//	@parameter g,h - cost of moving
	//	@parameter parent - the node when it takes backward
	Node(int order,
		Coord coord,
		valueType value = NULL,
		Node* parent = NULL) :
		_order(order),
		_inDegree(0),
		_coord(coord),
		_value(value),
		_g(0),
		_h(0),
		_f(0),
		_parent(parent)
	{
	}
};
template<typename nodeType>
class NodeCopmareByOrder
{
public:
	bool operator()(const nodeType& first, const nodeType& second)
	{
		return first->order() < second->order();
	}
};

}
#endif
