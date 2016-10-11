

#ifndef ASTAR_H
#define ASTAR_H
#include <Windows.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

namespace huger
{
template<class LocalIterator>
class AStar
{
	typedef typename LocalIterator::orderType orderType;
	typedef typename LocalIterator::distanceType distanceType;
	typedef typename LocalIterator::valueType valueType;
	typedef typename LocalIterator::pointerType pointerType;
	typedef typename LocalIterator::referenceType referenceType;
	typedef typename LocalIterator::category category;

public:
	AStar(LocalIterator& starter, LocalIterator& ender);
	void outPutWay();
	~AStar();
private:
	std::vector<valueType> getAroundFGH(LocalIterator iter);
	valueType getFGH(LocalIterator& current,LocalIterator& parent);
	std::vector<LocalIterator> findPath();
private:
	LocalIterator _starter;
	LocalIterator _ender;
};


//------------------implements------------------
template<typename LocalIterator>
AStar<LocalIterator>::AStar(LocalIterator& starter, LocalIterator& ender) :_starter(starter), _ender(ender)
{
	//do something
}
template<typename LocalIterator>
AStar<LocalIterator>::~AStar()
{

}
template<typename LocalIterator>
std::vector<typename LocalIterator::valueType> AStar<LocalIterator>::getAroundFGH(LocalIterator iter)
{
	std::vector<valueType> around;
	while (around.front() != ++iter)
	{
		around.push_back(getFGH();
	}
	return around;
}
template<typename LocalIterator>
typename LocalIterator::valueType AStar<LocalIterator>::getFGH(LocalIterator& current, LocalIterator& parent)
{
	int g = current - parent;
	int h = _ender - current;
	int f = g + h;
}
template<typename LocalIterator>
std::vector<LocalIterator> AStar<LocalIterator>::findPath()
{
	if (_starter == NULL || _ender == NULL)
	{
		std::cout << "Please select a visible beginning and destination." << std::endl;
		return std::vector<LocalIterator>();
	}
	std::vector<LocalIterator> openList;
	std::vector<LocalIterator> closeList;
	LocalIterator selectBlock = _starter;
	LocalIterator currentBlock;
	LocalIterator destination = _ender;
	openList.push_back(selectBlock);
	do
	{
		currentBlock = selectBlock;
		openList.erase(std::find<typename std::vector<LocalIterator>::iterator>(openList.begin(), openList.end(), currentBlock));
		closeList.push_back(currentBlock);
		std::vector<LocalIterator> around = getAroundFGH(currentBlock);
		for (typename std::vector<LocalIterator>::iterator iter = around.begin();
			iter != around.end();
			iter++)
		{
			typename std::vector<LocalIterator>::iterator iterBlock = std::find<typename std::vector<LocalIterator>::iterator>(openList.begin(), openList.end(), *iter);
			if (std::find<typename std::vector<LocalIterator>::iterator>(closeList.begin(), closeList.end(), *iter) != closeList.end())
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
		typename std::vector<LocalIterator>::iterator tmpIter = std::min_element<std::vector<LocalIterator>::iterator>(openList.begin(), openList.end());
		selectBlock = *tmpIter;
	} while (std::find<typename  std::vector<LocalIterator>::iterator>(openList.begin(), openList.end(), destination) == openList.end()
		&& !openList.empty());
	std::vector<LocalIterator> result;
	result.push_back(_ender);
	for (LocalIterator block = closeList.back(); block != NULL; block = block--)
	{
		result.push_back(block);
	}

	return result;
}
template<typename LocalIterator>
void AStar<LocalIterator>::outPutWay()
{
	std::vector<LocalIterator> way = findPath();
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
#endif
}