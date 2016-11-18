


//DataPacket.h

#ifndef DATA_PACKET_H
#define DATA_PACKET_H

#include "constance.h"
#include <utility>
namespace graphic
{
class RouterNode;

template< typename DataType>
class DataPacket
{
public:
	typedef enum { DATA, HELLO, RESPONCE } PacketType;
	DataPacket()
	{ }
	DataPacket(PacketType type, DataType data, RouterNode* start, RouterNode* destination, int length, int timeToLive = 10)
	{
		_type = type;
		_data = data;
		_start = start;
		_destination = destination;
		_length = length;
		_timeToLive = timeToLive;
	}
	void setData(DataType* data,int length)
	{
		_data = data;
		_length = length;
	}
	void fillData(DataType* data, int length)
	{
		_data = new DataType[length];
		for (int i = 0; i < length; i++)
		{
			if (NULL == data)
			{
				return;
			}
			*_data = *data;
			_data++, data++;
			_length++;
		}
	}
	void setStartAddress(RouterNode* start)
	{
		_start = start;
	}
	void setDestination(RouterNode* destination)
	{
		_destination = destination;
	}
	void setLength(int length)
	{
		_length = length;
	}
	void decTimeToLive()
	{
		--_timeToLive;
	}


	std::pair<DataType*,int> getData()const
	{
		return std::pair(_data, _length);
	}
	RouterNode* getStart()const
	{
		return _start;
	}
	RouterNode* getDestination()const
	{
		return _destination;
	}
	PacketType getType()const
	{
		return _type;
	}
	int getTimeToLive()const
	{
		return _timeToLive;
	}
	int getLength()const
	{
		return _length;
	}
private:
	PacketType _type;
	DataType _data;
	RouterNode* _start;
	RouterNode* _destination;
	int _length;
	int _timeToLive;
};
}
#endif
