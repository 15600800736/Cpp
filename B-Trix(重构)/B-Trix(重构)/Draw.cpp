
//Draw.cpp

#include "Draw.h"

Draw::Draw(Map* m) :_hOut(GetStdHandle(STD_OUTPUT_HANDLE)), _map(m){}
void Draw::draw(LPSTR LP_str, COORD coord)
{
	DWORD num_written;
	BOOL success;
	COORD p_coord;
	p_coord = _map->relativeToAbsolute(coord);
	success = WriteConsoleOutputCharacter(_hOut, LP_str, lstrlen(LP_str), p_coord, &num_written);
}
void Draw::DC(DrawOrClear dc,COORD coord[4])
{
	switch (dc)
	{
	case DRAW:
		for (int i = 0; i < 4; i++)
		{
			draw("¡ö", coord[i]);
		}
		break;
	case CLEAR:
		for (int i = 0; i < 4; i++)
		{
			draw("  ", coord[i]);
		}
		break;
	default:
		break;
	}
}

void BlockDrawer::draw(Block* block, DrawOrClear dc)
{
	COORD coord[4] = { 0 };
	relativeToDraw(block, coord);
	DC(dc, coord);
}
void NextDrawer::draw(Block* block, DrawOrClear dc)
{
	COORD coord[4] = { 0 };
	relativeToDraw(block, coord);
	DC(dc, coord);
}
void BlockDrawer::relativeToDraw(Block* block, COORD coord[4])
{
	for (int i = 0; i < 4; i++)
	{
		coord[i] = { block->GetPosition().X +2* block->getRelativePosition(block->GetCurrentBlock()->block[i]).X,
			block->GetPosition().Y + block->getRelativePosition(block->GetCurrentBlock()->block[i]).Y };
	}
}
void NextDrawer::relativeToDraw(Block* block, COORD coord[4])
{
	for (int i = 0; i < 4; i++)
	{
		coord[i] = { 2*_map->getWidth()+6+ 2*block->getRelativePosition(block->GetCurrentBlock()->block[i]).X,
			9 + block->getRelativePosition(block->GetCurrentBlock()->block[i]).Y };
	}
}