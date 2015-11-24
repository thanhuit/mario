#pragma once
#include<stdio.h>
#include"Sprite.h"
#include"RecF.h"
#include"TMXParser.h"

class Map{
private:
	Sprite* spriteSheet;
	RecFList collisionRecs;

	int width;
	int height;
	int* mapArr;
public:
	Map();
	Map(LPDIRECT3DDEVICE9 _d3ddv, char* _spriteSheet, char* _fileName);
	~Map();
	void Update();
	void Draw(int vpx, int vpy);

	int Width();
	int Height();
	void SetMap(int _width, int _height, int* _mapArr, RecFList _collisionRecs);
	RecFList CRecList();

};