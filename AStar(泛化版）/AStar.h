

#ifndef ASTAR_H
#define ASTAR_H
#include <Windows.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

namespace huger
{
template<class GlobalIterator>
class AStar
{
	typedef typename GlobalIterator::orderType orderType;
	typedef typename GlobalIterator::distanceType distanceType;
	typedef typename GlobalIterator::valueType valueType;
	typedef typename GlobalIterator::pointerType pointerType;
	typedef typename GlobalIterator::referenceType referenceType;
	typedef typename GlobalIterator::category category;

public:
	AStar(GlobalIterator& starter, GlobalIterator& ender) :_starter(starter), _ender(ender)
	{
	}
	void outPutWay()
	{
		std::vector<GlobalIterator> way = findPath();
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
	std::vector<valueType> getAroundFGH(GlobalIterator iter)
	{
		std::vector<valueType> around;
		while (around.front() != ++iter)
		{
			around.push_back(getFGH();
		}
		return around;
	}
	valueType getFGH(GlobalIterator& current, GlobalIterator& parent)
	{
		int g = current - parent;
		int h = _ender - current;
		int f = g + h;
	}
	std::vector<GlobalIterator> findPath()
	{
		if (_starter == NULL || _ender == NULL)
		{
			std::cout << "Please select a visible beginning and destination." << std::endl;
			return std::vector<GlobalIterator>();
		}
		std::vector<GlobalIterator> openList;
		std::vector<GlobalIterator> closeList;
		GlobalIterator selectBlock = _starter;
		GlobalIterator currentBlock;
		GlobalIterator destination = _ender;
		openList.push_back(selectBlock);
		do
		{
			currentBlock = selectBlock;
			openList.erase(std::find<typename std::vector<GlobalIterator>::iterator>(openList.begin(), openList.end(), currentBlock));
			closeList.push_back(currentBlock);
			std::vector<GlobalIterator> around = getAroundFGH(currentBlock);
			for (typename std::vector<GlobalIterator>::iterator iter = around.begin();
				iter != around.end();
				iter++)
			{
				typename std::vector<GlobalIterator>::iterator iterBlock = std::find<typename std::vector<GlobalIterator>::iterator>(openList.begin(), openList.end(), *iter);
				if (std::find<typename std::vector<GlobalIterator>::iterator>(closeList.begin(), closeList.end(), *iter) != closeList.end())
				{

				}
				else if (iterBlock != openList.end())
				{
					//rewrite
					*iterBlock = newBlock;

				}
				else if (iterBlock == openList.end())
				{
					openList.push_back(*iter);
				}
			}
			typename std::vector<GlobalIterator>::iterator tmpIter = std::min_element<std::vector<GlobalIterator>::iterator>(openList.begin(), openList.end());
			selectBlock = *tmpIter;
		} while (std::find<typename  std::vector<GlobalIterator>::iterator>(openList.begin(), openList.end(), destination) == openList.end()
			&& !openList.empty());
		std::vector<GlobalIterator> result;
		result.push_back(_ender);
		for (GlobalIterator block = closeList.back(); block != NULL; block = block--)
		{
			result.push_back(block);
		}

		return result;
	}
private:
	GlobalIterator _starter;
	GlobalIterator _ender;
};
#endif
}