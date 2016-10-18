

//Function.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace map
{
template<typename Node>int compareNode(Node& first, Node& second);
template<typename Node>void cutWith(Node& firstNode, Node& secondNode);
template<typename Node>void connectWith(Node& firstNode, Node& secondNode, Connection connection);
template<typename Node>bool isConnect(Node& first, Node& second);
}

#endif
