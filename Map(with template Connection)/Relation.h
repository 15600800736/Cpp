

//Relation.h

#ifndef RELATION_H
#define RELATION_H
namespace huger
{
/*
 *
 *	Abstract class of Relation
 *	This class is the base-class of all kinds of relationship
 *	Undefine function to get objects and data because maybe the child classes don't want to get both of them
 *	Or they need different function name
 *
 */
template<typename Object,typename DataType>
class Relation
{
public:
	typedef typename DataType dataType;
	typedef typename Object object;
	//////////////////////////////////////////////////////////////////////////////
	//	-constructor
	Relation(object* firstOjbect, 
		object* secondOjbect,
		dataType data) :
		_firstOjbect(firstOjbect), 
		_secondObject(secondOjbect),
		_data(data)
	{
	}
	Relation(const Relation& other)
	{
		_firstObject = other._firstObject;
		_secondObject = other._secondObject;
		_data = other._data;
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
	object* _firstObject;
	object* _secondObject;
	dataType _data;
};
}
#endif
