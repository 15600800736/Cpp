

//Relation.h

#ifndef RELATION_H
#define RELATION_H

#include "global.h"
namespace huger
{
/*
 *
 *	Abstract class of Relation
 *	This class is the base-class of all kinds of relationship
 *	Undefine function to get objects and value because maybe the child classes don't want to get both of them
 *	Or they need different function name
 *
 */
template<typename ValueType>
class Relation
{
public:
	typedef typename ValueType valueType;
	//////////////////////////////////////////////////////////////////////////////
	//	-constructor
	Relation() :_value(NULL)
	{

	}
	Relation(valueType value) :
		_value(value)
	{
	}
	Relation(const Relation& other)
	{
		_value = other._value;
	}
	virtual ~Relation()
	{
	}
	virtual valueType getValue()const = 0;
protected:
	valueType _value;
};
}
#endif
