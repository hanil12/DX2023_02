#include "framework.h"
#include "Program.h"

#include "../Scenes/PaintScene.h"
#include "../Scenes/LineScene.h"
#include "../Scenes/LineCollisionScene.h"
#include "../Scenes/CannonScene.h"
#include "../Scenes/MazeScene.h"

HDC Program::_backBuffer = nullptr;

Program::Program()
{
	srand(unsigned int(time(nullptr)));

	_curScene = make_shared<MazeScene>();

	HDC hdc = GetDC(hWnd);

	_backBuffer = CreateCompatibleDC(hdc);
	_hBit = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
	SelectObject(_backBuffer, _hBit);
}

Program::~Program()
{
	DeleteObject(_hBit);
	DeleteObject(_backBuffer);
}

void Program::Update()
{
	if (GetAsyncKeyState(VK_F1) & 0x0001)
	{
		Collider::DebugModeOnOff();
	}

	_curScene->Update();
}

void Program::Render(HDC hdc)
{
	PatBlt(_backBuffer,0,0,WIN_WIDTH,WIN_HEIGHT, BLACKNESS);

	_curScene->Render(_backBuffer);

	BitBlt
	(
	hdc, // 목적지
	0,0,WIN_WIDTH,WIN_HEIGHT, // 복사할 크기
	_backBuffer, 0,0, SRCCOPY // 복사할 정보
	);
}
