#include "GameObject.h"


GameObject::GameObject()
{
	Type = 0;
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
}
GameObject::GameObject(float X, float Y, float VX, float VY)
{
	x = X;
	y = Y;
	vx = VX;
	vy = VY;
}
void GameObject::Destroy()
{}

int GameObject::GetType()
{
	return Type;
}
float GameObject::Getx()
{
	return x;
}
float GameObject::Gety()
{
	return y;
}
float GameObject::Getvx()
{
	return vx;
}
float GameObject::Getvy()
{
	return vy;
}

void GameObject::SetType(int type)
{
	Type = type;
}
void GameObject::Setx(float X)
{
	x = X;
}
void GameObject::Sety(float Y)
{
	y = Y;
}
void GameObject::Setvx(float VX)
{
	vx = VX;
}
void GameObject::Setvy(float VY)
{
	vy = VY;
}

GameObject::~GameObject()
{
}
