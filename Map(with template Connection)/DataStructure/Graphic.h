

//graphic.h

#ifndef MAP_H
#define MAP_H

#include <set>
namespace graphic
{
template<typename Node>
class 
{
public:
	graphic()
	{
		//do nothing
	}
	graphic(const graphic& other)
	{
		_node = other._node;
	}
	template<typename iter>graphic(iter first, iter second)
	{
		for (; first != second; first++)
		{
			_node.insert(*first);
		}
	}
	template<typename iter>graphic(iter first, int n)
	{
		for (int i = 0; i < n; iter++, i++)
		{
			_node.insert(*iter);
		}
	}
	void addNode(const Node& node)
	{
		_node.insert(node);
	}
	void removeNode(const Node&)
protected:
	std::set<Node> _node;
};
}
#endif