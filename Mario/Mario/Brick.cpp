#include "Brick.h"
Brick::Brick() : GameObject()
{

}
Brick::Brick(float X, float Y, float VX, float VY) : GameObject(X, Y, VX, VY)
{

}
void Brick::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	brick = new Sprite(d3ddv, "Data\\brick.png", 32, 32, 1, 1);
	if (brick == NULL)
	{
		MessageBox(NULL, "Failed to load Brick", "Error", MB_OK);
	}
}
void Brick::Draw(int vpx, int vpy)
{
	brick->Render(x, y, vpx, vpy);
}
Brick::~Brick()
{
}
