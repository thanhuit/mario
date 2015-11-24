#ifndef _PLAYER_H_
#define _PLAYER_H_
#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Utils.h"
class Mario:public GameObject
{
private:
	Sprite *MarioL;
	Sprite *MarioR;
	DWORD LastTime, DeltaTime;
	float vxLast;
	int State;
	bool Left, Right, Down;
public:
	Mario();
	Mario(float X, float Y, float VX, float VY);
	void Init(LPDIRECT3DDEVICE9 d3ddv);
	void Draw(int vpx, int vpy);
	void Jum();
	void Go(bool left, bool right, bool down);
	void Update(DWORD dt);
	~Mario();
};
#endif