#pragma once
#include<Windows.h>
#include "Game.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	Game g(hInstance);
	g.GameInit();
	g.GameRun();
}

