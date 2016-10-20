

//Function.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace graphic
{
///////////////////////////////////////////////////////////////////////////////////////
//	-Compare two nodes according value F
//	-if first > second ,return -1
//	-if first == second,return 0
// -if first > second,return 1
//	@parameter first - the first node to compare
//	@parameter second -  the second node to compare

template<typename Node>int compareNode(const Node& first, const Node& second)
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
template<typename nodeType>void connectWith(nodeType& firstNode, nodeType& secondNode)
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
	return  first.isNeighbor(second) != first.end() || second.isNeighbor(first) != second.end();
}
///////////////////////////////////////////////////////////////////////////////////////
//	-the algorithm to find way
//	@starter - the node you came from
//	@ender - the node you're going to
template<typename Node>std::vector<Node>AStar(Node* starter, Node* ender)
{
	if (starter == NULL || *ender == NULL)
	{
		std::cout << "Please select a visible beginning and destination." << std::endl;
		return std::vector<Node>();
	}
	//openList
	std::vector<Node> openList;
	//closeList
	std::vector<Node> closeList;
	//the node to operate
	Node currentNode = *starter;
	Node destination = *ender;
	//push the stater
	openList.push_back(currentNode);
	while (std::find<typename  std::vector<Node>::iterator>(openList.begin(), openList.end(), destination) == openList.end()
		&& !openList.empty())
	{
		openList.erase(std::find<typename std::vector<Node>::iterator>(openList.begin(), openList.end(), currentNode));
		closeList.push_back(currentNode);
		//get around node and deal with it depends it's situation
		std::vector<Node> around = node.getNeighbor();
		for (typename std::vector<Node>::iterator iter = around.begin();
			iter != around.end();
			iter++)
		{
			iter->CalculateG(currentNode);
			iter->CalculateH(*ender);
			iter->CalculateF();
			iter->setParent(currentNode);
		}
		//for each node's around current node
		for (typename std::vector<Node>::iterator iterAround = around.begin();
			iterAround != around.end();
			iterAround++)
		{
			typename std::vector<Node>::iterator iterInOpen = std::find<typename std::vector<Node>::iterator>(openList.begin(), openList.end(), *iterAround);
			typename std::vector<Node>::iterator iterInClose = std::find<typename std::vector<Node>::iterator>(closeList.begin(), closeList.end(), *iterAround);
			if (iterator != around.end())
			{
				//do nothing
			}
			else if (iterInOpen != openList.end())
			{
				Node newNode = *iterInOpen;
				newNode.CalculateG(*iterAround);
				newNode.CalculateF();
				newNode.setParent(*iterAround);
				if (newNode.compareByF(*iterInOpen) < 0)
				{
					*iterInOpen = newNode;
				}
				else
				{
					//do nothing
				}
			}
			else if (iterInOpen == openList.end())
			{
				openList.push_back(*iter);
			}
		}
		//select the minium node in openList
		typename std::vector<Node>::iterator minIter = std::min_element<std::vector<Node>::iterator>(openList.begin(), openList.end());
		currentNode = *minIter;
	}
	std::vector<Node> result;
	result.push_back(*ender);
	for (Node node = closeList.back(); node != *ender; //only starter's parent == *ender
		node = node.getParent())
	{
		result.push_back(node);
	}
	return result;
}
}
#endif
