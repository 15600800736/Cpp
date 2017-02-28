
//Defination.h
#ifndef _DEF_H_
#define _DEF_H_

#define NULL 0
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_LEFT    75
#define KEY_RIGHT   77
#define KEY_ENTER 13
#define KEY_ESC 27

#define KEY_W 'w'
#define KEY_S 's'
#define KEY_A 'a'
#define KEY_D 'd'
#define KEY_CW 'W'
#define KEY_CS 'S'
#define KEY_CA 'A'
#define KEY_CD 'D'

#define _re_coord_
#define _ab_coord_
#define _out_

typedef int HEIGHT;//高度
typedef int LINE;//行数
typedef unsigned int NUMBER;//数量
typedef unsigned long SCORE;//分数
typedef bool* BLOCK;//方块




enum BlockType{ I, L, OP_L, T, N, OP_N, O, UNDICIDED };//方块类型
enum MoveDirection{ LEFT, RIGHT,DOWN };//移动方向
enum GameState{ RESTART, PAUSE, OVER };//游戏状态
enum DrawOrClear{ CLEAR, DRAW };
struct Time
{
	int hour;
	int minute;
	int second;
};//时间

#endif