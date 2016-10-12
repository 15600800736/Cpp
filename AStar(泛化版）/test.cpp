

#include "Node.h"

#include <iostream>
using namespace huger;


void main()
{
	Node<int> *node1 = new Node<int>(1, std::list<Node<int>*>());
	Node<int> *node2 = new Node<int>(2, std::list<Node<int>*>());
	Node<int> *node3 = new Node<int>(3, std::list<Node<int>*>());
	Node<int> *node4 = new Node<int>(4, std::list<Node<int>*>());
	node1->connectWith(node2);
	node1->connectWith(node3);
	node1->connectWith(node4);
	Node<int>::iterator iter = node1->begin();
	for (Node<int>::iterator iter = node1->begin();iter != node1->end(); iter++)
	{
		std::cout <<iter->order()<< std::endl;
	}
	for (Node<int>::iterator iter = node2->begin(); iter != node2->end(); iter++)
	{
		std::cout <<iter->order() << std::endl;
	}
}