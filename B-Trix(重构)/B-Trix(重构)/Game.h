
//Game.h

#ifndef _GAME_H_
#define _GAME_H_
#include "Draw.h"
class Game
{
public:
	Game(){}
	Game(int, int, COORD);
	SCORE process();
	~Game();
private:
	void blockFall();
	void updateMap();
	void deleteLine();
	void outputInformation(Block* next);
	bool lose();

	void gameControl(GameState);

	Map* _map;
	Draw* _drawer;
	Block* _block;
	void initiateClient();
	SCORE _score;
	int _level;
};
#endif