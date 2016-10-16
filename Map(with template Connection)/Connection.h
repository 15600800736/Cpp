

//Connection.h
#ifndef CONNECTION_H
#define CONNECTION_H
#include "Relation.h"

namespace huger
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
template<typename Object>
class Connection :public Relation<Object,Object,int>
{
public:
	typedef Relation::valueType valueType;
	typedef	Object firstType;
	typedef Object secondType;

	typedef Relation::valueType distanceTypeType;
	typedef Object objectType;
	///////////////////////////////////////////////////////////////////////
	//	-constructor
	Connection()
	{

	}
	Connection(objectType* sourceNode,
		objectType* destinationNode,
		distanceType distance) :
		_firstObject(sourceNode),
		_secondObject(destinationNode),
		_value(distance)
	{

	}
	///////////////////////////////////////////////////////////////////////
	//	-overload operator==
	//	 The connection equals one another only when they have the same source destination and distance
	//	Of course, if source and destination equals, distance must be equal
	//	@parameter otherConnection - the source
	bool operator==(const Connection& otherConnection)
	{
		return	_firstObject == otherConnection._firstObject && 
			_secondObject == otherConnection._secondObject && 
			_data == otherConnection._data;
	}	
	///////////////////////////////////////////////////////////////////////
	//	-overload operator!=
	//	-As long as one of them dosen't equal
	//	-They don't equal
	//	@parameter otherConnection - the source
	bool operator!=(const Connection& otherConnection)
	{
		return	_firstObject != otherConnection._firstObject ||
			_secondObject != otherConnection._secondObject ||
			_data != otherConnection._data;
	}
	///////////////////////////////////////////////////////////////////////
	//	-get the node connected to
	objectType getDestination()const
	{
		return _secondObject;
	}
	///////////////////////////////////////////////////////////////////////
	//	-get the node connected from
	objectType getSource()const
	{
		return _firstObject;
	}	
	///////////////////////////////////////////////////////////////////////
	//	-get two node's distance
	distanceType getDistance()const
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
