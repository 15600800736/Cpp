

#include "AStar.h"
#include <iostream>
void main()
{
	bool m[] = {0,0,0,0,0,0,0,
					  0,0,1,1,1,1,0,
					  0,0,0,0,0,1,0,
					  0,0,0,0,0,1,0,
					  0,0,1,1,1,1,0,
					  0,0,0,0,0,0,0};
	Map map(m, 7, 6);
	AStar astar({ 1, 2 }, { 6, 2 }, &map);
	astar.outPutWay();
}