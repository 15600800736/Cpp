

//Function.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace map
{
///////////////////////////////////////////////////////////////////////////////////////
//	-Compare two nodes according value F
//	-if first > second ,return -1
//	-if first == second,return 0
// -if first > second,return 1
//	@parameter first - the first node to compare
//	@parameter second -  the second node to compare

template<typename Node>int compareNode(Node& first, Node& second)
{
	if (&first != NULL)
	{
		return first.compareByF(second);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//	`-seperate two nodes
//	@parameter firstNode - the first node to cut
//	@paramater secondNode - the second node to cut
template<typename Node>void cutWith(Node& firstNode, Node& secondNode)
{
	if ((&firstNode) != NULL && (&secondNode) != NULL)
	{
		firstNode.cutTo(secondNode);
		secondNode.cutTo(firstNode);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//	`-connet two nodes with each other
//	@parameter firstNode - the first node to connect
//	@paramater secondNode - the second node to connect
template<typename nodeType, typename connectionType>void connectWith(nodeType& firstNode, nodeType& secondNode, connectionType connection)
{
	if ((&firstNode) != NULL && (&secondNode) != NULL)
	{
		firstNode.connectTo(secondNode);
		secondNode.connectTo(firstNode);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//	-return if two nodes has a connection
//	@parameter firstNode - the first node to connect
//	@paramater secondNode - the second node to connect
template<typename Node>bool isConnect(Node first, Node second)
{
	return  first.isNeighbor(second) || second.isNeighbor(first);
}
}

#endif
