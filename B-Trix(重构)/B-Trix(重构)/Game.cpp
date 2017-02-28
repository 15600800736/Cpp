
//Game.cpp

#include "Game.h"
#include <string>
#include <time.h>
void Game::initiateClient()
{
	_drawer = new NextDrawer(_map);
	//backGround[0] = leftTop
	//backGround[1] = rightTop
	//backGround[2] = leftBottom
	//backGround[3] = rightBottom
	COORD backGround[4] =
	{
		{-2,-1},
		{ 2 * _map->getWidth(),-1 },
		{ -2, _map->getLength() },
		{ 2 * _map->getWidth(), _map->getLength() }
	};
	for (int i = 0; i < 4; i++)
		_drawer->draw("⊙", backGround[i]);
	for (int x = 0; x < 2*_map->getWidth(); x += 2)
	{
		COORD coord = { x, backGround[0].Y };
		_drawer->draw("═", coord);
		coord.Y = backGround[2].Y;
		_drawer->draw("═", coord);
	}
	for (int y = 0; y < _map->getLength(); y++)
	{
		COORD coord = { backGround[0].X, y };
		_drawer->draw("║", coord);
		coord.X = backGround[1].X;
		_drawer->draw("║", coord);
	}
	char* context[3] = { "得分", "等级", "下一个" };
	COORD coord = { backGround[1].X + 6, backGround[1].Y + 3 };
	for (int i = 0; i < 3; i++, coord.Y += 3)
	{
		_drawer->draw(context[i], coord);
	}
}
Game::Game(int length,int width,COORD topleft):_map(new Map(length, width,topleft)),_drawer(NULL)
{
	initiateClient();
}
void Game::outputInformation(Block* next)
{
	char scoreBuffer[4] = { 0 };
	char levelBuffer[4] = { 0 };
	sprintf_s(scoreBuffer, "%d", _score);
	sprintf_s(levelBuffer, "%d", _level);
	_drawer->draw(scoreBuffer, { 2 * _map->getWidth() + 6, 3 });
	_drawer->draw(levelBuffer, { 2 * _map->getWidth() + 6, 6 });
	_drawer->draw(next, DRAW);
}

void Game::blockFall()
{
	while (1)
	{
		_drawer->draw(_block, CLEAR);
		if (!_block->Fall())
		{ _drawer->draw(_block, DRAW); break; }
		_drawer->draw(_block, DRAW);
		int fallSpeed = 0;
		while (fallSpeed < _block->GetFall_Speed())
		{
			if (_kbhit())
			{
				int control = _getch();
				switch (control)
				{
				case KEY_LEFT:
					_drawer->draw(_block, CLEAR);
					_block->Move(LEFT);
					_drawer->draw(_block, DRAW);
					break;
				case KEY_RIGHT:
					_drawer->draw(_block, CLEAR);
					_block->Move(RIGHT);
					_drawer->draw(_block, DRAW);
					break;
				case KEY_DOWN:
					_drawer->draw(_block,CLEAR);
					_block->Move(DOWN);
					_drawer->draw(_block, DRAW);
					break;
				case KEY_UP:
					_drawer->draw(_block, CLEAR);
					_block->Turn();
					_drawer->draw(_block, DRAW);
					break;
				case KEY_ESC:
					exit(0);
					break;
				case KEY_ENTER:
					_drawer->draw("已暂停，按回车键继续", { 6, -2 });
					gameControl(PAUSE);
					_drawer->draw("                                ", { 6, -2 });
					break;
				default:
					break;
				}
			}
			fallSpeed++;
			Sleep(8);
		}
	}
}

void Game::updateMap()
{
	for (int i = 0; i< 4; i++)
	{
		COORD coord =
		{
			_block->GetPosition().X/2 +_block->getRelativePosition(_block->GetCurrentBlock()->block[i]).X,
			_block->GetPosition().Y + _block->getRelativePosition(_block->GetCurrentBlock()->block[i]).Y
		};
		_map->map(coord) = true;
	}
}

void Game::deleteLine()
{
	for (int n = 0; n < 4; n++)
	{
		COORD coord = _block->getRelativePosition(_block->GetCurrentBlock()->block[n]);
		_map->numEmpty(_block->GetPosition().Y + coord.Y)--;
		if (!_map->numEmpty(_block->GetPosition().Y + coord.Y))
		{
			_score++;
			_map->numEmpty(0) = _map->getWidth();
			for (int x = 0; x < _map->getWidth(); x++)
			{
				_map->map({ x, 0 }) = 0;
				for (int y = _block->GetPosition().Y + coord.Y; y > 0; y--)
				{
					_map->map({ x, y }) = _map->map({ x, y - 1 });
					if (_map->map({ x, y }))_drawer->draw("■", { 2 * x, y });
					else _drawer->draw("  ", { 2 * x, y });
				}
			}
			for (int y = _block->GetPosition().Y + coord.Y; y > 0; y--)
			{
				_map->numEmpty(y) = _map->numEmpty(y - 1);
			}
		}
	}
}

SCORE Game::process()
{
	srand((unsigned)time(NULL));
	COORD coord = { _map->getWidth(), 0 };
	BlockType randType = (BlockType)(rand() % 7);
	_block = new Block(randType, coord, _map);
	do
	{
		randType = (BlockType)(rand() % 7);
		Block* next = new Block(randType,coord , _map);
		outputInformation(next);
		delete _drawer;
		_drawer = new BlockDrawer(_map);
		_drawer->draw(_block, DRAW);
		_block->SetFall_Speed(100 - 10 * _level);
		blockFall();
		updateMap();
		deleteLine();
		delete _drawer;
		_drawer = new NextDrawer(_map);
		_drawer->draw(next, CLEAR);
		delete _block;
		_block = next;
	} while (lose());
	_drawer->draw("您输了，是否重新开始游戏？", { -6, 10 });
	return _score;
}

bool Game::lose()
{
	return true;
}

void Game::gameControl(GameState state)
{

}
Game::~Game()
{
	delete _map;
	delete _drawer;
}