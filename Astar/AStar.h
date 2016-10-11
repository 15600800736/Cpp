
//the Type passed must typedef two type:position for starter and ender
//CurrentBlock should be a iterator instead of a block which can reduce the use of find-function
#include <Windows.h>
#include <vector>


struct Coord
{
	Coord();
	Coord(int x, int y);
	bool operator==(Coord otherCoord);
	Coord operator-(Coord& otherCoord);
	Coord operator+(Coord& otherCoord);
	int dot(Coord& otherCoord);
	int cross(Coord& otherCoord);
	int X;
	int Y;
};
struct Block
{
	Block();
	Block(Coord coord);
	Block(Coord coord, int G, int H,Block* parent);
	Block(const Block& otherBlock);
	Block& operator=(Block& otherBlock);
	~Block();
	bool operator<(Block otherBlock);
	bool operator==(Block otherBlock);
	bool operator!=(Block otherBlock);
	Coord _coord;
	double _f;
	int _g;
	int _h;
	Block* _parent;
};
struct Map
{
	Map(bool* map,int width,int length);
	bool* _map;
	int _width;
	int _length;
	bool operator[](Coord coord);
};
class AStar
{
public:
	typedef std::vector<Block> vecBlock;
	typedef std::vector<Coord> vecCoord;
	AStar(Coord stater, Coord ender, Map* map);
	void outPutWay();

	~AStar();
private:
	std::vector<Block> getAroundFGH(Block& block);
	Block getFGH(Coord coord,Block& parent);
	Coord intToCoord(int index);
	std::vector<Coord> findPath();

private:
	Block* _starter;
	Block* _ender;
	Map* _map;
};
