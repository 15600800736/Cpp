
//Block.h
#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <Windows.h>
#include "Defination.h"
#include "Map.h"
struct BlockMatrix
{
	int block[4];
	BlockMatrix* turn;
};//方块结构体
class Block
{
public:
	Block() :Num_Turn(0), CurrentBlock(NULL), BlockList(NULL), Type(UNDICIDED), Position({ 0, 0 }), Color(0),Fall_Speed(0),_map(NULL){} //创建空方块
	Block(BlockType, COORD&,Map*);
	virtual ~Block();
	BlockMatrix* InitiateBlock(BlockType);

	bool Move(MoveDirection);
	bool Turn();
	bool Fall();
	bool IsAvaliable();
	//只读接口
	NUMBER GetNum_Turn()const{ return Num_Turn; } 
	BlockMatrix* GetCurrentBlock()const{ return CurrentBlock; }
	BlockType GetType()const{ return Type; }
	COORD GetPosition()const{ return Position; }
	WORD Getcolor()const{ return Color; }
	int GetFall_Speed()const{ return Fall_Speed; }
	void SetFall_Speed(int s){ Fall_Speed = s; }
	_re_coord_ COORD getRelativePosition(int n);
private:
	NUMBER Num_Turn;
	BlockMatrix* CurrentBlock;
	BlockMatrix* BlockList;
	BlockType Type;
	_re_coord_ COORD Position;
	WORD Color;
	int Fall_Speed;
	Map* _map;
	void InitiateMatrix();
};
#endif