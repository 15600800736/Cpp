

//--------------UnitTestNode.h
#ifndef UNIT_TEST_NODE_H
#define UNIT_TEST_NODE_H
#include <iostream>
#include "Node.h"
#include <vector>
namespace huger
{
class UnitTestNode
{
public:
	UnitTestNode()
	{
		for (int i = 0; i < 4; i++)
		{
			node.push_back(Node<int>(i));
		}
		node[0].connectTo(&node[1]);
		node[0].connectTo(&node[2]);
		node[0].connectWith(&node[3]);
		node[1].connectWith(&node[3]);
	}
	void methodTest()
	{
		std::cout << "Test Node" << std::endl;
		//copy constructor test
		Node<int> node0Copy(node[0]);
		Node<int> node1Copy = node[1];
		std::cout << "node0Copy's information" << std::endl;
		std::cout << node0Copy.outPutInfo()<< std::endl;
		std::cout << std::endl;
		std::cout << "node1Copy's information" << std::endl;
		std::cout << node1Copy.outPutInfo() << std::endl;
		std::cout << std::endl;
		//operator overloding test
		std::cout << "node[0] == node0Copy" << std::endl;
		std::cout << (node[0] == node0Copy) << std::endl;
		std::cout << std::endl;
		std::cout << "node[0] != node[1]" << std::endl;
		std::cout << (node[0] != node[1]) << std::endl;
		std::cout << std::endl;
		std::cout << "node[0] <node[1]" << std::endl;
		std::cout << (node[0] < node[1]) << std::endl;
		std::cout << std::endl;
		std::cout << "node[0] > node[1]" << std::endl;
		std::cout << (node[0] > node[1]) << std::endl;
		std::cout << std::endl;
		std::cout << "node[0]'s neighbors" << std::endl;
		for (Node<int>::iterator iter = node[0].begin(); iter != node[0].end(); iter++)
		{
			std::cout<<iter->outPutInfo()<<std::endl;
		}
		std::cout << std::endl;
		std::cout << "node[3]'s neighbors" << std::endl;
		for (Node<int>::iterator iter = node[3].begin(); iter != node[3].end(); iter++)
		{
			std::cout << iter->outPutInfo() << std::endl;
		}
		std::cout << std::endl;
		Node<int>::iterator iter01 = node[0].begin();
		Node<int>::iterator iter02 = node[0].begin();
		Node<int>::iterator iter01Copy(iter01);
		std::cout << "iter01 == iter02" << std::endl;
		std::cout << (iter01 == iter02) << std::endl;
		std::cout << std::endl;
		std::cout << "iter01 == iter01Copy" << std::endl;
		std::cout << (iter01 == iter01Copy) << std::endl;
	}
private:
	std::vector <Node<int> >  node;
};
}
#endif