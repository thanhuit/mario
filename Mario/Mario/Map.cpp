#include"Map.h"

Map::Map()
{

}

Map::~Map()
{

}

Map::Map(LPDIRECT3DDEVICE9 _d3ddv, char* _spriteSheet, char* _fileName)
{
	Parser tmx(_fileName);
	tmx.ReadMap(width, height, mapArr, collisionRecs);
	spriteSheet = new Sprite(_d3ddv, _spriteSheet, 32, 32, 100, 10);
}

void Map::Update()
{

}

void Map::Draw(int vpx, int vpy)
{
	int i = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int posx = x*32;
			int posy = (height - y)*32;
			if ((posx < vpx +832) && (posx >= vpx - 32))
			{
					spriteSheet->SetIndex(mapArr[i]);
					spriteSheet->Render(posx, posy, vpx, vpy);
			}
			i++;
		}
	}
}

#pragma region Get_Set
int Map::Width(){
	return width;
}
int Map::Height(){
	return height;
}
void Map::SetMap(int _width, int _height, int* _mapArr, RecFList _collisionRecs)
{
	width = _width;
	height = _height;
	mapArr = _mapArr;
	collisionRecs = _collisionRecs;
}
RecFList Map::CRecList()
{
	return collisionRecs;
}

#pragma endregion