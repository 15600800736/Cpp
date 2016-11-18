

#ifndef NODE_FACTORY_H
#define NODE_FACTORY_H
#include "constance.h"
#include "Coord.h"
#include <stack>

namespace graphic
{
/*
 *
 *	Node factory to create nodes with insurance order
 *	Make sure that different nodes has different order
 *	When you delete a node,the node's order will be restore in a stack
 *	the order of node you will get is the reverse order of node you deleted till stack is empty
 *	i.e:create 0,1,2,3,4,5,delete 2,3 and now,if you create,you will get 3,2,6,7,8...
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
		typename NodeType::valueType data = NULL
		)
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
		typename NodeType::valueType data = NULL
		)
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
