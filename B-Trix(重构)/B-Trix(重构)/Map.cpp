
//Map.cpp
#include "Map.h"

Map::Map(const int length, const int width, const COORD topleft)
	:_mapLength(length), _mapWidth(width), _topLeft(topleft),
	 _numEmpty(new int[length])
{
	memset(_map, 0, 12*20);
	for (int i = 0; i < length; i++)
		_numEmpty[i] = width;
}
COORD Map::relativeToAbsolute(COORD re_coord)
{
	return { _topLeft.X + re_coord.X, _topLeft.Y + re_coord.Y };
}
bool Map::IsAvaliable(COORD coord)
{
	return (coord.X < _mapWidth  && coord.X >= 0) && (coord.Y < _mapLength && coord.Y >= 0) && (!map(coord));
}
Map::~Map()
{
	delete[] _map;
	delete[] _numEmpty;
}