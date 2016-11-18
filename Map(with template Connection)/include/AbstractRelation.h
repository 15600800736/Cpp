

//Relation.h

#ifndef ABSTRACT_RELATION_H
#define ABSTRACT_RELATION_H

#include "constance.h"
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
template <typename distanceType>
class AbstractRelation
{
public:
	virtual distanceType getDistance()const = 0;
	virtual void setDistance(distanceType distance) = 0;
};
}
#endif
