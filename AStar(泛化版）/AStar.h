

#ifndef ASTAR_H
#define ASTAR_H
#include <Windows.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

namespace huger
{
template<class Node>
class AStar
{
	typedef typename Node::orderType orderType;
	typedef typename Node::distanceType distanceType;
	typedef typename Node::valueType valueType;
	typedef typename Node::pointerType pointerType;
	typedef typename Node::referenceType referenceType;
	typedef typename Node::category category;

	typedef typename ptrNode ptrNode;
	typedef typename refNode refNode;

public:
	AStar(refNode starter, refNode ender) :_starter(starter), _ender(ender)
	{
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
				std::cout << iterWay->X << "  " << iterWay->Y << std::endl;
			}
		}
		else
		{
			std::cout << "Can not find the way from beginning to destination." << std::endl;
		}
	}
	~AStar();
private:
	std::vector<Node> getAroundFGH(Node node)
	{
		std::vector<Node> around;
		for (typename Node::iterator iter = node.begin(); iter != node.end(); iter++)
		{
			around.push_back(*iter);
		}
		return around;
	}
	valueType getFGH(refNode current, refNode parent)
	{
		int g = current - parent;
		int h = _ender - current;
		int f = g + h;
	}
	std::vector<Node> findPath()
	{
		if (_starter == NULL || _ender == NULL)
		{
			std::cout << "Please select a visible beginning and destination." << std::endl;
			return std::vector<Node>();
		}
		//openList
		std::vector<Node> openList;
		//closeList
		std::vector<Node> closeList;
		//the node that has minium F
		Node selectNode = _starter;
		//the node to operate
		Node currentNode;
		//
		Node destination = _ender;
		//push the stater
		openList.push_back(selectNode);
		do
		{
			currentNode = selectNode;
			openList.erase(std::find<typename std::vector<Node>::iterator>(openList.begin(), openList.end(), currentNode));
			closeList.push_back(currentNode);
			//get around node and deal with it depends it's situation
			std::vector<Node> around = getAroundFGH(currentNode);
			for (typename std::vector<Node>::iterator iter = around.begin();
				iter != around.end();
				iter++)
			{
				typename std::vector<Node>::iterator iterNode = std::find<typename std::vector<Node>::iterator>(openList.begin(), openList.end(), *iter);
				if (std::find<typename std::vector<Node>::iterator>(closeList.begin(), closeList.end(), *iter) != closeList.end())
				{

				}
				else if (iterNode != openList.end())
				{
					//rewrite
					
					*iterNode = newNode;

				}
				else if (iterNode == openList.end())
				{
					openList.push_back(*iter);
				}
			}
			//select the minium node in openList
			typename std::vector<Node>::iterator tmpIter = std::min_element<std::vector<Node>::iterator>(openList.begin(), openList.end());
			selectNode = *tmpIter;
		} while (std::find<typename  std::vector<Node>::iterator>(openList.begin(), openList.end(), destination) == openList.end()
			&& !openList.empty());
		std::vector<Node> result;
		result.push_back(_ender);
		for (Node node = closeList.back(); node != NULL; node = node--)
		{
			result.push_back(node);
		}

		return result;
	}
private:
	ptrNode _starter;
	ptrNode _ender;
};
#endif
}
