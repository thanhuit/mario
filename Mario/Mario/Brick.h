#ifndef _BRICK_H_
#define _BRICK_H_
#pragma once
#include "GameObject.h"
#include "Sprite.h"
class Brick :public GameObject
{
private:
	Sprite *brick;
public:
	Brick();
	Brick(float X, float Y, float VX, float VY);
	void Init(LPDIRECT3DDEVICE9 d3ddv);
	void Draw(int vpx, int vpy);
	~Brick();
};
#endif