#include "Mario.h"

Mario::Mario() :GameObject()
{

}
Mario::Mario(float X, float Y, float VX, float VY) : GameObject(X, Y, VX, VY)
{
	State = STAND;
	LastTime = 0;
	DeltaTime = 0;
	vxLast = 0;
	Left = false;
	Right = true;
	Down = false;
}

void Mario::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	MarioR = new Sprite(d3ddv, "Data\\mario_right.png", 39, 61, 3, 3);
	if (MarioR == NULL)
	{
		MessageBox(NULL, "Failed to load marioR", "Error", MB_OK);
	}
	MarioL = new Sprite(d3ddv, "Data\\mario_left.png", 39, 61, 3, 3);
	if (MarioL == NULL)
	{
		MessageBox(NULL, "Failed to load marioL", "Error", MB_OK);
	}
}

void Mario::Draw(int vpx, int vpy)
{
	if (vx > 0)
		MarioR->Render(x, y, vpx, vpy);
	else if (vx < 0)
		MarioL->Render(x, y, vpx, vpy);
	else if (vxLast < 0)
		MarioL->Render(x, y, vpx, vpy);
	else
		MarioR->Render(x, y, vpx, vpy);
}
void Mario::Jum()
{
	State = JUM;
	if (y <= Mario_Height)
		vy = Mario_VY;
}
void Mario::Go(bool left, bool right, bool down)
{
	Left = left;
	Right = right;
	Down = down;
}
void Mario::Update(DWORD dt)
{
	int keycode;
	DWORD now = GetTickCount();
	DeltaTime = now - LastTime;
	if (!Left && Right)
	{
		vx = Mario_Speed;
		vxLast = vx;
	}
	if (Left && !Right)
	{
		vx = -Mario_Speed;
		vxLast = vx;
	}
	if (Left && Right)
	{
		if (vx > 0)
			MarioR->Reset();
		else
			MarioL->Reset();
		vx = 0;
	}
	if (!Left && !Right)
	{
		vx = 0;
		if (vxLast > 0)
			MarioR->Reset();
		else
			MarioL->Reset();
	}
	if (DeltaTime > 100 / 6)
	{
		if (vy == 0)
		{
			if (vx > 0)
				MarioR->Next();
			else
				MarioL->Next();
		}
		else
		{
			if (vx > 0)
				MarioR->SetIndex(1);
			else
				MarioL->SetIndex(1);
		}
		LastTime = now;
	}	
	x += vx*dt;
	y += vy*dt;
	if (x <= 20)
		x = 20;
	if (y > Mario_Height)
	{
		vy -= 0.1;
	}
	else
	{
		y = Mario_Height;
		vy = 0;
	}
	
}
Mario::~Mario()
{
}
