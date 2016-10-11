

#ifndef ASTAR_H
#define ASTAR_H
#include <Windows.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

namespace huger
{
template<class LocalIter>
struct nodeTraits
{
	typedef typename LocalIter::order order;
	typedef typename LocalIter::distance distance;
};



template<class LocalIter>
class AStar
{
	typedef typename nodeTraits<LocalIter>::order order;
	typedef typename nodeTraits<LocalIter>::distance distance;

public:
	AStar(LocalIter& starter, LocalIter& ender);
	void outPutWay();
	~AStar();
private:
	std::vector<LocalIter>::iterator getAroundFGH(LocalIter iter);
	LocalIter getFGH(LocalIter& parent);
	std::vector<LocalIter> findPath();
private:
	LocalIter _starter;
	LocalIter _ender;
};


//------------------implements------------------
template<typename LocalIter>
AStar<LocalIter>::AStar(LocalIter& starter, LocalIter& ender) :_starter(starter), _ender(ender)
{
	//do something
}
template<typename LocalIter>
AStar<LocalIter>::~AStar()
{

}
template<typename LocalIter>
std::vector<LocalIter> AStar<LocalIter>::getAroundFGH(LocalIter iter)
{
	std::vector<LocalIter> around;
	while (around.front() != ++iter)
	{
		around.push_back(iter);
	}
	return around;
}
template<typename LocalIter>
LocalIter AStar<LocalIter>::getFGH(LocalIter& parent)
{

}
template<typename LocalIter>
std::vector<LocalIter> AStar<LocalIter>::findPath()
{
	if (_starter == NULL || _ender == NULL)
	{
		std::cout << "Please select a visible beginning and destination." << std::endl;
		return std::vector<LocalIter>();
	}
	std::vector<LocalIter> openList;
	std::vector<LocalIter> closeList;
	LocalIter selectBlock = _starter;
	LocalIter currentBlock;
	LocalIter destination = _ender;
	openList.push_back(selectBlock);
	do
	{
		currentBlock = selectBlock;
		openList.erase(std::find<typename std::vector<LocalIter>::iterator>(openList.begin(), openList.end(), currentBlock));
		closeList.push_back(currentBlock);
		std::vector<LocalIter> around = getAroundFGH(currentBlock);
		for (typename std::vector<LocalIter>::iterator iter = around.begin();
			iter != around.end();
			iter++)
		{
			typename std::vector<LocalIter>::iterator iterBlock = std::find<typename std::vector<LocalIter>::iterator>(openList.begin(), openList.end(), *iter);
			if (std::find<typename std::vector<LocalIter>::iterator>(closeList.begin(), closeList.end(), *iter) != closeList.end())
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
		typename std::vector<LocalIter>::iterator tmpIter = std::min_element<std::vector<LocalIter>::iterator>(openList.begin(), openList.end());
		selectBlock = *tmpIter;
	} while (std::find<typename  std::vector<LocalIter>::iterator>(openList.begin(), openList.end(), destination) == openList.end()
		&& !openList.empty());
	std::vector<LocalIter> result;
	result.push_back(_ender);
	for (LocalIter block = closeList.back(); block != NULL; block = block--)
	{
		result.push_back(block);
	}

	return result;
}
template<typename LocalIter>
void AStar<LocalIter>::outPutWay()
{
	std::vector<LocalIter> way = findPath();
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