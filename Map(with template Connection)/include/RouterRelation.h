
//RouterRelation.h
#ifndef ROUTER_RELATION_H
#define ROUTER_RELATION_H

#include "AbstractRelation.h"
#include "DataPacket.h"

namespace graphic
{
class RouterRelation :virtual public AbstractRelation <int>
{
public:
	int getDistance()const override
	{
		return _distance;
	}
	void getDistance(int distance)
	{
		_distance = distance;
	}
	void transData(DataPacket<std::string> data)
	{

	}
private:
	int _distance;
};
}
#endif