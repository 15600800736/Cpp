

//Relation.h

#ifndef RELATION_H
#define RELATION_H

#include "global.h"
namespace graphic
{
/*
 *
 *	Abstract class of Relation
 *	This class is the base-class of all kinds of relationship
 *	Undefine function to get objects and value because maybe the child classes don't want to get both of them
 *	Or they need different function name
 *
 */
class Relation
{
public:
	//////////////////////////////////////////////////////////////////////////////
	//	-constructor
	Relation() 
	{

	}
	virtual ~Relation()
	{
	}
protected:
	virtual bool operator==(const Relation&)= 0;
};
}
#endif
