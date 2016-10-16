

//--------------UnitTestNode.cpp
#include <iostream>
#include "NodeFactory.h"
#include "Node.h"
#include <vector>
namespace huger
{
template<typename T>void destructNodeFactor();
class UnitTestNode
{
public:
	UnitTestNode()
	{
		nodeFactoryForTest = new NodeFactory<Node<int,int> >();
		for (int i = 0; i < 4; i++)
		{
			node.push_back(nodeFactoryForTest->createNodeInStack({ i, i }));
		}
		node[0].connectTo(0,node[1]);
		node[0].connectTo(1,node[2]);
		connectWith(node[0], node[3],3);
		connectWith(node[1],node[3],4);

	}
	void methodTest()
	{
		Node<int,int>* ptrNode4 = nodeFactoryForTest->createNodeInHeap({ 4, 4 });
		Node<int,int>* ptrNode5 = nodeFactoryForTest->createNodeInHeap({ 5, 5 });
		Node<int,int>* ptrNode6 = nodeFactoryForTest->createNodeInHeap({ 6, 6 });
		std::cout << "Test Node" << std::endl;
		//copy constructor test
		Node<int,int> node0Copy(node[0]);
		Node<int,int> node1Copy = node[1];
		std::cout << "node0Copy's information" << std::endl;
		std::cout << node0Copy.toString() << std::endl;
		std::cout << std::endl;
		std::cout << "node1Copy's information" << std::endl;
		std::cout << node1Copy.toString() << std::endl;
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
		for (Node<int,int>::iterator iter = node[0].begin(); iter != node[0].end(); iter++)
		{
			std::cout << iter->first->toString() << std::endl;
		}
		std::cout << std::endl;
		std::cout << "node[0]'s reverse neighbor" << std::endl;
		for (Node<int,int>::reverseIterator riter = node[0].rbegin(); riter != node[0].rend(); riter++)
		{
			std::cout << riter->first->toString() << std::endl;
		}
		std::cout << std::endl;
		std::cout << "test getNeighbor" << std::endl;
		std::cout << "node[0]'s neighbors" << std::endl;
		std::vector<Node<int,int> > neighbor = node[0].getNeighbor();
		for (std::vector<Node<int,int>>::iterator iter = neighbor.begin();
			iter != neighbor.end();
			iter++)
		{
			std::cout << iter->order() << std::endl;
		}
		std::cout << std::endl;
		std::cout << "node[3]'s neighbors" << std::endl;
		for (Node<int,int>::iterator iter = node[3].begin(); iter != node[3].end(); iter++)
		{
			std::cout << iter->first->toString() << std::endl;
		}
		std::cout << std::endl;
		std::cout << "cut node[0] and node[1]" << std::endl;
		cutWith(node[0], node[1]);
		for (Node<int,int>::reverseIterator riter = node[0].rbegin(); riter != node[0].rend(); riter++)
		{
			std::cout << riter->first->toString() << std::endl;
		}
		Node<int,int>::iterator iter01 = node[0].begin();
		Node<int,int>::iterator iter02 = node[0].begin();
		Node<int,int>::iterator iter01Copy(iter01);
		std::cout << "iter01 == iter02" << std::endl;
		std::cout << (iter01 == iter02) << std::endl;
		std::cout << std::endl;
		std::cout << "iter01 == iter01Copy" << std::endl;
		std::cout << (iter01 == iter01Copy) << std::endl;
		std::cout << std::endl;
		Node<int,int>::iterator iter = node[0].begin();
		std::cout << "iter's order:" << std::endl;
		std::cout << iter->first->order() << std::endl;
		Node<int,int>::iterator prePlusIter = ++iter;
		std::cout << "prePlusIter's order:" << std::endl;
		std::cout << prePlusIter->first->order() << std::endl;
		iter = node[0].begin();
		Node<int,int>::iterator posPlusIter = iter++;
		std::cout << "posPlusIter's order:" << std::endl;
		std::cout << posPlusIter->first->order() << std::endl;
		std::cout << std::endl;
		iter = ++node[0].begin();
		std::cout << "iter's order:" << std::endl;
		std::cout << iter->first->order() << std::endl;
		Node<int,int>::iterator preMinusIter = --iter;
		std::cout << "preMinusIter's order:" << std::endl;
		std::cout << preMinusIter->first->order() << std::endl;
		iter = ++node[0].begin();
		Node<int,int>::iterator posMinusIter = iter--;
		std::cout << "posMinusIter's order:" << std::endl;
		std::cout << posMinusIter->first->order() << std::endl;
		std::cout << std::endl;
		std::cout << "node4,node5,node6's order:" << std::endl;
		std::cout << ptrNode4->order() << std::endl << ptrNode5->order() << std::endl << ptrNode6->order() << std::endl;
		std::cout << "destructor node4 and node5 and rebuilt two nodes" << std::endl;
		nodeFactoryForTest->destruct(ptrNode4);
		nodeFactoryForTest->destruct(ptrNode5);
		Node<int,int> reNode4 = nodeFactoryForTest->createNodeInStack({ 4, 4 });
		Node<int,int> reNode5 = nodeFactoryForTest->createNodeInStack({ 5, 5 });
		std::cout << "rebuild node's order" << std::endl;
		std::cout << reNode4.order() << std::endl;
		std::cout << reNode5.order() << std::endl;
		std::cout << "built a new node assert order = 7" << std::endl;
		Node<int,int> node7 = nodeFactoryForTest->createNodeInStack({ 7, 7 });
		std::cout << node7.order() << std::endl;
		std::cout << std::endl;
		std::cout << "built a new node assert order = 8" << std::endl;
		Node<int,int> node8 = nodeFactoryForTest->createNodeInStack({ 8, 8 });
		std::cout << node8.order() << std::endl;
		std::cout << std::endl;
		std::cout << "built a new node assert order = 9" << std::endl;
		Node<int,int>* node9 = nodeFactoryForTest->createNodeInHeap({ 9, 9 });
		std::cout << node9->order() << std::endl;

			
		std::cout << std::endl;
		std::cout << "g value from node0 to node1" << std::endl;
		node[0].caculateG(node[1]);
		std::cout << node[0].getG() << std::endl;
		std::cout << std::endl;
		std::cout << "node2'sh value from node0 to node9" << std::endl;
		node[2].caculateH(node[0], *node9);
		std::cout << node[2].getH() << std::endl;
		std::cout << std::endl;
		nodeFactoryForTest->destruct(ptrNode6);
		nodeFactoryForTest->destruct(node9);
		std::cout << std::endl;
	}
	virtual ~UnitTestNode()
	{
		delete nodeFactoryForTest;
	}
private:
	std::vector <Node<int,int> >  node;
	NodeFactory<Node<int,int> >* nodeFactoryForTest;
};
}


void main()
{
	huger::UnitTestNode test;
	test.methodTest();
}
