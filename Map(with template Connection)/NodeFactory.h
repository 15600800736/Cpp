

#ifndef NODE_FACTORY_H
#define NODE_FACTORY_H
#include "global.h"
#include "Coord.h"
#include <stack>

namespace huger
{
/*
*
*	Node factory to create nodes with insurance order
*	Make sure that different nodes has different order
*
*/
template<typename NodeType>
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
	NodeType* createNodeInHeap(
		Coord coord,
		typename NodeType::valueType data = NULL,
		NodeType* parent = NULL)
	{
		if (_availiableOrder.size() == 1)
		{
			NodeType* node = new NodeType(_availiableOrder.top(), coord);
			int tmp = _availiableOrder.top();
			_availiableOrder.pop();
			_availiableOrder.push(++tmp);
			return node;
		}
		else
		{
			NodeType* node = new NodeType(_availiableOrder.top(), coord);
			_availiableOrder.pop();
			return node;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
	//	-Creat a node in stack
	NodeType createNodeInStack(
		Coord coord,
		typename NodeType::valueType data = NULL,
		NodeType* parent = NULL)
	{
		if (_availiableOrder.size() == 1)
		{
			NodeType node(_availiableOrder.top(), coord);
			int tmp = _availiableOrder.top();
			_availiableOrder.pop();
			_availiableOrder.push(++tmp);
			return node;
		}
		else
		{
			NodeType node(_availiableOrder.top(), coord);
			_availiableOrder.pop();
			return node;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////
	//	-Destruct a node in stack
	//	-record the order
	void destruct(NodeType* node)
	{
		_availiableOrder.push(node->order());
		node->~Node();
	}
private:
	std::stack<int> _availiableOrder;
};
}
#endif
