#ifndef _GAME_H_
#define _GAME_H_
#pragma once
#include<Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include <dinput.h>
#include "Utils.h"
#include"Mario.h"
#include"Ground.h"
#include "Brick.h"
#include"Map.h"




class Game
{
protected:
	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3ddev;
	LPDIRECT3DSURFACE9 _back_buffer;
	LPDIRECTINPUT8       _di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 
	BYTE  _keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];
	Mario *mario;
	Ground *ground;
	Brick *brick;
	HINSTANCE _hInstance;
	HWND _hWnd;
	Map* map;
public:
	int vpx, vpy;
	Game(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	void _InitWindow();
	void _InitDirectX();
	void _InitKeyboard();
	void GameInit();
	void _ProcessKeyBoard();
	void _LoadData(LPDIRECT3DDEVICE9 d3ddev);
	void UdateWorld(DWORD dt);
	void UpdateKeyboard();
	void Render();
	bool IsKeyDown(BYTE keyCode);
	void OnKeyUp(BYTE keyCode);
	void OnKeyDown(BYTE keyCode);
	void GameRun();
	void GameEnd();
	~Game();
};
#endif