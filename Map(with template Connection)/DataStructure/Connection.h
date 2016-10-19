

//Connection.h
#ifndef CONNECTION_H
#define CONNECTION_H
#include "Relation.h"

namespace graphic
{

/*
 *
 *	The child class of Relation specially for two node's connection
 *	The member value means two node's distance
 *	more specific details should be defined in node's class
 *	The connection equals one another only when they have the same source destination and distance
 *	Of course,if source and destination equals,distance must be equal
 *
 */
class Connection :public Relation<int>
{
public:
	typedef Relation::valueType valueType;
	typedef Relation::valueType distanceType;
	///////////////////////////////////////////////////////////////////////
	//	-constructor
	Connection()
	{

	}
	Connection(distanceType distance) :Relation(distance)
	{

	}
	///////////////////////////////////////////////////////////////////////
	//	-overload operator==
	//	 The connection equals one another only when they have the same source destination and distance
	//	Of course, if source and destination equals, distance must be equal
	//	@parameter otherConnection - the source
	bool operator==(const Connection& otherConnection)
	{
		return _value == otherConnection._value;
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
	distanceType getValue()const
	{
		return _value;
	}
	///////////////////////////////////////////////////////////////////////
	//	-set two node's distance
	//	@parameter value - source
	void setDistance(distanceType value)
	{
		_value = value;
	}
};
}
#endif
