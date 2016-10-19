

//--------------UnitTestNode.cpp
#include "DataStructure\UnitTestNode.h"
namespace graphic
{
UnitTestNode::UnitTestNode()
{
	nodeFactoryForTest = new NodeFactory<Node<int>>();
	for (int i = 0; i < 4; i++)
	{
		node.push_back(nodeFactoryForTest->createNodeInStack({ i, i }));
	}
	node[0].connectTo(node[1]);
	node[0].connectTo(node[2]);
	connectWith(node[0], node[3]);
	connectWith(node[1], node[3]);

}

void UnitTestNode::methodTest()
{
	Node<int>* ptrNode4 = nodeFactoryForTest->createNodeInHeap({ 4, 4 });
	Node<int>* ptrNode5 = nodeFactoryForTest->createNodeInHeap({ 5, 5 });
	Node<int>* ptrNode6 = nodeFactoryForTest->createNodeInHeap({ 6, 6 });
	std::cout << "Test Node" << std::endl;
	//copy constructor test
	Node<int> node0Copy(node[0]);
	Node<int> node1Copy = node[1];
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
	std::cout << "node[0]'s neighbors" << std::endl;
	for (Node<int>::iterator iter = node[0].begin(); iter != node[0].end(); iter++)
	{
		std::cout << iter->first->toString() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "node[0]'s reverse neighbor" << std::endl;
	for (Node<int>::reverseIterator riter = node[0].rbegin(); riter != node[0].rend(); riter++)
	{
		std::cout << riter->first->toString() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "test getNeighbor" << std::endl;
	std::cout << "node[0]'s neighbors" << std::endl;
	std::vector<Node<int> > neighbor = node[0].getNeighbor();
	for (std::vector<Node<int>>::iterator iter = neighbor.begin();
		iter != neighbor.end();
		iter++)
	{
		std::cout << iter->order() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "test repeating insert with node2Copy" << std::endl;
	Node<int> nodeCopy = node[2];
	node[0].connectTo(nodeCopy);
	std::cout << "node[0]'s neighbors" << std::endl;
	std::vector<Node<int> > neighbor2 = node[0].getNeighbor();
	for (std::vector<Node<int>>::iterator iter = neighbor2.begin();
		iter != neighbor2.end();
		iter++)
	{
		std::cout << iter->order() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "node[3]'s neighbors" << std::endl;
	for (Node<int>::iterator iter = node[3].begin(); iter != node[3].end(); iter++)
	{
		std::cout << iter->first->toString() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "cut node[0] and node[1]" << std::endl;
	cutWith(node[0], node[1]);
	for (Node<int>::reverseIterator riter = node[0].rbegin(); riter != node[0].rend(); riter++)
	{
		std::cout << riter->first->toString() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "test cut with an node3Copy" << std::endl;
	Node<int> node3Copy = node[3];
	node[0].cutTo(node[3]);
	std::cout << "node[0]'s neighbor assert without node3" << std::endl;
	std::vector<Node<int> > neighbor3 = node[0].getNeighbor();
	for (std::vector<Node<int>>::iterator iter = neighbor3.begin();
		iter != neighbor3.end();
		iter++)
	{
		std::cout << iter->order() << std::endl;
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
	Node<int>::iterator iter00 = node[0].begin();
	std::cout << "iter's order:" << std::endl;
	std::cout << iter00->first->order() << std::endl;
	node[0].connectTo(node[3]);
	Node<int>::iterator prePlusIter = ++iter00;
	std::cout << "prePlusIter's order:" << std::endl;
	std::cout << prePlusIter->first->order() << std::endl;
	iter00 = node[0].begin();
	Node<int>::iterator posPlusIter = iter00++;
	std::cout << "posPlusIter's order:" << std::endl;
	std::cout << posPlusIter->first->order() << std::endl;
	std::cout << std::endl;
	iter00 = ++node[0].begin();
	std::cout << "iter's order:" << std::endl;
	std::cout << iter00->first->order() << std::endl;
	Node<int>::iterator preMinusIter = --iter00;
	std::cout << "preMinusIter's order:" << std::endl;
	std::cout << preMinusIter->first->order() << std::endl;
	iter00 = ++node[0].begin();
	Node<int>::iterator posMinusIter = iter00--;
	std::cout << "posMinusIter's order:" << std::endl;
	std::cout << posMinusIter->first->order() << std::endl;
	std::cout << std::endl;
	std::cout << "node4,node5,node6's order:" << std::endl;
	std::cout << ptrNode4->order() << std::endl << ptrNode5->order() << std::endl << ptrNode6->order() << std::endl;
	std::cout << "destructor node4 and node5 and rebuilt two nodes" << std::endl;
	nodeFactoryForTest->destruct(ptrNode4);
	nodeFactoryForTest->destruct(ptrNode5);
	Node<int> reNode4 = nodeFactoryForTest->createNodeInStack({ 4, 4 });
	Node<int> reNode5 = nodeFactoryForTest->createNodeInStack({ 5, 5 });
	std::cout << "rebuild node's order" << std::endl;
	std::cout << reNode4.order() << std::endl;
	std::cout << reNode5.order() << std::endl;
	std::cout << "built a new node assert order = 7" << std::endl;
	Node<int> node7 = nodeFactoryForTest->createNodeInStack({ 7, 7 });
	std::cout << node7.order() << std::endl;
	std::cout << std::endl;
	std::cout << "built a new node assert order = 8" << std::endl;
	Node<int> node8 = nodeFactoryForTest->createNodeInStack({ 8, 8 });
	std::cout << node8.order() << std::endl;
	std::cout << std::endl;
	std::cout << "built a new node assert order = 9" << std::endl;
	Node<int>* node9 = nodeFactoryForTest->createNodeInHeap({ 9, 9 });
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
	std::cout << "test parent" << std::endl;
	node[0].setParent(node[1]);
	std::cout << "node[0]'s parent : " << std::endl;
	std::cout << node[0].getParent().order() << std::endl;
	std::cout << "if make node[1] = node[2]" << std::endl;
	std::cout << "node[0]'s parent : assert 1" << std::endl;
	std::cout << node[0].getParent().order() << std::endl;
	std::cout << std::endl;
	std::cout << "test isConnect" << std::endl;
	std::cout << "is node0 and node2Copy connected,assert 1" << std::endl;
	Node<int, Connection> node2Copy = node[2];
	std::cout << isConnect(node[0], node2Copy) << std::endl;
	std::cout << isConnect(node2Copy, node[0]) << std::endl;



	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "test sort by order" << std::endl;
	Node<int, Connection> testOrder = nodeFactoryForTest->createNodeInStack({ 0, 0 });
	std::cout << "insert in order node0 node1 node2" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		testOrder.connectTo(node[i]);
	}
	std::vector<Node<int, Connection> > orderNeighbor = testOrder.getNeighbor();
	for (std::vector<Node<int, Connection>>::iterator iter = orderNeighbor.begin();
		iter != orderNeighbor.end();
		iter++)
	{
		std::cout << iter->order() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "insert in order node2 node1 node0" << std::endl;
	testOrder.clear();
	for (int i =2 ; i > -1; i--)
	{
		testOrder.connectTo(node[i]);
	}
	orderNeighbor = testOrder.getNeighbor();
	for (std::vector<Node<int, Connection>>::iterator iter = orderNeighbor.begin();
		iter != orderNeighbor.end();
		iter++)
	{
		std::cout << iter->order() << std::endl;
	}
}
UnitTestNode:: ~UnitTestNode()
{
	delete nodeFactoryForTest;
}

}


void main()
{
graphic::UnitTestNode test;
test.methodTest();
}
