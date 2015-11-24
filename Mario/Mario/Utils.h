#ifndef _UTILS_H_
#define _UTILS_H_
//Game.h -------------------------------------------------
#define KEYBOARD_BUFFER_SIZE	1024
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define FRAME_RATE 60
#define FULLSCREEN 0
#define VIEWPORTY 600
//--------------------------------------------------------------
//Mario.h---------------------------------------------------
#define Mario_Speed 0.3
#define Mario_VY 1.7f
#define Mario_Height 70
enum MarioState
{
	STAND,
	SIT,
	JUM,
	MOVE
};
//--------------------------------------------------------------
enum Type
{
	_brick
};
#endif