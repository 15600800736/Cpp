

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
template<typename First,typename Second,typename ValueType>
class Relation
{
public:
	typedef typename ValueType valueType;
	typedef typename First firstType;
	typedef typename Second secondType;
	//////////////////////////////////////////////////////////////////////////////
	//	-constructor
	Relation() :_firstObject(NULL), _secondObject(NULL), _value(NULL)
	{

	}
	Relation(object* firstOjbect, 
		object* secondOjbect,
		valueType value) :
		_firstOjbect(firstOjbect), 
		_secondObject(secondOjbect),
		_value(value)
	{
	}
	Relation(const Relation& other)
	{
		_firstObject = other._firstObject;
		_secondObject = other._secondObject;
		_value = other._value;
	}
	virtual ~Relation()
	{
	}
	//////////////////////////////////////////////////////////////////////////////
	//	-overlaoding operator==
	virtual bool operater == (const Relation& otherRelation) = 0;
	//////////////////////////////////////////////////////////////////////////////
	//	-overlaoding operator!=
	virtual bool operater != (const Relation& otherRelation) = 0;
protected:
	firstType* _firstObject;
	secondType* _secondObject;
	valueType _value;
};
}
#endif
