

//SimpleRelation.h

#ifndef SIMPLE_RELATION_H
#define SIMPLE_RELATION_H
#include "AbstractRelation.h"

namespace graphic
{
class SimpleRelation:virtual public AbstractRelation<int>
{
public:
	SimpleRelation() {}
	SimpleRelation(int distance)
	{
		_distance = distance;
	}
	void setDistance(int distance) override
	{
		_distance = distance;
	}
	int getDistance()const override
	{
		return _distance;
	}
private:
	int _distance;
};
}
#endif