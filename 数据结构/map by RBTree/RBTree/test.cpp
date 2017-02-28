
#include "RBNode.h"
#include "Map.h"

int main()
{
	CMap<int, int> map;
	map.Insert(5, 5);
	map.Insert(4, 4);
	map.Insert(7, 7);
	map.Insert(9, 9);
	map.Insert(10, 10);
	map.Insert(11, 11);
	map.Erase(9);
	//Create the cut to examine
	//map.Erase(5);
	map.GetRoot()->GetRC()->GetLC()->OutPut();
}
