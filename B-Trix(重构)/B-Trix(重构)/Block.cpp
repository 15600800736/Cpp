
//Block.cpp

#include "Block.h"

void Block::InitiateMatrix()
{
	for (int i = 0; i < Num_Turn; i++)//n个矩阵
	{
		for (int index = 0; index < 4; index++)
			BlockList[i].block[index] = 0;
		BlockList[i].turn = &BlockList[(i + 1) % Num_Turn];//构成单向循环链表
	}
}//矩阵初始化清零
BlockMatrix* Block::InitiateBlock(BlockType type)
{
	switch (type)
	{
	case I:
		// I
		//初始化
		Type = I;
		Num_Turn = 2;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_RED | FOREGROUND_INTENSITY;
		//第一形态
		BlockList[0].block[0] = 0;
		BlockList[0].block[1] = 1;
		BlockList[0].block[2] = 2;
		BlockList[0].block[3] = 3;
		//第二形态
		BlockList[1].block[0] = 0;
		BlockList[1].block[1] = 4;
		BlockList[1].block[2] = 8;
		BlockList[1].block[3] = 12;
		break;
	case L:
		//L
		//初始化
		Type = L;
		Num_Turn = 4;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		//第一形态
		BlockList[0].block[0] = 2;
		BlockList[0].block[1] = 4;
		BlockList[0].block[2] = 5;
		BlockList[0].block[3] = 6;
		//第二形态
		BlockList[1].block[0] = 0;
		BlockList[1].block[1] = 4;
		BlockList[1].block[2] = 8;
		BlockList[1].block[3] = 9;

		//第三形态
		BlockList[2].block[0] = 0;
		BlockList[2].block[1] = 1;
		BlockList[2].block[2] = 2;
		BlockList[2].block[3] = 4;

		//第四形态
		BlockList[3].block[0] = 0;
		BlockList[3].block[1] = 1;
		BlockList[3].block[2] = 5;
		BlockList[3].block[3] = 9;

		break;
	case OP_L:
		//反L
		//初始化
		Type = OP_L;
		Num_Turn = 4;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		//第一形态
		BlockList[0].block[0] = 0;
		BlockList[0].block[1] = 1;
		BlockList[0].block[2] = 2;
		BlockList[0].block[3] = 6;
		//第二形态
		BlockList[1].block[0] = 1;
		BlockList[1].block[1] = 5;
		BlockList[1].block[2] = 8;
		BlockList[1].block[3] = 9;
		//第三形态
		BlockList[2].block[0] = 0;
		BlockList[2].block[1] = 4;
		BlockList[2].block[2] = 5;
		BlockList[2].block[3] = 6;
		//第四形态
		BlockList[3].block[0] = 0;
		BlockList[3].block[1] = 1;
		BlockList[3].block[2] = 4;
		BlockList[3].block[3] = 8;

		break;
	case T:
		//T
		//初始化
		Type = T;
		Num_Turn = 4;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		//第一形态
		BlockList[0].block[0] = 1;
		BlockList[0].block[1] = 4;
		BlockList[0].block[2] = 5;
		BlockList[0].block[3] = 6;

		//第二形态
		BlockList[1].block[0] = 0;
		BlockList[1].block[1] = 4;
		BlockList[1].block[2] = 5;
		BlockList[1].block[3] = 8;

		//第三形态
		BlockList[2].block[0] = 0;
		BlockList[2].block[1] = 1;
		BlockList[2].block[2] = 2;
		BlockList[2].block[3] = 5;

		//第四形态
		BlockList[3].block[0] = 1;
		BlockList[3].block[1] = 4;
		BlockList[3].block[2] = 5;
		BlockList[3].block[3] = 9;

		break;
	case N:
		//N
		//初始化
		Type = N;
		Num_Turn = 2;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		//第一形态
		BlockList[0].block[0] = 0;
		BlockList[0].block[1] = 4;
		BlockList[0].block[2] = 5;
		BlockList[0].block[3] = 9;
		//第二形态
		BlockList[1].block[0] = 1;
		BlockList[1].block[1] = 2;
		BlockList[1].block[2] = 4;
		BlockList[1].block[3] = 5;

		break;
	case OP_N:
		//反N
		//初始化
		Type = OP_N;
		Num_Turn = 2;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		//第一形态
		BlockList[0].block[0] = 1;
		BlockList[0].block[1] = 4;
		BlockList[0].block[2] = 5;
		BlockList[0].block[3] = 8;
		//第二形态
		BlockList[1].block[0] = 0;
		BlockList[1].block[1] = 1;
		BlockList[1].block[2] = 5;
		BlockList[1].block[3] = 6;

		break;
	case O:
		//方块
		//初始化
		Type = O;
		Num_Turn = 1;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		//第一形态
		BlockList[0].block[0] = 0;
		BlockList[0].block[1] = 1;
		BlockList[0].block[2] = 4;
		BlockList[0].block[3] = 5;

		break;
	case UNDICIDED:
		//空方块，用于擦除
		//初始化
		Type = UNDICIDED;
		Num_Turn = 1;
		BlockList = new BlockMatrix[Num_Turn];
		//第一形态
		BlockList[0].block[0] = 0;
		BlockList[0].block[1] = 0;
		BlockList[0].block[2] = 0;
		BlockList[0].block[3] = 0;
		break;
	}
	return BlockList;
}
Block::Block(BlockType  type, COORD& p, Map* m) :Fall_Speed(0), BlockList(NULL),Position(p), _map(m)//方块构造函数，用于构造方块及其旋转后的方块
{
	CurrentBlock = InitiateBlock(type);//创建方块,并将当前方块初始化为第一形态
}
Block::~Block()
{
	Num_Turn = 0;
	Type = UNDICIDED;
	Position = { 0, 0, };
	delete[] BlockList;
}
bool Block::Move(MoveDirection direction)
{
	COORD tmppos = Position;
	switch (direction)
	{
	case LEFT://向左
		Position.X -=2;
		break;
	case RIGHT://向右
		Position.X+=2;
		break;
	case DOWN:
		while (Fall());
		break;
	default:
		break;
	}
	//若不可行，则不移动
	if (!IsAvaliable())
	{
		Position = tmppos;
		return false;
	}
	return true;
}
bool Block::Turn()
{
	BlockMatrix* tmpblock = CurrentBlock;
	CurrentBlock = CurrentBlock->turn;
	//若不可行，则不旋转
	if (!IsAvaliable())
	{
		CurrentBlock = tmpblock;
		return false;
	}
	return true;
}
bool Block::Fall()
{
	Position.Y++;
	//若不可行，则不下落
	if (!IsAvaliable())
	{
		Position.Y--;
		return false;
	}
	return true;
}//下落
bool Block::IsAvaliable()
{
	COORD coord = { 0, 0 };
	for (int i = 0; i < 4; i++)
	{
		coord = { getRelativePosition(CurrentBlock->block[i]).X + Position.X/2, getRelativePosition(CurrentBlock->block[i]).Y + Position.Y };
		if (!_map->IsAvaliable(coord)) return false;
	}
	return true;
}
COORD Block::getRelativePosition(int n)
{
	return{ n % 4, n / 4 };
}