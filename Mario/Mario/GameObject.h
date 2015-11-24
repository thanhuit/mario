#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#pragma once
#include "RecF.h"
class GameObject
{
protected:
	int Type;
	float x, y;
	float vx, vy;
public:
	RecF recf;
	GameObject();
	GameObject(float X, float Y, float VX, float VY);
	virtual void Destroy();

	int GetType();
	float Getx();
	float Gety();
	float Getvx();
	float Getvy();

	void SetType(int type);
	void Setx(float X);
	void Sety(float Y);
	void Setvx(float VX);
	void Setvy(float VY);
	~GameObject();
};
#endif