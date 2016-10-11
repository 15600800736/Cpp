//Use the cross
#include <math.h>
#include <algorithm>
#include <iostream>
#include "AStar.h"

Coord::Coord() :X(0), Y(0)
{
}
Coord::Coord(int x,int y)
{
	X = x;
	Y = y;
}
bool Coord::operator==(Coord otherCoord)
{
	return (this->X == otherCoord.X) && (this->Y == otherCoord.Y) ? true : false;
}
Coord Coord::operator-(Coord& otherCoord)
{
	Coord coord(X - otherCoord.X, Y - otherCoord.Y);
	return coord;
}
Coord Coord::operator+(Coord& otherCoord)
{
	Coord coord(X + otherCoord.X, Y + otherCoord.Y);
	return coord;
}
int Coord::dot(Coord& otherCoord)
{
	return X*otherCoord.X + Y*otherCoord.Y;
}
int Coord::cross(Coord& otherCoord)
{
	return X*otherCoord.Y - Y*otherCoord.X;
}

Block::Block() :_coord(0, 0), _f(0), _g(0), _h(0), _parent(NULL)
{
}
Block::Block(Coord coord) :_coord(coord), _f(0), _g(0), _h(0), _parent(NULL)
{}
Block::Block(Coord coord, int G, int H, Block* parent) : _coord(coord), _f( G + H), _g(G), _h(H), _parent(new Block(*parent))
{
}
Block::Block(const Block& otherBlock)
{
		_coord.Y = otherBlock._coord.Y;
		_coord.X = otherBlock._coord.X;
	
		_f = otherBlock._f;
		_g = otherBlock._g;
		_h = otherBlock._h;
		if (otherBlock._parent == NULL)
		{
			_parent = NULL;
		}
		else
		{
			_parent = new Block( *otherBlock._parent);
		}
}
Block::~Block()
{
	delete _parent;
}
Block& Block::operator=(Block& otherBlock)
{
	if (*this == otherBlock)
	{
		return *this;
	}
	_coord.Y = otherBlock._coord.Y;
	_coord.X = otherBlock._coord.X;

	_f = otherBlock._f;
	_g = otherBlock._g;
	_h = otherBlock._h;
	if (otherBlock._parent == NULL)
	{
		_parent = NULL;
	}
	else
	{
		_parent = new Block(*otherBlock._parent);
	}
	return *this;
}
bool Block::operator<(Block otherBlock)
{
	return this->_f < otherBlock._f ? true : false;
}
bool Block::operator==(Block otherBlock)
{
	return this->_coord == otherBlock._coord ? true : false;
}
bool Block::operator!=(Block otherBlock)
{
	return !(*this == otherBlock);
}

Map::Map(bool* map, int width, int length) : _map(map), _width(width), _length(length)
{}
bool Map::operator[](Coord coord)
{
	return _map[coord.Y*_width + coord.X];
}

AStar::AStar(Coord starter, Coord ender, Map* map) :_map(map)
{
	_starter = (*_map)[starter] == 1 ? NULL : new Block(starter);
	_ender = (*_map)[ender] == 1 ? NULL : new Block(ender);
}

AStar::~AStar()
{
	delete _starter;
	delete _ender;
}

std::vector<Block> AStar::getAroundFGH(Block& block)
{
	vecBlock around;
	Coord aroundCoord[8] = {
		{ block._coord.X - 1, block._coord.Y - 1 },
		{ block._coord.X, block._coord.Y - 1 },
		{ block._coord.X + 1, block._coord.Y - 1 },
		{ block._coord.X - 1, block._coord.Y },
		{ block._coord.X + 1, block._coord.Y },
		{ block._coord.X - 1, block._coord.Y + 1 },
		{ block._coord.X, block._coord.Y + 1 },
		{ block._coord.X + 1, block._coord.Y + 1 }
	};
	for (int i = 0; i < 8; i++)
	{
		if (aroundCoord[i].X > -1 && aroundCoord[i].Y > -1 && aroundCoord[i].X < _map->_width && aroundCoord[i].Y < _map->_length)
		{
			around.push_back(getFGH(aroundCoord[i],block));
		}
	}
	return around;
}
Block AStar::getFGH(Coord coord, Block& parent)
{
	Coord vecStarterToCurrent(coord - _starter->_coord );
	Coord vecStarterToEnder(_ender->_coord - _starter->_coord);

	int G = abs(parent._coord.X - coord.X) + abs(parent._coord.Y - coord.Y);
	int H = abs(_ender->_coord.X - coord.X) + abs(_ender->_coord.Y - coord.Y)  + vecStarterToCurrent.cross(vecStarterToEnder);
	Block block(coord, G, H, &parent);
	return block;
}
std::vector<Coord> AStar::findPath()
{
	if (_starter == NULL || _ender == NULL)
	{
		std::cout << "Please select a visible beginning and destination." << std::endl;
		return vecCoord();
	}
	vecBlock openList;
	vecBlock closeList;
	Block selectBlock = *_starter;
	Block currentBlock;
	Block destination = *_ender;
	openList.push_back(selectBlock);
	do
	{
		currentBlock = selectBlock;
		openList.erase(std::find<vecBlock::iterator>(openList.begin(), openList.end(), currentBlock));
		closeList.push_back(currentBlock);
		vecBlock around = getAroundFGH(currentBlock);
		vecBlock::iterator iter = around.begin();
		while (iter != around.end())
		{
			vecBlock::iterator iterBlock = std::find<vecBlock::iterator>(openList.begin(), openList.end(), *iter);

			if (std::find<vecBlock::iterator>(closeList.begin(), closeList.end(), *iter) != closeList.end() || ((*_map)[iter->_coord]) == 1)
			{
				
			}
			else if (iterBlock != openList.end())
			{
				Block newBlock = getFGH(iter->_coord, currentBlock);
				double tempF = iter->_f;
				if (getFGH(iter->_coord,currentBlock)._f < tempF)
				{
					*iterBlock = newBlock;
				}
			}
			else if (iterBlock == openList.end())
			{
				openList.push_back(*iter);
			}
			iter++;
		}
		vecBlock::iterator tmpIter = std::min_element<vecBlock::iterator>(openList.begin(), openList.end());
		selectBlock = *tmpIter;
	} while (std::find<vecBlock::iterator>(openList.begin(), openList.end(), destination) == openList.end()
		&& !openList.empty());
	vecCoord result;
	result.push_back(_ender->_coord);
	for (Block* block = &closeList.back(); block != NULL; block = block->_parent)
	{
		result.push_back(block->_coord);
	}

	return result;
}
void AStar::outPutWay()
{
	vecCoord way = findPath();
	if (!way.empty())
	{
		for (vecCoord::reverse_iterator iterWay = way.rbegin();
			iterWay != way.rend();
			iterWay++)
		{
			std::cout << iterWay->X << "  " << iterWay->Y << std::endl;
		}
	}
	else
	{
		std::cout << "Can not find the way from beginning to destination." << std::endl;
	}
}