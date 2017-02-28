
//Block.cpp

#include "Block.h"

void Block::InitiateMatrix()
{
	for (int i = 0; i < Num_Turn; i++)//n������
	{
		for (int index = 0; index < 4; index++)
			BlockList[i].block[index] = 0;
		BlockList[i].turn = &BlockList[(i + 1) % Num_Turn];//���ɵ���ѭ������
	}
}//�����ʼ������
BlockMatrix* Block::InitiateBlock(BlockType type)
{
	switch (type)
	{
	case I:
		// I
		//��ʼ��
		Type = I;
		Num_Turn = 2;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_RED | FOREGROUND_INTENSITY;
		//��һ��̬
		BlockList[0].block[0] = 0;
		BlockList[0].block[1] = 1;
		BlockList[0].block[2] = 2;
		BlockList[0].block[3] = 3;
		//�ڶ���̬
		BlockList[1].block[0] = 0;
		BlockList[1].block[1] = 4;
		BlockList[1].block[2] = 8;
		BlockList[1].block[3] = 12;
		break;
	case L:
		//L
		//��ʼ��
		Type = L;
		Num_Turn = 4;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		//��һ��̬
		BlockList[0].block[0] = 2;
		BlockList[0].block[1] = 4;
		BlockList[0].block[2] = 5;
		BlockList[0].block[3] = 6;
		//�ڶ���̬
		BlockList[1].block[0] = 0;
		BlockList[1].block[1] = 4;
		BlockList[1].block[2] = 8;
		BlockList[1].block[3] = 9;

		//������̬
		BlockList[2].block[0] = 0;
		BlockList[2].block[1] = 1;
		BlockList[2].block[2] = 2;
		BlockList[2].block[3] = 4;

		//������̬
		BlockList[3].block[0] = 0;
		BlockList[3].block[1] = 1;
		BlockList[3].block[2] = 5;
		BlockList[3].block[3] = 9;

		break;
	case OP_L:
		//��L
		//��ʼ��
		Type = OP_L;
		Num_Turn = 4;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		//��һ��̬
		BlockList[0].block[0] = 0;
		BlockList[0].block[1] = 1;
		BlockList[0].block[2] = 2;
		BlockList[0].block[3] = 6;
		//�ڶ���̬
		BlockList[1].block[0] = 1;
		BlockList[1].block[1] = 5;
		BlockList[1].block[2] = 8;
		BlockList[1].block[3] = 9;
		//������̬
		BlockList[2].block[0] = 0;
		BlockList[2].block[1] = 4;
		BlockList[2].block[2] = 5;
		BlockList[2].block[3] = 6;
		//������̬
		BlockList[3].block[0] = 0;
		BlockList[3].block[1] = 1;
		BlockList[3].block[2] = 4;
		BlockList[3].block[3] = 8;

		break;
	case T:
		//T
		//��ʼ��
		Type = T;
		Num_Turn = 4;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		//��һ��̬
		BlockList[0].block[0] = 1;
		BlockList[0].block[1] = 4;
		BlockList[0].block[2] = 5;
		BlockList[0].block[3] = 6;

		//�ڶ���̬
		BlockList[1].block[0] = 0;
		BlockList[1].block[1] = 4;
		BlockList[1].block[2] = 5;
		BlockList[1].block[3] = 8;

		//������̬
		BlockList[2].block[0] = 0;
		BlockList[2].block[1] = 1;
		BlockList[2].block[2] = 2;
		BlockList[2].block[3] = 5;

		//������̬
		BlockList[3].block[0] = 1;
		BlockList[3].block[1] = 4;
		BlockList[3].block[2] = 5;
		BlockList[3].block[3] = 9;

		break;
	case N:
		//N
		//��ʼ��
		Type = N;
		Num_Turn = 2;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		//��һ��̬
		BlockList[0].block[0] = 0;
		BlockList[0].block[1] = 4;
		BlockList[0].block[2] = 5;
		BlockList[0].block[3] = 9;
		//�ڶ���̬
		BlockList[1].block[0] = 1;
		BlockList[1].block[1] = 2;
		BlockList[1].block[2] = 4;
		BlockList[1].block[3] = 5;

		break;
	case OP_N:
		//��N
		//��ʼ��
		Type = OP_N;
		Num_Turn = 2;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		//��һ��̬
		BlockList[0].block[0] = 1;
		BlockList[0].block[1] = 4;
		BlockList[0].block[2] = 5;
		BlockList[0].block[3] = 8;
		//�ڶ���̬
		BlockList[1].block[0] = 0;
		BlockList[1].block[1] = 1;
		BlockList[1].block[2] = 5;
		BlockList[1].block[3] = 6;

		break;
	case O:
		//����
		//��ʼ��
		Type = O;
		Num_Turn = 1;
		BlockList = new BlockMatrix[Num_Turn];
		InitiateMatrix();
		Color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		//��һ��̬
		BlockList[0].block[0] = 0;
		BlockList[0].block[1] = 1;
		BlockList[0].block[2] = 4;
		BlockList[0].block[3] = 5;

		break;
	case UNDICIDED:
		//�շ��飬���ڲ���
		//��ʼ��
		Type = UNDICIDED;
		Num_Turn = 1;
		BlockList = new BlockMatrix[Num_Turn];
		//��һ��̬
		BlockList[0].block[0] = 0;
		BlockList[0].block[1] = 0;
		BlockList[0].block[2] = 0;
		BlockList[0].block[3] = 0;
		break;
	}
	return BlockList;
}
Block::Block(BlockType  type, COORD& p, Map* m) :Fall_Speed(0), BlockList(NULL),Position(p), _map(m)//���鹹�캯�������ڹ��췽�鼰����ת��ķ���
{
	CurrentBlock = InitiateBlock(type);//��������,������ǰ�����ʼ��Ϊ��һ��̬
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
	case LEFT://����
		Position.X -=2;
		break;
	case RIGHT://����
		Position.X+=2;
		break;
	case DOWN:
		while (Fall());
		break;
	default:
		break;
	}
	//�������У����ƶ�
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
	//�������У�����ת
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
	//�������У�������
	if (!IsAvaliable())
	{
		Position.Y--;
		return false;
	}
	return true;
}//����
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