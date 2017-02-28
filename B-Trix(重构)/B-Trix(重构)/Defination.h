
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

typedef int HEIGHT;//�߶�
typedef int LINE;//����
typedef unsigned int NUMBER;//����
typedef unsigned long SCORE;//����
typedef bool* BLOCK;//����




enum BlockType{ I, L, OP_L, T, N, OP_N, O, UNDICIDED };//��������
enum MoveDirection{ LEFT, RIGHT,DOWN };//�ƶ�����
enum GameState{ RESTART, PAUSE, OVER };//��Ϸ״̬
enum DrawOrClear{ CLEAR, DRAW };
struct Time
{
	int hour;
	int minute;
	int second;
};//ʱ��

#endif