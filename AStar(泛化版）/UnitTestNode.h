

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
			node.push_back(NodeFactor<int>::createNodeInStack());
		}
		node[0].connectTo(&node[1]);
		node[0].connectTo(&node[2]);
		node[0].connectWith(&node[3]);
		node[1].connectWith(&node[3]);

	}
	void methodTest()
	{
		Node<int>* ptrNode4 = NodeFactor<int>::createNodeInHeap();
		Node<int>* ptrNode5 = NodeFactor<int>::createNodeInHeap();
		Node<int>* ptrNode6 = NodeFactor<int>::createNodeInHeap();
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
		std::cout << "node[0]'s reverse neighbor" << std::endl;
		for (Node<int>::reverseIterator riter = node[0].rbegin(); riter != node[0].rend(); riter ++ )
		{
			std::cout << riter->outPutInfo() << std::endl;
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
		std::cout << std::endl;
		Node<int>::iterator iter = node[0].begin();
		std::cout << "iter's order:" << std::endl;
		std::cout << iter->order() << std::endl;
		Node<int>::iterator prePlusIter = ++iter;
		std::cout << "prePlusIter's order:" << std::endl;
		std::cout << prePlusIter->order() << std::endl;
		iter = node[0].begin();
		Node<int>::iterator posPlusIter = iter++;
		std::cout << "posPlusIter's order:" << std::endl;
		std::cout << posPlusIter->order() << std::endl;
		std::cout << std::endl;
		iter = ++node[0].begin();
		std::cout << "iter's order:" << std::endl;
		std::cout << iter->order() << std::endl;
		Node<int>::iterator preMinusIter = --iter;
		std::cout << "preMinusIter's order:" << std::endl;
		std::cout << preMinusIter->order() << std::endl;
		iter = ++node[0].begin();
		Node<int>::iterator posMinusIter = iter--;
		std::cout << "posMinusIter's order:" << std::endl;
		std::cout << posMinusIter->order() << std::endl;
		std::cout << std::endl;
		std::cout << "node4,node5,node6's order:" << std::endl;
		std::cout << ptrNode4->order() << std::endl << ptrNode5->order() << std::endl << ptrNode6->order() << std::endl;
		std::cout << "destructor node4 and node5 and rebuilt two nodes" << std::endl;
		NodeFactor<int>::destruct(ptrNode4);
		NodeFactor<int>::destruct(ptrNode5);
		Node<int> reNode4 = NodeFactor<int>::createNodeInStack();
		Node<int> reNode5 = NodeFactor<int>::createNodeInStack();
		std::cout << "rebuild node's order" << std::endl;
		std::cout << reNode4.order() << std::endl;
		std::cout << reNode5.order() << std::endl;
		std::cout << "built a new node assert order = 7" << std::endl;
		Node<int> node7 = NodeFactor<int>::createNodeInStack();
		std::cout << node7.order() << std::endl;
		NodeFactor<int>::destruct(ptrNode6);
		std::cout << std::endl;
	}
private:
	std::vector <Node<int> >  node;
};
}
#endif