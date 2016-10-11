
//the Type passed must typedef two type:position for starter and ender
//CurrentBlock should be a iterator instead of a block which can reduce the use of find-function
#include <Windows.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>


template<class Node>
struct nodeTraits
{
	typedef typename Node::order order;
	typedef typename Node::distance distance;
};



template<class Node>
class AStar
{
	typedef typename nodeTraits<Node>::order order;
	typedef typename nodeTraits<Node>::distance distance;
	typedef std::vector<Node> vecNode;
	typedef std::vector<order> vecCoord;
public:
	AStar(Node& starter, Node& ender);
	void outPutWay();
	~AStar();
private:
	vecNode getAroundFGH(Node& node);
	Node getFGH(Node& parent);
	vecNode findPath();
private:
	Node* _starter;
	Node* _ender;
};


//------------------implements------------------
template<typename Node>
AStar<Node>::AStar(Node& starter, Node& ender) :_starter(new Node(starter)), _ender(new Node(ender))
{
	//do something
}
template<typename Node>
AStar<Node>::~AStar()
{
	delete _starter;
	delete _ender;
}
template<typename Node>
std::vector<Node> AStar<Node>::getAroundFGH(Node& node)
{
	
}
template<typename Node>
Node AStar<Node>::getFGH(Node& parent)
{
	
}
template<typename Node>
std::vector<Node> AStar<Node>::findPath()
{
	if (_starter == NULL || _ender == NULL)
	{
		std::cout << "Please select a visible beginning and destination." << std::endl;
		return vecNode();
	}
	vecNode openList;
	vecNode closeList;
	Node selectBlock = *_starter;
	Node currentBlock;
	Node destination = *_ender;
	openList.push_back(selectBlock);
	do
	{
		currentBlock = selectBlock;
		openList.erase(std::find<vecNode::iterator>(openList.begin(), openList.end(), currentBlock));
		closeList.push_back(currentBlock);
		vecNode around = getAroundFGH(currentBlock);
		vecNode::iterator iter = around.begin();
		while (iter != around.end())
		{
			vecNode::iterator iterBlock = std::find<vecNode::iterator>(openList.begin(), openList.end(), *iter);

			if (std::find<vecNode::iterator>(closeList.begin(), closeList.end(), *iter) != closeList.end() || ((*_map)[iter->_coord]) == 1)
			{

			}
			else if (iterBlock != openList.end())
			{
				Node newBlock = getFGH(iter->_coord, currentBlock);
				double tempF = iter->_f;
				if (getFGH(iter->_coord, currentBlock)._f < tempF)
				{
					*iterBlock = newBlock;
				}
			}
			else if (iterBlock == openList.end())
			{
				openList.push_back(*iter);
			}
			iter++;
		}
		vecNode::iterator tmpIter = std::min_element<vecNode::iterator>(openList.begin(), openList.end());
		selectBlock = *tmpIter;
	} while (std::find<vecNode::iterator>(openList.begin(), openList.end(), destination) == openList.end()
		&& !openList.empty());
	vecNode result;
	result.push_back(_ender->_coord);
	for (Node* block = &closeList.back(); block != NULL; block = block->_parent)
	{
		result.push_back(block->_coord);
	}

	return result;
}
template<typename Node>
void AStar<Node>::outPutWay()
{
	vecNode way = findPath();
	if (!way.empty())
	{
		for (vecCoord::reverse_iterator iterWay = way.rbegin();
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