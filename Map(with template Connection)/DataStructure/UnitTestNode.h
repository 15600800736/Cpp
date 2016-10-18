

//UnitTestNode.h
#include <iostream>
#include "NodeFactory.h"
#include "Node.h"
#include "Connection.h"
#include "Functions.h"
#include <vector>

namespace map
{
class UnitTestNode
{
public:
	UnitTestNode();
	void methodTest();
	virtual ~UnitTestNode();
private:
	std::vector <Node<int, Connection> >  node;
	NodeFactory<Node<int, Connection> >* nodeFactoryForTest;
};
}