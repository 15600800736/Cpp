

//Connection.h
#ifndef CONNECTION_H
#define CONNECTION_H
#include "Relation.h"

namespace graphic
{

/*
 *
 *	The child class of Relation specially for two node's connection
 *	The member cost means two node's distance
 *	more specific details should be defined in node's class
 *	The connection equals one another only when they have the same source destination and distance
 *	Of course,if source and destination equals,distance must be equal
 *
 */
class Connection :public Relation
{
public:

	///////////////////////////////////////////////////////////////////////
	//	-overload operator==
	//	 The connection equals one another only when they have the same source destination and distance
	//	Of course, if source and destination equals, distance must be equal
	//	@parameter otherConnection - the source
	bool operator==(const Connection& otherConnection)
	{
		return _cost == otherConnection._cost;
	}	
	///////////////////////////////////////////////////////////////////////
	//	-overload operator!=
	//	-As long as one of them dosen't equal
	//	-They don't equal
	//	@parameter otherConnection - the source
	bool operator!=(const Connection& otherConnection)
	{
		return *this != otherConnection;
	}
	///////////////////////////////////////////////////////////////////////
	//	-get two node's distance
	int getCost()const
	{
		return _cost;
	}
	///////////////////////////////////////////////////////////////////////
	//	-set two node's distance
	//	@parameter cost - source
	void setCost(int cost)
	{
		_cost = cost;
	}
	void init(int cost)
	{
		_cost = cost;
	}
	friend class RelationFactory;
protected:
	void extendFromRelation()
	{

	}
private:
	///////////////////////////////////////////////////////////////////////
	//	-constructor
	Connection()
	{

	}
	int _cost;
};
}
#endif
