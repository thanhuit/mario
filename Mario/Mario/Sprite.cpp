#include "Sprite.h"

Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddv, char *Path, int Width, int Height, int Count, int SpritePerRow)
{
	//d3ddev = d3ddv;
	D3DXCreateSprite(d3ddv, &_SpriteHandler);
	D3DXIMAGE_INFO info;
	HRESULT result;

	_Image = NULL;

	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;

	result = D3DXGetImageInfoFromFile(Path, &info);
	if (result != D3D_OK)
	{
		return;
	}

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		Path,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 63, 63),
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		return;
	}
}

void Sprite::Render( int X, int Y, int vpx, int vpy) {
	RECT srect;

	srect.left = (_Index % _SpritePerRow)*(_Width);
	srect.top = (_Index / _SpritePerRow)*(_Height);
	srect.right = srect.left + _Width ;
	srect.bottom = srect.top + _Height;

	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 position((float)X, (float)Y, 0);

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -vpx;
	mt._42 = vpy;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);

	_SpriteHandler->Draw(
		_Image,
		&srect,
		&center,
		&p,
		D3DCOLOR_XRGB(255, 255, 255)	// Hardcode!
		);
	_SpriteHandler->End();
}

void Sprite::Next()
{
	_Index = (_Index + _Count - 1) % _Count;
}
void Sprite::SetIndex(int i)
{
	_Index = i;
}
void Sprite::Reset()
{
	_Index = 0;
}

Sprite::~Sprite()
{
	_Image->Release();
}
