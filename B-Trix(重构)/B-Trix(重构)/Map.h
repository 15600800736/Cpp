
//Map.h
#ifndef _MAP_H_
#define _MAP_H_
#include <Windows.h>
#include "Defination.h"
class Map
{
public:
	Map():_mapLength(0), _mapWidth(0), _topLeft({ 0, 0 }), _numEmpty(NULL){}
	Map(const int, const int, const COORD);
	~Map();
	//this function is used for transfering a relative coordinate to a absolute coordinate
	_ab_coord_ COORD relativeToAbsolute(_re_coord_ COORD);
	bool IsAvaliable(_re_coord_ COORD);
	bool& map(COORD coord){ return *(_map + _mapWidth*coord.Y + coord.X); }
	int& numEmpty(int n)const{ return *(_numEmpty+n); }
	const int getLength()const{ return _mapLength; }
	const int getWidth()const {return _mapWidth; }
	_ab_coord_ COORD getTopLeft()const{ return _topLeft; }
private:
	//the size of the map
	const int _mapLength;
	const int _mapWidth;
	//the topLeft of the map
	const COORD _topLeft;
	bool _map[12*20];
	int* _numEmpty;
};
#endif