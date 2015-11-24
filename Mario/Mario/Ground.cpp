#include "Ground.h"

Ground::Ground() :GameObject()
{

}
Ground::Ground(float X, float Y, float VX, float VY) : GameObject(X,Y,VX,VY)
{

}

void Ground::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	//ground_middle = new Sprite(d3ddv, "Data\\ground_middle.png", 32, 32, 1, 1);
	map = new Map(d3ddv, "Data//mappp.bmp", "Data//mappp.tmx");
	/*if (ground_middle == NULL)
	{
		MessageBox(NULL, "Failed to load ground_middle", "Error", MB_OK);
	}*/
}
void Ground::Draw(int vpx, int vpy)
{
	map->Draw(vpx, vpy);
	/*int i=0;
	//{
	//	ground_middle->Render(x, y);
	//	x = x + 31;
	//}
	ground_middle->Render(x, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	i = i + 31;
	i = i + 31;
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	i = i + 31;
	ground_middle->Render(x + i, y, vpx, vpy);
	*/
}

Ground::~Ground()
{
}

