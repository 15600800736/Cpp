

#include "DataPacket.h"
#include "Node.h"
#include "NodeFactory.h"
namespace graphic
{
class DataPacketTest
{
public:
	DataPacketTest(int start, int destination, int* data, int length) :
		_data(data),
		_start(start),
		_destination(destination),
		_dataPacket(DataPacket<int,int>::DATA, data, &_start, &_destination, length)
	{
		
	}
private:
	int* _data;
	int _start;
	int _destination;
	DataPacket<int, int> _dataPacket;

};
}

void main()
{
	int data[] = { 1, 2, 3, 3, 5, 4, 5, 6 };
	graphic::DataPacketTest test(1, 2, data, 8);
}