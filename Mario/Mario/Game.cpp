#include "Game.h"
float _left = 0;

Game::Game(HINSTANCE hInstance)
{
	_hInstance = hInstance;
	_d3d = NULL;
	_d3ddev = NULL;
	_back_buffer = NULL;
	_di = NULL;
	_Keyboard = NULL;
	mario = NULL;
	brick = NULL;
	ground = NULL;
	vpx = 0;
	vpy = VIEWPORTY;
}
void Game::_InitWindow()
{
	WNDCLASSEX wndClass = { 0 };

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	wndClass.hInstance = _hInstance;
	wndClass.lpfnWndProc = (WNDPROC)Game::WndProc;

	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = "APPGAME";

	if (!RegisterClassEx(&wndClass))
		return;

	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;
	 _hWnd = CreateWindow("APPGAME",
		"Mario3",
		//WS_OVERLAPPEDWINDOW,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		_hInstance,
		NULL);

	 if (!_hWnd)
	 {
		 MessageBox(NULL, "Failed to create Window", "Error", MB_OK);
		 return;
	 }

	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);
}
void Game::_InitDirectX()
{
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!_d3d)	{
		MessageBox(NULL, "Failed to create d3d", "Error", MB_OK);
		return;
	};

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = FULLSCREEN? FALSE:TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;

	_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&_d3ddev);

	if (_d3ddev == NULL) {
		MessageBox(NULL, "Failed to create device", "Error", MB_OK);
		return;
	}

	_d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &_back_buffer);
	if (_back_buffer == NULL) {
		MessageBox(NULL, "Failed to create back_buffer", "Error", MB_OK);
		return;
	}
	return;
}
void Game::_InitKeyboard()
{
	DirectInput8Create
		(
		_hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&_di, NULL
		);
	_di->CreateDevice(GUID_SysKeyboard, &_Keyboard, NULL);
	_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	_Keyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	_Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	_Keyboard->Acquire();
}
void Game::_LoadData(LPDIRECT3DDEVICE9 d3ddev)
{
	mario = new Mario(20,62, 0,0);
	if (mario == NULL)
	{
		MessageBox(NULL, "Failed to create d3d", "Error", MB_OK);
	}
	mario->Init(d3ddev);
	brick = new Brick(400,400,0,0);
	if (brick == NULL)
	{
		MessageBox(NULL, "Failed to create d3d", "Error", MB_OK);
	}
	brick->Init(d3ddev);
	ground = new Ground(0, 16, 0, 0);
	if (ground == NULL)
	{
		MessageBox(NULL, "Failed to create d3d", "Error", MB_OK);
	}
	ground->Init(d3ddev);
}

void Game::GameInit()
{	
	_InitWindow();
	_InitDirectX();
	_InitKeyboard();
	_LoadData(_d3ddev);
}
void Game::_ProcessKeyBoard()
{
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	// Collect all key states first
	_Keyboard->GetDeviceState(sizeof(_keyStates), _keyStates);

	if (IsKeyDown(DIK_ESCAPE))
	{
		PostMessage(_hWnd, WM_QUIT, 0, 0);
	}

	if (IsKeyDown(DIK_DOWN))
		down = true;
	else
		down = false;
	if (IsKeyDown(DIK_LEFT)) 
		left = true;
	else
		left = false;
	if (IsKeyDown(DIK_RIGHT))
		right = true;
	else
		right = false;
	mario->Go(left,right,down);
	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = _Keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}
bool Game::IsKeyDown(BYTE KeyCode)
{
	return (_keyStates[KeyCode] & 0x80) > 0;
}
void Game::OnKeyDown(BYTE KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		mario->Jum();
		break;
	}
}
void Game::OnKeyUp(BYTE KeyCode)
{
}
void Game::UdateWorld(DWORD dt)
{
		mario->Update(dt);
}

void Game::Render()
{
	if (mario->Getx()-400 > 0)
		vpx = mario->Getx() - 400;
	_d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	if (_d3ddev->BeginScene()) 
	{
		ground->Draw(vpx, vpy);
		brick->Draw(vpx,vpy);
		mario->Draw(vpx, vpy);
		_d3ddev->EndScene();
	}

	_d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Game::GameRun()
{
	DWORD dt = 0;	

	DWORD frame_start = GetTickCount();

	DWORD count_per_frame = 100 / FRAME_RATE;

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Do our game stuff here
		DWORD now = GetTickCount();
		dt = now - frame_start;
		if (dt >= count_per_frame)
		{
			frame_start = now;		
			UdateWorld(dt);
			Render();			
		}
		else
		{
			Sleep(count_per_frame - dt);
		}
		_ProcessKeyBoard();
	}

	GameEnd();

	return ;
}

void Game::GameEnd()
{
	if (_d3ddev != NULL) _d3ddev->Release();
	if (_d3d != NULL) _d3d->Release();
}

LRESULT CALLBACK Game::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

Game::~Game()
{
	
}
