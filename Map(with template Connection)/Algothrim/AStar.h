

#ifndef ASTAR_H
#define ASTAR_H
#include <Windows.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

namespace huger
{
template<typename Node>
class AStar
{
	typedef typename Node::valueType valueType;
	typedef typename Node::pointerType pointerType;
	typedef typename Node::referenceType referenceType;

	typedef typename Node* ptrNode;
	typedef typename Node& refNode;

public:
	AStar(ptrNode starter, ptrNode ender) :_starter(starter), *_ender(ender)
	{
		_starter.setParent(**_ender);
		*_ender.setParent(*_starter);
	}
	void outPutWay()
	{
		std::vector<Node> way = findPath();
		if (!way.empty())
		{
			for (std::vector<order>::reverse_iterator iterWay = way.rbegin();
				iterWay != way.rend();
				iterWay++)
			{
				std::cout << iterWay->order() << std::endl;
			}
		}
		else
		{
			std::cout << "Can not find the way from beginning to destination." << std::endl;
		}
	}
	~AStar();
private:
	std::vector<Node> getAround(refNode parent)
	{
		std::vector<Node> around;
		around = node.getNeighbor();
		for (typename std::vector<Node>::iterator iter = around.begin();
			iter != around.end();
			iter++)
		{
			iter->CalculateG(parent);
			iter->CalculateH(**_ender);
			iter->CalculateF();
			iter->setParent(parent);

		}
		return around;
	}
	std::vector<Node> findPath()
	{
		if (_starter == NULL || *_ender == NULL)
		{
			std::cout << "Please select a visible beginning and destination." << std::endl;
			return std::vector<Node>();
		}
		//openList
		std::vector<Node> openList;
		//closeList
		std::vector<Node> closeList;
		//the node to operate
		Node currentNode = *_starter;
		Node destination = *_ender;
		//push the stater
		openList.push_back(currentNode);
		while (std::find<typename  std::vector<Node>::iterator>(openList.begin(), openList.end(), destination) == openList.end()
			&& !openList.empty())
		{
			openList.erase(std::find<typename std::vector<Node>::iterator>(openList.begin(), openList.end(), currentNode));
			closeList.push_back(currentNode);
			//get around node and deal with it depends it's situation
			std::vector<Node> around = getAround(currentNode);
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
		result.push_back(*_ender);
		for (Node node = closeList.back(); node != *_ender; //only _starter's parent == *_ender
			node = node.getParent())
		{
			result.push_back(node);
		}

		return result;
	}
private:
	ptrNode _starter;
	ptrNode _ender;
};
}

#endif

