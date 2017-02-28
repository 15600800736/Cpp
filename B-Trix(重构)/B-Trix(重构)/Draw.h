
//Draw.h
#ifndef _DRAW_H_
#define _DRAW_H_
#include <Windows.h>
#include <string>
#include <conio.h>
#include <stdio.h>
#include "Defination.h"
#include "Map.h"
#include "Block.h"
class Draw
{
public:
	Draw(){}
	Draw(Map*);
	~Draw(){}
	virtual void draw(Block*, DrawOrClear) = 0;
	void draw(LPSTR, _re_coord_ COORD);
	virtual void relativeToDraw(Block*,_out_ _re_coord_ COORD[4]) = 0;
protected:
	void DC(DrawOrClear,_re_coord_ COORD[4]);
	HANDLE _hOut;
	Map* _map;
};

class BlockDrawer :public Draw
{
public:
	BlockDrawer(){}
	BlockDrawer(Map* m) :Draw(m){}
	~BlockDrawer(){ CloseHandle(_hOut); }
	void draw(Block*, DrawOrClear);
	void relativeToDraw(Block*, _out_ _re_coord_ COORD[4]);
};
class NextDrawer :public Draw
{
public:
	NextDrawer(){}
	NextDrawer(Map* m) :Draw(m){}
	~NextDrawer(){ CloseHandle(_hOut); }
	void draw(Block*, DrawOrClear);
	void relativeToDraw(Block*, _out_ _re_coord_ COORD[4]);
};
#endif