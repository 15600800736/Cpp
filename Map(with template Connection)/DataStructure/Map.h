

//Map.h

#ifndef MAP_H
#define MAP_H

#include <set>
namespace map
{
template<typename Node>
class Map
{
public:
	Map()
	{
		//do nothing
	}
	Map(const Map& other)
	{
		_node = other._node;
	}
	template<typename iter>Map(iter first, iter second)
	{
		for (; first != second; first++)
		{
			_node.insert(*first);
		}
	}

	void addNode(Node& node)
	{
		_node.insert(node);
	}
protected:
	std::set<Node> _node;
};
}
#endif