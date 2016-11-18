

//UnitTestNode.h
#include <iostream>
#include "NodeFactory.h"
#include "Node.h"
#include "SimpleRelation.h"
#include "Functions.h"
#include <vector>

namespace graphic
{
class UnitTestNode
{
public:
	UnitTestNode();
	void methodTest();
	virtual ~UnitTestNode();
private:
	std::vector <Node<int> >  node;
	NodeFactory<Node<int> >* nodeFactoryForTest;
};
}