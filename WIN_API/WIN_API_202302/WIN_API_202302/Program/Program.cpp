#include "framework.h"
#include "Program.h"

#include "../Scenes/PaintScene.h"
#include "../Scenes/LineScene.h"
#include "../Scenes/LineCollisionScene.h"
#include "../Scenes/CannonScene.h"
#include "../Scenes/MazeScene.h"

Program::Program()
{
	_curScene = make_shared<MazeScene>();
}

Program::~Program()
{
}

void Program::Update()
{
	if(GetAsyncKeyState(VK_F1) & 0x0001)
		isDebugMode = true;

	_curScene->Update();
}

void Program::Render(HDC hdc)
{
	_curScene->Render(hdc);
}
