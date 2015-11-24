#ifndef _SPRITE_H_
#define _SPRITE_H_
#pragma once
#include<d3dx9.h>

class Sprite
{
public:
protected:
			// The “container”
	LPD3DXSPRITE _SpriteHandler;
	LPDIRECT3DTEXTURE9 _Image;
	//LPDIRECT3DDEVICE9 d3ddev;

	int _Index; 		// Current sprite index
	int _Width;   		// Sprite width
	int _Height;		// Sprite height
	int _Count;			// Number of sprites in the container
	int _SpritePerRow;	// Number of sprites per row

public:
	Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddv, char *Path, int Width, int Height, int Count, int SpritePerRow);

	// Advance to next sprite in the list
	void Next();
	void SetIndex(int i);
	void Reset();
	LPDIRECT3DTEXTURE9 getImage()
	{
		return _Image;
	}
	// Render current sprite at location (X,Y) at the target surface
	void Render( int X, int Y, int vpx, int vpy);
	~Sprite();
};
#endif