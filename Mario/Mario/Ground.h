#ifndef _GROUND_H_
#define _GROUND_H_
#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include"Map.h"
class Ground :public GameObject
{
private:
	LPDIRECT3DDEVICE9 d3ddv;
	Sprite *ground_middle;
	Map* map;
	Sprite* nen;
public:
	Ground();
	Ground(float X, float Y, float VX, float VY);
	void Init(LPDIRECT3DDEVICE9 d3ddv);
	void Draw(int vpx, int vpy);
	~Ground();
};
#endif