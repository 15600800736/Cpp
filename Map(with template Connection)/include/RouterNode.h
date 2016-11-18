

//RouterNode.h

#ifndef ROUTER_NODE_H
#define ROUTER_NODE_H

#include <list>
#include "Node.h"
#include "RouterRelation.h"
#include "DataPacket.h"
namespace graphic
{
class RouterNode :public Node <int,RouterRelation>
{
public:
	RouterNode() :Node() {}
	void connectTo(Node& otherNode) override
	{
		if (isNeighbor(otherNode) == _neighbor.end())
		{
			RouterRelation* connection = createConnection(abs(otherNode.order() - _order));
			_neighbor.insert(std::make_pair(&otherNode, connection));
			otherNode.setInDegree(otherNode.getInDegree() + 1);
		}
	}
	DataPacket<std::string> sendLinkedStatusPacket()
	{

	}
	DataPacket<std::string> makeDataPacket(
		DataPacket<std::string>::PacketType type,
		std::string data,
		RouterNode* start,
		RouterNode* destination,
		int length,
		int timeToLive = 10
		)
	{
		DataPacket<std::string> newPacket(type, data, start, destination, length, timeToLive);
	}

	void sendPacket(
		DataPacket<std::string>::PacketType type,
		std::string data,
		RouterNode* start,
		RouterNode* destination,
		int length,
		int timeToLive = 10
		)
	{
		DataPacket<std::string> packetToSend = makeDataPacket(type, data, this, destination, length, timeToLive);
		//???
		std::map<RouterNode*,
			std::map <Node*, RouterRelation*, NodeCopmareByOrder<Node*>>::iterator>::iterator iter = _allRouters.find(destination);
		iter->second->second->transData(packetToSend);
	}
protected:
	void init()
	{

	}
	void findNeighbor()
	{

	}
private:
	Node* _startAddress;
	int _order;
	int _age;
	std::map<RouterNode*,
		std::map <Node*, RouterRelation*, NodeCopmareByOrder<Node*>>::iterator>
	_allRouters;
};
}
#endif